#pragma once
#include "raylib.h"
#include "SpriteUtils.h"
#include "PlantTile.h"
class GroundTile {
public:
    Sprite sprite;
    PlantTile currentPlant;
    bool hasPlant = false;
    bool isHoed = false;
    void SetupRest();
    void Plant(PlantTypes type, Texture2D tex[]);
    void Hoe();
    GroundTile();


};
