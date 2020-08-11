#pragma once
#include "Engine.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MMOPROJECTFPS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Items")
	bool AddItem(class UItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Items")
	bool RemoveItem(class UItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Items")
	bool CraftItem(class UItem* ItemToCraft, class UItem* ResourceItem);

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "Items")
	TArray<class UItem*> DefaultItems;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 Capacity;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	TArray<class UItem*> Items;

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "Items")
	TArray<class UItem*> CraftableItems;
};
