// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"



void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent ->BindAction("Shoot", EInputEvent::IE_Pressed,this, &AMyPlayerController::OnShoot);
	InputComponent ->BindAxis("MoveForward", this, &AMyPlayerController::OnMoveForward);
	InputComponent ->BindAxis("RotateRight", this, &AMyPlayerController::OnRotateRight);
	InputComponent ->BindAxis("MoveRight", this, &AMyPlayerController::OnMoveRight);
	InputComponent ->BindAction("Fire",IE_Pressed, this, &AMyPlayerController::OnStartFire);
	InputComponent ->BindAction("Fire",IE_Released, this, &AMyPlayerController::OnStopFire);
	InputComponent ->BindAction("FiringBursts",IE_Pressed, this, &AMyPlayerController::OnFireBurst);
	InputComponent ->BindAction("SwitchWeapon", EInputEvent::IE_Pressed,this, &AMyPlayerController::OnSwitchWeapon);
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
		WorldMousePosition = MousePosition-MouseDirection * Z / MouseDirection.Z;
	}
	
}

void AMyPlayerController::OnSwitchWeapon()
{
	if (Tank)
	{
		Tank->SwitchWeapon();
	}
}

void AMyPlayerController::OnStartFire()
{
	if (Tank)
	{
		Tank->StartFire();
	}
}

void AMyPlayerController::OnFireBurst()
{
	if (Tank)
	{
		Tank->FireBurst();
	}
	
}

void AMyPlayerController::OnStopFire()
{
	if (Tank)
	{
		Tank->StopFire();
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
