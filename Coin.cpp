#include <cmath> // Add this line to include the cmath header
#include "Coin.h"

Coin::Coin(float x, float y) : rec{ x, y, 20, 20 }, collected(false), initialY(y), oscillationSpeed(2.0f), oscillationAmplitude(10.0f) {} // Increase oscillationAmplitude to 10.0f

void Coin::Update() {
    if (!collected) {
        // Oscillation logic
        rec.y = initialY + oscillationAmplitude * sin(GetTime() * oscillationSpeed);
    }
}

void Coin::Draw() {
    if (!collected) {
        DrawCircle(rec.x + rec.width / 2, rec.y + rec.height / 2, rec.width / 2, GOLD);
    }
}

bool Coin::IsCollected() const {
    return collected;
}

void Coin::Collect() {
    collected = true;
}

Rectangle Coin::GetRec() const {
    return rec;
}

void Coin::Reset() {
    collected = false;
    rec.y = initialY; // Reset the y-position to the initial value
}

void Coin::SetPosition(float x, float y) { // Add this method
    rec.x = x;
    rec.y = y;
}
