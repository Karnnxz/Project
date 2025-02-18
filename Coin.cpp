#include "Coin.h"

Coin CreateCoin(float x, float y) {
    Coin coin = { {x, y, 20, 20}, false };
    return coin;
}

void UpdateCoin(Coin* coin) {
    if (coin->collected) return;
}

void DrawCoin(Coin coin) {
    if (!coin.collected) {
        DrawCircleV(Vector2{ coin.rec.x + coin.rec.width / 2, coin.rec.y + coin.rec.height / 2 }, 10, YELLOW);
    }
}
