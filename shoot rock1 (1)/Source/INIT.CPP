#include <math.h>
#include "raylib.h"
#include "define.h"
#include "game.h"
#include "global.h"

void Level::InitGame(void)
{
    game.activeEnemies   = 10;
    game.activeDiamonds  = 0;
    game.shootRate       = 0;
    game.gameOver        = false;
    game.enemiesKill     = 0;
    game.score           = 0;
    game.paused          = false;
    game.startScreen     = true;
    game.enemiesKill     = 0;
    game.chargeTime      = 1;
    game.highScore       = 0;
    game.comboBonus      = 0;
    game.collectedFromSameEnemy = 0;
    game.pointsTimer     = 0;

    player.rect.x       = screenWidth / 2.0f;
    player.rect.y       = screenHeight - (float)30;
    player.rect.width   = PLAYER_WIDTH;
    player.rect.height  = PLAYER_HEIGHT;
    player.speed.x      = PLAYER_SPEED;
    player.speed.y      = PLAYER_SPEED;
    player.chargeTime   = 0;
    player.canShoot     = true;
    player.shotsLeft    = 0;
    player.chargingactive = false;
    player.color        = BLACK;

    // Initialize enemies
    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {
        enemy[i].rect.width     = ENEMY_WIDTH;
        enemy[i].rect.height    = ENEMY_HEIGHT;
        enemy[i].rect.x         = (float)GetRandomValue(0, screenWidth);
        enemy[i].rect.y         = (float)GetRandomValue(-screenHeight, -20);
        enemy[i].speed.x        = ENEMY_SPEED;
        enemy[i].speed.y        = ENEMY_SPEED;
        enemy[i].active         = true;
        enemy[i].color          = BLUE;
        enemy[i].direction      = GetRandomValue(0, 2); //1,2 for diagonal, 0 for vertical
    }

    // Initialize shoots
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        shoot[i].rect.x         = player.rect.x;
        shoot[i].rect.y         = player.rect.y + player.rect.height / 4;
        shoot[i].rect.width     = SHOOT_WIDTH;
        shoot[i].rect.height    = SHOOT_HEIGHT;
        shoot[i].speed.x        = 0;
        shoot[i].speed.y        = SHOOT_SPEED;
        shoot[i].active         = false;
        shoot[i].color          = GREEN;
    }

    for (int i = 0; i < NUM_DIAMONDS; i++)
    {
        diamond[i].rect.width   = DIAMOND_WIDTH;
        diamond[i].rect.height  = DIAMOND_HEIGHT;
        diamond[i].rect.x       = (float)GetRandomValue(0, screenWidth);
        diamond[i].rect.y       = (float)GetRandomValue(-screenHeight, -20);
        diamond[i].speed.x      = DIAMOND_SPEED;
        diamond[i].speed.y      = DIAMOND_SPEED;
        diamond[i].active       = false;
        diamond[i].color        = GOLD;
    }

    ui.background   = LoadTexture("./Source/bg.png");
    ui.spaceship    = LoadTexture("./Source/spaceship.png");
    ui.fireball     = LoadTexture("./Source/fireball.png");
    ui.shooting     = LoadTexture("./Source/shoot.png");
    ui.charging     = LoadTexture("./Source/charging.png");
    ui.explosion1   = LoadTexture("./Source/explosion.png");
    ui.explosion    = LoadSound("./Source/explosion.wav");

    boom.active     = false;
    boom.start_time = (float)GetTime();
    boom.duration   = 2.0f;
}