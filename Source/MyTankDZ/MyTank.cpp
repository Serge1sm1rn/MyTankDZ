// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTank.h"
#include "DrawDebugHelpers.h"
#include "GrenadeLauncher.h"
#include "TargetController.h"
#include "Components/AudioComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystemComponent.h"

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

	CannonAttachment = CreateDefaultSubobject<UArrowComponent>("CannonAttachment");
	CannonAttachment->SetupAttachment(TurretMesh);
	
	GrenadeLauncherAttachment = CreateDefaultSubobject<UArrowComponent>("GrenadeLauncherAttachment");
	GrenadeLauncherAttachment->SetupAttachment(TurretMesh);

	ParticlesEffect = CreateDefaultSubobject<UParticleSystemComponent>("ParticleEffect");
	ParticlesEffect->SetupAttachment(RootComponent);

	AudioEffect = CreateDefaultSubobject<UAudioComponent>("AudioEffect");
	AudioEffect->SetupAttachment(RootComponent);

	DamageEffect = CreateDefaultSubobject<UParticleSystemComponent>("DamageEffect");
	DamageEffect->SetupAttachment(RootComponent);

	DamageAudioEffect = CreateDefaultSubobject<UAudioComponent>("DamageAudioEffect");
	DamageAudioEffect->SetupAttachment(RootComponent);

	Arm = CreateDefaultSubobject<USpringArmComponent>("Arm");
	Arm->SetupAttachment(RootComponent);
	Arm->bInheritPitch = false;
	Arm->bInheritRoll = false;
	Arm->bInheritYaw = false;
	Arm->bDoCollisionTest = false;
	Arm->TargetArmLength = 800;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(Arm);

	TargetRange = CreateDefaultSubobject<USphereComponent>("TargetRange");
	TargetRange->SetupAttachment(Collision);
	TargetRange->OnComponentBeginOverlap.AddDynamic(this, &AMyTank::OnTargetRangeBeginOverLap);
	TargetRange->OnComponentEndOverlap.AddDynamic(this, &AMyTank::OnTargetRangeEndOverLap);
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	HealthComponent->OnDamaged.AddUObject(this, &AMyTank::OnDamaged);
	HealthComponent->OnDeath.AddUObject(this, &AMyTank::OnDeath);
	
}

void AMyTank::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Cyan, FString::Printf(TEXT("Tank Spawned %d"), SpawnID));
}

void AMyTank::StartFire()
{
	if (Cannon)
	{
		Cannon->StartFire();
	}
}

void AMyTank::StopFire()
{
	if (Cannon)
	{
		Cannon->StopFire();
	}
}

void AMyTank::FireBurst()
{
	if (GrenadeLauncher)
	{
		GrenadeLauncher->FireBurst();
	}
}

void AMyTank::Shoot()
{
	if (Cannon)
	{
		Cannon->Shoot();
	}
}

void AMyTank::MoveForward(float Scale)
{
	MoveForwardScale = Scale;
}

void AMyTank::MoveRight(float Scale)
{
	MoveRightScale = Scale;
}

void AMyTank::RotateRight(float Scale)
{
	RotateRightScale = Scale;
}

void AMyTank::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	TankController = Cast<ITargetController>(NewController);
}

void AMyTank::ControllerTurretRotation(float Scale)
{
	ControllerTurretRotationScale = Scale;
}

