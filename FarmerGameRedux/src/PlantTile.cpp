#include "raylib.h"
#include "PlantTile.h"

PlantTile::PlantTile(PlantTypes p, Sprite tex) {
	this->type = p;
	this->sprite = tex;
	this->sprite.frame = 6;
	this->nextGrow = GetRandomValue(1, 5);
}
PlantTile::PlantTile() {

}

void PlantTile::Update() {
	if (this->shouldGrow == true) {
		if (this->growStage < 8) {
			if (this->growTime > (this->nextGrow * 60)) {
				this->growTime = 0;
				this->growStage++;
				this->sprite.frame = this->growStage;
				this->nextGrow = GetRandomValue(2, 9);
			}
			this->growTime++;
			//TraceLog(LOG_INFO, TextFormat("%i", this->growStage));
		}
		else {
			this->harvestable = true;
		}
	}
}


