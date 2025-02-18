#ifndef COIN_H
#define COIN_H

#include "raylib.h"

typedef struct Coin {
    Rectangle rec;
    bool collected;
} Coin;

Coin CreateCoin(float x, float y);
void UpdateCoin(Coin* coin);
void DrawCoin(Coin coin);

#endif // COIN_H
