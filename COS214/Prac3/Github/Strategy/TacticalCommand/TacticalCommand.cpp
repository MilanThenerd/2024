#include "TacticalCommand.h"
#include "../BattleStrategy/Attack.h"

TacticalCommand::TacticalCommand(Map *map, int playerNo)
{
    this->map = map;
    this->player = playerNo;
    this->strategy = nullptr;
    this->archives = WarArchives();
}

void TacticalCommand::setStrategy(BattleStrategy *s)
{
    // if (strategy != nullptr)
    //     delete strategy;

    strategy = s;
}

void TacticalCommand::executeStrategy()
{
    strategy->engage();
    TacticalMemento *memento = new TacticalMemento();
    memento->storeStrategy(strategy);
    archives.addTacticalMemento(memento, player);
}

BattleStrategy *TacticalCommand::chooseBestStrategy()
{
    BattleStrategy *best = nullptr;
    double bestScore = 0.0;

    std::vector<Coords> myUnits = map->getFriendlyLegions(player);

    int totalStrats = 0;
    std::map<std::string, int> counter;
    // std::cout << "\nOur previous strategies:\n";
    for (auto strat : archives.getAll(player))
    {
        if (strat->strategy->getName() == "Move")
            continue;

        // std::cout << "\tStrat: " << strat->strategy->getName() << std::endl;
        if (counter.count(strat->strategy->getName()) == 0)
        {
            counter[strat->strategy->getName()] = 1;
        }
        else
        {
            counter[strat->strategy->getName()]++;
        }
        totalStrats++;
    }

    for (auto &unit : myUnits)
    {
        /* Move Strategy */
        Move *moveStrat = new Move(map, unit, player);

        double score = moveStrat->getScore(unit);

        if (score > bestScore)
        {
            bestScore = score;

            if (best != nullptr)
                delete best;

            best = moveStrat;
        }
        else
        {
            delete moveStrat;
        }

        // std::cout << std::endl;
        // std::cout << "Best move strat: " << score << std::endl;

        /* Fortify Strategy */
        Fortification *fortStrat = new Fortification(map, unit, player);

        score = fortStrat->getScore(unit);

        double effective = 1.0;
        if (counter.count(fortStrat->getName()) != 0)
        {
            effective = 1.0 - static_cast<double>(counter[moveStrat->getName()]) / totalStrats;
            if (effective < 0.5)
                effective = 0.5;
        }

        if (score * effective > bestScore)
        {
            bestScore = score * effective;

            if (best != nullptr)
                delete best;

            best = fortStrat;
        }
        else
        {
            delete fortStrat;
        }

        // std::cout << std::endl;
        // std::cout << "Best fortify strat: " << score << "\t";
        // std::cout << "Effective strat: " << effective * score << std::endl;

        /* Attack Strategy */
        Attack *attackStrat = new Attack(map, unit, player);

        score = attackStrat->getScore(unit);

        effective = 1.0;
        if (counter.count(attackStrat->getName()) != 0)
        {
            effective = 1.0 - static_cast<double>(counter[moveStrat->getName()]) / totalStrats;
            if (effective < 0.5)
                effective = 0.5;
        }

        if (score * effective > bestScore)
        {
            bestScore = score * effective;

            if (best != nullptr)
                delete best;

            best = attackStrat;
        }
        else
        {
            delete attackStrat;
        }

        // std::cout << std::endl;
        // std::cout << "Best attack strat: " << score << "\t";
        // std::cout << "Effective strat: " << effective * score << std::endl;

        /* Ambush Strategy */
        Ambush *ambStrat = new Ambush(map, unit, player);

        score = ambStrat->getScore(unit);

        effective = 1.0;
        if (counter.count(ambStrat->getName()) != 0)
        {
            effective = 1.0 - static_cast<double>(counter[moveStrat->getName()]) / totalStrats;
            if (effective < 0.5)
                effective = 0.5;
        }

        if (score * effective > bestScore)
        {
            bestScore = score * effective;

            if (best != nullptr)
                delete best;

            best = ambStrat;
        }
        else
        {
            delete ambStrat;
        }

        // std::cout << std::endl;
        // std::cout << "Best ambush strat: " << score << "\t";
        // std::cout << "Effective strat: " << effective * score << std::endl;

        /* Flank Strategy */
        Flanking *flankStrat = new Flanking(map, unit, player);

        score = flankStrat->getScore(unit);

        effective = 1.0;
        if (counter.count(flankStrat->getName()) != 0)
        {
            effective = 1.0 - static_cast<double>(counter[moveStrat->getName()]) / totalStrats;
            if (effective < 0.5)
                effective = 0.5;
        }

        if (score * effective > bestScore)
        {
            bestScore = score * effective;

            if (best != nullptr)
                delete best;

            best = flankStrat;
        }
        else
        {
            delete flankStrat;
        }

        // std::cout << std::endl;
        // std::cout << "Best flanking strat: " << score << "\t";
        // std::cout << "Effective strat: " << effective * score << std::endl;
        // std::cout << std::endl;
    }

    return best;
}