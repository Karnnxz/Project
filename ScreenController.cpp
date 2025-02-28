#include "ScreenController.h"
#include "TextRenderer.h"
#include "raylib.h"
#include "Player.h"
#include "Coin.h"
#include "Obstacle.h"
#include <cmath>

#define GROUND_Y 450 
#define MAP_LENGTH 2000 
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

        // จำกัดการเคลื่อนที่ของผู้เล่นให้อยู่ในขอบเขตแมพ
        float playerNextX = player.GetRec().x + player.GetVelocity().x; // ดูตำแหน่งถัดไปของ player

        if (playerNextX < mapStartX) {
            player.SetPosition(mapStartX, player.GetRec().y);
        }
        if (playerNextX + player.GetRec().width > mapEndX) {
            player.SetPosition(mapEndX - player.GetRec().width, player.GetRec().y);
        }


        // อัปเดตเหรียญ
        for (int i = 0; i < coinCount; i++) {
            coins[i].SetPosition(coins[i].GetRec().x, GROUND_Y - 180 + 50 * sin(time + i));
            coins[i].Update();
        }

        // อัปเดตอุปสรรค
        obstacle.Update();

        // ตรวจสอบการชนกับเหรียญ
        for (int i = 0; i < coinCount; i++) {
            if (!coins[i].IsCollected() && CheckCollisionRecs(player.GetRec(), coins[i].GetRec())) {
                coins[i].Collect();
                score += 5;
            }
        }

        // ตรวจสอบการชนกับอุปสรรค
        if (CheckCollisionRecs(player.GetRec(), obstacle.GetRec())) {
            gameOver = true;
        }

        time += 0.05f;

        if (score == 100 && backgroundState == 1) {
            score = 0;  // รีเซ็ตคะแนน
            time = 0.0f;  // รีเซ็ตเวลา
            gameOver = false;  // รีเซ็ตสถานะเกม
            backgroundState = 2;  // เปลี่ยนสถานะพื้นหลัง

            // โหลดพื้นหลังใหม่
            UnloadTexture(background);
            background = LoadTexture("../../../OneDrive/Desktop/Coding/Project/Compro/Background2.png");

            // รีเซ็ตค่าของ Player
            player.SetGameOver(false);
            player.Reset(100, GROUND_Y - 80);


            // รีเซ็ตอุปสรรค
            obstacle = Obstacle(500, GROUND_Y - 50);
        }


        // จำกัดการเลื่อนของกล้อง
        float playerCenterX = player.GetRec().x + player.GetRec().width / 2;
        float cameraMinX = screenWidth / 2;
        float cameraMaxX = mapEndX - screenWidth / 2;

        camera.target.x = fmax(cameraMinX, fmin(playerCenterX, cameraMaxX));
        // ✅ ทำให้กล้องติดตามตัวละครอย่างสมูท
        float followSpeed = 0.1f; // ค่าความเร็วในการติดตาม
        camera.target.y += (player.GetRec().y - camera.target.y) * followSpeed;

        float minCameraY = 200.0f;  // ป้องกันกล้องลงต่ำเกินไป
        float maxCameraY = 500.0f;  // ป้องกันกล้องขึ้นสูงเกินไป

        if (camera.target.y < minCameraY) camera.target.y = minCameraY;
        if (camera.target.y > maxCameraY) camera.target.y = maxCameraY;
    }
    else {
        //  รีเซ็ตเกมเมื่อกดปุ่ม R  
        if (IsKeyPressed(KEY_R)) {
            score = 0;
            gameOver = false;
            time = 0.0f;

            // รีเซ็ตค่าของ Player
            player.SetGameOver(false);
            player.Reset(100, GROUND_Y - 80);

            // รีเซ็ตเหรียญทั้งหมด
            for (int i = 0; i < coinCount; i++) {
                coins[i].Reset();
            }

            // รีเซ็ตอุปสรรค  
            obstacle = Obstacle(500, GROUND_Y - 50);
        }
    }
}



void ScreenController::Draw(int score, bool gameOver) {
    ClearBackground(RAYWHITE);

    // 🔹 วาดพื้นหลังในตำแหน่งคงที่บนหน้าจอ
    DrawTextureEx(background, Vector2{ 0, 0 }, 0.0f, (float)screenWidth / background.width, WHITE);

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
