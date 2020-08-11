#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MMOProjectFPS/Interactables/InteractableObject.h"
#include "MMOProjectFPSController.generated.h"

UCLASS()
class MMOPROJECTFPS_API AMMOProjectFPSController : public APlayerController
{
	GENERATED_BODY()

public:
	AMMOProjectFPSController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AInteractableObject* CurrentInteractableObject;

protected:
	void Interact();
	virtual void SetupInputComponent() override;
};
