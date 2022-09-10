// Fill out your copyright notice in the Description page of Project Settings.


#include "TankFactory.h"

// Sets default values
ATankFactory::ATankFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = Collision;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("BodyMesh");
	BodyMesh->SetupAttachment(RootComponent);

	TankSpawnPoint = CreateDefaultSubobject<UArrowComponent>("TankSpawnPoint");
	TankSpawnPoint->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	HealthComponent->OnDamaged.AddUObject(this, &ATankFactory::OnDamaged);
	HealthComponent->OnDeath.AddUObject(this, &ATankFactory::OnDeath);

}

void ATankFactory::TakeDamage(FDamageData Damage)
{
}

// Called when the game starts or when spawned
void ATankFactory::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ATankFactory::OnSpawnTick,SpawnRate,true );
	
}

// Called every frame
void ATankFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATankFactory::OnDamaged(FDamageData Damage)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Purple, FString::Printf(TEXT("Tank health %f"), HealthComponent->CurrentHealth));

}

void ATankFactory::OnDeath()
{
	Destroy();
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
}

void ATankFactory::OnSpawnTick()
{
}

