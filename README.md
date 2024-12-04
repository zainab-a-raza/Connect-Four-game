# ConnectFour Game
Connect 4 is a classic two-player strategy game where players take turns dropping tokens into a vertical grid. The objective is to form a horizontal, vertical, or diagonal line of four tokens before the opponent does. The game's simplicity and strategic depth make it an ideal project for applying programming concepts. This project implements a simple console-based, two-player game of Connect 4 where players interact through a text-based interface for their turns. 

## Game Logic

### Grid Size:
- The grid size is dynamically allocated based on user input.  
- The grid's dimensions (rows and columns) will be specified by the player when starting the game, allowing the game to adapt to any size grid. Available grid options are 4x4, 5x5, or 6x6.

### Rules and Winning Conditions:
- The rules remain similar to the Connect Four game: players take turns to drop their discs in one of the columns.  
- A player wins if they achieve a horizontal, vertical, or diagonal line of four consecutive discs (this part does not change based on grid size).  
The grid will have dynamic dimensions, but the winning condition (four in a row) stays the same.

### How Moves are Processed:

#### Grid Initialization:
- The program will allocate memory dynamically for the grid based on user input for the number of rows and columns.  
- Available grid sizes are 4x4, 5x5, and 6x6.

#### Turn Logic:
- Players take turns to input a column number (from 1 to the number of columns).
- After the player inputs the column, the program checks for the first available (empty) spot in that column, starting from the bottom row and moving upwards.

#### Win Check:
- After each move, the program will check for the win condition (4 consecutive discs in a row, column, or diagonal) in the dynamically allocated grid.
- The win checking process remains the same: horizontal, vertical, and diagonal checks, but the grid size is flexible now.

#### End of Game:
- The game ends when a player wins by aligning 4 consecutive discs in a row, column, or diagonal, or when the grid is full.
