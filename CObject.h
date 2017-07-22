//
// Created by Jack Foltz on 7/21/17.
//

#pragma once

#include <k5/k5.h>

class CObject {
public:
    virtual void draw(SpriteRenderer& rnd) {
        rnd.DrawSprite(tex, pos, size, 0.0f, glm::vec3(1.0f));
    };

    glm::vec2 getPos() { return pos; }
    void setPos(glm::vec2 pos) { this->pos = pos; }

    glm::vec2 getSize() { return size; }
    void setSize(glm::vec2 size) { this->size = size; }

protected:
    glm::vec2 pos;
    glm::vec2 size;

    Texture tex;
};


