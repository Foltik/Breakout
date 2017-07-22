//
// Created by Jack Foltz on 7/21/17.
//

#include "Level.h"

void Level::loadFromFile(std::string fileName) {
    std::ifstream file(fileName);

    // Read rows/cols
    file >> m_rows;
    file >> m_cols;

    // Resize the vector
    tiles.resize(static_cast<unsigned long>(m_rows));
    for (auto& v : tiles)
        v.resize(static_cast<unsigned long>(m_cols));

    float tileWidth = 1280.0f / m_cols;
    float tileHeight = (720.0f / 2) / m_rows;

    // Load the level data
    int num;
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            file >> num;

            tiles[i][j] = Tile(num, glm::vec2(tileWidth * j, tileHeight * i), glm::vec2(tileWidth, tileHeight));

            if (num > 1)
                tileCount++;
        }
    }
}

void Level::draw(SpriteRenderer& rnd) {
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            if (tiles[i][j].getVariant() != 0) {
                tiles[i][j].draw(rnd);
            }
        }
    }
}

void Level::breakTile(int row, int col) {
    tiles[row][col].setVariant(0);
    tileCount--;
}
