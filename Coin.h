#ifndef COIN_H
#define COIN_H

#include "raylib.h"

class Coin {
public:
    Coin(float x, float y);
    void Update();
    void Draw();
    bool IsCollected() const;
    void Collect();
    Rectangle GetRec() const;
    void Reset();
    void SetPosition(float x, float y); 

private:
    Rectangle rec;
    bool collected;
    float initialY;
    float oscillationSpeed;
    float oscillationAmplitude; // Add this line
};

#endif // COIN_H
