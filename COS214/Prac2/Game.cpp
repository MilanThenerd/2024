#include "Game.h"
#include <limits>
#include <unistd.h>

Game::Game(int playerAmount, int currencyPerTurn) : playerAmount(playerAmount), currencyPerTurn(currencyPerTurn)
{
  for (int i = 1; i <= playerAmount; i++)
  {
    string playerName = "Player " + to_string(i);
    currency[playerName] = 50;
  }
  careTaker = new CareTaker();
  infantryFactory = new InfantryFactory();
  boatmanFactory = new BoatmanFactory();
  shieldBearerFactory = new ShieldBearerFactory();
}

void Game::run()
{
  activePlayer = 1;
  cout << "Turn " << turnNumber << endl;
  while (running)
  {
    usleep(timeout);
    // Save at start of each round
    if (prevTurn < turnNumber)
    {
      save();
      prevTurn++;
    }

    string playerName = "Player " + to_string(activePlayer);
    if (defeatedPlayers.find(playerName) != defeatedPlayers.end())
    {
      cout << playerName << " has been defeated and is skipped." << endl;
      activePlayer++;
      if (activePlayer > playerAmount)
      {
        activePlayer = 1; // Reset to the first player if exceeding the total number of players
        turnNumber++;
      }
      continue; // Skip the rest of the loop for defeated players
    }
    Menu();
    activePlayer++;
    if (activePlayer > playerAmount)
    {
      activePlayer = 1;
      turnNumber++;
      maxTurnNumber = turnNumber;
      for (int i = 1; i <= playerAmount; i++)
      {
        string playerName = "Player " + to_string(i);
        currency[playerName] += currencyPerTurn;
      }
      cout << "Turn " << turnNumber << endl;
    }
    checkWinCondition();
  }
  cout << "Thanks for playing..." << endl;
}

void Game::Menu()
{
  cout << "\x1B[2J\x1B[H"; // clear console
  string playerName = "Player " + to_string(activePlayer);
  while (true)
  {
    cout << "Game Round No: " << turnNumber << endl;
    cout << playerName << ", you have $" << currency[playerName] << endl;
    cout << playerName << ", what do you want to do?\n\tSkip,\n\tAttack,\n\tBuy,\n\tList,\n\tStop,\n\tSave,\n\tUndo,\n\tRedo\nI want to: ";
    string response;
    cin >> response;
    lowerCase(response);
    cout << "\x1B[2J\x1B[H"; // clear console

    if (response == "attack")
    {
      if (playerSoldiers[playerName].size() < 1)
      {
        cout << playerName << " does not own any units, consider buying some first." << endl;
      }
      else
      {
        this->attack();
        break;
      }
    }
    else if (response == "skip")
    {
      break;
    }
    else if (response == "buy")
    {
      this->buy();
      break;
    }
    else if (response == "list")
    {
      this->list();
    }
    else if (response == "save")
    {
      this->save();
      break;
    }
    else if (response == "undo" && turnNumber > 1)
    {
      this->undo();
      break;
    }
    else if (response == "redo" && turnNumber < maxTurnNumber)
    {
      this->redo();
      break;
    }
    else if (response == "stop" || response == "skip")
    {
      running = false;
      break;
    }
    else
    {
      cout << "You did not choose a valid option..." << endl;
    }
  }
}

