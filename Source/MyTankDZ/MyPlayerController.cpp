// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "DrawDebugHelpers.h"

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent ->BindAction("Shoot", EInputEvent::IE_Pressed,this, &AMyPlayerController::OnShoot);
	InputComponent ->BindAxis("MoveForward", this, &AMyPlayerController::OnMoveForward);
	InputComponent ->BindAxis("RotateRight", this, &AMyPlayerController::OnRotateRight);
	InputComponent ->BindAxis("MoveRight", this, &AMyPlayerController::OnMoveRight);
	
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Tank = Cast<AMyTank>(InPawn);
	
}

void AMyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (Tank)
	{
		FVector MousePosition;
		FVector MouseDirection;
	
		DeprojectMousePositionToWorld(MousePosition,MouseDirection);

		auto Z = FMath::Abs(Tank->GetActorLocation().Z - MousePosition.Z);
		WorldMousePosition = MousePosition+MouseDirection * Z / MouseDirection.Z;
	}
	
}

void AMyPlayerController::OnShoot()
{
	if (Tank)
	{
		Tank->Shoot();
	}
}

void AMyPlayerController::OnMoveForward(float Scale)
{
	if (Tank)
	{
		Tank->MoveForward(Scale);
	}
}
void AMyPlayerController::OnMoveRight(float Scale)
{
	if (Tank)
	{
		Tank->MoveRight(Scale);
	}
}

void AMyPlayerController::OnRotateRight(float Scale)
{
	if (Tank)
	{
		Tank->RotateRight(Scale);
	}
}
