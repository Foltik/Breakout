//
// Created by Jack Foltz on 7/21/17.
//

#pragma once

#include <k5/texture.h>
#include <k5/spriterenderer.h>
#include "CObject.h"

class Paddle : public CObject {
public:
    Paddle();

    void moveRight();
    void moveLeft();

private:
    float paddleSpeed = 7.0f;
};


