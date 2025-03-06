#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include "raylib.h"
#include "Player.h"
#include "Coin.h"
#include "Obstacle.h"
#include <vector>
#define MAP_LENGTH 2000

class ScreenController {
public:
    ScreenController(int screenWidth, int screenHeight, Player& player, Coin* coins, int coinCount, Obstacle& obstacle, std::vector<Texture2D>& backgrounds, std::vector<Texture2D>& coinPatterns, Texture2D coinTexture);
    ~ScreenController();

    void Update(float& time, int& score, bool& gameOver);
    void Draw(int score, bool gameOver);
    void ChangeLevel(float& time, int& score, bool& gameOver);
private:
    float messageTimer = 0.0f;
    bool showWinMessage = false;
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
    Texture2D backgrounds[5];
    Texture2D coinPatterns[5]; // Declare 
    Texture2D coinTexture;
    void SetCoinPattern(int backgroundState);
};

#endif // SCREENCONTROLLER_H
