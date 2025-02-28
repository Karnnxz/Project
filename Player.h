#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
public:
    Player(float x, float y);
    ~Player();

    void Update();
    void Draw();
    void Unload();
    void SetPosition(float x, float y);
    void Reset(float x, float y); // Declaration of Reset method
    Rectangle GetRec() const; // Getter for rec
    Vector2 GetVelocity() const;
    bool IsJumping() const; // Getter for isJumping
    void SetGameOver(bool gameOver); // Setter for isGameOver

private:
    int jumpCount = 0;
    const int maxJumps = 2; // กระโดดได้สูงสุด 2 ครั้ง (Double Jump)
    Rectangle rec;
    Vector2 velocity;
    bool isJumping;
    bool isGameOver;
    Texture2D textures[2];
    int currentFrame;
    int frameCounter;
    float scaleX;
};

#endif // PLAYER_H
