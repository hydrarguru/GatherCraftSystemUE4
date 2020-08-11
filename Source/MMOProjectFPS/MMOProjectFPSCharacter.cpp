// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MMOProjectFPSCharacter.h"
#include "MMOProjectFPSProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h"

#include "MMOProjectFPS/Interactables/InteractableObject.h"
#include "MMOProjectFPS/MMOProjectFPSController.h"
#include "MMOProjectFPS/Items/Item.h"
#include "MMOProjectFPS/Inventory/InventoryComponent.h"
#include "Components/SphereComponent.h"
#include "MMOProjectFPS/Components/PlayerInteractionComponent.h"



DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);
AMMOProjectFPSCharacter::AMMOProjectFPSCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);

	VR_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VR_Gun"));
	VR_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	VR_Gun->bCastDynamicShadow = false;
	VR_Gun->CastShadow = false;
	VR_Gun->SetupAttachment(R_MotionController);
	VR_Gun->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	VR_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("VR_MuzzleLocation"));
	VR_MuzzleLocation->SetupAttachment(VR_Gun);
	VR_MuzzleLocation->SetRelativeLocation(FVector(0.000004, 53.999992, 10.000000));
	VR_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));		// Counteract the rotation of the VR gun model.


	//Interact Sphere
	InteractSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Interact Sphere"));
	InteractSphere->SetupAttachment(RootComponent);
	InteractSphere->SetSphereRadius(200.f);

	//Inventory
	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Inventory->Capacity = 50;

	/*Player Health*/
	MaxPlayerHealth = 0.f;

	//Player Interaction Component
	InteractionComponent = CreateDefaultSubobject<UPlayerInteractionComponent>(TEXT("PInteractionComponent"));
}

void AMMOProjectFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerHealth = MaxPlayerHealth;

	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	if (bUsingMotionControllers)
	{
		VR_Gun->SetHiddenInGame(false, true);
		Mesh1P->SetHiddenInGame(true, true);
	}
	else
	{
		VR_Gun->SetHiddenInGame(true, true);
		Mesh1P->SetHiddenInGame(false, true);
	}
}

void AMMOProjectFPSCharacter::UseItem(class UItem* Item)
{
	if (Item)
	{
		Item->UseItem(this);
		Item->BP_OnUseItem(this);
	}
}

void AMMOProjectFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckForInteractableObjects();
}

void AMMOProjectFPSCharacter::CheckForInteractableObjects()
{
	FHitResult HitResult;

	int32 Range = 1000;
	FVector StartTrace = FirstPersonCameraComponent->GetComponentLocation();
	FVector EndTrace = (FirstPersonCameraComponent->GetForwardVector() * Range) + StartTrace;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	AMMOProjectFPSController* IController = Cast<AMMOProjectFPSController>(GetController());

	if (IController)
	{
		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, QueryParams))
		{
			AInteractableObject* InteractableObject = Cast<AInteractableObject>(HitResult.GetActor());
			if (InteractableObject)
			{
				IController->CurrentInteractableObject = InteractableObject;
				return;
			}
		}
		IController->CurrentInteractableObject = nullptr;
	}
}

void AMMOProjectFPSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMMOProjectFPSCharacter::OnFire);
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AMMOProjectFPSCharacter::OnResetVR);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMMOProjectFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMMOProjectFPSCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMMOProjectFPSCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMMOProjectFPSCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("N_Interact", IE_Pressed, this, &AMMOProjectFPSCharacter::InteractPressed);
	PlayerInputComponent->BindAction("N_Interact", IE_Released, this, &AMMOProjectFPSCharacter::InteractReleased);

	EnableTouchscreenMovement(PlayerInputComponent);
}

void AMMOProjectFPSCharacter::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			if (bUsingMotionControllers)
			{
				const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
				const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
				World->SpawnActor<AMMOProjectFPSProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
			}
			else
			{
				const FRotator SpawnRotation = GetControlRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// spawn the projectile at the muzzle
				World->SpawnActor<AMMOProjectFPSProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void AMMOProjectFPSCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMMOProjectFPSCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AMMOProjectFPSCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

void AMMOProjectFPSCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMMOProjectFPSCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMMOProjectFPSCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMMOProjectFPSCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMMOProjectFPSCharacter::InteractPressed()
{
	InteractionComponent->StartInteracting();
}

void AMMOProjectFPSCharacter::InteractReleased()
{
	InteractionComponent->StopInteracting();
}

bool AMMOProjectFPSCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMMOProjectFPSCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AMMOProjectFPSCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMMOProjectFPSCharacter::TouchUpdate);
		return true;
	}
	
	return false;
}
