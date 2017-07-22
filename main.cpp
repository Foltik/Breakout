#include <k5/k5.h>

#include "breakout.h"

int main() {
    CEngine& game = CEngine::Instance();

    game.CreateWindow("Breakout", 1600, 900, false);
    game.ChangeFrame(&Breakout::Instance());

    while (game.Running())
        game.Tick();
    game.Cleanup();

    return 0;
}