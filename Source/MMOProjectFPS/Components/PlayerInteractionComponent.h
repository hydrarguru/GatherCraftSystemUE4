#pragma once

#include "Engine.h"
#include "Components/ActorComponent.h"
#include "PlayerInteractionComponent.generated.h"

class UInteractionComponent;
class AActor;
class UInteractionWidget;

UCLASS()
class MMOPROJECTFPS_API UPlayerInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UPlayerInteractionComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartInteracting();
	void StopInteracting();

	UFUNCTION(BlueprintPure, Category = "Interaction")
	FORCEINLINE bool IsInteracting() const { return bIsInteracting; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionLength = 200.0f;

	UPROPERTY(Transient)
	UInteractionComponent* CurrentInteractable = nullptr;

	UPROPERTY(EditAnywhere, NoClear, Category = Setup)
	TSubclassOf<UInteractionWidget> WidgetClass;

	UPROPERTY(Transient)
	UInteractionWidget* WidgetInstance = nullptr;

	bool bIsInteracting = false;
};
