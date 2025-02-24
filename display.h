#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "raylib.h"

class TextRenderer {
public:
    void DrawTextCentered(const char* text, int fontSize, Color color, int screenWidth, int screenHeight);
    void DrawScore(int score);
    void DrawGameOver(int screenWidth, int screenHeight);
    void DrawGroundBackground(int screenWidth); // Add this line
};


#endif // TEXTRENDERER_H
