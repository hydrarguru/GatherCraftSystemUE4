#pragma once

#include "Engine.h"
#include "InteractableObject.h"
#include "MMOProjectFPS/Items/Item.h"
#include "InteractableActor.generated.h"

UCLASS()
class MMOPROJECTFPS_API AInteractableActor : public AInteractableObject
{
	GENERATED_BODY()

public:
	AInteractableActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	class USoundBase* InteractionSound;

	void Interact_Implementation(APlayerController* Controller) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:

	UFUNCTION(BlueprintCallable)
	void DecreaseNodeHealth();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItem* ResourceItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bResource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxGatheringNodeHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentGatheringNodeHealth;
};
