#include "Item.h"


UItem::UItem()
{
	/*Setup Default Item Values*/
	Weight = 1.f;
	ItemDisplayName = FText::FromString("ItemDefaultName");
	UseActionText = FText::FromString("DefaultActionText");
}

void UItem::UseItem(class AMMOProjectFPSCharacter* Character)
{

}
