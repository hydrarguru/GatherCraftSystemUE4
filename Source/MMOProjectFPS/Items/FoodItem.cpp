#include "FoodItem.h"
#include "MMOProjectFPS/Inventory/InventoryComponent.h"
#include "MMOProjectFPS/MMOProjectFPSCharacter.h"


void UFoodItem::UseItem(class AMMOProjectFPSCharacter* Character)
{
	if (Character)
	{
		Character->PlayerHealth += HealAmount;

		if (OwningInventory)
		{
			OwningInventory->RemoveItem(this);
		}
	}
}
