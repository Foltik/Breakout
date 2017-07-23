#pragma once
#include <k5/k5.h>
#include "Level.h"
#include "Paddle.h"
#include "Ball.h"

class Breakout : public IFrame {
public:
    void Init(CEngine* e) override;
    void Cleanup() override;

    void Pause() override;
    void Resume() override;

    void ProcessInput(bool *keyboard, bool *mouse, double mxpos, double mypos) override;
    void Loop() override;
    void Render() override;

    static Breakout& Instance() {
        static Breakout instance;
        return instance;
    }

protected:
    Breakout() = default;
    Breakout(const Breakout&) = delete;
    Breakout(Breakout&&) = delete;
    void operator=(const Breakout&) = delete;
    void operator=(Breakout&&) = delete;

private:
    glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);

    SpriteRenderer rnd = SpriteRenderer(proj);

    Level level;
    Paddle player;
    Ball ball = Ball(glm::vec2(player.getPos().x + player.getSize().x / 2 - 12.5f / 2, 720.0f - player.getSize().y - 25.0f), 12.5f, glm::vec2(5.0f, -5.0f), true);
};