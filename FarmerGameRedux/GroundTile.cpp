#include "raylib.h"
#include "GroundTile.h"

GroundTile::GroundTile() {

}
void GroundTile::SetupRest() {
    //GrassRec = { 0.0f, 0.0f, (float)CurrentTex.width, (float)CurrentTex.height };
    //GrassRecScale = { 0.0f, 0.0f, (float)CurrentTex.width * 10, (float)CurrentTex.height * 10 };

}

void GroundTile::Plant(PlantTypes type, Texture2D tex[]) {
    if (this->HasPlant == true || this->isHoeed == false) {
        return;
    }
    else {
        if (this->isHoeed && this->HasPlant == false) {
            HasPlant = true;
            PlantTile p = PlantTile();
            p.sprite = createSprite(tex[type], Vector2{ 100,100 });
            p.ShouldGrow = true;
            p.sprite.pos.x = this->sprite.pos.x;
            p.sprite.pos.y = this->sprite.pos.y - 160;
            this->CurrentPlant = p;
        }

    }

}

void GroundTile::Hoe() {
    if (this->isHoeed == false) {
        this->isHoeed = true;
        this->sprite.texture = LoadTexture("Textures/dirt.png");
    }
    if (this->isHoeed == true && this->CurrentPlant.Harvestable == true) {
        this->HasPlant = false;
        this->CurrentPlant.sprite.frame = 0;
        this->CurrentPlant.ShouldGrow = false;
    }
}

