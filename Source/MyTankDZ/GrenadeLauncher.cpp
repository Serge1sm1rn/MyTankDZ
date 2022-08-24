// Fill out your copyright notice in the Description page of Project Settings.


#include "GrenadeLauncher.h"
#include "MyTankDZ.h"
#include "Projectile.h"
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

	void AGrenadeLauncher::DecreaseAmmo()
	{
		CurrentAmmo.Bullets --;
		LogAmmo();

		if (IsClipEmpty() && !IsAmmoEmpty())
		{
			ChangeClip();
		}
	}

	bool AGrenadeLauncher::IsAmmoEmpty() const

	{
		return !CurrentAmmo.infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
	}


	bool AGrenadeLauncher::IsClipEmpty() const
	{
		return CurrentAmmo.Bullets == 0;
	}

	void AGrenadeLauncher::ChangeClip()
	{
	
		CurrentAmmo.Bullets = DefaultAmmo.Bullets;
		if (!CurrentAmmo.infinite)
		{
			CurrentAmmo.Clips --;
		}
		UE_LOG(LogTanks, Display, TEXT("------Change Clip-------"),);
	 
	

	}

	void AGrenadeLauncher::LogAmmo()
	{
		FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + "/ ";
		AmmoInfo += CurrentAmmo.infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
		UE_LOG(LogTanks, Display, TEXT("%s"), *AmmoInfo);
	}


	// Called when the game starts or when spawned
	void AGrenadeLauncher::BeginPlay()
	{
		Super::BeginPlay();

	CurrentAmmo = DefaultAmmo;
	}

	// Called every frame
	void AGrenadeLauncher::Tick(float DeltaTime)
	{
		
	}

	void AGrenadeLauncher::FireBurst()
	{
	
		
		GetWorldTimerManager().SetTimer(TimeShoots,this,&AGrenadeLauncher::OnShoots, TimeShoot);

	}

void AGrenadeLauncher::OnReload()
{
	IsReadyToShoot = true;

}


void AGrenadeLauncher::OnShoots()
{
	if (IsAmmoEmpty())return;
	if (GrenadeClass)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = GetInstigator();
				
		GetWorld()->SpawnActor<AProjectile>(GrenadeClass, GrenadeSpawnPoint->GetComponentTransform(), SpawnParameters);
	}
	
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue,
					FString::Printf(TEXT("FireBurst")) );

	
	
	DecreaseAmmo();
}


