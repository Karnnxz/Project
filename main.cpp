#include "raylib.h"
#include "Player.h"
#include "Coin.h"
#include "Obstacle.h"
#include <cmath>

#define GROUND_Y 400
#define COIN_COUNT 5  // จำนวนเหรียญที่ต้องการ

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Run for score");

    SetTargetFPS(60);

    // โหลดพื้นหลัง
    Texture2D background = LoadTexture("../../../../AssetsCompro/Monster/background.png");
    if (background.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load background texture!");
    }

    // สร้างตัวละครและวัตถุในเกม
    Player player = CreatePlayer(100, GROUND_Y - 80);
    Coin coins[COIN_COUNT];  // สร้าง Array สำหรับเก็บหลายเหรียญ
    for (int i = 0; i < COIN_COUNT; i++) {
        coins[i] = CreateCoin(200 + i * 100, GROUND_Y - 180);  // กำหนดตำแหน่งเหรียญ
    }
    Obstacle obstacle = CreateObstacle(600, GROUND_Y - 80);

    int score = 0;
    bool gameOver = false;

    float time = 0.0f;  // ใช้สำหรับควบคุมการเคลื่อนไหวของเหรียญ

    while (!WindowShouldClose()) {
        if (!gameOver) {
            // อัปเดตตัวละครและวัตถุ
            UpdatePlayer(&player);
            for (int i = 0; i < COIN_COUNT; i++) {
                // ทำให้เหรียญขยับขึ้นลง
                coins[i].rec.y = GROUND_Y - 180 + 50 * sin(time + i);  // เพิ่มการเคลื่อนที่แบบซิกแซก
                UpdateCoin(&coins[i]);  // อัปเดตเหรียญแต่ละตัว
            }
            UpdateObstacle(&obstacle);

            // ตรวจสอบการชนกับเหรียญ
            for (int i = 0; i < COIN_COUNT; i++) {
                if (!coins[i].collected && CheckCollisionRecs(player.rec, coins[i].rec)) {
                    coins[i].collected = true;
                    score += 10;
                }
            }

            // ตรวจสอบการชนกับสิ่งกีดขวาง
            if (CheckCollisionRecs(player.rec, obstacle.rec)) {
                gameOver = true;
            }

            time += 0.05f;  // เพิ่มเวลาเพื่อให้การเคลื่อนไหวไม่หยุด
        }
        else {
            // รีเซ็ตเกมเมื่อกดปุ่ม R
            if (IsKeyPressed(KEY_R)) {
                // รีเซ็ตค่าต่างๆ
                score = 0;
                gameOver = false;
                player.isGameOver = false;  // รีเซ็ตสถานะเกมโอเวอร์
                player = CreatePlayer(100, GROUND_Y - 80);
                for (int i = 0; i < COIN_COUNT; i++) {
                    coins[i] = CreateCoin(200 + i * 100, GROUND_Y - 180);  // รีเซ็ตตำแหน่งเหรียญ
                }
                obstacle = CreateObstacle(600, GROUND_Y - 80);
            }
        }

        // วาดภาพ
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTextureEx(background, Vector2{ 0, 0 }, 0.0f, (float)screenWidth / background.width, WHITE);

        if (gameOver) {
            // วัดขนาดของทั้งสองข้อความ
            Vector2 gameOverTextSize = MeasureTextEx(GetFontDefault(), "Game Over!", 40, 1);
            Vector2 restartTextSize = MeasureTextEx(GetFontDefault(), "Press R to restart", 30, 1);

            // คำนวณขนาดกรอบที่จะครอบคลุมทั้งสองข้อความ
            float boxWidth = (gameOverTextSize.x > restartTextSize.x) ? gameOverTextSize.x : restartTextSize.x;
            float boxHeight = gameOverTextSize.y + restartTextSize.y + 20; // ขนาดรวมของข้อความทั้งสอง (เพิ่มพื้นที่ระหว่างข้อความ)

            // กำหนดตำแหน่งกรอบ
            Rectangle backgroundRect = Rectangle{
                screenWidth / 2 - boxWidth / 2 - 10, // เลื่อนไปทางซ้ายเล็กน้อย
                screenHeight / 2 - boxHeight / 2 - 10, // เลื่อนไปทางบนเล็กน้อย
                boxWidth + 20, // ขยายกรอบออกเพื่อมีระยะห่างจากข้อความ
                boxHeight + 20 // ขยายกรอบออกเพื่อมีระยะห่างจากข้อความ
            };

            // วาดกรอบสีขาว
            DrawRectangleRec(backgroundRect, WHITE);

            // วาดข้อความ "Game Over!"
            DrawTextEx(GetFontDefault(), "Game Over!", Vector2{ screenWidth / 2 - gameOverTextSize.x / 2, screenHeight / 2 - gameOverTextSize.y / 2 }, 40, 1, RED);

            // วาดข้อความ "Press R to restart"
            DrawTextEx(GetFontDefault(), "Press R to restart", Vector2{ screenWidth / 2 - restartTextSize.x / 2, screenHeight / 2 + gameOverTextSize.y / 2 }, 30, 1, RED);
        }
        else {
            // วาดตัวละคร, เหรียญ, อุปสรรค
            DrawPlayer(player);
            for (int i = 0; i < COIN_COUNT; i++) {
                DrawCoin(coins[i]);  // วาดเหรียญทุกตัว
            }
            DrawObstacle(obstacle);
            DrawText(TextFormat("Score: %d", score), 10, 10, 20, DARKGRAY);
        }

        EndDrawing();
    }

    // ปิดเกมและล้างหน่วยความจำ
    CloseWindow();
    UnloadPlayer(&player);
    UnloadTexture(background);
    UnloadTexture(obstacle.texture);

    return 0;
}
