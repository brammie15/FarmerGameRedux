#pragma once
#include "raylib.h"
#include "SpriteUtils.h"
#include "PlantTile.h"
class GroundTile {
public:
    Sprite sprite;
    PlantTile CurrentPlant;
    bool HasPlant = false;
    bool isHoeed = false;
    void SetupRest();
    void Plant(PlantTypes type, Texture2D tex[]);
    void Hoe();
    GroundTile();


};
