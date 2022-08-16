// Fill out your copyright notice in the Description page of Project Settings.


#include "GrenadeLauncher.h"

#include "Components/ArrowComponent.h"

// Sets default values
AGrenadeLauncher::AGrenadeLauncher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>("DefaultRoot");
	RootComponent = DefaultRoot;

	GrenadeLauncherBody = CreateDefaultSubobject<UStaticMeshComponent>("GrenadeLauncherBody");
	GrenadeLauncherBody->SetupAttachment(RootComponent);

	GrenadeSpawnPoint = CreateDefaultSubobject<UArrowComponent>("GrenadeSpawnPoint");
	GrenadeSpawnPoint->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGrenadeLauncher::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrenadeLauncher::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(12, -1, FColor::Blue,
				FString::Printf(TEXT("Reload in %f seconds"),GetWorldTimerManager().GetTimerRemaining(ReloadTimer))  );

}

void AGrenadeLauncher::FireBust()
{
	
}

