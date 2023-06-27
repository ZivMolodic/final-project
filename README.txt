=====================================================================

OOP Project

			            RAFT WARS
                  ======================

by: hadarka     zivmo
ID: 316093160   206998668

=====================================================================

Description:
=============

Raft Wars is an exciting and addictive game that challenges players to defend their treasure against invading enemies. The game features a unique combination of strategic planning, aiming skills, and physics-based gameplay.
the game is an engaging turn-based game where players control a team of characters battling against each other. Each turn, the control alternates between the computer and the player. Within the player's turn, he can control different character each time in their team to either build additional parts for their raft or fire a selected projectile. The game incorporates a "life" for each character, which decreases upon receiving hits.

Gameplay:
=========

In Raft Wars, players assume the role of two brothers who stumble upon a hidden treasure on a deserted beach. As they try to claim their treasure, they encounter a series of enemies who are also after the riches. The players must use their skills to defeat the enemies and protect their treasure.

The game incorporates various gameplay mechanics and features:

1. Aim and shoot: Players control the angle and power of their shots to hit enemies and eliminate them from the screen. Precise aiming and strategic shot selection are crucial for success.

2. Environmental interactions: Players can strategically position themselves. They can take cover behind obstacles or make use of the terrain for tactical advantage.

3. Physics-based mechanics: The game implements custom physics calculations to simulate realistic projectile trajectories and object interactions. This adds an extra layer of challenge and requires players to consider gravity and other physical forces.

4. Enemy AI: Enemies in Raft Wars exhibit intelligent behavior, such as forging raft structure, aim shots, and attempting to outmaneuver the players. This adds strategic depth and keeps the gameplay engaging.

Features:
==========

- Engaging gameplay: Experience a mix of strategy, aiming, and physics-based gameplay.
- Interactive environment: Utilize objects in the environment to your advantage.
- Physics simulation: Realistic projectile trajectories and object interactions.
- Intelligent enemy AI: Enemies exhibit intelligent behavior for added challenge.

Included Files:
================
1. *Animation.h* and *Animation.cpp*:
   - Description: Provides classes and functions for handling sprite animations.
   - Usage: Manages the animation frames and timings for various game elements.

2. *AnimationData.h*:
   - Description: Contains the necessary data structures for storing animation data.
   - Usage: Used in conjunction with the Animation class to define animations for game objects.

3. *Board.h* and *Board.cpp*:
   - Description: Defines the game board and its functionalities.
   - Usage: Manages the game board, including the positioning of game objects and collision detection.

4. *Button.h* and *Button.cpp*:
   - Description: Implements interactive buttons for user input.
   - Usage: Allows players to interact with the game through button clicks.

5. *Collisions.h*:
   - Description: Provides collision detection functions.
   - Usage: Helps identify and handle collisions between game objects.

7. *Direction.h*:
   - Description: Enumerates different directions for game object movement.
   - Usage: Used for specifying movement directions in the game.

8. *Explosion.h*:
   - Description: Implements explosion effects for the game.
   - Usage: Displays explosion animations upon specific game events.

9. *GameObject.h* and *GameObject.cpp*:
   - Description: Defines the base game object class.
   - Usage: Serves as the foundation for all game objects, providing common functionalities and properties.

10. *GamePlay.h* and *GamePlay.cpp*:
    - Description: Implements the main game logic and flow.
    - Usage: Manages the game loop, player turns, and interactions between game objects.

11. *Macros.h*:
    - Description: Contains useful macros and constants for the game.
    - Usage: Defines constant values and macros for easy access and modification.

12. *MainMenu.h* and *MainMenu.cpp*:
    - Description: Implements the main menu of the game.
    - Usage: Displays the main menu options and handles user input.

13. *Objectile.h* and *Objectile.cpp*:
    - Description: Defines projectiles fired by game characters.
    - Usage: Manages the behavior and properties of projectiles, including their movement and collision detection.

14. *PhysicsBehavior.h* and *PhysicsBehavior.cpp*:
    - Description: Provides physics-related functionalities for game objects.
    - Usage: Handles gravity, movement, and collision physics for game objects.

15. *Player.h* and *Player.cpp*:
    - Description: Defines the player class and its functionalities.
    - Usage: Manages the player's team of characters, including health and turn control.

16. *RaftBlock.h* and *RaftBlock.cpp*:
    - Description: Implements raft blocks used for building the player's raft.
    - Usage: Handles the construction and positioning of raft blocks.

17. *RaftMan.h* and *RaftMan.cpp*:
    - Description: Defines the RaftMan character class.
    - Usage: Manages the behavior and properties of

 RaftMan characters.

18. *Resources.h* and *Resources.cpp*:
    - Description: Provides resource management for the game.
    - Usage: Handles loading and accessing game resources such as images, sounds, and fonts.

19. *Weapon.h* and *Weapon.cpp*:
    - Description: Defines weapons used by game characters.
    - Usage: Manages the behavior and properties of weapons, including their firing mechanics and damage calculation.

20. *main.cpp*:
    - Description: The entry point of the game.
    - Usage: Initializes the game and starts the main game loop.

*Note:* The README provides an overview of the game and describes the purpose and usage of each included file. For more detailed information about specific classes and functions, refer to the corresponding header and source files.


1. The program starts in the *main.cpp* file. This file contains the `main` function, which initializes and runs the game, providing the main program flow.

2. than *MainMenu runs its loop which offers options such as starting the game, accessing help, or exiting the game.

3. When the user starts the game, the  The GamePlay initializes Board which will be initializng both user and computer.

4. gameloop handles entire gameplay process, board will split the turns allowing players to build additional parts for their raft or shoot projectiles.

5. both Player and Computer activates RaftMan who will shoot or build standing on their raft base.


Technical Details:
==================

Raft Wars is developed using object-oriented programming principles. The game's core mechanics, including physics simulations and enemy AI, are implemented from scratch by the development team. The SFML library is utilized for graphics rendering and input handling.

The game features a combination of 2D graphics, animations, and sound effects to enhance the player's immersion. It utilizes event-driven programming to handle user input and update the game state accordingly.


Algorithm worth mention
=======================
Collision detection: the programm uses AABB algorithm to detect collisions and modifies it to compute the response vector if needed
Ballistis shot: the AI uses ballistic shot formula to compute the velocity to hit the user
Movement: AI uses mini movment algorithm that navigates it to the selected raft and stops if reaches an edge

Known Issues:
==============

=====================================================================
