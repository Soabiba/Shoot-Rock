#include <math.h>
#include "raylib.h"
#include "define.h"
#include "game.h"
#include "global.h"

void Level::UnloadGame(void)
{
    UnloadTexture(ui.background);
    UnloadTexture(ui.shooting);
    UnloadTexture(ui.charging);
    UnloadTexture(ui.explosion1);
    UnloadTexture(ui.fireball);
    UnloadTexture(ui.spaceship);
    UnloadSound(ui.explosion);
}