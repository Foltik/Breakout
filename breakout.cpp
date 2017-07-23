#include "breakout.h"

enum Direction {
    LEFT,
    DOWN,
    UP,
    RIGHT
};

struct Collision {
    bool didCollide;
    Direction direction;
    glm::vec2 distance;
};

bool checkCollision(CObject& a, CObject& b) {
    bool collidingX = a.getPos().x + a.getSize().x >= b.getPos().x + b.getSize().x;
    bool collidingY = a.getPos().y + a.getSize().y >= b.getPos().y + b.getSize().y;

    return collidingX && collidingY;
}

glm::vec2 rotate(const glm::vec2& vec, const float deg) {
    float cos = glm::cos(glm::radians(deg));
    float sin = glm::sin(glm::radians(deg));
    return glm::vec2(vec.x * cos + vec.y * sin, vec.x * sin - vec.y * cos);
}

Direction vectorDirection(glm::vec2 vec) {
    std::vector<glm::vec2> directions {
        glm::vec2(-1.0f, 0.0f), // Left
        glm::vec2(0.0f, -1.0f), // Down
        glm::vec2(0.0f, 1.0f),  // Up
        glm::vec2(1.0f, 0.0f)   // Right
    };

    auto it = std::max_element(directions.begin(), directions.end(), [vec](glm::vec2 a, glm::vec2 b) {
        return glm::dot(glm::normalize(vec), a) > glm::dot(glm::normalize(vec), b);
    });

    return (Direction)std::distance(directions.begin(), it);
}

Collision checkCollision(Ball& a, CObject& b) {
    glm::vec2 aCenter = glm::vec2(a.getPos().x + a.getRadius(), a.getPos().y + a.getRadius());
    glm::vec2 bCenter = glm::vec2(b.getPos().x + b.getSize().x / 2, b.getPos().y + b.getSize().y / 2);
    glm::vec2 halfB = glm::vec2(b.getSize().x / 2, b.getSize().y / 2);

    glm::vec2 difference = aCenter - bCenter;

    float ballX, ballY;
    float rectX, rectY;

    glm::vec2 clamped = glm::clamp(difference, -halfB, halfB);

    glm::vec2 closestPoint = bCenter + clamped;

    difference = closestPoint - aCenter;

    if (glm::length(difference) < a.getRadius()) {
        return Collision {
            true,
            vectorDirection(difference),
            difference
        };
    } else {
        return Collision {
            false,
            UP,
            glm::vec2(0.0f, 0.0f)
        };
    }

}

    
void Breakout::Init(CEngine *e) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    level.loadFromFile("resources/level1.txt");
}
void Breakout::Cleanup() {}

void Breakout::Pause() {}
void Breakout::Resume() {}

void Breakout::ProcessInput(bool *keyboard, bool *mouse, double mxpos, double mypos) {
    if (keyboard[GLFW_KEY_RIGHT]) {
        player.moveRight();
        if (ball.isStuck())
            ball.setPos(glm::vec2(player.getPos().x + player.getSize().x / 2 - ball.getSize().x / 2, 720.0f - player.getSize().y - ball.getSize().y));
    }

    if (keyboard[GLFW_KEY_LEFT]) {
        player.moveLeft();
        if (ball.isStuck())
            ball.setPos(glm::vec2(player.getPos().x + player.getSize().x / 2 - ball.getSize().x / 2, 720.0f - player.getSize().y - ball.getSize().y));
    }

    if (keyboard[GLFW_KEY_SPACE]) {
        if (ball.isStuck())
            ball.unstuck();
    }

    if (keyboard[GLFW_KEY_ESCAPE])
        engine->Quit();
}

void Breakout::Loop() {
    ball.move();

    // Check collision with tiles
    auto tiles = level.getTiles();
    for (int i = 0; i < tiles.size(); i++) {
        for (int j = 0; j < tiles[i].size(); j++) {
            if (tiles[i][j].getVariant() > 0) {
                Collision c = checkCollision(ball, tiles[i][j]);
                if (c.didCollide) {
                    if (tiles[i][j].getVariant() > 1)
                        level.breakTile(i, j);

                    glm::vec2 vel = ball.getVelocity();
                    glm::vec2 pos = ball.getPos();
                    if (c.direction == RIGHT || c.direction == LEFT) {
                        ball.setVelocity(glm::vec2(-vel.x, vel.y));
                        float innerDistance = ball.getRadius() - std::abs(c.distance.x);
                        if (c.direction == LEFT)
                            ball.setPos(glm::vec2(pos.x - innerDistance, pos.y));
                        else
                            ball.setPos(glm::vec2(pos.x + innerDistance, pos.y));
                    } else {
                        float innerDistance = ball.getRadius() - std::abs(c.distance.y);
                        ball.setVelocity(glm::vec2(vel.x, -vel.y));
                        if (c.direction == UP)
                            ball.setPos(glm::vec2(pos.x, pos.y + innerDistance));
                        else
                            ball.setPos(glm::vec2(pos.x, pos.y - innerDistance));
                    }
                }
            }
        }
    }

    Collision c = checkCollision(ball, player);
    if (c.didCollide) {
        glm::vec2 vel = ball.getVelocity();
        glm::vec2 pos = ball.getPos();
        if (c.direction == RIGHT || c.direction == LEFT) {
            ball.setVelocity(glm::vec2(-vel.x, vel.y));
            float innerDistance = ball.getRadius() - std::abs(c.distance.x);
            if (c.direction == LEFT)
                ball.setPos(glm::vec2(pos.x + innerDistance, pos.y));
            else
                ball.setPos(glm::vec2(pos.x - innerDistance, pos.y));
        } else {
            float offset = ball.getPos().x + ball.getRadius() - player.getPos().x - player.getSize().x / 2;
            ball.setVelocity(rotate(vel, offset));
            float innerDistance = ball.getRadius() - std::abs(c.distance.y);
            if (c.direction == UP)
                ball.setPos(glm::vec2(pos.x, pos.y + innerDistance));
            else
                ball.setPos(glm::vec2(pos.x, pos.y - innerDistance));
        }
    }
}

void Breakout::Render() {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    level.draw(rnd);
    player.draw(rnd);
    ball.draw(rnd);

    glfwSwapBuffers(CEngine::Instance().wnd);
}