//
// Created by Jack Foltz on 7/21/17.
//

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <k5/texture.h>
#include <k5/spriterenderer.h>
#include "Tile.h"

class Level {
public:
    Level() = default;

    void loadFromFile(std::string fileName);

    void breakTile(int row, int col);

    bool isCleared() { return tileCount == 0; }

    std::vector<std::vector<Tile>> getTiles() { return tiles; }

    void draw(SpriteRenderer& rnd);

private:
    std::vector<std::vector<Tile>> tiles;

    Texture tile = Texture("textures/tile.png");
    Texture tileSolid = Texture("textures/tile_solid.png");

    int m_rows, m_cols;
    int tileCount;
};


