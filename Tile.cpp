//
// Created by Jack Foltz on 7/21/17.
//

#include "Tile.h"

Tile::Tile(int variant, glm::vec2 pos, glm::vec2 size) {
    this->variant = variant;
    this->size = size;
    this->pos = pos;

    tex = variant == 1 ? Texture("textures/tile_solid.png") : Texture("textures/tile.png");
}

void Tile::draw(SpriteRenderer &rnd) {
    std::vector<glm::vec3> colors {
        glm::vec3(0.25f, 0.52f, 1.0f),
        glm::vec3(0.66f, 0.13f, 0.13f),
        glm::vec3(0.81f, 0.77f, 0.16f),
        glm::vec3(0.16f, 0.76f, 0.81f)
    };

    if (variant == 1)
        rnd.DrawSprite(tex, pos, size, 0.0f, glm::vec3(1.0f));
    else
        rnd.DrawSprite(tex, pos, size, 0.0f, glm::vec3(colors[variant % colors.size()]));
}
