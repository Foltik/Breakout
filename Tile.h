//
// Created by Jack Foltz on 7/21/17.
//

#pragma once

#include "CObject.h"

class Tile : public CObject {
public:
    Tile() = default;
    Tile(int variant, glm::vec2 size, glm::vec2 pos);

    void draw(SpriteRenderer& rnd);

    int getVariant() { return variant; }
    void setVariant(int variant) { this->variant = variant; }

private:
    int variant;
};


