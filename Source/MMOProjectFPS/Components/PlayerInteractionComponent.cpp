#include "PlayerInteractionComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "MMOProjectFPS/Components/InteractionComponent.h"
#include "MMOProjectFPS/InteractionWidget.h"
#include <DrawDebugHelpers.h>


UPlayerInteractionComponent::UPlayerInteractionComponent()
{
	WidgetClass = UInteractionWidget::StaticClass();
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	APawn* UserPawn = Cast<APawn>(GetOwner());
	APlayerController* PlayerController = Cast<APlayerController>(UserPawn->GetController());

	if (PlayerController && PlayerController->IsLocalController())
	{
		WidgetInstance = CreateWidget<UInteractionWidget>(PlayerController, WidgetClass);
	}
	else
	{
		SetComponentTickEnabled(false);
	}
}

void UPlayerInteractionComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector ViewLocation;
	FRotator ViewRotation;
	GetOwner()->GetActorEyesViewPoint(ViewLocation, ViewRotation);
	DrawDebugLine(GetWorld(), ViewLocation, ViewLocation + ViewRotation.Vector() * InteractionLength, FColor::Green);
	const FVector EndLocation = ViewLocation + ViewRotation.Vector() * InteractionLength;
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(Hit, ViewLocation, EndLocation, ECollisionChannel::ECC_Visibility, Params);

	if (Hit.Actor.IsValid())
	{
		UInteractionComponent* NewInteractable = Hit.Actor->FindComponentByClass<UInteractionComponent>();

		if (NewInteractable != CurrentInteractable)
		{
			if (CurrentInteractable)
			{
				WidgetInstance->OnInteractionNotVisible(CurrentInteractable, GetOwner());
				WidgetInstance->RemoveFromParent();
			}

			if (NewInteractable)
			{
				WidgetInstance->AddToViewport();
				WidgetInstance->OnInteractionVisible(NewInteractable, GetOwner());
			}
			bIsInteracting = false;
		}
		CurrentInteractable = NewInteractable;
	}

	else if (!Hit.Actor.IsValid() && CurrentInteractable)
	{
		if (bIsInteracting)
		{
			StopInteracting();
		}

		WidgetInstance->OnInteractionNotVisible(CurrentInteractable, GetOwner());
		WidgetInstance->RemoveFromParent();
		bIsInteracting = false;
		CurrentInteractable = nullptr;
	}

	if (CurrentInteractable && bIsInteracting)
	{
		CurrentInteractable->OnInteract(GetOwner(), DeltaTime);
		WidgetInstance->OnInteraction(CurrentInteractable, GetOwner());
		if (CurrentInteractable->IsInteractionSuccessful())
		{
			WidgetInstance->OnInteractionSuccess(CurrentInteractable, GetOwner());
			CurrentInteractable->InteractionSuccess(GetOwner());
			bIsInteracting = false;
		}
	}
}

void UPlayerInteractionComponent::StartInteracting()
{
	if (!CurrentInteractable)
	{
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Silver, TEXT("Start interacting"));
	bIsInteracting = true;
	CurrentInteractable->InteractionStarted(GetOwner());
	WidgetInstance->OnInteractionStarted(CurrentInteractable, GetOwner());
}

void UPlayerInteractionComponent::StopInteracting()
{
	if (!CurrentInteractable)
	{
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Silver, TEXT("Stop interacting"));
	bIsInteracting = false;
	CurrentInteractable->InteractionStopped(GetOwner());
	WidgetInstance->OnInteractionStopped(CurrentInteractable, GetOwner());
}



