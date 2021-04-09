#pragma once
#include "raylib.h"
#include "SpriteUtils.h"
enum PlantTypes { Wheat = 0, potato = 1 };
class PlantTile {
public:
	Sprite sprite;
	int growStage = 1;
	bool Harvestable = false;
	bool ShouldGrow = false;
	PlantTypes type;
	int growTime = 0;
	int nextGrow = 2;
	PlantTile();
	PlantTile(PlantTypes p, Sprite tex);
	void Update();
};
