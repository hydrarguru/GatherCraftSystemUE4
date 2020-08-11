#pragma once
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "MMOProjectFPS/Items/Item.h"
#include "GatheringNode.generated.h"

class UStaticMeshComponent;
class UInteractionComponent;

UCLASS()
class MMOPROJECTFPS_API AGatheringNode : public AActor
{
	GENERATED_BODY()
	
public:	
	AGatheringNode();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Harvest();

	UFUNCTION(BlueprintCallable)
	void DecreaseNodeHealth();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
	class USoundBase* InteractionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
	bool bResource;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(VisibleDefaultsOnly, Category = Interaction)
	UInteractionComponent* Interaction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
	UItem* ResourceItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxGatheringNodeHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentGatheringNodeHealth;
};
