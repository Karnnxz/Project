#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include "raylib.h"
#include "Player.h"
#include "Coin.h"
#include "Obstacle.h"

class ScreenController {
public:
    ScreenController(int screenWidth, int screenHeight, Player& player, Coin* coins, int coinCount, Obstacle& obstacle, Texture2D& background);
    ~ScreenController(); // Add this line

    void Update(float& time, int& score, bool& gameOver);
    void Draw(int score, bool gameOver);

private:
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
