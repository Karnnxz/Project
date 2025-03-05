#include "ScreenController.h"
#include "TextRenderer.h"
#include "raylib.h"
#include "Player.h"
#include "Coin.h"
#include "Obstacle.h"
#include <cmath>
#include <iostream>
#define GROUND_Y 450 
#define MAP_LENGTH 2000 
// #define GROUND_HEIGHT 150 

ScreenController::ScreenController(int screenWidth, int screenHeight, Player& player, Coin* coins, int coinCount, Obstacle& obstacle, std::vector<Texture2D>& backgrounds, std::vector<Texture2D>& coinPatterns, Texture2D coinTexture)
    : screenWidth(screenWidth), screenHeight(screenHeight), player(player), coins(coins), coinCount(coinCount), obstacle(obstacle), backgrounds(), coinPatterns(), coinTexture(coinTexture), background(backgrounds[0]) {
    camera.target = Vector2{ player.GetRec().x + player.GetRec().width / 2, player.GetRec().y + player.GetRec().height / 2 };
    camera.offset = Vector2{ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Initialize backgrounds array
    this->backgrounds[0] = LoadTexture("../../../../AssetsCompro/Monster/background3.jpg");
    this->backgrounds[1] = LoadTexture("../../../../AssetsCompro/Monster/background.png");
    this->backgrounds[2] = LoadTexture("../../../../AssetsCompro/Monster/background2.jpg");
    this->backgrounds[3] = LoadTexture("../../../../AssetsCompro/Monster/background4.jpg");
    this->backgrounds[4] = LoadTexture("../../../../AssetsCompro/Monster/background5.png");

    SetCoinPattern(backgroundState); // เรียกใช้เมื่อเริ่มเกม
}

ScreenController::~ScreenController() {
}

void ScreenController::Update(float& time, int& score, bool& gameOver) {
    if (!gameOver) {
        player.Update();

        if (showLevelUpMessage) {
            messageTimer -= GetFrameTime();
            if (messageTimer <= 0) {
                showLevelUpMessage = false;
            }
        }

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
        //เงื่อนไขการเปลี่ยนด่าน
        if (score == 100 && backgroundState == 1) { //ด่าน1ไป2
            time = 0.0f;
            gameOver = false;
            backgroundState = 2;
            level++;

            showLevelUpMessage = true;
            messageTimer = 2.0f;

            UnloadTexture(background);
            background = LoadTexture("../../../../AssetsCompro/Monster/background4.jpg");
            player.SetGameOver(false);
            player.Reset(60, GROUND_Y - 80);

            obstacle = Obstacle(800, GROUND_Y - 50);

            // ⭐ เปลี่ยนรูปแบบการวางเหรียญ
            SetCoinPattern(backgroundState);
        }
        else if (score == 200 && backgroundState == 2) { //ด่าน2ไป3
            time = 0.0f;
            gameOver = false;
            backgroundState = 3;
            level++;

            showLevelUpMessage = true;
            messageTimer = 2.0f;

            UnloadTexture(background);
            background = LoadTexture("../../../../AssetsCompro/Monster/background.png");

            player.SetGameOver(false);
            player.Reset(60, GROUND_Y - 80);

            obstacle = Obstacle(1000, GROUND_Y - 50);

            // ⭐ เปลี่ยนรูปแบบการวางเหรียญ
            SetCoinPattern(backgroundState);
        }
        // เปลี่ยนจากด่าน 3 -> ด่าน 4
        else if (score == 300 && backgroundState == 3) {
            time = 0.0f;
            gameOver = false;
            backgroundState = 4;
            level++;

            showLevelUpMessage = true;
            messageTimer = 2.0f;

            UnloadTexture(background);
            background = LoadTexture("../../../../AssetsCompro/Monster/background2.jpg");

            player.SetGameOver(false);
            player.Reset(60, GROUND_Y - 80);

            obstacle = Obstacle(1000, GROUND_Y - 50);

            // ⭐ เปลี่ยนรูปแบบการวางเหรียญ
            SetCoinPattern(backgroundState);
        }

        // เปลี่ยนจากด่าน 4 -> ด่าน 5
        else if (score == 400 && backgroundState == 4) {
            time = 0.0f;
            gameOver = false;
            backgroundState = 5;
            level++;

            showLevelUpMessage = true;
            messageTimer = 2.0f;

            UnloadTexture(background);
            background = LoadTexture("../../../../AssetsCompro/Monster/background5.png");

            player.SetGameOver(false);
            player.Reset(60, GROUND_Y - 80);

            obstacle = Obstacle(1000, GROUND_Y - 50);

            // ⭐ เปลี่ยนรูปแบบการวางเหรียญ
            SetCoinPattern(backgroundState);
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
            if (backgroundState == 2) {
                score = 100;
            }
            else if (backgroundState == 3) {
                score = 200;
            }
            else if (backgroundState == 4) {
                score = 300;
            }
            else if (backgroundState == 5) {
                score = 400;
            }
            else {
                score = 0;
            }
            gameOver = false;
            time = 0.0f;

            // รีเซ็ตค่าของ Player
            player.SetGameOver(false);
            player.Reset(60, GROUND_Y - 80);

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
    DrawTextureEx(background, Vector2{ 0, 0 }, 0.0f, (float)screenWidth / background.width, WHITE);

    BeginMode2D(camera);
    player.Draw();
    for (int i = 0; i < coinCount; i++) {
        coins[i].Draw(coinTexture);
    }
    obstacle.Draw();
    EndMode2D();

    TextRenderer textRenderer;
    if (gameOver) {
        textRenderer.DrawGameOver(screenWidth, screenHeight);
    }
    else {
        textRenderer.DrawScore(score);

        // ⭐ แสดงกล่องข้อความ "Great!" เมื่อเปลี่ยนด่าน
        if (showLevelUpMessage) {
            DrawRectangle(screenWidth / 2 - 90, screenHeight / 2 - 50, 200, 100, Fade(YELLOW, 0.5f));
            DrawText("Great!", screenWidth / 2 - 50, screenHeight / 2 - 20, 40, WHITE);
        }
    }
}

void ScreenController::SetCoinPattern(int backgroundState) {
    // กำหนดตำแหน่งเหรียญล่วงหน้าแบบไม่มีการซ้อนทับ
    std::vector<Vector2> coinPositions;

    if (backgroundState == 1) {
        coinPositions = { {300, GROUND_Y - 130}, {400, GROUND_Y - 180}, {500, GROUND_Y - 220}, {600, GROUND_Y - 180}
, {700, GROUND_Y - 130}, {950, GROUND_Y - 130}, {1050, GROUND_Y - 130}, {1150, GROUND_Y - 130}, {1250, GROUND_Y - 130}
, {1350, GROUND_Y - 130} , {1500, GROUND_Y - 220} , {1550, GROUND_Y - 220} , {1600, GROUND_Y - 220} , {1650, GROUND_Y - 220}
, {1700, GROUND_Y - 130} , {1750, GROUND_Y - 130} , {1800, GROUND_Y - 130} , {1850, GROUND_Y - 130} , {1900, GROUND_Y - 220}
, {1900, GROUND_Y - 350} };
    }
    else if (backgroundState == 2) {
        coinCount = 20;
        coinPositions = { {300, GROUND_Y - 130}, {400, GROUND_Y - 180}, {500, GROUND_Y - 220}, {600, GROUND_Y - 180}
, {700, GROUND_Y - 130}, {950, GROUND_Y - 130}, {1050, GROUND_Y - 130}, {1150, GROUND_Y - 130}, {1250, GROUND_Y - 130}
, {1350, GROUND_Y - 130} , {1500, GROUND_Y - 220} , {1550, GROUND_Y - 220} , {1600, GROUND_Y - 220} , {1650, GROUND_Y - 220}
, {1700, GROUND_Y - 130} , {1750, GROUND_Y - 130} , {1800, GROUND_Y - 130} , {1850, GROUND_Y - 130} , {1900, GROUND_Y - 220}
, {1900, GROUND_Y - 350} };
    }
    else if (backgroundState == 3) {
        coinCount = 20;
        coinPositions = { {300, GROUND_Y - 130}, {400, GROUND_Y - 180}, {500, GROUND_Y - 220}, {600, GROUND_Y - 180}
, {700, GROUND_Y - 130}, {950, GROUND_Y - 130}, {1050, GROUND_Y - 130}, {1150, GROUND_Y - 130}, {1250, GROUND_Y - 130}
, {1350, GROUND_Y - 130} , {1500, GROUND_Y - 220} , {1550, GROUND_Y - 220} , {1600, GROUND_Y - 220} , {1650, GROUND_Y - 220}
, {1700, GROUND_Y - 130} , {1750, GROUND_Y - 130} , {1800, GROUND_Y - 130} , {1850, GROUND_Y - 130} , {1900, GROUND_Y - 220}
, {1900, GROUND_Y - 350} };
    }
    else if (backgroundState == 4) { // ด่าน 4
        coinCount = 20;
         coinPositions = { {300, GROUND_Y - 130}, {400, GROUND_Y - 180}, {500, GROUND_Y - 220}, {600, GROUND_Y - 180}
, {700, GROUND_Y - 130}, {950, GROUND_Y - 130}, {1050, GROUND_Y - 130}, {1150, GROUND_Y - 130}, {1250, GROUND_Y - 130}
, {1350, GROUND_Y - 130} , {1500, GROUND_Y - 220} , {1550, GROUND_Y - 220} , {1600, GROUND_Y - 220} , {1650, GROUND_Y - 220}
, {1700, GROUND_Y - 130} , {1750, GROUND_Y - 130} , {1800, GROUND_Y - 130} , {1850, GROUND_Y - 130} , {1900, GROUND_Y - 220}
, {1900, GROUND_Y - 350} };
    }

    else if (backgroundState == 5) { // ด่าน 5
        coinCount = 20;
        coinPositions = { {300, GROUND_Y - 130}, {400, GROUND_Y - 180}, {500, GROUND_Y - 220}, {600, GROUND_Y - 180}
, {700, GROUND_Y - 130}, {950, GROUND_Y - 130}, {1050, GROUND_Y - 130}, {1150, GROUND_Y - 130}, {1250, GROUND_Y - 130}
, {1350, GROUND_Y - 130} , {1500, GROUND_Y - 220} , {1550, GROUND_Y - 220} , {1600, GROUND_Y - 220} , {1650, GROUND_Y - 220}
, {1700, GROUND_Y - 130} , {1750, GROUND_Y - 130} , {1800, GROUND_Y - 130} , {1850, GROUND_Y - 130} , {1900, GROUND_Y - 220}
, {1900, GROUND_Y - 350} };
    }


    // นำตำแหน่งที่กำหนดไปใช้กับเหรียญ
    for (int i = 0; i < coinCount && i < coinPositions.size(); i++) {
        coins[i].Reset();
        coins[i].SetPosition(coinPositions[i].x, coinPositions[i].y);
    }
}


void ScreenController::ChangeLevel(float& time, int& score, bool& gameOver) {
    std::cout << "Changing level to: " << (backgroundState + 1) << std::endl;

    time = 0.0f;
    gameOver = false;
    backgroundState++;
    level++;

    showLevelUpMessage = true;
    messageTimer = 2.0f;

    player.SetGameOver(false);
    player.Reset(100, GROUND_Y - 80);

    obstacle = Obstacle(500, GROUND_Y - 50);

    // โหลด Background และ Texture ใหม่
    background = backgrounds[backgroundState - 1];
    coinTexture = coinPatterns[backgroundState - 1];

    std::cout << "Calling SetCoinPattern(" << backgroundState << ")" << std::endl;
    SetCoinPattern(backgroundState);
}
