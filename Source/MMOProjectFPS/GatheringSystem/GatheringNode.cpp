#include "GatheringNode.h"
#include "Components/StaticMeshComponent.h"
#include "MMOProjectFPS/Components/InteractionComponent.h"

AGatheringNode::AGatheringNode()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Interaction = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction"));
}

void AGatheringNode::BeginPlay()
{
	Super::BeginPlay();
	CurrentGatheringNodeHealth = MaxGatheringNodeHealth;
}

void AGatheringNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGatheringNode::DecreaseNodeHealth()
{
	//TODO: Make this depending the power of a tool.
	//instead of hardcoded values
	int RandomDamage = FMath::FRandRange(10, 75);
	CurrentGatheringNodeHealth -= RandomDamage;
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::FromInt(RandomDamage));
}

void AGatheringNode::Harvest()
{
	if (bResource)
	{
		if (InteractionSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, InteractionSound, GetActorLocation());
		}
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::FString("Harvest()"));
		DecreaseNodeHealth();
	}
}
