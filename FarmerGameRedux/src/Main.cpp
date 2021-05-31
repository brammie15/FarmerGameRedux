#include "raylib.h"
#include "raymath.h"
#include "GroundTile.h"
#include "SpriteUtils.h"
#include "Inventory.h"
#include "Enums.h"
#include <iostream>

const Rectangle ZERO_REC{ 0,0,0,0 };
const Vector2 ZERO_VEC{ 0,0 };

const Texture2D ItemTex[3];
//enum ItemType { EMPTY = 0, HOE = 1, WHEATSEED = 2 };



int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1600;
	const int screenHeight = 800;
	InitWindow(screenWidth, screenHeight, "Farmer Sim");
#pragma region LoadFunctions
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
	Texture2D WheatSeedTex = LoadTexture("Textures/wheat_seeds.png");
	Texture2D HotBarSlotTex = LoadTexture("Textures/Hotbar.png");
	Texture2D PlantTex[] = { WheatTex };
	Texture2D ItemTex[] = { LoadTexture("Textures/Empty.png"), LoadTexture("Textures/diamond_hoe.png"), LoadTexture("Textures/wheat_seeds.png") };
#pragma endregion

	//make sprites for farmer, the yellow selection box, 
	Sprite Farmer = createSpriteFramed(FarmerTex, Vector2{ 32,screenHeight - (160 * 3) }, Vector2{ 8 ,16 }, Vector2{ 0,0 }, 1 , 2 ,1);
	Sprite SelectionBox = createSprite(SelectionTex, Vector2{ 0, screenHeight - 160 });

	//index for the groundtile selected
	int selectionIndex = 0;
	bool Selecting = false;

	Inventory inv = Inventory(ItemTex);
	inv.inv[0].slotItem = Item(HOE, 1,true);
	inv.inv[1].slotItem = Item(WHEATSEED, 10);

	//The rect for the bg sky
	Rectangle SkyRec = { 0, 0, (float)SkyTex.width, (float)SkyTex.height };
	Rectangle SkyRecScale = { 0, 0, 1600, 800 + 160 };
	//TODO: Improve ground System ALOT
	

	//making the groundtiles
	GroundTile GroundTiles[10];
	for (int a = 0; a < 10; a++) {
		GroundTile tile = GroundTile();
		//setting their pos
		tile.sprite = createSprite(GrassTex, Vector2{ a * (float)160,screenHeight - 160 });
		GroundTiles[a] = tile;
	}
	for (int f = 0; f < 3; f++) {
		//make the hotbar tiles's sprites
		inv.inv[f].HotBarsprite = createSprite(HotBarSlotTex, Vector2{(float)f * 120 + 10, 10});
	}
	inv.inv[0].slotItem = Item(HOE, 69);
	inv.inv[1].slotItem = Item(WHEATSEED, 20);


	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		//Possible TODO: add/implemnt input system (Optional)
		for (int i = 0; i < 10; i++)
		{
			if (GroundTiles[i].hasPlant) {
				GroundTiles[i].currentPlant.Update();
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
		if (IsKeyDown(KEY_B)) {
			inv.GiveItem(Item(WHEATSEED));
		}
		if (IsKeyReleased(KEY_SPACE) && Selecting == true) {
			if (inv.inv[inv.CurrentItemIndex].slotItem.type == WHEATSEED) {
				if (GroundTiles[selectionIndex].hasPlant == false && GroundTiles[selectionIndex].isHoed) {
					GroundTiles[selectionIndex].Plant(Wheat, PlantTex);
					inv.inv[inv.CurrentItemIndex].slotItem.amount--;
				}
			}
			else if (inv.inv[inv.CurrentItemIndex].slotItem.type == HOE) {
				GroundTiles[selectionIndex].Hoe();
			}
		}
		if (IsKeyReleased(KEY_E)) {
			inv.MoveSlot(1);
			//if (inv.CurrentItemIndex != 3) {
			//	inv.CurrentItemIndex++;
			//	inv.inv[inv.CurrentItemIndex] = inv.inv[inv.CurrentItemIndex];
			//	Item c = inv.inv[inv.CurrentItemIndex].slotItem;
			//	//inv.currentItemSprite = createSprite(ItemTex[c.type], Vector2{ 10, 10 });

			//}
			//else {
			//}
		}
		else if (IsKeyReleased(KEY_Q)) {
			inv.MoveSlot(-1);
			//if (inv.CurrentItemIndex != 0) {
			//	inv.CurrentItemIndex--;
			//	inv.inv[inv.CurrentItemIndex] = inv.inv[inv.CurrentItemIndex];
			//	Item c = inv.inv[inv.CurrentItemIndex].slotItem;
			//	//inv.currentItemSprite = createSprite(ItemTex[c.type], Vector2{ 10, 10 });
			//}
		}

		// Draw
		//TODO: SPRITES R LIFE
		BeginDrawing();

		//ClearBackground(RAYWHITE);

		DrawTexturePro(SkyTex, SkyRec, SkyRecScale, Vector2{ 0, 0 }, 0, RAYWHITE);
		//drawSprite(&SelectionBoxItem, 0, 6);
		//drawSprite(&inv.inv[inv.CurrentItemIndex].sprite, 0, 7);
		for (int i = 0; i < 3; i++)
		{
			drawSprite(&inv.inv[i].HotBarsprite, 0, 6);
			drawSprite(&inv.inv[i].slotItem.sprite, 0, 5);
			if (inv.inv[i].slotItem.amount > 1) {
				DrawTextEx(MinecraftFont, TextFormat("%i", inv.inv[i].slotItem.amount), Vector2{ 75.0f + (float)(i * 120.0f),80.0f }, 40, 0, RAYWHITE);
			}

			
		}
		
		drawSprite(&Farmer, 0, 10);
		for (int x = 0; x < 10; x++) {
			GroundTile t = GroundTiles[x];
			drawSprite(&t.sprite, 0, 10);
			drawSprite(&t.currentPlant.sprite, 0, 10);
		}
		if (Selecting) {
			selectionIndex = round(Remap(Farmer.pos.x, 0, screenWidth, 0, 10));
			SelectionBox.pos.x = selectionIndex * 160;
			drawSprite(&SelectionBox, 0, 10);
		}
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	UnloadFont(MinecraftFont);
	UnloadTexture(FarmerTex);
	UnloadTexture(SkyTex);
	UnloadTexture(GrassTex);
	UnloadTexture(SelectionTex);
	UnloadTexture(DirtTex);
	UnloadTexture(WheatTex);
	UnloadTexture(EmptyTex);
	UnloadTexture(BackgroundUITex);
	UnloadTexture(HoeTex);
	UnloadTexture(SelectionTex);
	UnloadTexture(WheatSeedTex);
	UnloadTexture(HotBarSlotTex);
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}