void Game::attack()
{
  Soldiers *attacker = nullptr;
  Soldiers *defender = nullptr;
  string playerName = "Player " + to_string(activePlayer);
  string response;

  // When checking if a player has units to attack with or to be attacked, and finding none:

  int troopCount = 0;

  for (auto soldier : playerSoldiers[playerName])
  {
    if (soldier->getHealth() > 0)
    {
      troopCount++;
    }
  }
  if (playerSoldiers[playerName].empty())
  {
    defeatedPlayers.insert(playerName);
    cout << playerName << " has been defeated due to having no units." << endl;
    return; // Exit the attack function early
  }

  // Step 1: Select an attacking unit
  while (attacker == nullptr)
  {
    cout << "\x1B[2J\x1B[H";
    cout << playerName << ", which unit do you want to attack with?";
    for (const auto &unit : playerSoldiers[playerName])
    {
      if (unit->getHealth() > 0)
      {
        cout << "\n\t" << unit->getUnitName() << " with " << unit->getHealth() << " HP, ";
      }
    }
    cout << "\nI want to attack with: ";
    cin >> response;
    lowerCase(response);

    // Validate and select attacker
    for (const auto &unit : playerSoldiers[playerName])
    {
      string unitName = unit->getUnitName();
      lowerCase(unitName);
      if (unitName == response)
      {
        attacker = unit;
        break; // Exit loop if attacker is found
      }
    }
  }

  // Step 2: Select a target player
  int chosenPlayer;
  while (true)
  {
    cout << "\x1B[2J\x1B[H";
    cout << "Which player do you want to attack? (Enter their number): ";
    cin >> chosenPlayer;
    if (chosenPlayer >= 1 && chosenPlayer <= playerAmount && chosenPlayer != activePlayer)
    {
      break; // Exit loop if a valid player is chosen
    }
    else
    {
      cout << "You need to choose a valid player..." << endl;
    }
  }

  // Step 3: Select a target unit
  string name = "Player " + to_string(chosenPlayer);

  troopCount = 0;

  for (auto soldier : playerSoldiers[name])
  {
    if (soldier->getHealth() > 0)
    {
      troopCount++;
    }
  }

  if (troopCount == 0)
  {
    defeatedPlayers.insert(name);
    cout << name << " has been defeated due to having no units." << endl;
    return; // Prevent further execution for defeated players
  }

  while (defender == nullptr)
  {
    cout << "\x1B[2J\x1B[H";
    cout << "Enemy's units:\n";
    for (const auto &unit : playerSoldiers[name])
    {
      if (unit->getHealth() > 0)
      {
        cout << unit->getUnitName() << " with " << unit->getHealth() << " HP, \n\t";
      }
    }
    cout << "Which unit do you want to attack?\n";
    cout << "I want to attack: ";
    cin >> response;
    lowerCase(response);

    // Validate and select defender
    for (const auto &unit : playerSoldiers[name])
    {
      string unitName = unit->getUnitName();
      lowerCase(unitName);
      if (unitName == response)
      {
        defender = unit;
        break; // Exit loop if defender is found
      }
    }
  }

  // Step 4: Battle commences
  while (attacker != nullptr && defender != nullptr && attacker->getHealth() > 0 && defender->getHealth() > 0)
  {
    cout << "\x1B[2J\x1B[H";
    cout << "Battle Commences!" << endl;
    attacker->engage(); // Engage the attacker

    // Calculate and deal damage
    int damage = attacker->getDamagePerSoldier() * attacker->getAmountOfSoldiers(); // Assuming these methods exist
    defender->damage(damage);

    int defdamage = defender->getDamagePerSoldier() * defender->getAmountOfSoldiers() * 0.8; // Assuming these methods exist
    attacker->damage(defdamage);

    // Check if defender's health is zero or less
    if (defender->getHealth() <= 0)
    {
      cout << "Defender's unit has been defeated." << endl;
      break; // End battle if defender is defeated
    }

    if (attacker->getHealth() <= 0)
    {
      cout << "Your unit has been defeated." << endl;
      break; // End battle if defender is defeated
    }

    // Ask attacker if they want to continue attacking
    cout << "Enemy " << defender->getUnitName() << " still has " << defender->getHealth() << "HP" << endl;
    cout << "Your " << attacker->getUnitName() << " still has " << attacker->getHealth() << "HP" << endl;

    cout << "Do you want to continue attacking? (yes/no): ";
    cin >> response;
    lowerCase(response);
    if (response == "no")
    {
      attacker->disengage(); // Disengage if the attacker chooses to stop
      break;                 // End battle
    }
    usleep(timeout);
  }

  cout << "\x1B[2J\x1B[H";

  // After the battle, check if the attacker or defender was defeated
  if (attacker->getHealth() > 0 && defender->getHealth() > 0)
  {
    cout << "You have disengaged from the battle." << endl;
  }
  if (defender->getHealth() <= 0)
  {
    cout << "You have defeated the defender's unit." << endl;
    // Remove defender from the game, assuming a method exists to remove defeated units
  }
  if (attacker->getHealth() <= 0)
  {
    cout << "Your unit has been defeated." << endl;
    // Remove attacker from the game, assuming a method exists to remove defeated units
  }

  cout << "Press enter to continue." << endl;
  cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
  cin.get();
}

