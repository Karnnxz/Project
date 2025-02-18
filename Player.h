#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct Player {
    Rectangle rec;
    Vector2 velocity;
    bool isJumping;
    bool isGameOver; // Ensure isGameOver member is included
    Texture2D texture; // Add texture for the player image
} Player;

Player CreatePlayer(float x, float y);
void UpdatePlayer(Player* player);
void DrawPlayer(Player player);
void UnloadPlayer(Player* player); // Add function to unload the texture

#endif // PLAYER_H
