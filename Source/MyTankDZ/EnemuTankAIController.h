// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyTank.h"
#include "PatrollingPoint.h"
#include "EnemuTankAIController.generated.h"

 

/**
 * 
 */
UCLASS()
class MYTANKDZ_API AEnemuTankAIController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Patrolling);
	FName PatrollingPointTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Patrolling);
	float MovementAccuracy = 10;
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

private:
	void RebuildMayPoints();
	
	AMyTank* TankPawn;

	int CurrentWayPointIndex = 0;
	
	TArray<TWeakObjectPtr<APatrollingPoint>> PatrollingPoints;
	
};