// Called when the game starts or when spawned
void AMyTank::BeginPlay()
{
	Super::BeginPlay();
	SetupCannon(CannonClass);

	if(GrenadeLauncher)
	{
		GrenadeLauncher->Destroy();
		GrenadeLauncher = nullptr;
	}
	
	if (GrenadeLauncherClass)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = GetInstigator();
		
		GrenadeLauncher = GetWorld()->SpawnActor<AGrenadeLauncher>(GrenadeLauncherClass, SpawnParameters);
		GrenadeLauncher->AttachToComponent(GrenadeLauncherAttachment, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}
void AMyTank::SetupCannon(TSubclassOf<ACannon> InCannonClass)
{
		if(Cannon)
		{
			Cannon->Destroy();
			Cannon = nullptr;
		}
		if (InCannonClass)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;
			SpawnParameters.Instigator = this;
			Cannon = GetWorld()->SpawnActor<ACannon>(InCannonClass, SpawnParameters);
			Cannon->AttachToComponent(CannonAttachment, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
}

/*void AMyTank::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}*/

// Called every frame
void AMyTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Logs
	//UE_LOG(LogTanks,Warning,TEXT("Acceleration %f"), CurrentMoveForwardScale);
	
	//MoveForward
	
	CurrentMoveForwardScale = FMath::Lerp(CurrentMoveForwardScale, MoveForwardScale, Acceleration);

	auto Location = GetActorLocation();
	auto NewLocation = Location + GetActorForwardVector() * CurrentMoveForwardScale * Speed * DeltaTime;
	SetActorLocation(NewLocation, true);
	
	//MoveRight
	
	CurrentMoveRightScale = FMath::Lerp(CurrentMoveRightScale, MoveRightScale, Acceleration);

	auto CurrentLocation = GetActorLocation();
	auto NewCurrentLocation = CurrentLocation + GetActorRightVector() * CurrentMoveRightScale * Speed * DeltaTime;
	SetActorLocation(NewCurrentLocation, true);
	
	//Rotation
	
	CurrentRotateRightScale = FMath::Lerp(CurrentRotateRightScale, RotateRightScale, Acceleration);
	
	auto Rotation = GetActorRotation();
	Rotation.Yaw = Rotation.Yaw + RotationSpeed * CurrentRotateRightScale * DeltaTime;
	SetActorRotation(Rotation);

	
	//Controller rotation
	if (ControllerTurretRotationScale != 0)
	{
		ControllerTurretRotationScale = FMath::Lerp(ControllerTurretRotationScale, RotateRightScale, Acceleration);
        	
        	auto ControllerTurretRotation = TurretMesh->GetComponentRotation();
        	ControllerTurretRotation.Yaw = ControllerTurretRotation.Yaw + RotationSpeed * ControllerTurretRotationScale * DeltaTime;
        	TurretMesh->SetWorldRotation(ControllerTurretRotation);
	}
	else
	{
		auto MousePosition = TankController->GetTargetLocation();
		
		auto TurretRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),MousePosition );
		auto CurrentTurretRotation = TurretMesh->GetComponentRotation();
		TurretRotation.Pitch = CurrentTurretRotation.Pitch;
		TurretRotation.Roll = CurrentTurretRotation.Roll;
		CurrentTurretRotation = FMath::Lerp(CurrentTurretRotation, TurretRotation, TurretRotationSpeed);
		TurretMesh->SetWorldRotation(CurrentTurretRotation);

		DrawDebugLine(GetWorld(),
		CannonAttachment->GetComponentLocation(),
		CannonAttachment->GetComponentLocation() + CannonAttachment->GetForwardVector() * 100, FColor::Green,
		false,-1,0,5);

		DrawDebugLine(GetWorld(),
		GrenadeLauncherAttachment->GetComponentLocation(),
		GrenadeLauncherAttachment->GetComponentLocation() + GrenadeLauncherAttachment->GetForwardVector() * 1000, FColor::Yellow,
		false,-1,0,5);
	}
}

// Called to bind functionality to input
void AMyTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AMyTank::Destroyed()
{
	if (Cannon)
	{
		Cannon->Destroy();
		auto PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController)
		{
			UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController,EQuitPreference::Quit,false);
		}
	}
	if (GrenadeLauncher)
     	{
     		GrenadeLauncher->Destroy();
     	}
}

void AMyTank::TakeDamage(FDamageData Damage)
{
	HealthComponent->TakeDamage(Damage);

	DamageEffect->ActivateSystem();
	DamageAudioEffect->Play();
}
void AMyTank::OnDamaged(FDamageData Damage)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT("Tank health %f"), HealthComponent->CurrentHealth));
}

void AMyTank::OnDeath()
{
	ParticlesEffect->ActivateSystem();
 	AudioEffect->Play();

	GetWorldTimerManager().SetTimer(StopDestroy,this,&AMyTank::OnDestroy, StopDestroyTime);
	
}

void AMyTank::OnDestroy()
{
	Destroy();
}

void AMyTank::OnTargetRangeBeginOverLap(UPrimitiveComponent* OverlappedComp, AActor* Other,
										UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Other == this || Other == GetInstigator()|| Other ==nullptr)
	{
		return;
	}
	
	auto OtherTank = Cast<AMyTank>(Other);
	if (OtherTank)
	{
		Targets.Add(OtherTank);
		OnTargetsChanged.Broadcast();
	}
	
}

void AMyTank::OnTargetRangeEndOverLap(UPrimitiveComponent* OverlappedComp, AActor* Other,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Other == this || Other == GetInstigator())
	{
		return;
	}
	
	auto OtherTank = Cast<AMyTank>(Other);
	if (OtherTank)
	{
		Targets.Add(OtherTank);
		OnTargetsChanged.Broadcast();
	}
	
}