void Game::checkWinCondition()
{
  if (defeatedPlayers.size() == playerAmount - 1)
  {
    // Only one player remains undefeated
    for (int i = 1; i <= playerAmount; ++i)
    {
      std::string playerName = "Player " + std::to_string(i);
      if (defeatedPlayers.find(playerName) == defeatedPlayers.end())
      {
        cout << playerName << " is the winner!" << endl;
        running = false; // End the game
        break;           // Exit the loop
      }
    }
  }
}

void Game::buy()
{
  string playerName = "Player " + to_string(activePlayer);
  while (true)
  {
    cout << "\x1B[2J\x1B[H";
    cout << playerName << ", what do you want to buy?\n\tInfantry $" << infantryPrice << ",\n\tShieldBearer $" << shieldBearerPrice << ",\n\tBoatman $" << boatmanPrice << "\nor return (back):\nI want to buy: ";
    string response;
    cin >> response;
    lowerCase(response);

    if (response == "infantry")
    {
      if (currency[playerName] >= infantryPrice)
      {
        currency[playerName] -= infantryPrice;
        Soldiers *soldier = infantryFactory->createUnit();
        soldier->setPlayerID(playerName);
        playerSoldiers[playerName].push_back(soldier);

        cout << "You bought an infantry unit." << endl;
        break;
      }
      else
      {
        cout << "You do not have enough money for this unit..." << endl;
      }
    }
    else if (response == "shieldbearer")
    {
      if (currency[playerName] >= shieldBearerPrice)
      {
        currency[playerName] -= shieldBearerPrice;
        Soldiers *soldier = shieldBearerFactory->createUnit();
        soldier->setPlayerID(playerName);
        playerSoldiers[playerName].push_back(soldier);
        cout << "You bought a shieldbearer unit." << endl;
        break;
      }
      else
      {
        cout << "You do not have enough money for this unit..." << endl;
      }
    }
    else if (response == "boatman")
    {
      if (currency[playerName] >= boatmanPrice)
      {
        currency[playerName] -= boatmanPrice;
        Soldiers *soldier = boatmanFactory->createUnit();
        soldier->setPlayerID(playerName);
        playerSoldiers[playerName].push_back(soldier);
        cout << "You bought a boatman unit." << endl;
        break;
      }
      else
      {
        cout << "You do not have enough money for this unit..." << endl;
        cout << "Press enter to continue." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        cin.get();
      }
    }
    else if (response == "back")
    {
      Menu();
      break;
    }
    else
    {
      cout << "You did not choose a valid option..." << endl;
    }
  }
  cout << "Press enter to continue." << endl;
  cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
  cin.get();
}

void Game::list()
{
  string playerName = "Player " + to_string(activePlayer);
  int size = playerSoldiers[playerName].size();
  if (size < 1)
  {
    cout << playerName << " does not own any units, consider buying some first." << endl;
  }
  else
  {
    cout << playerName << " owns the following units: " << endl;
    for (int i = 0; i < size; i++)
    {
      cout << playerSoldiers[playerName].at(i)->getUnitName() << ", " << playerSoldiers[playerName].at(i)->getHealth() << "HP" << endl;
    }
  }
}

void Game::save()
{
  careTaker->addGameState(playerSoldiers, currency, turnNumber);
}

void Game::load(int turn)
{
  careTaker->applyGameState(playerSoldiers, currency, turn);
}

void Game::undo()
{
  if (turnNumber > 1)
  {
    load(--turnNumber);
    activePlayer = 0;
    cout << "Turn " << turnNumber << endl;
  }
}

void Game::redo()
{
  if (turnNumber < maxTurnNumber)
  {
    load(++turnNumber);
    activePlayer = 0;
    cout << "Turn " << turnNumber << endl;
    if (turnNumber == maxTurnNumber)
    {
      for (int i = 1; i <= playerAmount; i++)
      {
        string playerName = "Player " + to_string(i);
      }
    }
  }
}

void Game::clear()
{
  for (int i = 1; i <= playerAmount; i++)
  {
    string playerName = "Player " + to_string(i);
    if (playerSoldiers.find(playerName) != playerSoldiers.end())
    {
      for (Soldiers *soldier : playerSoldiers[playerName])
      {
        delete soldier;
      }
      playerSoldiers[playerName].clear();
    }
  }
  delete boatmanFactory;
  delete infantryFactory;
  delete shieldBearerFactory;
  delete careTaker;
}

void Game::lowerCase(string &word)
{
  for (auto &x : word)
  {
    x = tolower(x);
  }
}

Game::~Game()
{
  clear();
}
