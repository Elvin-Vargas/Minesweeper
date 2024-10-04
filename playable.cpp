#include "Board.h"
#include "Tile.h"
#include <iostream>

// To determine if someone has won, we have to check if the player has cleared all tiles containing NO MINES
    // To calculate this, we can use safeTiles = (width * height) - mineCount; in order to find out how many tiles have to clear
    // If we keep count of how many safe tiles have been revealed, we can keep testing if the amount of revealedTiles == safeTiles;
    // If revealedTiles == safeTiles, we set won == true and the loop ends.

// To determine if someone has lost, we only have to check if the player selected a tile that contains a mine.
    // From there, we set lost == true and the loop ends.
    // We reveal the final board, and end the program.

// In order to display revealed tiles, each tile could have their own boolean variables whether they have been revealed or not.
    // When the tile is selected, it can use the revealed variable to determine whether to display "#" (covered), or a value (revealed).
    // Letting the Tile object do this work makes it so that Board doesn't need to be changed.

int main() {
    // Initialize the size variables
    int width, height, mineCount;
    int r_row, r_col;

    // Prompt the user to enter the board's size
    std::cout << "Enter Rows, Cols, and Mines: ";
    std::cin >> width >> height >> mineCount;
    std::cout << std::endl;

    // Construct the board and all of its functions
    Board board(width, height, mineCount);
    board.plant_mines();
    board.initial_board();

    int safeTiles = (width * height) - mineCount;
    int tileCounter{0};

    bool endLoop = false;
    // While the game isn't over
    while (!endLoop) {
        // We will first update the counts so that all counts are present within the board.
        board.update_counts();
        // Prompt the user to select a tile
        std::cout << "Enter a row and column to dig: ";
        std::cin >> r_row >> r_col;
        std::cout << std::endl;

        // Call the revealed_mines function passing in the selected tile
        // If revealed_mines returns true, the loop ends and the game is over.
        if (board.revealed_mines(r_row, r_col)) {
            std::cout << std::endl;
            std::cout << "YOU'VE LOST!!!!!!!" << std::endl;
            std::cout << "Final Board:" << std::endl;
            board.final_board(); // Revealing the final board
            endLoop = true; // Ending the loop
        }
        
        tileCounter++;

        if (tileCounter == safeTiles) {
            std::cout << std::endl;
            std::cout << "YOU'VE WON!!!" << std::endl << std::endl;
            std::cout << "Final Board:" << std::endl;
            board.final_board(); // Revealing the final board
            endLoop = true; // Ending the loop
        }
    }
}