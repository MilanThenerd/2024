# COS 214 PA2

## Game loop:
- Player receives currency at start of turn
- Player chooses attack/rest(skip) round
    - Rest heals units?
- If attacking:
    - Choose player to attack
    - List opponent's unit names
    - Choose unit to attack


## TODO:

Add name next to it when busy, mark with x when done/working.

- [X] Game Class: Player rotations/turns
- [X] Game Class: Currency
- [X] Game Class: Buying troops
- [X] Game Class: Battles
- [X] CareTaker Class: Retrieve game state
- [X] Soldiers Subclasses: Make sure no 2 units can have same name (memento needs unique name)
- [X] Soldiers Subclasses: Implement take damage / calculate total damage
    - Instead of dying, might be worth it to make the amount of troops per unit 0 and then "hide" it from all the menus, as we will need it to exist when we restore previous turns
- [X] UML: Check Memento
- [X] UML: Check CareTaker
- [X] UML: Check Factory Method
- [X] UML: Check Prototype
- [X] UML: Check Template Method
- [X] UML: Create Object diagram at certain point
- [ ] FitchFork: Check coverage / write testing code
