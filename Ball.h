//
// Created by Jack Foltz on 7/21/17.
//

#pragma once

#include <k5/texture.h>
#include <k5/spriterenderer.h>
#include "CObject.h"

class Ball : public CObject {
public:

    Ball(glm::vec2 position, float radius, glm::vec2 velocity, bool isStuck);

    void move();

    glm::vec2 getVelocity() { return vel; }
    void setVelocity(glm::vec2 velocity) { vel = velocity; }

    float getRadius() { return rad; }
    void setRadius(float radius) { rad = radius; }

    bool isStuck() { return stuck; }
    void unstuck() { stuck = false; }

private:
    glm::vec2 vel;

    float rad;
    bool stuck;
};


