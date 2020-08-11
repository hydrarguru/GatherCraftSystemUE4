#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MMOProjectFPS/Inventory/InventoryComponent.h"
#include "InteractableObject.generated.h"

UCLASS()
class MMOPROJECTFPS_API AInteractableObject : public AActor
{
	GENERATED_BODY()

public:
	AInteractableObject();

	UFUNCTION(BlueprintNativeEvent)
	void Interact(APlayerController* Controller);

	virtual void Interact_Implementation(APlayerController* Controller);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString Action;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	FString GetInteractText() const;
};
