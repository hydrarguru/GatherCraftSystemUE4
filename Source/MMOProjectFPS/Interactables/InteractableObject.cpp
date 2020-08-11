#include "InteractableObject.h"

AInteractableObject::AInteractableObject()
{
	Name = "Interactable";
	Action = "Interact";
}

void AInteractableObject::Interact_Implementation(APlayerController* Controller)
{
	return;
}

FString AInteractableObject::GetInteractText() const
{
	return FString::Printf(TEXT("%s: Press E to %s"), *Name, *Action);
}
