#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "raylib.h"

typedef struct Obstacle {
    Rectangle rec;
    bool active;
    Texture2D texture;
    float velocity;  // ความเร็วในการเคลื่อนที่
    bool movingRight; // ใช้บ่งบอกทิศทางการเคลื่อนที่
    float leftBoundary;  // ขอบเขตการเคลื่อนที่ซ้าย
    float rightBoundary; // ขอบเขตการเคลื่อนที่ขวา
} Obstacle;

Obstacle CreateObstacle(float x, float y);
void UpdateObstacle(Obstacle* obstacle);
void DrawObstacle(Obstacle obstacle);

#endif // OBSTACLE_H
