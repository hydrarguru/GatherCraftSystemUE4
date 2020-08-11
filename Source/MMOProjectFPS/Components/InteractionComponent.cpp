#include "InteractionComponent.h"

UInteractionComponent::UInteractionComponent()
{

}

void UInteractionComponent::InteractionSuccess(AActor* Instigator)
{
	OnInteractionSuccess.Broadcast(this, Instigator);
}

void UInteractionComponent::InteractionStarted(AActor* Instigator)
{
	InteractionProgress = 0.0f;
	OnInteractionStarted.Broadcast(this, Instigator);
}

void UInteractionComponent::InteractionStopped(AActor* Instigator)
{
	OnInteractionStopped.Broadcast(this, Instigator);
	InteractionProgress = 0.0f;
}

void UInteractionComponent::OnInteract(AActor* Instigator, float DeltaTime)
{
	InteractionProgress = FMath::Min(InteractionProgress + DeltaTime, InteractionTime);
}

bool UInteractionComponent::OnePressActivation() const
{
	return FMath::IsNearlyZero(InteractionTime);
}

float UInteractionComponent::GetProgressFraction() const
{
	return OnePressActivation() ? 1.0f : InteractionProgress / InteractionTime;
}

