#include "MMOProjectFPSController.h"

AMMOProjectFPSController::AMMOProjectFPSController()
{

}

void AMMOProjectFPSController::Interact()
{
	if (CurrentInteractableObject)
	{
		CurrentInteractableObject->Interact(this);
	}
	else if (!CurrentInteractableObject)
	{
		return;
	}
}

void AMMOProjectFPSController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Interact", IE_Pressed, this, &AMMOProjectFPSController::Interact);
}

