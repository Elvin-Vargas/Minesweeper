#ifndef TILE_H
#define TILE_H

class Tile {
    private:
        // Mine value
        int m_value;
        bool m_revealed;

    public:
        Tile();
        // Accessor/Getter
        int get_value() const;
        // Mutator/Setter
        void set_value(int);
        // Setting the revealed Tile
        void set_revealed();
        bool is_revealed() const;
};

#endif