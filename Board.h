#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"

class Board {
    private:
        // We will now be able to dynamically change the grid size
        int m_height;
        int m_width;
        int m_mines;
        Tile* grid;

    public:
        // We instead now call the constructor with the grid size as parameters now
        Board(int width, int height, int mineCount);
        ~Board();
        void plant_mines();
        bool revealed_mines(int, int) const; // Print out the board with the mines that have been revealed.
        bool check_revealed(int, int) const;
        void initial_board() const; // Print out the unrevealed board.
        void final_board() const; // Print out the revealed board.
        void update_counts();
};

#endif