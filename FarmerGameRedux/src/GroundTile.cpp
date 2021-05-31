#include "raylib.h"
#include "GroundTile.h"

GroundTile::GroundTile() {

}
void GroundTile::SetupRest() {
    //GrassRec = { 0.0f, 0.0f, (float)CurrentTex.width, (float)CurrentTex.height };
    //GrassRecScale = { 0.0f, 0.0f, (float)CurrentTex.width * 10, (float)CurrentTex.height * 10 };

}

void GroundTile::Plant(PlantTypes type, Texture2D tex[]) {
    if (this->hasPlant == true || this->isHoed == false) {
        return;
    }
    else {
        if (this->isHoed && this->hasPlant == false) {
            hasPlant = true;
            PlantTile p = PlantTile();
            p.sprite = createSpriteFramed(tex[type], Vector2{ 100,100 }, Vector2{ 16,16 }, Vector2{ 0,0 },0,8,1);
            p.shouldGrow = true;
            p.sprite.pos.x = this->sprite.pos.x;
            p.sprite.pos.y = this->sprite.pos.y - 160;
            this->currentPlant = p;
        }

    }

}

void GroundTile::Hoe() {
    if (this->isHoed == false) {
        this->isHoed = true;
        this->sprite.texture = LoadTexture("Textures/dirt.png");
    }
    if (this->isHoed == true && this->currentPlant.harvestable == true) {
        this->hasPlant = false;
        this->currentPlant.sprite.frame = 0;
        this->currentPlant.shouldGrow = false;
    }
}

