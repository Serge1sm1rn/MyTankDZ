// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyTank.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYTANKDZ_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	FVector GetWorldMousePosition() const
	{
		return  WorldMousePosition;
	}
private:
	void OnStartFire();
	
	void OnFireBurst();
	
	void OnStopFire();
	
	void OnShoot();
	
	void OnMoveForward(float Scale);
	
	void OnMoveRight(float Scale);

	void OnRotateRight(float Scale);
	
	AMyTank* Tank = nullptr;

	FVector WorldMousePosition;
};
