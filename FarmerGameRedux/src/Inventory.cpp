#include <vector> 
#include "Enums.h"
#include "Inventory.h"


//class Item {
//public:
//	bool isUseable;
//	ItemType type;
//	int amount;
//	Item() : Item(EMPTY) {};
//	Item(ItemType type) : Item(type, 1) {}
//	Item(ItemType type, int amount) : Item(type, amount, true) {}
//	Item(ItemType type, int amount, bool isUseable) {
//		
//	}
//};


Item::Item(ItemType type_ = EMPTY, int amount_ = 1, bool isUseable_ = false)
	: type{ type_ }
	, amount{ amount_ }
	, isUseable{ isUseable_ }
{
	char* n = "";
	if (this->type == WHEATSEED) {
		n = "Textures/wheat_seeds.png";
	}
	else if (this->type == HOE) {
		n = "Textures/diamond_hoe.png";
	}
	else {
		n = "This shouldnt happen ;(";
	}

	//this->sprite = createSprite(LoadTexture(n), Vector2{ 0,0 });
	this->sprite.texture = LoadTexture(n);
}


HotbarSlot::HotbarSlot() {
	//this->sprite = createSprite(LoadTexture("Textures/Hotbar.png"), Vector2{ 0,0 });
	this->slotItem = Item(EMPTY);
	this->slotItem.sprite.pos = Vector2{ this->HotBarsprite.pos.x+ 10, this->HotBarsprite.pos.y + 10 };
}


Inventory::Inventory(Texture2D tex[]) {
	this->CurrentItemIndex = 0;


}

void Inventory::MoveSlot(int dir) {
	this->CurrentItemIndex += dir;
	if (this->CurrentItemIndex < 0) { this->CurrentItemIndex = 0; }
	if (this->CurrentItemIndex > sizeof(this->inv) / sizeof(this->inv[0])) { CurrentItemIndex = sizeof(this->inv) / sizeof(this->inv[0]); }
}

void Inventory::GiveItem(Item item) {
	int recievedItemsAmount = item.amount;

	for (int i = 0; i < 3; i++)
	{
		if (this->inv[i].slotItem.type == item.type) {
			this->inv[i].slotItem.amount += recievedItemsAmount;
			return;
		}
	}

}

