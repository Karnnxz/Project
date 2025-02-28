#include "Player.h"  

#define PLAYER_GRAVITY 0.5f  
#define PLAYER_JUMP_SPEED 14.0f  
#define PLAYER_SPEED 5.0f  
#define GROUND_Y 480

Player::Player(float x, float y) {
    float scaleFactor = 1.5f;
    float originalWidth = 80;
    float originalHeight = 105;

    rec = Rectangle{ x, y - (originalHeight * (scaleFactor - 1)),
                     originalWidth * scaleFactor,
                     originalHeight * scaleFactor };

    velocity = Vector2{ 0, 0 };
    isJumping = false;
    isGameOver = false; // Initialize isGameOver
    scaleX = 1.0f;

    // ตรวจสอบว่าไฟล์ภาพที่โหลดตรงกันหรือไม่
    textures[0] = LoadTexture("../../../../AssetsCompro/Charact/CharLevel01/walk/Player.png");
    textures[1] = LoadTexture("../../../../AssetsCompro/Charact/CharLevel01/walk/01.png");

    currentFrame = 0;
    frameCounter = 0;

    if (textures[0].id == 0 || textures[1].id == 0) {
        TraceLog(LOG_ERROR, "Failed to load player textures!");
    }
}



Player::~Player() {
    Unload();  // ปลดโหลดทรัพยากรเมื่อทำลาย Player
}

void Player::Unload() {
    // ปลดโหลดทรัพยากรภาพที่ใช้
    UnloadTexture(textures[0]);
    UnloadTexture(textures[1]);
}

void Player::Update() {
    float deltaTime = GetFrameTime();  // ใช้ deltaTime เพื่อให้การเคลื่อนที่ลื่นขึ้น

    // อัปเดตความเร็วของตัวละคร (หากกด A หรือ D)
    velocity.x = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * PLAYER_SPEED;

    // ตรวจสอบว่าค่าความเร็วเปลี่ยนแปลงหรือไม่
    TraceLog(LOG_INFO, "Velocity X: %.2f", velocity.x);

    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_ENTER)) && jumpCount < maxJumps) {
        velocity.y = -PLAYER_JUMP_SPEED;
        isJumping = true;
        jumpCount++;  // เพิ่มจำนวนครั้งที่กระโดด
    }

    velocity.y += PLAYER_GRAVITY;

    // อัปเดตตำแหน่งของตัวละคร
    rec.x += velocity.x * deltaTime * 60;  // ใช้ deltaTime ปรับให้ความเร็วสม่ำเสมอ
    rec.y += velocity.y * deltaTime * 60;

    // ตรวจสอบว่าตัวละครอยู่ที่พื้นหรือไม่
    if (rec.y + rec.height >= GROUND_Y) {
        rec.y = GROUND_Y - rec.height;
        velocity.y = 0;
        isJumping = false;
        jumpCount = 0;  // รีเซ็ตจำนวนครั้งที่กระโดด
    }

    // อัปเดตแอนิเมชันเมื่อเคลื่อนที่
    if (velocity.x != 0) {
        frameCounter++;
        if (frameCounter >= 15) {
            currentFrame = (currentFrame + 1) % 2;
            frameCounter = 0;
        }
    }
    else {
        currentFrame = 0;
    }

    // กำหนดทิศทางของตัวละคร (ซ้ายหรือขวา)
    if (velocity.x < 0) {
        scaleX = -1;
    }
    else if (velocity.x > 0) {
        scaleX = 1;
    }
}



void Player::Draw() {
    if (textures[currentFrame].id != 0) {
        Rectangle sourceRec = { 0, 0, scaleX * textures[currentFrame].width, textures[currentFrame].height };
        Rectangle destRec = { rec.x, rec.y, rec.width, rec.height };
        Vector2 origin = { 0, 0 };

        DrawTexturePro(textures[currentFrame], sourceRec, destRec, origin, 0.0f, WHITE);

    }
    else {
        DrawRectangleRec(rec, RED);
    }
}

void Player::SetPosition(float x, float y) {
    rec.x = x;
    rec.y = y;
}


Rectangle Player::GetRec() const {
    float marginX = 10.0f;  // ลดขนาด Hitbox ด้านข้าง
    float marginY = 5.0f;   // ลดขนาด Hitbox ด้านบน-ล่าง
    return { rec.x + marginX, rec.y + marginY, rec.width - 2 * marginX, rec.height - 2 * marginY };
}


bool Player::IsJumping() const {
    return isJumping;
}

void Player::Reset(float x, float y) {
    rec.x = x;
    rec.y = y;
    velocity = Vector2{ 0, 0 };
    isJumping = false;
    currentFrame = 0;
    frameCounter = 0;
    scaleX = 1.0f;
}

void Player::SetGameOver(bool gameOver) {
    isGameOver = gameOver;
}

Vector2 Player::GetVelocity() const {
    return velocity;
}
