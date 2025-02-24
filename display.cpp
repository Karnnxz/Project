#include "TextRenderer.h"
#include "raylib.h"

#define GROUND_Y 400
#define GROUND_HEIGHT 50

void TextRenderer::DrawGroundBackground(int screenWidth) {
    DrawRectangle(0, GROUND_Y, screenWidth, GROUND_HEIGHT, DARKGREEN);
}

void TextRenderer::DrawTextCentered(const char* text, int fontSize, Color color, int screenWidth, int screenHeight) {
    int textWidth = MeasureText(text, fontSize);
    int textHeight = fontSize; // Assuming the height of the text is equal to the font size
    int posX = (screenWidth - textWidth) / 2;
    int posY = (screenHeight - textHeight) / 2;
    DrawText(text, posX, posY, fontSize, color);
}


void TextRenderer::DrawScore(int score) {
    DrawText(TextFormat("Score: %d", score), 10, 10, 20, DARKGRAY);
}

void TextRenderer::DrawGameOver(int screenWidth, int screenHeight) {
    Vector2 gameOverTextSize = MeasureTextEx(GetFontDefault(), "Game Over!", 40, 1);
    Vector2 restartTextSize = MeasureTextEx(GetFontDefault(), "Press R to restart", 30, 1);
    float boxWidth = (gameOverTextSize.x > restartTextSize.x) ? gameOverTextSize.x : restartTextSize.x;
    float boxHeight = gameOverTextSize.y + restartTextSize.y + 20;
    Rectangle backgroundRect = Rectangle{
        screenWidth / 2 - boxWidth / 2 - 10,
        screenHeight / 2 - boxHeight / 2 - 10,
        boxWidth + 20,
        boxHeight + 20
    };

    DrawRectangleRec(backgroundRect, WHITE);
    DrawTextEx(GetFontDefault(), "Game Over!", Vector2{ screenWidth / 2 - gameOverTextSize.x / 2, screenHeight / 2 - gameOverTextSize.y / 2 }, 40, 1, RED);
    DrawTextEx(GetFontDefault(), "Press R to restart", Vector2{ screenWidth / 2 - restartTextSize.x / 2, screenHeight / 2 + gameOverTextSize.y / 2 }, 30, 1, RED);
}
