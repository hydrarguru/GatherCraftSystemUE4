#pragma once
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class AActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInteractionStateSignature, class UInteractionComponent*, Interactable, class AActor*, Instigator);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MMOPROJECTFPS_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UInteractionComponent();
	
	virtual void InteractionSuccess(AActor* Instigator);
	virtual void InteractionStarted(AActor* Instigator);
	virtual void InteractionStopped(AActor* Instigator);
	virtual void OnInteract(AActor* Instigator, float DeltaTime);

	UFUNCTION(BlueprintPure, Category = "Interaction")
	bool OnePressActivation() const;

	UFUNCTION(BlueprintPure, Category = "Interaction")
	FORCEINLINE float GetInteractionProgress() const { return InteractionProgress; }

	UFUNCTION(BlueprintPure, Category = "Interaction")
	float GetProgressFraction() const;

	UFUNCTION(BlueprintPure, Category = "Interaction")
	FORCEINLINE bool IsInteractionSuccessful() const { return FMath::IsNearlyEqual(InteractionProgress, InteractionTime); }

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FInteractionStateSignature OnInteractionStarted;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FInteractionStateSignature OnInteractionStopped;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FInteractionStateSignature OnInteractionSuccess;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Setup)
	FText InteractionPrompt;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Setup)
	FText ActorName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Setup)
	FText ActorAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Setup, meta = (ClampMin = 0.0))
	float InteractionTime = 0.0f;

protected:
	float InteractionProgress = 0.0f;
};
