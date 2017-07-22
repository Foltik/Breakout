//
// Created by Jack Foltz on 7/21/17.
//

#include "Ball.h"

Ball::Ball(glm::vec2 position, float radius, glm::vec2 velocity, bool isStuck) {
    rad = radius;
    vel = velocity;
    stuck = isStuck;

    tex = Texture("textures/ball.png");

    pos = position;
    size = glm::vec2(rad * 2);
}

void Ball::move() {
    if (!stuck) {
        pos += vel;

        if (pos.x <= 0.0f) {
            vel.x = -vel.x;
            pos.x = 0.0f;
        }

        if (pos.x + 2 * rad >= 1280.0f) {
            vel.x = -vel.x;
            pos.x = 1280.0f - 2 * rad;
        }

        if (pos.y <= 0.0f) {
            vel.y = -vel.y;
            pos.y = 0.0f;
        }
    }
}