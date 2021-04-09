#pragma once
#include "raylib.h"
typedef struct Sprite {
    Texture2D texture;
    Vector2 frameSize;
    Vector2 origin;
    int frame;
    Vector2 pos;
    int maxFrame;
};
Sprite createSprite(Texture2D _tex, Vector2 _pos = Vector2{ 0,0 }, Vector2 _frameSize = Vector2{ 16,16 }, Vector2 _origin = Vector2{ 0,0 }, int _frame = 0, int _maxFrame = 1, int _framesWide = 1);
void drawSprite(Sprite* sprite, float ang, float scale, bool override, Rectangle c = Rectangle{ 0,0,0,0 });