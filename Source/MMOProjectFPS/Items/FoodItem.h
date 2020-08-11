#pragma once
#include "CoreMinimal.h"
#include "Item.h"
#include "FoodItem.generated.h"

UCLASS()
class MMOPROJECTFPS_API UFoodItem : public UItem
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items", meta = (ClampMin = 1.0))
	float HealAmount;

protected:
	virtual void UseItem(class AMMOProjectFPSCharacter* Character) override;
	
};
