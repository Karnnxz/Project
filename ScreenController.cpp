#include "ScreenController.h"
#include "TextRenderer.h"
#include "raylib.h"
#include "Player.h"
#include "Coin.h"
#include "Obstacle.h"
#include <cmath>

#define GROUND_Y 480 
#define MAP_LENGTH 800
// #define GROUND_HEIGHT 150 

ScreenController::ScreenController(int screenWidth, int screenHeight, Player& player, Coin* coins, int coinCount, Obstacle& obstacle, Texture2D& background)
    : screenWidth(screenWidth), screenHeight(screenHeight), player(player), coins(coins), coinCount(coinCount), obstacle(obstacle), background(background), groundTile{} {
    camera.target = Vector2{ player.GetRec().x + player.GetRec().width / 2, player.GetRec().y + player.GetRec().height / 2 };
    camera.offset = Vector2{ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}


ScreenController::~ScreenController() {
}

void ScreenController::Update(float& time, int& score, bool& gameOver) {
    if (!gameOver) {
        player.Update();
        for (int i = 0; i < coinCount; i++) {
            coins[i].SetPosition(coins[i].GetRec().x, GROUND_Y - 180 + 50 * sin(time + i));
            coins[i].Update();
        }
        obstacle.Update();

        for (int i = 0; i < coinCount; i++) {
            if (!coins[i].IsCollected() && CheckCollisionRecs(player.GetRec(), coins[i].GetRec())) {
                coins[i].Collect();
                score += 10;
            }
        }

        if (score >= 25 && !backgroundChanged) {
            UnloadTexture(background);  // ลบพื้นหลังเดิม
            background = LoadTexture("../../../OneDrive/Desktop/Coding/Project/Compro/Background2.png"); // โหลดพื้นหลังใหม่
            backgroundChanged = true;  // ป้องกันการโหลดซ้ำ
        }

        Rectangle playerRec = player.GetRec();
        Rectangle obstacleRec = obstacle.GetRec();

        Vector2 playerCenter = { playerRec.x + playerRec.width / 2, playerRec.y + playerRec.height / 2 };
        Vector2 obstacleCenter = { obstacleRec.x + obstacleRec.width / 2, obstacleRec.y + obstacleRec.height / 2 };

        float distance = static_cast<float>(sqrt(pow(playerCenter.x - obstacleCenter.x, 2) + pow(playerCenter.y - obstacleCenter.y, 2)));
        float collisionThreshold = 10.0f;

        if (CheckCollisionRecs(playerRec, obstacleRec) || distance < collisionThreshold) {
            TraceLog(LOG_INFO, "Collision Detected! Distance: %.2f", distance);
            gameOver = true;
        }

        time += 0.05f;
        camera.target = Vector2{ player.GetRec().x + player.GetRec().width / 2, player.GetRec().y + player.GetRec().height / 2 };
    }
    else {
        if (IsKeyPressed(KEY_R)) {
            score = 0;
            gameOver = false;
            backgroundChanged = false;  // รีเซ็ตการเปลี่ยนพื้นหลัง
            UnloadTexture(background);
            background = LoadTexture("../../../OneDrive/Desktop/Coding/Project/Compro/Background.png"); // โหลดพื้นหลังเดิม
            player.SetGameOver(false);
            player.Reset(100, GROUND_Y - 80);
            for (int i = 0; i < coinCount; i++) {
                coins[i].Reset();
            }
            obstacle = Obstacle(600, GROUND_Y - 80);
        }
    }
}

void ScreenController::Draw(int score, bool gameOver) {
    ClearBackground(RAYWHITE);  // ลบ BeginDrawing() ออกไป
    DrawTextureEx(background, Vector2{ 0, 0 }, 0.0f, (float)screenWidth / background.width, WHITE);
    // 🟩 วาดพื้นดินให้มีความยาวเท่ากับ MAP_LENGTH


    BeginMode2D(camera);
    //DrawRectangle(0, GROUND_Y, MAP_LENGTH, GROUND_HEIGHT, DARKBROWN);



    player.Draw();
    for (int i = 0; i < coinCount; i++) {
        coins[i].Draw();
    }
    obstacle.Draw();

    EndMode2D();

    TextRenderer textRenderer;
    if (gameOver) {
        textRenderer.DrawGameOver(screenWidth, screenHeight);
    }
    else {
        textRenderer.DrawScore(score);
    }
}
