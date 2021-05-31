#pragma once
#include "raylib.h"
#include <vector>
#include "Enums.h"
#include "SpriteUtils.h"


#include <map>


//Texture2D ItemTexLocal[] = { LoadTexture("Textures/Empty.png"), LoadTexture("Textures/diamond_hoe.png"), LoadTexture("Textures/wheat_seeds.png") };

//TODO: Make a system to translate the ItemType to a useable sprite altough i hav 0 idea how to do it
//		Was thinking maybe a param to a fucntion but that seems abit sloppy and than even where the inv class doesnt seem to be the best place
class Item {
public:
	bool isUseable;
	ItemType type;
	Sprite sprite;
	int amount;
	Item();
	Item(ItemType type);
	Item(ItemType type, int amount);
	Item(ItemType type, int amount, bool isUseable);
};


class HotbarSlot {
public:
	Item slotItem = Item(EMPTY);
	Sprite HotBarsprite;

	HotbarSlot();

};


class Inventory {
public:
	



	HotbarSlot inv[3];
	int CurrentItemIndex;
	Inventory(Texture2D tex[]);
	void GiveItem(Item item);
	void MoveSlot(int dir);

};





