#include "Board.h"
#include "Tile.h"
#include <cstdlib>
#include <ctime>
#include <array>
#include <iostream>

Board::Board(int width, int height, int mineCount) {
    // Setting size variables
    m_width = width;
    m_height = height;
    m_mines = mineCount;
    // Calculating the area
    int area = m_width * m_height;
    // Setting the grid's size
    grid = new Tile[area];
}

Board::~Board() {
    // Delete the dynamically allocated grid
    delete[] grid;
}

// Places the mines in random spots around the board
void Board::plant_mines() {
    // This function will be used to randomly plant each of the 10 mines on the board

    // Setting up the random number generator.
    std::srand(time(NULL));
    int area = m_width * m_height;

    // Randomly placing the mines across the board
    for (int i{0}; i < m_mines; i++) {
        int random_placement = rand() % area;
        grid[random_placement].set_value(-1);
    }
}

// Reveals selected tiles by the user
bool Board::revealed_mines(int selRow, int selCol) const {
    int selIndex = m_width * selRow + selCol;
    if (grid[selIndex].get_value() == -1) {
        return true;
    }
    // This function primarily just reveals the mines that have been revealed
    // Same concept as last time but now we are using our Accessor/Getter
    std::cout << "    ";
    for (int i{0}; i < m_height; i++) {
        std::cout << i << "   ";
    }
    std::cout << std::endl;

    std::cout << "  ";
    for (int i{0}; i < m_height; i++) {
        std::cout << "|---";
    }
    std::cout << "|" << '\n';

    for (int row{0}; row < m_height; row++) {
        std::cout << row << " ";
        // Loop through each column in the row
        for (int col{0}; col < m_width; col++) {
            int index = m_width * row + col;
            // Checking if the current tile is a mine/revealed
            if (row == selRow && col == selCol) {
                if (grid[index].get_value() == -1) {
                    return true;
                }
                if (!grid[index].is_revealed()) {
                    grid[index].set_revealed();
                    // If it's the selected tile, reveal it
                    if (grid[index].get_value() != -1) {
                        std::cout << "| " << grid[index].get_value() << " ";
                    }
                }
                
            }
            else if (grid[index].is_revealed()) { // Check if the tile is already revealed
                // If tile is revealed, display its value or mine symbol
                if (grid[index].get_value() != -1) {
                    std::cout << "| " << grid[index].get_value() << " ";
                }
                else {
                    return true;
                }
            }
            else {
                // If tile is not revealed, display covered tile
                std::cout << "| # ";
            }
        }
        std::cout << "|" << '\n';

        std::cout << "  ";
        for (int j{0}; j < m_height; j++) {
            std::cout << "|---";
        }
        std::cout << "|" << '\n';
    }
    return false;
}

bool Board::check_revealed(int selRow, int selCol) const {
    int selIndex = m_width * selRow + selCol;
    if (!grid[selIndex].is_revealed()) {
        std::cout << "False" << std::endl;
        return false;
    }
    std::cout << "True" << std::endl;
    return true;
}

// Reveals the board when all mines are covered
void Board::initial_board() const {
    // This function primarily just reveals the mines that have been revealed
    // Same concept as last time but now we are using our Accessor/Getter
    std::cout << "    ";
    for (int i{0}; i < m_height; i++) {
        std::cout << i << "   ";
    }
    std::cout << std::endl;

    std::cout << "  ";
    for (int i{0}; i < m_height; i++) {
        std::cout << "|---";
    }
    std::cout << "|" << '\n';

    for (int row{0}; row < m_height; row++) {
        std::cout << row << " ";
        for (int col{0}; col < m_width; col++) {
            int index = m_width * row + col;
            // Checking if the current tile is a mine
            if (grid[index].get_value() != -1) {
                std::cout << "| " << '#' << " ";
            }
            else {
                std::cout << "| " << "#" << " ";
            }
        }
        std::cout << "|" << '\n';

        std::cout << "  ";
        for (int j{0}; j < m_height; j++) {
            std::cout << "|---";
        }
        std::cout << "|" << '\n';
    }
}

// Reveals the board when the game is won or lost
void Board::final_board() const {
    // This function primarily just reveals the mines that have been revealed
    // Same concept as last time but now we are using our Accessor/Getter
    std::cout << "    ";
    for (int i{0}; i < m_height; i++) {
        std::cout << i << "   ";
    }
    std::cout << std::endl;

    std::cout << "  ";
    for (int i{0}; i < m_height; i++) {
        std::cout << "|---";
    }
    std::cout << "|" << '\n';

    for (int row{0}; row < m_height; row++) {
        std::cout << row << " ";
        for (int col{0}; col < m_width; col++) {
            int index = m_width * row + col;
            // Checking if the current tile is a mine
            if (grid[index].get_value() != -1) {
                std::cout << "| " << grid[index].get_value() << " ";
            }
            else {
                std::cout << "| M ";
            }
        }
        std::cout << "|" << '\n';

        std::cout << "  ";
        for (int j{0}; j < m_height; j++) {
            std::cout << "|---";
        }
        std::cout << "|" << '\n';
    }
}

void Board::update_counts() {
    // For each row in each column, if the tile is a mine, then increment the surrounding cells by +1
    for (int row{0}; row < m_height; row++) {
        for (int col{0}; col < m_width; col++) {
            int index = m_width * row + col;
            // Checking if the current tile is a mine
            if (grid[index].get_value() != -1) {
                int count{0};
                for (int i{-1}; i <= 1; i++) {
                    for (int j{-1}; j <= 1; j++) {
                        int dx = row + i;
                        int dy = col + j;
                        if (dx >= 0 && dx < m_height && dy >= 0 && dy < m_width) {
                            int index2 = m_width * dx + dy;
                            if (grid[index2].get_value() == -1) {
                                count++;
                            }
                        }
                    }
                }
                grid[index].set_value(count);
            }
        }
    }
}