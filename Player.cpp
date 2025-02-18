#include "Player.h"

#define PLAYER_GRAVITY 0.5f
#define PLAYER_JUMP_SPEED 13.0f
#define PLAYER_SPEED 5.0f
#define GROUND_Y 400

Player CreatePlayer(float x, float y) {
    Player player;

    float scaleFactor = 1.5f;
    float originalWidth = 100;
    float originalHeight = 120;

    player.rec = Rectangle{ x, y - (originalHeight * (scaleFactor - 1)),
                            originalWidth * scaleFactor,
                            originalHeight * scaleFactor };

    player.velocity = Vector2{ 0, 0 };
    player.isJumping = false;
    player.textures[0] = LoadTexture("../../../../OneDrive/Desktop/Coding/Project/Compro/01.png"); // เฟรมแรก
    player.textures[1] = LoadTexture("../../../../OneDrive/Desktop/Coding/Project/Compro/02.png"); // เฟรมที่สอง
    player.currentFrame = 0;
    player.frameCounter = 0;

    if (player.textures[0].id == 0 || player.textures[1].id == 0) {
        TraceLog(LOG_ERROR, "Failed to load player textures!");
    }

    return player;
}

void UpdatePlayer(Player* player) {
    player->velocity.x = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * PLAYER_SPEED;

    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_ENTER)) && !player->isJumping) {
        player->velocity.y = -PLAYER_JUMP_SPEED;
        player->isJumping = true;
    }

    player->velocity.y += PLAYER_GRAVITY;
    player->rec.x += player->velocity.x;
    player->rec.y += player->velocity.y;

    if (player->rec.y + player->rec.height >= GROUND_Y) {
        player->rec.y = GROUND_Y - player->rec.height;
        player->velocity.y = 0;
        player->isJumping = false;
    }

    // อัปเดตแอนิเมชันการเดิน
    if (player->velocity.x != 0) {
        player->frameCounter++;
        if (player->frameCounter >= 15) { // เปลี่ยนภาพทุก 10 เฟรม
            player->currentFrame = (player->currentFrame + 1) % 2;
            player->frameCounter = 0;
        }
    }
    else {
        player->currentFrame = 0; // ถ้าหยุดเดินให้ใช้ภาพแรก
    }
}

void DrawPlayer(Player player) {
    if (player.textures[player.currentFrame].id != 0) {
        DrawTexturePro(player.textures[player.currentFrame],
            Rectangle{ 0, 0, (float)player.textures[player.currentFrame].width, (float)player.textures[player.currentFrame].height },
            player.rec,
            Vector2{ 0, 0 },
            0.0f, WHITE);
    }
    else {
        DrawRectangleRec(player.rec, RED);
    }
}

void UnloadPlayer(Player* player) {
    UnloadTexture(player->textures[0]);
    UnloadTexture(player->textures[1]);
}
