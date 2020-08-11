#include "InteractableActor.h"
#include "MMOProjectFPS/MMOProjectFPSController.h"
#include "Components/StaticMeshComponent.h"

AInteractableActor::AInteractableActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	MaxGatheringNodeHealth = 100;
	bResource = false;
	Super::Name = "Name";
	Super::Action = "Action";
}

void AInteractableActor::BeginPlay()
{
	CurrentGatheringNodeHealth = MaxGatheringNodeHealth;
}

void AInteractableActor::Tick(float DeltaTime)
{

}

void AInteractableActor::DecreaseNodeHealth()
{
	int RandomDamage = FMath::FRandRange(10, 75);
	CurrentGatheringNodeHealth -= RandomDamage;
}

void AInteractableActor::Interact_Implementation(APlayerController* Controller)
{
	Super::Interact_Implementation(Controller);
	AMMOProjectFPSController* IController = Cast<AMMOProjectFPSController>(Controller);
	if (bResource)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::FString("bResource = true"));
		if (InteractionSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, InteractionSound, GetActorLocation());
		}
		DecreaseNodeHealth();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::FString("Not a gathering node"));
	}
}
