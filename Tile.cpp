#include "Tile.h"
#include <iostream>

Tile::Tile() {
    // Value to represent mine
    m_value = 0;
    m_revealed = false; // Initializing our revealed state as false
}

void Tile::set_value(int value) {
    m_value = value;
}

int Tile::get_value() const {
    return m_value;
}

void Tile::set_revealed() {
    m_revealed = true;
}

bool Tile::is_revealed() const {
    return m_revealed;
}