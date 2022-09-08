// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"

#include "DamageTaker.h"
#include "DrawDebugHelpers.h"
#include "MyTankDZ.h"
#include "Projectile.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"

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

	ParticlesEffect = CreateDefaultSubobject<UParticleSystemComponent>("ParticleEffect");
	ParticlesEffect->SetupAttachment(RootComponent);

	AudioEffect = CreateDefaultSubobject<UAudioComponent>("AudioEffect");
	AudioEffect->SetupAttachment(RootComponent);
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
			if (ProjectileClass)
			{
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.Owner = this;
				SpawnParameters.Instigator = GetInstigator();
				
				GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentTransform(), SpawnParameters);

				ParticlesEffect->ActivateSystem();
				AudioEffect->Play();
			}
			
			break;
			
		case ECannonType::Trace:
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red,
				FString::Printf(TEXT("Trace")) );
			
			FHitResult HitResult;
			FCollisionQueryParams Params;
			
			Params.AddIgnoredActor(this);
			Params.AddIgnoredActor(GetInstigator());

			auto Start = ProjectileSpawnPoint->GetComponentLocation();
			auto End = ProjectileSpawnPoint->GetComponentLocation() + ProjectileSpawnPoint ->GetForwardVector() * TraceDistance;
			
			
			if(GetWorld()->LineTraceSingleByChannel(HitResult,
				Start,
				End,
				ECollisionChannel::ECC_Visibility))
			{
				if(HitResult.Actor==this || GetInstigator()==HitResult.Actor)
				{
					return;
				}
				
				auto Damageble =  Cast<IDamageTaker>(HitResult.Actor);
				
				if (Damageble)
				{
					FDamageData Data;
					Data.DamageMaker = this;
					Data.DamageValue = TraceDamage;
					Data.Instigator = GetInstigator();
					Damageble->TakeDamage(Data);
				}
				else
				{
					HitResult.Actor->Destroy();
				}
			}

				DrawDebugLine(GetWorld(), Start, End, FColor::Cyan, false,0.5f);
			break;
		}
	
	IsReadyToShoot = false;
	GetWorldTimerManager().SetTimer(ReloadTimer,this,&ACannon::OnReload, ReloadTime);
	ParticlesEffect->ActivateSystem();
	AudioEffect->Play();
}

//Alternative shooting

void ACannon::StartFire()
{
		GetWorldTimerManager().SetTimer(TimeShoots,this,&ACannon::OnShoots, TimeShoot, true);
	
}

void ACannon::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimeShoots);
}

//SWITCH WEAPON



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
				FString::Printf(TEXT("Reload shoot in %f seconds"),GetWorldTimerManager().GetTimerRemaining(ReloadTimer))  );

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

