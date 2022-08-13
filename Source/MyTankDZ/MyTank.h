// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
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
	
	// Sets default values for this pawn's properties
	AMyTank();
	
	virtual void OnConstruction(const FTransform& Transform) override;

	void Shoot();
	void MoveForward(float Scale);
	void MoveRight(float Scale);
	void RotateRight(float Scale);


	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= MovementParams)
	float Speed = 500;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= MovementParams)
	float RotationSpeed = 1;

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

};
