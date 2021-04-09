#include "raylib.h"
#include "SpriteUtils.h"


Sprite createSprite(Texture2D _tex, Vector2 _pos, Vector2 _frameSize, Vector2 _origin, int _frame, int _maxFrame, int _framesWide) {
    Sprite temp;
    temp.texture = _tex;
    temp.frameSize = _frameSize;
    temp.maxFrame = _maxFrame;
    temp.origin = _origin;
    temp.frame = _frame;
    temp.pos = _pos;

    return temp;

}

void drawSprite(Sprite* sprite, float ang, float scale, bool override, Rectangle c)
{
    Rectangle a = { (float)sprite->texture.width / sprite->maxFrame * (sprite->frame), 0, (float)(sprite->texture.width / sprite->maxFrame), (float)sprite->texture.height };
    Rectangle b;
    b = { sprite->pos.x, sprite->pos.y, sprite->texture.width / sprite->maxFrame * scale, sprite->texture.height * scale };
    if (override) {
        b = c;
    }
    DrawTexturePro(sprite->texture, a, b, Vector2{ 0, 0 }, ang, RAYWHITE);
}

