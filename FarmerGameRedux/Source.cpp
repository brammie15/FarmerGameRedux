#include "raylib.h"
#include "raymath.h"
#include "GroundTile.h"
#include "SpriteUtils.h"
#include <vector> 
#include <iostream>

const Rectangle ZERO_REC{ 0,0,0,0 };
const Vector2 ZERO_VEC{ 0,0 };
enum ItemType { empty = 0, hoe = 1, wheatSeed = 2 };
class Item {
public:
	bool IsUseable;
	ItemType type;
	int amount;
	Item() {};
	Item(bool isUseable, ItemType type, int amount) {
		this->IsUseable = isUseable;
		this->type = type;
		this->amount = amount;
	}
};
class Inventory {
public:
	std::vector<Item> inv;
	//Item inv[3];
	Item CurrentItem;
	int CurrentItemIndex = 0;
	Sprite CurrentItemSprite = createSprite(LoadTexture("Textures/diamond_hoe.png"), Vector2{ 10,10 });
	Inventory() {
	}
};


int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1600;
	const int screenHeight = 800;
	InitWindow(screenWidth, screenHeight, "Farmer Sim");

	Font MinecraftFont = LoadFontEx("Textures/Minecraft.otf", 128, 0, 256);
	Texture2D FarmerTex = LoadTexture("Textures/Farmer.png");
	Texture2D SkyTex = LoadTexture("Textures/sky.png");
	Texture2D GrassTex = LoadTexture("Textures/Grass.png");
	Texture2D SelectionTex = LoadTexture("Textures/Selection.png");
	Texture2D DirtTex = LoadTexture("Textures/dirt.png");
	Texture2D WheatTex = LoadTexture("Textures/Wheat.png");
	Texture2D EmptyTex = LoadTexture("Textures/Empty.png");
	Texture2D BackgroundUITex = LoadTexture("Textures/background.png");
	Texture2D HoeTex = LoadTexture("Textures/diamond_hoe.png");
	Texture2D SelectionBoxTex = LoadTexture("Textures/SelectionBox.png");
	Texture2D WheatSeedTex = LoadTexture("Textures/wheat_seeds.png");
	Texture2D PlantTex[] = { WheatTex };
	Texture2D ItemTex[] = { EmptyTex, HoeTex, WheatSeedTex };

	//Sprite Farmer = createSprite(FarmerTex, Vector2{ 32, 32 }, 2, 1, Vector2{ 0, 0 }, 0, );
	Sprite SelectionBox = createSprite(SelectionTex, Vector2{ 0, screenHeight - 160 });
	Sprite SelectionBoxItem = createSprite(SelectionBoxTex, Vector2{ 0, 0 }, Vector2{ 22,22 });

	Sprite Farmer = createSprite(FarmerTex, Vector2{ 0, screenHeight - (160 * 3) }, Vector2{ 32,32 }, Vector2{ 0,0 }, 1, 2, 1);
	int selectionIndex = 0;
	bool Selecting = false;

	Inventory inv = Inventory();
	for (int i = 0; i < 3; i++)
	{
		inv.inv.push_back(Item(false, empty, 1));
	}
	//inv.inv.push_back(Item(true, hoe, 1));
	//inv.inv.push_back(Item(false, wheatSeed, 10));
	inv.CurrentItem = inv.inv[0];

	Rectangle SkyRec = { 0, 0, (float)SkyTex.width, (float)SkyTex.height };
	Rectangle SkyRecScale = { 0, 0, 1600, 800 + 160 };
	//TODO: Improve ground System ALOT
	GroundTile GroundTiles[10];
	for (int a = 0; a < 10; a++) {
		GroundTile tile = GroundTile();
		tile.sprite = createSprite(GrassTex, Vector2{ a * (float)160,screenHeight - 160 });
		GroundTiles[a] = tile;
	}

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		//Possible TODO: add/implemnt input system (Optional)
		for (int i = 0; i < 10; i++)
		{
			if (GroundTiles[i].HasPlant) {
				GroundTiles[i].CurrentPlant.Update();
			}
		}
		if (IsKeyDown(KEY_D)) {
			if (Farmer.pos.x < screenWidth - 160) {
				if (IsKeyDown(KEY_LEFT_SHIFT)) {
					Farmer.pos.x += 6.0f;
				}
				else {
					Farmer.pos.x += 4.0f;
				}
			}
			Farmer.frame = 0;
		}
		if (IsKeyDown(KEY_A)) {
			if (Farmer.pos.x > 0) {
				if (IsKeyDown(KEY_LEFT_SHIFT)) {
					Farmer.pos.x -= 6.0f;
				}
				else {
					Farmer.pos.x -= 4.0f;
				}
			}
			Farmer.frame = 1;
		}
		if (IsKeyDown(KEY_S)) {
			Selecting = true;
		}
		else {
			Selecting = false;
		}
		if (IsKeyReleased(KEY_SPACE) && Selecting == true) {
			if (inv.CurrentItem.type == wheatSeed) {
				if (GroundTiles[selectionIndex].HasPlant == false && GroundTiles[selectionIndex].isHoeed) {
					GroundTiles[selectionIndex].Plant(Wheat, PlantTex);
					inv.CurrentItem.amount--;
				}
			}
			else if (inv.CurrentItem.type == hoe) {
				GroundTiles[selectionIndex].Hoe();
			}
		}
		if (IsKeyReleased(KEY_E)) {
			if (inv.CurrentItemIndex != inv.inv.size()) {
				inv.CurrentItemIndex++;
				inv.CurrentItem = inv.inv[inv.CurrentItemIndex];
				Item c = inv.CurrentItem;
				inv.CurrentItemSprite = createSprite(ItemTex[c.type], Vector2{ 10, 10 });

			}
			else {
			}
		}
		else if (IsKeyReleased(KEY_Q)) {
			if (inv.CurrentItemIndex != 0) {
				inv.CurrentItemIndex--;
				inv.CurrentItem = inv.inv[inv.CurrentItemIndex];
				Item c = inv.CurrentItem;
				inv.CurrentItemSprite = createSprite(ItemTex[c.type], Vector2{ 10, 10 });
			}
			else {

			}
		}

		// Draw
		//TODO: SPRITES R LIFE
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTexturePro(SkyTex, SkyRec, SkyRecScale, Vector2{ 0, 0 }, 0, RAYWHITE);
		drawSprite(&SelectionBoxItem, 0, 6, false);
		drawSprite(&inv.CurrentItemSprite, 0, 7, false);
		if (inv.CurrentItem.amount > 1) {
			//DrawText(TextFormat("%i", inv.CurrentItem.amount), 100, 90, 35, RAYWHITE);
			DrawTextEx(MinecraftFont, TextFormat("%i", inv.CurrentItem.amount), Vector2{ 100.0f,90.0f }, 40, 0, RAYWHITE);
		}
		drawSprite(&Farmer, 0, 10, false);
		for (int x = 0; x < 10; x++) {
			GroundTile t = GroundTiles[x];
			drawSprite(&t.sprite, 0, 10, false);
			drawSprite(&t.CurrentPlant.sprite, 0, 10, false);
		}
		if (Selecting) {
			selectionIndex = round(Remap(Farmer.pos.x, 0, screenWidth, 0, 10));
			SelectionBox.pos.x = selectionIndex * 160;
			drawSprite(&SelectionBox, 0, 10, false);
		}
		//DrawFPS(10, 10);
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	UnloadTexture(SelectionTex);
	UnloadTexture(SkyTex);
	UnloadTexture(GrassTex);
	UnloadTexture(FarmerTex);
	UnloadTexture(DirtTex);
	UnloadTexture(EmptyTex);
	UnloadTexture(HoeTex);
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}