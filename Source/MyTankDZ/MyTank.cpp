// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTank.h"

// Sets default values
AMyTank::AMyTank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = Collision;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("BodyMesh");
	BodyMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("TurretMesh");
	TurretMesh->SetupAttachment(BodyMesh);

	Arm = CreateDefaultSubobject<USpringArmComponent>("Arm");
	Arm->SetupAttachment(RootComponent);
	Arm->bInheritPitch = false;
	Arm->bInheritRoll = false;
	Arm->bInheritYaw = false;
	Arm->TargetArmLength = 800;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(Arm);
	
}

void AMyTank::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMyTank::Shoot()
{
}

void AMyTank::MoveForward(float Scale)
{
	MoveForwardScale = Scale;
}

void AMyTank::MoveRight(float Scale)
{
	MoveRightScale = Scale;
}


// Called when the game starts or when spawned
void AMyTank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto Location = GetActorLocation();
	auto NewLocation = Location + GetActorForwardVector() * MoveForwardScale * Speed * DeltaTime;
	SetActorLocation(NewLocation, true);

	auto CurrentLocation = GetActorLocation();
	auto NewCurrentLocation = CurrentLocation + GetActorRightVector() * MoveRightScale * Speed * DeltaTime;
	SetActorLocation(NewCurrentLocation, true);
}

// Called to bind functionality to input
void AMyTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

