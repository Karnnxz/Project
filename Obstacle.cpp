#include "Obstacle.h"
#include "raylib.h"

// ฟังก์ชันที่ใช้โหลดภาพของอุปสรรค
Obstacle CreateObstacle(float x, float y) {
    Obstacle obstacle;
    obstacle.texture = LoadTexture("../../../../AssetsCompro/Monster/MonsterB.png");

    // ตรวจสอบว่าโหลดภาพสำเร็จ
    if (obstacle.texture.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load texture for MonsterB.png");
    }

    // ปรับขนาดของ Rectangle ให้เล็กลง
    obstacle.rec = Rectangle{ x, y, (float)obstacle.texture.width * 0.1f, (float)obstacle.texture.height * 0.1f };

    // กำหนดขอบเขตการเคลื่อนที่
    obstacle.leftBoundary = x - 100;   // ขอบซ้าย (ตัวอย่างให้มอนสเตอร์เดินไปซ้าย 100 หน่วย)
    obstacle.rightBoundary = x + 100;  // ขอบขวา (ตัวอย่างให้มอนสเตอร์เดินไปขวา 100 หน่วย)

    obstacle.active = true;
    obstacle.velocity = 2.0f;
    obstacle.movingRight = true;  // เริ่มต้นเคลื่อนที่ไปขวา

    return obstacle;
}

void UpdateObstacle(Obstacle* obstacle) {
    // เปลี่ยนทิศทางการเคลื่อนที่เมื่อถึงขอบซ้ายหรือขวา
    if (obstacle->movingRight) {
        obstacle->rec.x += obstacle->velocity;  // เคลื่อนที่ไปขวา
        if (obstacle->rec.x + obstacle->rec.width >= obstacle->rightBoundary) {  // ขอบขวาของการเคลื่อนที่
            obstacle->movingRight = false;  // เปลี่ยนทิศทางไปซ้าย
        }
    }
    else {
        obstacle->rec.x -= obstacle->velocity;  // เคลื่อนที่ไปซ้าย
        if (obstacle->rec.x <= obstacle->leftBoundary) {  // ขอบซ้ายของการเคลื่อนที่
            obstacle->movingRight = true;  // เปลี่ยนทิศทางไปขวา
        }
    }
}

void DrawObstacle(Obstacle obstacle) {
    if (obstacle.texture.id != 0) { // ตรวจสอบว่าภาพโหลดสำเร็จหรือไม่
        // ใช้ DrawTexturePro เพื่อปรับขนาดภาพ
        DrawTexturePro(obstacle.texture,
            Rectangle{ 0, 0, (float)obstacle.texture.width, (float)obstacle.texture.height }, // ต้นฉบับ
            Rectangle{ obstacle.rec.x, obstacle.rec.y, obstacle.rec.width, obstacle.rec.height }, // วาดที่ตำแหน่งเดิม
            Vector2{ obstacle.rec.width / 2, obstacle.rec.height / 2 }, // ใช้ origin เดิม
            0.0f, WHITE);
    }
    else {
        DrawRectangleRec(obstacle.rec, RED); // ถ้าโหลดภาพไม่ได้ ให้แสดงกล่องสีแดงแทน
    }
}
