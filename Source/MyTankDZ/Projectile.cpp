// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "DamageTaker.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	RootComponent = Collision;
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnProjectileBeginOverLap);
	

    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	ProjectileMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + GetActorForwardVector() * MovementSpeed * DeltaTime,true);

	if (FVector::DistXY(StartLocation,GetActorLocation()) > FlyDistance)
	{
		Destroy();
	}
}

void AProjectile::OnProjectileBeginOverLap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Other==this || GetInstigator()==Other)
	{
		return;
	}
	if (Other)
	{
		auto Damageble =  Cast<IDamageTaker>(Other);
		
		if (Damageble)
		{
			FDamageData Data;
			Data.DamageMaker = this;
			Data.DamageValue = Damage;
			Data.Instigator = GetInstigator();
			Damageble->TakeDamage(Data);
		}
		else
		{
			Other->Destroy();
		}
		
	}
	Destroy();
}

