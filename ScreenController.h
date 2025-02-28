#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include "raylib.h"
#include "Player.h"
#include "Coin.h"
#include "Obstacle.h"
#define MAP_LENGTH 2000.0f

class ScreenController {
public:
    ScreenController(int screenWidth, int screenHeight, Player& player, Coin* coins, int coinCount, Obstacle& obstacle, Texture2D& background);
    ~ScreenController();

    void Update(float& time, int& score, bool& gameOver);
    void Draw(int score, bool gameOver);

private:
    float messageTimer = 0.0f;
    bool showLevelUpMessage = false;
    int level = 1;
    const float mapStartX = 0;
    const float mapEndX = MAP_LENGTH;
    int screenWidth;
    int screenHeight;
    Player& player;
    Coin* coins;
    int coinCount;
    Obstacle& obstacle;
    Texture2D& background;
    Camera2D camera;
    Texture2D groundTile;
    bool backgroundChanged = false;
    int backgroundState = 1;  // 1 = พื้นหลังเริ่มต้น, 2 = พื้นหลังที่ 2, 3 = พื้นหลังที่ 3
};

#endif // SCREENCONTROLLER_H
