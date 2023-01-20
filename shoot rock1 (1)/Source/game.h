#pragma once

struct Game
{
    bool gameOver;
    int score;

    int shootRate;
    int activeEnemies;
    int activeDiamonds;
    int enemiesKill;
    bool paused;
    bool startScreen;
    int chargeTime;
    int highScore;
    int comboBonus;
    int collectedFromSameEnemy;
    float pointsTimer;
}; 
Game game;

struct Player
{
    Rectangle rect;
    Vector2 speed;
    Color color;
    bool canShoot;
    float chargeTime;
    int shotsLeft;
    bool chargingactive;
}; 
Player player;

struct Shoot
{
    Rectangle rect;
    Vector2 speed;
    bool active;
    Color color;
}; 
Shoot shoot[NUM_SHOOTS];

struct Diamond
{
    Rectangle rect;
    Vector2 speed;
    bool active;
    Color color;
};
Diamond diamond[NUM_DIAMONDS];

struct Enemy
{
    Rectangle rect;
    Vector2 speed;
    bool active;
    Color color;
}; 
Enemy enemy[NUM_MAX_ENEMIES];

struct UI
{
    Texture2D background;
    Texture2D spaceship;
    Texture2D fireball;
    Texture2D shooting;
    Texture2D charging;
    Texture2D explosion1;

    Sound explosion;
};
UI ui;