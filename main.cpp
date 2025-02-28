#include "raylib.h"
#include "Player.h"
#include "Coin.h"
#include "Obstacle.h"
#include "ScreenController.h"
#include <cmath>
#include "TextRenderer.h"

#define GROUND_Y 450
#define COIN_COUNT 20
#define MAP_LENGTH 2000  // Define the length of the map

TextRenderer textRenderer;

void UpdateDrawFrame(ScreenController& screenController, float& time, int& score, bool& gameOver, Texture2D& background) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    screenController.Update(time, score, gameOver);
    screenController.Draw(score, gameOver);
    EndDrawing();
}


int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Run for score");

    SetTargetFPS(60);

    Texture2D background = LoadTexture("../../../../AssetsCompro/Monster/background.png");
    if (background.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load background texture!");
    }

    Player player(100, GROUND_Y - 80);
    Coin coins[COIN_COUNT] = { {300, GROUND_Y - 130}, {400, GROUND_Y - 180}, {500, GROUND_Y - 220}, {600, GROUND_Y - 180}
, {700, GROUND_Y - 130}, {950, GROUND_Y - 130}, {1050, GROUND_Y - 130}, {1150, GROUND_Y - 130}, {1250, GROUND_Y - 130}
, {1350, GROUND_Y - 130} , {1500, GROUND_Y - 220} , {1550, GROUND_Y - 220} , {1600, GROUND_Y - 220} , {1650, GROUND_Y - 220}
, {1700, GROUND_Y - 130} , {1750, GROUND_Y - 130} , {1800, GROUND_Y - 130} , {1850, GROUND_Y - 130} , {1900, GROUND_Y - 220}
, {1900, GROUND_Y - 350} };
    Obstacle obstacle(500, GROUND_Y - 50);

    int score = 0;
    bool gameOver = false;
    float time = 0.0f;

    ScreenController screenController(screenWidth, screenHeight, player, coins, COIN_COUNT, obstacle, background);

    while (!WindowShouldClose()) {
        UpdateDrawFrame(screenController, time, score, gameOver, background);
    }

    CloseWindow();
    player.Unload();
    UnloadTexture(background);
    obstacle.Unload();

    return 0;
}
