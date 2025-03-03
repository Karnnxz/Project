#include "Obstacle.h"
#include "raylib.h" 
#define GROUND_Y 480

// Obstacle.cpp
Obstacle::Obstacle(float x, float y) {
    float scaleFactor = 0.1f; // ปรับขนาดใหม่
    texture = LoadTexture("../../../OneDrive/Desktop/Coding/Project/Compro/MonsterB.png");

    if (texture.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load obstacle texture!");
    }

    // **ปรับแก้ตำแหน่งของ Obstacle ให้วางบนพื้นอย่างถูกต้อง**
    rec = { x, GROUND_Y - (texture.height * scaleFactor),
            texture.width * scaleFactor, texture.height * scaleFactor };

    active = true;
    velocity = 1.5f;
    movingRight = true;
    leftBoundary = x - 100;
    rightBoundary = x + 100;

    // **ตรวจสอบค่า rec.x, rec.y, rec.width, rec.height**
    TraceLog(LOG_INFO, "Obstacle Created at x=%.2f, y=%.2f, width=%.2f, height=%.2f",
        rec.x, rec.y, rec.width, rec.height);
}


void Obstacle::Update() {
    if (active) {
        if (movingRight) {
            rec.x += velocity;
            if (rec.x >= rightBoundary) movingRight = false;
        }
        else {
            rec.x -= velocity;
            if (rec.x <= leftBoundary) movingRight = true;
        }
    }
}



void Obstacle::Draw() {
    if (texture.id != 0) {
        Rectangle sourceRec = { 0, 0, (float)texture.width, (float)texture.height };
        Rectangle destRec = { rec.x, rec.y, rec.width, rec.height };
        DrawTexturePro(texture, { 0, 0, (float)texture.width, (float)texture.height }, destRec, { 0, 0 }, 0.0f, WHITE);

        Vector2 origin = { 0, 0 };
    }
    else {
        TraceLog(LOG_ERROR, "Obstacle texture is not loaded properly.");
    }
}

Rectangle Obstacle::GetRec() const {

    float hitboxMarginX = 10.0f;  // ลดขนาดขอบด้านข้าง
    float hitboxMarginY = 5.0f;   // ลดขนาดขอบด้านบน-ล่าง
    return { rec.x + hitboxMarginX, rec.y + hitboxMarginY,
             rec.width - 2 * hitboxMarginX, rec.height - 2 * hitboxMarginY };


}

bool Obstacle::IsMovingRight() const {
    return movingRight;
}

void Obstacle::Unload() {
    // ปลดโหลดทรัพยากรของ Obstacle
    UnloadTexture(texture);
}

void Obstacle::Reset(float x, float y) {
    rec.y = GROUND_Y - rec.height;
    rec.x = x;
    movingRight = true;
}
