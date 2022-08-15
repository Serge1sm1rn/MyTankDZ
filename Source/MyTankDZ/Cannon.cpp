// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>("DefaultRoot");
	RootComponent = DefaultRoot;

	CanonBody = CreateDefaultSubobject<UStaticMeshComponent>("CanonBody");
	CanonBody->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>("ProjectileSpawnPoint");
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
}
//Usualu
void ACannon::Shoot()
{
	if (!IsReadyToShoot)
	{
		return;
	}
	 
		switch (CannonType)
		{
		case ECannonType::Projectile:
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red,
				FString::Printf(TEXT("Shoot")) );
			break;
		case ECannonType::Trace:
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red,
				FString::Printf(TEXT("Trace")) );
			break;
		}
	
	IsReadyToShoot = false;
	GetWorldTimerManager().SetTimer(ReloadTimer,this,&ACannon::OnReload, ReloadTime);
}

void ACannon::StartFire()
{
	
	GetWorldTimerManager().SetTimer(TimeShoots,this,&ACannon::OnShoots, TimeShoot, true);
}

void ACannon::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimeShoots);
}


// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(123, -1, FColor::Red,
				FString::Printf(TEXT("Reload in %f seconds"),GetWorldTimerManager().GetTimerRemaining(ReloadTimer))  );

}

void ACannon::OnReload()
{
	IsReadyToShoot = true;
}
void ACannon::OnShoots()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow,
				FString::Printf(TEXT("Fire")) );
	
}

