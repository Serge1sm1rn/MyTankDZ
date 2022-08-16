// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "GrenadeLauncher.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyTank.generated.h"

UCLASS()
class MYTANKDZ_API AMyTank : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UBoxComponent* Collision;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UStaticMeshComponent* BodyMesh;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	USpringArmComponent* Arm;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UCameraComponent* Camera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UArrowComponent* CannonAttachment;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UArrowComponent* GrenadeLauncherAttachment;
	
	// Sets default values for this pawn's properties
	AMyTank();
	
	virtual void OnConstruction(const FTransform& Transform) override;

	void FireBust();
	void Shoot();
	void MoveForward(float Scale);
	void MoveRight(float Scale);
	void RotateRight(float Scale);
	void StartFire();
	void StopFire();



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
	TSubclassOf<ACannon> GrenadeLauncherClass;

	virtual void PossessedBy(AController* NewController) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float MoveForwardScale = 0;
	float MoveRightScale = 0;
	float RotateRightScale = 0;
	float CurrentMoveForwardScale = 0;
	float CurrentRotateRightScale = 0;
	float CurrentMoveRightScale = 0;
	

	class AMyPlayerController* TankController;

	UPROPERTY()
	ACannon* Cannon;
	AGrenadeLauncher* GrenadeLauncher;

};
