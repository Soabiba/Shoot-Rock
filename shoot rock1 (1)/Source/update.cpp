#include <math.h>
#include "raylib.h"
#include "define.h"
#include "game.h"
#include "global.h"

void Level::UpdateGame(void)
{
    if (!game.gameOver)
    {
        // Player movement
        if (IsKeyDown(KEY_RIGHT))
        {
            player.rect.x += player.speed.x;
        }
        if (IsKeyDown(KEY_LEFT))
        {
            player.rect.x -= player.speed.x;
        }

        // Player collision with enemy
        for (int i = 0; i < game.activeEnemies; i++)
        {
            if (CheckCollisionRecs(player.rect, enemy[i].rect))
            {
                game.gameOver = true;
            }
        }
        // Enemy behaviour
        for (int i = 0; i < game.activeEnemies; i++)
        {
            if (enemy[i].active)
            {
                enemy[i].rect.y += enemy[i].speed.y;

                if (enemy[i].rect.y > screenHeight)
                {
                    enemy[i].rect.x = (float)GetRandomValue(0, screenWidth);
                    enemy[i].rect.y = (float)GetRandomValue(-screenHeight, -20);
                }
            }
        }

        // Diamond behaviour

        for (int i = 0; i < game.activeDiamonds; i++)
        {
            if (diamond[i].active)
            {
                diamond[i].rect.y += diamond[i].speed.y;
            }
        }

        // Wall behaviour
        if (player.rect.x <= 0)
        {
            player.rect.x = 0;
        }
        if (player.rect.x + player.rect.width >= screenWidth)
        {
            player.rect.x = screenWidth - player.rect.width;
        }
        if (player.rect.y <= 0)
        {
            player.rect.y = 0;
        }
        if (player.rect.y + player.rect.height >= screenHeight)
        {
            player.rect.y = screenHeight - player.rect.height;
        }

        if (IsKeyDown(KEY_Z))
        {
            player.chargeTime += GetFrameTime();
            //player.chargeProgress = player.chargeTime / chargeTime;
            if (player.chargeTime >= game.chargeTime)
            {
                player.chargingactive = true;
                player.canShoot = true;
                player.shotsLeft = 1; // reset the number of shots left
            }
        }

        //Shoot initialization
        if (IsKeyReleased('Z') && player.canShoot && player.shotsLeft > 0)
        {
            player.chargingactive = false;
            player.chargeTime = 0;
            for (int i = 0; i < NUM_SHOOTS; i++)
            {
                if (!shoot[i].active)
                {
                    shoot[i].rect.x = player.rect.x;
                    shoot[i].rect.y = player.rect.y + player.rect.height / 4;
                    shoot[i].active = true;
                    player.shotsLeft--; // decrement the number of shots left
                    break;
                }
            }
            if (player.shotsLeft == 0)
            {
                player.canShoot = false;
            }
        }
        if (!IsKeyDown(KEY_Z) && !player.canShoot)
        {
            player.chargeTime = 0;
        }

        // Shoot logic
        for (int i = 0; i < NUM_SHOOTS; i++)
        {
            if (shoot[i].active)
            {
                // Movement
                shoot[i].rect.y += shoot[i].speed.y;

                // Collision with enemy
                for (int j = 0; j < game.activeEnemies; j++)
                {
                    if (enemy[j].active)
                    {
                        for (int i = 0; i < NUM_SHOOTS; i++)
                        {
                            if (shoot[i].active)
                            {
                                for (int j = 0; j < NUM_MAX_ENEMIES; j++)
                                {
                                    if (enemy[j].active && CheckCollisionRecs(shoot[i].rect, enemy[j].rect))
                                    {

                                        enemy[j].active = false;
                                        game.activeEnemies--;
                                        shoot[i].active = true;
                                        
                                        // spawn diamonds when enemy is destroyed by shoot
                                        for (int k = 0; k < NUM_DIAMONDS; k++)
                                        {
                                            diamond[k].rect.x = enemy[j].rect.x + GetRandomValue(-20, 20);
                                            diamond[k].rect.y = enemy[j].rect.y + GetRandomValue(-20, 20);
                                            diamond[k].rect.width = DIAMOND_WIDTH;
                                            diamond[k].rect.height = DIAMOND_HEIGHT;
                                            diamond[k].speed.x = DIAMOND_SPEED;
                                            diamond[k].speed.y = DIAMOND_SPEED;
                                            diamond[k].active = true;
                                            diamond[k].color = YELLOW;
                                        }
                                        game.activeDiamonds += NUM_DIAMONDS;
                                        //PlaySoundMulti(explosion);
                                    }
                                }
                            }
                        }

                        if (shoot[i].rect.y <= 0) //goes above the screen
                        {
                            shoot[i].active = false;
                            game.shootRate = 0;
                        }

                        // Update enemies
                        for (int i = 0; i < NUM_MAX_ENEMIES; i++)
                        {
                            if (enemy[i].active)
                            {

                                if (enemy[i].rect.y > screenHeight)
                                {
                                    enemy[i].active = false;
                                    game.activeEnemies--;
                                }
                            }
                            // Spawn new enemies only inside the screen
                            else if (game.activeEnemies < 10)
                            {
                                enemy[i].rect.width = ENEMY_WIDTH;
                                enemy[i].rect.height = ENEMY_HEIGHT;
                                enemy[i].rect.x = (float)GetRandomValue(0, screenWidth - ENEMY_WIDTH);
                                enemy[i].rect.y = (float)GetRandomValue(-screenHeight, -20);
                                enemy[i].speed.x = ENEMY_SPEED;
                                enemy[i].speed.y = ENEMY_SPEED;
                                enemy[i].active = true;
                                enemy[i].color = BLUE;
                                game.activeEnemies++;
                            }
                        }
                    }
                }
            }
        }

        game.collectedFromSameEnemy = 0;
        for (int i = 0; i < NUM_DIAMONDS; i++)
        {
            if (diamond[i].active && CheckCollisionRecs(player.rect, diamond[i].rect))
            {
                diamond[i].active = false;
                game.activeDiamonds--;
                game.collectedFromSameEnemy++;
                game.comboBonus = (50 + (game.collectedFromSameEnemy * 10));
                game.score += game.comboBonus;
                game.pointsTimer = (float)GetTime() + 1.0f;
            }

            if (i > 0 && diamond[i].rect.x != diamond[i - 1].rect.x)
            {
                game.collectedFromSameEnemy = 0;
            }
        }
    }

}