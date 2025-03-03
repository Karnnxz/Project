#include <cmath> // Add this line to include the cmath header
#include "Coin.h"

Coin::Coin(float x, float y) : rec{ x, y, 20, 20 }, collected(false), initialY(y), oscillationSpeed(2.0f), oscillationAmplitude(10.0f) {} // Increase oscillationAmplitude to 10.0f

void Coin::Update() {
    if (!collected) {
        // Oscillation logic
        rec.y = initialY + oscillationAmplitude * sin(GetTime() * oscillationSpeed);
    }
}

void Coin::Draw(Texture2D texture) {
    if (!collected) {
        Vector2 position = { rec.x, rec.y }; // Define the position variable
        TraceLog(LOG_INFO, "Drawing coin at (%f, %f)", position.x, position.y);
        DrawTextureRec(texture, { 0, 0, (float)texture.width, (float)texture.height }, position, WHITE);
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
