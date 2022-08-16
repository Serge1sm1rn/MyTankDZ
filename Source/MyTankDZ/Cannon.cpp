// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"

#include "MyTankDZ.h"

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
//Shooting
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
//Alternative shooting
void ACannon::StartFire()
{
	if (IsAmmoEmpty())return;
	
		GetWorldTimerManager().SetTimer(TimeShoots,this,&ACannon::OnShoots, TimeShoot, true);

		
	
	
}

void ACannon::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimeShoots);
}

void ACannon::DecreaseAmmo()
{
	CurrentAmmo.Bullets --;
	LogAmmo();

	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		ChangeClip();
	}
}

bool ACannon::IsAmmoEmpty() const
{
	return !CurrentAmmo.infinite && CurrentAmmo.Clips == 0 &&IsClipEmpty();
}

bool ACannon::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

void ACannon::ChangeClip()
{
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	if (!CurrentAmmo.infinite)
	{
		CurrentAmmo.Clips --;
	}
	UE_LOG(LogTanks, Display, TEXT("------Change Clip-------"), );
}

void ACannon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + "/ ";
	AmmoInfo += CurrentAmmo.infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogTanks, Display, TEXT("%s"), *AmmoInfo);
}


// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentAmmo = DefaultAmmo;
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
	if (IsAmmoEmpty())return;
	
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow,
				FString::Printf(TEXT("Fire")) );
	
	DecreaseAmmo();
}

