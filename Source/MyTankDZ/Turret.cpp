// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "MyTank.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = Collision;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("BodyMesh");
	BodyMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("TurretMesh");
	TurretMesh->SetupAttachment(BodyMesh);

	CannonAttachment = CreateDefaultSubobject<UArrowComponent>("CannonAttachment");
	CannonAttachment->SetupAttachment(TurretMesh);

	TargetRange = CreateDefaultSubobject<USphereComponent>("TargetRange");
	TargetRange->SetupAttachment(Collision);
	TargetRange->OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnTargetRangeBeginOverLap);
	TargetRange->OnComponentEndOverlap.AddDynamic(this, &ATurret::OnTargetRangeEndOverLap);

}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	if (CannonClass)
	{
		FActorSpawnParameters SpawnParameters;
        	SpawnParameters.Owner = this;
        	SpawnParameters.Instigator = this;
        	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, SpawnParameters);
        	Cannon->AttachToComponent(CannonAttachment, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
	
	
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Targeting();

	if (Cannon && CanFire())
	{
		Cannon->Shoot();
	}
}

void ATurret::Targeting()
{
	if (!CurrentTarget.IsValid())
	{
		return;
	}
	auto Rotation =  UKismetMathLibrary::FindLookAtRotation(TurretMesh->GetComponentLocation(),CurrentTarget->GetActorLocation());
	auto CurrentRotation = TurretMesh->GetComponentRotation();
	Rotation.Pitch = CurrentRotation.Pitch;
	Rotation.Roll = CurrentRotation.Roll;
	CurrentRotation = FMath::Lerp(CurrentRotation, Rotation, TurretRotationSpeed);
	TurretMesh->SetWorldRotation(CurrentRotation);
}

bool ATurret::CanFire()
{
	if (!CurrentTarget.IsValid())
	{
		return false;
	}
	auto Rotation =  UKismetMathLibrary::FindLookAtRotation(TurretMesh->GetComponentLocation(),CurrentTarget->GetActorLocation());
	auto CurrentRotation = TurretMesh->GetComponentRotation();
	
	if (FMath::Abs(Rotation.Yaw - CurrentRotation.Yaw) <= Accuracy)
	{
		return true;
	}
	return false;
}

void ATurret::OnTargetRangeBeginOverLap(UPrimitiveComponent* OverlappedComp, AActor* Other,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Other == this || Other == GetInstigator()|| Other ==nullptr)
	{
		return;
	}
	if (!Other->IsA<AMyTank>())
	{
		return;
	}
	Targets.Add(Other);
	FindBestTarget();

}

void ATurret::OnTargetRangeEndOverLap(UPrimitiveComponent* OverlappedComp, AActor* Other,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Other == this || Other == GetInstigator())
	{
		return;
	}
	if (!Other->IsA<AMyTank>())
	{
		return;
	}
	Targets.Remove(Other);
	if (Other == CurrentTarget)
	{
		FindBestTarget();
	}
}

void ATurret::FindBestTarget()
{
	float MinDistance = 100000000;
	auto Location = GetActorLocation();
	AActor* NewTarget = nullptr;
	for (auto Target : Targets)
	{
		if (Target.IsValid())
		{
			auto Distance = FVector::DistXY(Location, Target->GetActorLocation());
			
			if(Distance < MinDistance)
			{
				MinDistance = Distance;
				NewTarget = Target.Get();
			}
		}
	}
	CurrentTarget = NewTarget;
}



