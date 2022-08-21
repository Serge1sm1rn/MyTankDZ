// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBox.h"
#include "MyTank.h"

// Sets default values
AGunBox::AGunBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = Collision;
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AGunBox::OnProjectileBeginOverLap);


	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("BodyMesh");
	BodyMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGunBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AGunBox::OnProjectileBeginOverLap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Tank = Cast<AMyTank>(Other);
	if (Tank)
	{
		Tank->SetupCannon(CannonClass.Get());
	}
}

