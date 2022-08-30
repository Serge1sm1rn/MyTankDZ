// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemuTankAIController.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

void AEnemuTankAIController::OnPossess(APawn* InPawn)
{
  Super::OnPossess(InPawn);
}
 void AEnemuTankAIController::Tick(float DataSeconds)
 {
   Super::Tick(DataSeconds);
 }
 void AEnemuTankAIController::BeginPlay()
 {
	Super::BeginPlay();
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), APatrollingPoint::StaticClass(), PatrollingPointTag, Actors);

	PatrollingPoints.Empty();
	for (auto Actor : Actors)
	{
		PatrollingPoints.Add(CastChecked<APatrollingPoint>(Actor));
		
	}

	PatrollingPoints.Sort([](const APatrollingPoint& A, const APatrollingPoint& B)
	{
		return A.Index > B.Index;
	});

	for (int i = 1; i < PatrollingPoints.Num(); i++)
	{
		DrawDebugLine(GetWorld(), PatrollingPoints[i - 1]->GetActorLocation(), PatrollingPoints[i]->GetActorLocation(),
			FColor::Green, false,20);
	}
 }