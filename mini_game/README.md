# Mini Game Project (C++)

A console-based mini game collection featuring Tic Tac Toe and Snake Game.

## Games

### Tic Tac Toe
- Two-player 3x3 board.
- Players take turns placing X and O.
- Board is displayed after each valid move.
- Detects horizontal, vertical, and diagonal wins.
- Detects a draw and offers replay.

### Snake Game
- Grid-based board displayed after every move.
- Enter W, A, S, or D followed by Enter to move one cell.
- Eat the food (*) to grow.
- Detects wall and self-collisions.
- Offers replay after game over.

## Concepts used
- Loops and conditional statements
- Two-dimensional arrays
- Vectors and structures
- Functions and modular programming
- Random number generation
- Input validation

## Compile and run

Windows (MinGW):
~~~bash
g++ -std=c++11 -Wall -Wextra -pedantic MiniGame.cpp -o MiniGame.exe
MiniGame.exe
~~~

Linux / macOS:
~~~bash
g++ -std=c++11 -Wall -Wextra -pedantic MiniGame.cpp -o MiniGame
./MiniGame
~~~

Visual Studio: Create a C++ Console App, add MiniGame.cpp, then build and run.

## Menu
~~~text
1. Tic Tac Toe
2. Snake Game
3. Exit
~~~

Snake is turn-based in the console: enter one direction and press Enter for each move.

## Project structure
~~~text
Intership/
└── mini_game/
    ├── MiniGame.cpp
    └── README.md
~~~
