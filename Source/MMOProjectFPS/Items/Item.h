#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class MMOPROJECTFPS_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UItem();

	virtual class UWorld* GetWorld() const { return World; };

	UPROPERTY(Transient)
	class UWorld* World;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
	FText UseActionText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
	class UTexture2D* ItemThumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
	FText ItemDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Items")
	TArray<class UItem*> CraftingComponents;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items", meta = (ClampMin = 0.0))
	float Weight;

	UPROPERTY()
	class UInventoryComponent* OwningInventory; /*Player Inventory, Chests, Bank system*/

	virtual void UseItem(class AMMOProjectFPSCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnUseItem(class AMMOProjectFPSCharacter* Character);
};
