//
// Created by Jack Foltz on 7/21/17.
//

#include "Paddle.h"

void Paddle::moveRight() {
    if (pos.x < 1280.0f - size.x) {
        pos.x += paddleSpeed;
    }
}

void Paddle::moveLeft() {
    if (pos.x > 0) {
        pos.x -= paddleSpeed;
    }
}

Paddle::Paddle() {
    tex = Texture("textures/paddle.png");

    size.x = tex.width / 4.0f;
    size.y = tex.height / 4.0f;

    pos.x = (1280.0f / 2) - size.x;
    pos.y = 720.0f - size.y;
}
