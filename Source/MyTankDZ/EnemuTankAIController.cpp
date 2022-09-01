// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemuTankAIController.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

void AEnemuTankAIController::OnPossess(APawn* InPawn)
{
  Super::OnPossess(InPawn);
}
 void AEnemuTankAIController::Tick(float DeltaSeconds)
 {
   Super::Tick(DeltaSeconds);
 }
 void AEnemuTankAIController::BeginPlay()
 {
	Super::BeginPlay();
	PatrollingPoints.Empty();
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), APatrollingPoint::StaticClass(), PatrollingPointTag, Actors);

	TArray<APatrollingPoint*> Points;
	
	for (auto Actor : Actors)
	{
		Points.Add(CastChecked<APatrollingPoint>(Actor));
	}

	Points.Sort([](const APatrollingPoint& A, const APatrollingPoint& B)
	{
		return A.Index > B.Index;
	});

	for (auto Actor : Points)
	{
		PatrollingPoints.Add(Actor);
	}
	
	for (int i = 1; i < PatrollingPoints.Num(); i++)
	{
		DrawDebugLine(GetWorld(),
			PatrollingPoints[i - 1]->GetActorLocation() + FVector(0,0,20),
			PatrollingPoints[i]->GetActorLocation() + FVector(0,0,20),
			FColor::Green, false,20);
	}
	if (PatrollingPoints.Num() > 1)
	{
		DrawDebugLine(GetWorld(),
			PatrollingPoints[0]->GetActorLocation() + FVector(0,0,20),
			PatrollingPoints[PatrollingPoints.Num() - 1]->GetActorLocation() + FVector(0,0,20),
			FColor::Green, false,20);
	}
 }