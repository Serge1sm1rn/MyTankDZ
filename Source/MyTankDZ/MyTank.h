// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "DamageTaker.h"
#include "GrenadeLauncher.h"
#include "HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyTank.generated.h"

UCLASS()
class MYTANKDZ_API AMyTank : public APawn , public IDamageTaker
{
	GENERATED_BODY()

	DECLARE_EVENT(AMyTank, FOnTargetsChanged);

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UBoxComponent* Collision;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UStaticMeshComponent* BodyMesh;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UStaticMeshComponent* TurretMesh;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	USphereComponent* TargetRange;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	USpringArmComponent* Arm;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UCameraComponent* Camera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UArrowComponent* CannonAttachment;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UArrowComponent* GrenadeLauncherAttachment;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UHealthComponent* HealthComponent;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category= Components)
	UParticleSystemComponent* ParticlesEffect;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category= Components)
	UAudioComponent* AudioEffect;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category= Components)
	UParticleSystemComponent* DamageEffect;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category= Components)
	UAudioComponent* DamageAudioEffect;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly,Category= Canon)
	float StopDestroyTime = 0.4;
	
	// Sets default values for this pawn's properties
	AMyTank();
	
	virtual void OnConstruction(const FTransform& Transform) override;

	void FireBurst();
	void Shoot();
	void MoveForward(float Scale);
	void MoveRight(float Scale);
	void RotateRight(float Scale);
	void StartFire();
	void StopFire();
	void ControllerTurretRotation(float Scale);
	



	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= MovementParams)
	float Speed = 500;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= MovementParams)
	float RotationSpeed = 60;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= MovementParams)
	float Acceleration = 0.1f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= MovementParams)
	float TurretRotationSpeed = 0.1f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= MovementParams)
	TSubclassOf<ACannon> CannonClass;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= MovementParams)
	TSubclassOf<AGrenadeLauncher> GrenadeLauncherClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Patrolling);
	FName PatrollingPointTag;

	virtual void PossessedBy(AController* NewController) override;
	

	void SetupCannon(TSubclassOf<ACannon> InCannonClass);

	FOnTargetsChanged OnTargetsChanged;

	int SpawnID = -1;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void TakeDamage(FDamageData Damage) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Destroyed();

	const TArray<TWeakObjectPtr<AActor>>& GetPossibleTargets() const
	{
		return Targets;
	}

private:
	
	void OnDamaged(FDamageData Damage);
	void OnDeath();
	void OnDestroy();

	float MoveForwardScale = 0;
	float MoveRightScale = 0;
	float RotateRightScale = 0;
	float CurrentMoveForwardScale = 0;
	float CurrentRotateRightScale = 0;
	float CurrentMoveRightScale = 0;
	float ControllerTurretRotationScale = 0;
	

	class ITargetController* TankController;

	UFUNCTION()
	void OnTargetRangeBeginOverLap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTargetRangeEndOverLap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY()
	ACannon* Cannon;
	AGrenadeLauncher* GrenadeLauncher;

	FTimerHandle StopDestroy;
	
	TArray<TWeakObjectPtr<AActor>>Targets;
};
