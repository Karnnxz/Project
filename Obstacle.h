#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "raylib.h"
#include "Player.h"

class Obstacle {
public:
    Obstacle(float x, float y);
    void Update();
    void Draw();
    void Unload();
    Rectangle GetRec() const; // Getter for rec
    bool IsMovingRight() const; // Getter for movingRight
    void Reset(float x, float y); // Declaration of Reset method

private:
    Rectangle rec;
    bool active;
    Texture2D texture;
    float velocity;
    bool movingRight;
    float leftBoundary;
    float rightBoundary;
};

#endif // OBSTACLE_H
