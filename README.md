# Checkers Game

This repository contains a Checkers game implemented in C++ as part of a data structures project. The game features various components including a title page, login page, highscores, and utilizes several data structures such as AVL trees, queues, stacks, linked lists, quick sort, and binary search.

## Features:

- **Title Page:** The game starts with a title page, setting the tone and theme for the gameplay experience.

- **Main Menu:** After the title page, players are presented with a main menu where they can choose from the following options:
  - **Play:** Opens the login page to enter player names and start the game.
  - **Scores:** Displays highscores using an AVL tree, showcasing player names and their scores.
  - **Quit:** Exits the game.

- **Login Page:** Upon selecting "Play" from the main menu, users are prompted to log in by entering their names. The game begins once the players have entered their names.

- **Gameplay:** The Checkers game follows standard Checkers rules:
  - Players take turns moving their pieces diagonally across the board.
  - When a piece reaches the opposite end of the board, it becomes a queen.
  - The player whose turn it is has their name highlighted.
  - Scores are calculated based on the number of moves, with fewer moves resulting in a higher score.

- **Game Over Page:** Upon completion of a game, a game over page displays the winner and relevant information, such as final scores and game duration. The game over screen includes buttons to:
  - Quit the game.
  - Go back to the main menu.
  - View the highscores.

- **Highscores:** Highscores are stored and managed using an AVL tree. The highscores screen displays the top scores along with the names of the players who achieved them.

## Usage:

To run the Checkers game:

1. Clone the repository to your local machine.
   
2. Ensure you have a C++ compiler installed that supports the necessary features.
   
3. Compile the source code with appropriate compiler flags and settings.
   
4. Run the compiled executable to start the game.

## Contributions:

Contributions to this project are welcome. Feel free to fork this repository, make changes, and submit pull requests with your improvements.

## Authors:

- [Syeda Fizza](https://github.com/SFizzaR) 
- [Falah Zainab](https://github.com/FalahZainab)
- [Ziya Ali](https://github.com/ziyyaa1)

## Acknowledgments:

Special thanks to the creators and contributors of the data structures used in this project, as well as the SFML library for providing tools for graphics and user interaction in C++.
