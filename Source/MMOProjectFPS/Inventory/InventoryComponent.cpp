
#include "InventoryComponent.h"
#include "MMOProjectFPS/Items/Item.h"

UInventoryComponent::UInventoryComponent()
{
	Capacity = 50;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	for (auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
}

bool UInventoryComponent::AddItem(class UItem* Item)
{
	if (Items.Num() >= Capacity || !Item)
	{
		return false;
	}

	Item->OwningInventory = this;
	Item->World = GetWorld();
	Items.Add(Item);


	/*Update UI*/
	OnInventoryUpdated.Broadcast();
	return true;
}

bool UInventoryComponent::RemoveItem(class UItem* Item)
{
	if (Item)
	{
		Item->OwningInventory = this;
		Item->World = nullptr;
		Items.RemoveSingle(Item);
		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}

/*
*	ItemToCraft: IronBar
*	Crafting Components of IronBar: Iron Ore
*	ResourceItem/PlayerItems: Should be iron ore/check if player inventory have an valid crafting component
*/
bool UInventoryComponent::CraftItem(class UItem* ItemToCraft, class UItem* ResourceItem)
{
	//OnInventoryUpdated.Broadcast();
	return true;
}


