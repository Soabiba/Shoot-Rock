#include <math.h>
#include "raylib.h"
#include "define.h"
#include "game.h"
#include "global.h"


// Draw game (one frame)
void Level::DrawGame(void)
{
    BeginDrawing();

    ClearBackground(BLACK);

    void drawPlayer();

    if (game.startScreen)
    {
        DrawTexture(ui.background, 0, 0, WHITE);
        DrawText("SPACE ROCKS", screenWidth / 2 - MeasureText("SPACE ROCKS", 30) / 2, screenHeight / 2 - 30, 30, WHITE);
        DrawText("PRESS [ENTER] TO START", screenWidth / 2 - MeasureText("PRESS [ENTER] TO START", 20) / 2, screenHeight / 2 + 20, 20, WHITE);
    }
    else if (!game.gameOver)
    {
        DrawTexture(ui.background, 0, 0, WHITE);

        //DrawRectangleRec(player.rect, player.color);
        DrawTexture(ui.spaceship, (int)(player.rect.x - player.rect.width), (int)player.rect.y, WHITE);

        for (int i = 0; i < game.activeEnemies; i++)
        {
            if (enemy[i].active)
            {
                DrawTexture(ui.fireball, (int)(enemy[i].rect.x - enemy[i].rect.width), (int)enemy[i].rect.y, WHITE);
            }
        }

        for (int i = 0; i < NUM_SHOOTS; i++)
        {
            if (shoot[i].active)
            {
                DrawRectangleRec(shoot[i].rect, shoot[i].color);
            }
        }

        for (int i = 0; i < NUM_DIAMONDS; i++)
        {
            if (diamond[i].active)
            {
                DrawRectangleRec(diamond[i].rect, diamond[i].color);
                if (GetTime() < game.pointsTimer)
                {
                    DrawText(TextFormat("+ %02i", (int)game.comboBonus), (int)diamond[i].rect.x - 50, (int)(diamond[i].rect.y - 50), 50, GRAY);
                }
            }
        }

        if (boom.active)
        {
            DrawTexture(ui.explosion1, (int)boom.rect.x, (int)boom.rect.y, WHITE);
        }
        if (boom.active && GetTime() - boom.start_time > boom.duration)
        {
            boom.active = false;
        }

        if (player.chargingactive)
        {
            DrawTexture(ui.charging, (int)(player.rect.x + 20), (int)(player.rect.y - 20), WHITE);
        }

        DrawText(TextFormat("Score : %04i", game.score), 20, 20, 20, GRAY);
        DrawText(TextFormat("High Score : %04i", game.highScore), 200, 20, 20, GRAY);

        if (game.paused)
        {
            DrawText("GAME PAUSED", GetScreenWidth() / 2 - MeasureText("GAME PAUSED", 20) / 2, GetScreenHeight() / 2 - 50, 20, WHITE);
        }
    }
    else
    {
        DrawTexture(ui.background, 0, 0, WHITE);
        DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, WHITE);
    }

    EndDrawing();
}


// Update and Draw (one frame)
void Level::UpdateDrawFrame(void)
{
    if (game.startScreen)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            game.startScreen = false;
        }
    }
    else if (game.gameOver)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            level.InitGame();
            game.gameOver = false;
            player.canShoot = true;
            player.chargeTime = 0;
            game.score = 0;
        }
    }
    else
    {
        // Handle pause
        if (IsKeyPressed(KEY_SPACE))
        {
            game.paused = !game.paused;
        }
        if (!game.paused)
        {
            level.UpdateGame();
        }
    }
    level.DrawGame();
}