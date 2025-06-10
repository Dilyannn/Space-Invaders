# Project Architecture

## Overview

Space-Invaders is a C++ implementation of the classic arcade game built using the **raylib** library. The game logic is organized into a set of classes defined under `header/` and implemented under `source/`.

This document describes the overall structure of the project, the key classes, and the purpose of important functions.

## File Layout

- `main.cpp` – entry point that initializes raylib, loads fonts and textures, creates a `Game` instance and runs the main loop.
- `header/` – header files declaring the game classes:
  - `Game.hpp`
  - `GameObject.hpp`
  - `Player.hpp`
  - `Enemy.hpp`
  - `Bullet.hpp`
  - `Barrier.hpp`
- `source/` – implementation of the classes and assets (images and fonts).
- `algorithms/levels/` – text notes describing the design of each level.
- `CMakeLists.txt` – build configuration using CMake and FetchContent to include raylib.

## Class Overview

### Game
Represents the overall game state and orchestrates the other objects.

Key responsibilities:
- Manage player, enemies, bullets, and barriers.
- Handle input, update game objects, render them, and check for collisions.
- Control game progression and levels.

Important methods:
- `input()` – reads keyboard input to move the player or fire bullets.
- `update()` – moves enemies, updates bullets, spawns enemy bullets, and triggers level changes.
- `render()` – draws all active objects on screen and displays messages.
- `checkCollisions()` – detects bullet–enemy, bullet–barrier, and enemy bullet–player collisions.
- `initializeGame()`/`reset()` – sets up or resets all game objects for a new session.
- `enemyShoot()` – periodically chooses a random bottom enemy to fire a bullet at the player.

### GameObject
Base class providing X/Y coordinates, accessors, and basic rendering hooks.

### Player
Derived from `GameObject`. Tracks lives, score, and the list of bullets fired by the player.

Main methods:
- `moveLeft()` / `moveRight()` – move the player horizontally within the screen bounds.
- `shoot()` – spawn a new `Bullet` object when the space bar is pressed, respecting a fire rate delay.
- `draw()` – render the player's ship texture.
- `reset()` – reposition the player and clear bullets after losing a life.

### Enemy
Represents an individual alien. Holds a texture corresponding to its type.

Methods:
- `update()` – currently moves the enemy to the right; overall enemy movement is coordinated by `Game::moveEnemies()`.
- `render()` – draw the enemy texture.
- `getRect()` – axis-aligned rectangle used for collision detection.
- `unloadImages()` – release loaded textures when finished.

### Bullet
Represents a projectile fired by the player or enemies.

Key attributes:
- `Vector2 direction` – holds the current position of the bullet.
- `int speed` – vertical speed (positive for downward, negative for upward).
- `bool active` – indicates if the bullet is still on screen.

Important methods:
- `update()` – update position and deactivate when leaving the screen.
- `render()` – draw a player bullet.
- `renderEnemy()` – draw an enemy bullet in a random color.
- `getRect()` – rectangle for collisions.

### Barrier and Block
Barriers are made up of small `Block` objects arranged according to a grid. Each block can be destroyed individually when hit by a bullet.

## Game Loop
`main.cpp` sets up the window, fonts, and textures. It then repeatedly:
1. Calls `game.input()` and `game.update()`.
2. Starts drawing (`BeginDrawing`), clears the screen, draws UI elements and game objects via `game.render()`.
3. Ends drawing (`EndDrawing`).

The game ends when the player loses all lives or clears the enemies after the third level. Pressing **Enter** resets the game.

## Building
Build the project using CMake (version 3.30 or later):
```bash
cmake -S . -B build
cmake --build build
```
The executable will be named `Space-Invaders` and links against raylib, which is fetched automatically.
