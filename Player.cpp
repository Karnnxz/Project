#include "Player.h"

#define PLAYER_GRAVITY 0.5f
#define PLAYER_JUMP_SPEED 13.0f
#define PLAYER_SPEED 5.0f
#define GROUND_Y 400

Player CreatePlayer(float x, float y) {
    Player player;
    player.rec = Rectangle{ x, y, 50, 80 };
    player.velocity = Vector2{ 0, 0 };
    player.isJumping = false;

    player.texture = LoadTexture("../../../../AssetsCompro/Charact/CharLevel01/walk/Player.png");

    if (player.texture.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load player texture!");
    }

    return player;
}

void UpdatePlayer(Player* player) {
    // รับค่าการเคลื่อนที่ซ้ายขวา
    player->velocity.x = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * PLAYER_SPEED;

    // ตรวจจับการกดปุ่มกระโดด
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_ENTER)) && !player->isJumping) {
        player->velocity.y = -PLAYER_JUMP_SPEED;
        player->isJumping = true;
    }

    // แรงโน้มถ่วง
    player->velocity.y += PLAYER_GRAVITY;

    // อัปเดตตำแหน่ง
    player->rec.x += player->velocity.x;
    player->rec.y += player->velocity.y;

    // ตรวจสอบการชนกับพื้น
    if (player->rec.y >= GROUND_Y - player->rec.height) {
        player->rec.y = GROUND_Y - player->rec.height;
        player->velocity.y = 0;
        player->isJumping = false;
    }
}

void DrawPlayer(Player player) {
    if (player.texture.id != 0) { // ตรวจสอบว่าภาพโหลดสำเร็จหรือไม่
        float scaleFactor = 1.5f; // ขยายขนาด 1.5 เท่า

        DrawTexturePro(player.texture,
            Rectangle{ 0, 0, (float)player.texture.width, (float)player.texture.height }, // ต้นฉบับ
            Rectangle{ player.rec.x, player.rec.y, player.rec.width, player.rec.height }, // วาดที่ตำแหน่งเดิม
            Vector2{ player.rec.width / 2, player.rec.height / 2 }, // ใช้ origin เดิม
            0.0f, WHITE);
    }
    else {
        DrawRectangleRec(player.rec, RED); // ถ้าโหลดภาพไม่ได้ ให้แสดงกล่องสีแดงแทน
    }
}


void UnloadPlayer(Player* player) {
    UnloadTexture(player->texture);
}
