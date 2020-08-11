#pragma once
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

class UInteractionComponent;
class AActor;

UCLASS()
class MMOPROJECTFPS_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void OnInteractionVisible(UInteractionComponent* Interactable, AActor* Instigator);
	virtual void OnInteractionNotVisible(UInteractionComponent* Interactable, AActor* Instigator);
	virtual void OnInteractionStarted(UInteractionComponent* Interactable, AActor* Instigator);
	virtual void OnInteractionStopped(UInteractionComponent* Interactable, AActor* Instigator);
	virtual void OnInteractionSuccess(UInteractionComponent* Interactable, AActor* Instigator);
	virtual void OnInteraction(UInteractionComponent* Interactable, AActor* Instigator);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Interaction Visible"))
	void BP_OnInteractionVisible(UInteractionComponent* Interactable, AActor* Instigator);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Interaction NotVisible"))
	void BP_OnInteractionNotVisible(UInteractionComponent* Interactable, AActor* Instigator);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Interaction Started"))
	void BP_OnInteractionStarted(UInteractionComponent* Interactable, AActor* Instigator);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Interaction Started"))
	void BP_OnInteractionStopped(UInteractionComponent* Interactable, AActor* Instigator);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Interaction Success"))
	void BP_OnInteractionSuccess(UInteractionComponent* Interactable, AActor* Instigator);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Interaction"))
	void BP_OnInteraction(UInteractionComponent* Interactable, AActor* Instigator);
};
