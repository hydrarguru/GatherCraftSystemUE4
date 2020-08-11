#include "InteractionWidget.h"

void UInteractionWidget::OnInteractionVisible(UInteractionComponent* Interactable, AActor* Instigator)
{
	BP_OnInteractionVisible(Interactable, Instigator);
}

void UInteractionWidget::OnInteractionNotVisible(UInteractionComponent* Interactable, AActor* Instigator)
{
	BP_OnInteractionNotVisible(Interactable, Instigator);
}

void UInteractionWidget::OnInteractionStarted(UInteractionComponent* Interactable, AActor* Instigator)
{
	BP_OnInteractionStarted(Interactable, Instigator);

}

void UInteractionWidget::OnInteractionStopped(UInteractionComponent* Interactable, AActor* Instigator)
{
	BP_OnInteractionStopped(Interactable, Instigator);
}

void UInteractionWidget::OnInteractionSuccess(UInteractionComponent* Interactable, AActor* Instigator)
{
	BP_OnInteractionSuccess(Interactable, Instigator);
}

void UInteractionWidget::OnInteraction(UInteractionComponent* Interactable, AActor* Instigator)
{
	BP_OnInteraction(Interactable, Instigator);
}
