# Elementorum 
Elementorum is a 2D action plataformer where you control our character Derexito! a little koala that has to fight against hard enemies while completing the level jumping against walls!


## Team:
- Pol de la Torre Solé https://github.com/polf780.

  Colliders, phisics, level 2, entities, pathfinding, UI

- Marc Palma Turón https://github.com/marcpt98.

  Loading things from XML, level 1,animations, keybinds, entities, pathfinding, UI


## Controls 

- A: Move left.

- D: Move right.

- F: Shoot.

- SPACE BAR: Jump.


## Special controls
- F1: Charge level 1 from the begining

- F2: Charge level 2 from the begining

- F3: Charge current level from the begining

- F5: Save your current position

- F6: Load your past position

- F8: Show all UI debug

- F9: Show all colliders and pathfinding

- F10: God mode (player without collisions and can fly)

- F11: Cap frames (siwtch fps cap between 30-60)


## Inovation

-Enemy states and patrol

-Game pause

-Jump particles

-Coldown on projectiles

-Particle effects

-Checkpoints


## Main core subsytems
This game has 3 main core subsystems:

- Entity core: in charge of the management of all the objects in the game (player, enemies with pathfinding, coins and checkpoints). This core controls the addition, elimination, save and load of all entities. All the management can be controlled throught the EntityManager module. Every entity has his own movement, states and physics but they share variables that are located in the Entity module.

- UI core: in charge of the management of all HUD in the game (windows, menus, buttons, sliders, images and texts). This core, like the entity core, can control the addition, elimination of his elements. All the management can be controlled throught the Gui and SceneUI modules. Every UI also have some common variables and are located in the UI_element module.

- Scene core: in charge of the management of the maps and keybinds of the game. All the management can be controlled throught the Scene module. In this module you can control the load and unload of the maps and music. Also, in this module you have all the keybinds functionality.

## Trailer


## Links
# Repository
https://github.com/marcpt98/Plataformer-2D

# Download the game!
https://github.com/marcpt98/Plataformer-2D/releases

## License
//MIT License

Copyright (c) [2019] [Pol de la Torre Solé and Marc Palma Turón]

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.//
