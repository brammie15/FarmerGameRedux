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
Sprite createSprite(Texture2D _tex, Vector2 _pos);
Sprite createSpriteFramed(Texture2D _tex, Vector2 _pos, Vector2 _frameSize, Vector2 _origin, int _frame, int _maxFrame, int _framesWide);
void drawSprite(Sprite* sprite, float ang, float scale, Rectangle c);
void drawSprite(Sprite* sprite, float ang, float scale);