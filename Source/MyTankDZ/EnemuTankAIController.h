// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyTank.h"
#include "TargetController.h"
#include "PatrollingPoint.h"
#include "EnemuTankAIController.generated.h"

 

/**
 * 
 */
UCLASS()
class MYTANKDZ_API AEnemuTankAIController : public AAIController,public ITargetController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Patrolling);
	FName PatrollingPointTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Patrolling);
	float MovementAccuracy = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= MovementParams)
	float Accuracy = 10;
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	virtual FVector GetTargetLocation() const override;

private:
	void FindBestTarget();
	bool CanFire();
	void RebuildMayPoints();
	void OnTargetsChanged();
	
	AMyTank* TankPawn;

	int CurrentWayPointIndex = 0;

	FDelegateHandle TargetChangeDelegateHandle;
	
	TArray<TWeakObjectPtr<APatrollingPoint>> PatrollingPoints;
	TWeakObjectPtr<AActor>CurrentTarget;
	
};
