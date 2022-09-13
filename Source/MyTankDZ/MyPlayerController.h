// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyTank.h"
#include "TargetController.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYTANKDZ_API AMyPlayerController : public APlayerController, public ITargetController
{
	GENERATED_BODY()

public:
	
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;
	
	virtual FVector GetTargetLocation() const override
	{
		return WorldMousePosition;
	}
private:
	//Variable
	
	
	
	void OnStartFire();
	
	void OnFireBurst();
	
	void OnStopFire();
	
	void OnShoot();
	
	void OnMoveForward(float Scale);
	
	void OnMoveRight(float Scale);

	void OnRotateRight(float Scale);

	void OnControllerTurretRotation (float Scale);
	
	AMyTank* Tank = nullptr;

	FVector WorldMousePosition;
};
