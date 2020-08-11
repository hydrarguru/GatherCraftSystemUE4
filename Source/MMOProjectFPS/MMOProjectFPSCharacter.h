#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MMOProjectFPSCharacter.generated.h"

class UInputComponent;
class UPlayerInteractionComponent;

UCLASS(config=Game)
class AMMOProjectFPSCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* VR_Gun;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* VR_MuzzleLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* R_MotionController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* L_MotionController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* InteractSphere;
public:
	AMMOProjectFPSCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float PlayerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxPlayerHealth;

	UFUNCTION(BlueprintCallable, Category = "Items")
	void UseItem(class UItem* Item);

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay();

	void CheckForInteractableObjects();


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	UPlayerInteractionComponent* InteractionComponent = nullptr;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AMMOProjectFPSProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint32 bUsingMotionControllers : 1;

protected:
	void OnFire();
	void OnResetVR();
	void MoveForward(float Val);
	void MoveRight(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void InteractPressed();
	void InteractReleased();





	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);
public:
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};

