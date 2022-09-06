// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemuTankAIController.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void AEnemuTankAIController::OnPossess(APawn* InPawn)
{
  Super::OnPossess(InPawn);
  if (TankPawn)
  {
  	TankPawn->OnTargetsChanged.Remove(TargetChangeDelegateHandle);
  }
	TankPawn = Cast<AMyTank>(InPawn);
  if (TankPawn)
  {
	 PatrollingPointTag = TankPawn -> PatrollingPointTag;
  	RebuildMayPoints();

  	TankPawn->OnTargetsChanged.AddUObject(this, &AEnemuTankAIController::OnTargetsChanged);
  }
}
 void AEnemuTankAIController::Tick(float DeltaSeconds)
 {
   Super::Tick(DeltaSeconds);

   if (!TankPawn || PatrollingPoints.Num() < 2)
   {
	   return;
   }
   if (CurrentWayPointIndex >= PatrollingPoints.Num() || PatrollingPoints.Num() < 0)
   {
	   CurrentWayPointIndex = 0;
   }
	
	TankPawn->MoveForward(1);

	auto Point = PatrollingPoints[CurrentWayPointIndex];
	auto PointLocation = Point->GetActorLocation();
	auto Location = TankPawn->GetActorLocation();

	auto MovementDirection = PointLocation - Location;
	MovementDirection.Normalize();

	auto ForwardAngle = FMath::RadiansToDegrees( FMath::Acos(FVector::DotProduct(TankPawn->GetActorForwardVector(), MovementDirection)));
	auto RightAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(TankPawn->GetActorRightVector(), MovementDirection)));
	float RotationValue = 0;

	if (ForwardAngle > 5) RotationValue = 1;
	if (RightAngle > 90) RotationValue = -RotationValue;
   if (ForwardAngle > 45 )
   {
	   TankPawn->MoveForward(0);
   }
   else
   {
   	TankPawn->MoveForward(1);
   }

	TankPawn-> RotateRight(RotationValue);
	
   if (FVector::Dist2D(PointLocation,Location) < MovementAccuracy)
   {
	   CurrentWayPointIndex++;
   }

   if (CanFire())
   {
	   TankPawn->Shoot();
   }
	
 }
 void AEnemuTankAIController::BeginPlay()
 {
	Super::BeginPlay();
	RebuildMayPoints();
 }

void AEnemuTankAIController::RebuildMayPoints()
{
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

void AEnemuTankAIController::OnTargetsChanged()
{
	FindBestTarget();
	
}
void AEnemuTankAIController::FindBestTarget()
{
	if (!TankPawn)
	{
		return;
	}
	float MinDistance = 100000000;
	auto Location = TankPawn->GetActorLocation();
	AActor* NewTarget = nullptr;
	for (auto Target : TankPawn-> GetPossibleTargets())
	{
		if (Target.IsValid())
		{
			auto Distance = FVector::DistXY(Location, Target->GetActorLocation());
			
			if(Distance < MinDistance)
			{
				MinDistance = Distance;
				NewTarget = Target.Get();
			}
		}
	}
	CurrentTarget = NewTarget;
}
bool AEnemuTankAIController::CanFire()
{
	if (!CurrentTarget.IsValid() ||!TankPawn)
	{
		return false;
	}
	auto Rotation =  UKismetMathLibrary::FindLookAtRotation( TankPawn->TurretMesh->GetComponentLocation(),CurrentTarget->GetActorLocation());
	auto CurrentRotation = TankPawn->TurretMesh->GetComponentRotation();
	
	if (FMath::Abs(Rotation.Yaw - CurrentRotation.Yaw) <= Accuracy)
	{
		return true;
	}
	return false;
}

FVector AEnemuTankAIController::GetTargetLocation() const
{
	if (CurrentTarget.IsValid())
	{
		return CurrentTarget->GetActorLocation();
	}
	if(TankPawn)
	return TankPawn-> GetActorLocation() + TankPawn->GetActorForwardVector() * 1000;
	return FVector::ZeroVector;
}
