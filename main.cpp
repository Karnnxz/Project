#include "raylib.h"
#include "Player.h"
#include "Coin.h"
#include "Obstacle.h"
#include "ScreenController.h"
#include "Button.h"
#include <cmath>
#include "TextRenderer.h"
#include <vector>

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

    Texture2D background = LoadTexture("../../../OneDrive/Desktop/Coding/Project/Compro/Background1.png");
    Texture2D Menubackground = LoadTexture("../../../OneDrive/Desktop/Coding/Project/Compro/MenuBackground.png");
	Texture2D Endbackground = LoadTexture("../../../OneDrive/Desktop/Coding/Project/Compro/EndBackground.png");
    if (background.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load background texture!");
    }
    // ปรับตำแหน่งปุ่มให้อยู่มุมล่างตรงกลาง
    Vector2 buttonPosition = { screenWidth / 2 - 100, screenHeight - 120 };

    // สร้างปุ่มด้วยตำแหน่งที่กำหนด
    Button startButton("../../../OneDrive/Desktop/Coding/Project/Compro/Button.png", buttonPosition, 0.5f);

    bool gameStarted = false; // เพิ่มตัวแปรเพื่อตรวจสอบว่าเกมเริ่มหรือยัง

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!gameStarted) {
            DrawTexture(Menubackground, 0, 0, WHITE); // แสดงภาพเริ่มต้น
            startButton.Draw();

            Vector2 mousePos = GetMousePosition();
            if (startButton.isPressed(mousePos, IsMouseButtonPressed(MOUSE_LEFT_BUTTON))) {
                gameStarted = true; // เปลี่ยนสถานะเป็นเริ่มเกม
            }
        }
        else {
            DrawTexture(background, 0, 0, WHITE); // เปลี่ยนไปใช้ Background เกม
            break; // ออกจากลูปเพื่อเข้าสู่เกมหลัก
        }

        EndDrawing();
    }

    Player player(60, GROUND_Y - 80);
    Coin coins[COIN_COUNT] = { {300, GROUND_Y - 130}, {400, GROUND_Y - 180}, {500, GROUND_Y - 220}, {600, GROUND_Y - 180},
                               {700, GROUND_Y - 130}, {950, GROUND_Y - 130}, {1050, GROUND_Y - 130}, {1150, GROUND_Y - 130},
                               {1250, GROUND_Y - 130}, {1350, GROUND_Y - 130}, {1500, GROUND_Y - 220}, {1550, GROUND_Y - 220},
                               {1600, GROUND_Y - 220}, {1650, GROUND_Y - 220}, {1700, GROUND_Y - 130}, {1750, GROUND_Y - 130},
                               {1800, GROUND_Y - 130}, {1850, GROUND_Y - 130}, {1900, GROUND_Y - 220}, {1900, GROUND_Y - 350} };
    Obstacle obstacle(500, GROUND_Y - 50);

    int score = 0;
    bool gameOver = false;
	bool gameWin = false;
    float time = 0.0f;

    Image coinImage = GenImageColor(20, 20, BLANK); // สร้าง Image โปร่งใส
    ImageDrawCircle(&coinImage, 10, 10, 10, GOLD); // วาดวงกลมสีทอง
    Texture2D coinTexture = LoadTextureFromImage(coinImage); // แปลง Image เป็น Texture
    UnloadImage(coinImage); // ลบ Image เมื่อไม่ใช้งานแล้ว

    std::vector<Texture2D> backgrounds = { background };
    std::vector<Texture2D> coinPatterns = { coinTexture };

    ScreenController screenController(screenWidth, screenHeight, player, coins, COIN_COUNT, obstacle, backgrounds, coinPatterns, coinTexture);

    while (!WindowShouldClose()) {
        if (score == 500) {
			gameWin = true;
            DrawTexture(Endbackground, 0, 0, WHITE);
        }
        UpdateDrawFrame(screenController, time, score, gameOver, background);
    }
    UnloadTexture(Menubackground);
    UnloadTexture(Endbackground);
    CloseWindow();
    player.Unload();
    UnloadTexture(background);
    obstacle.Unload();

    return 0;
}
