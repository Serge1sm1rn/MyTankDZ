// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Turret.generated.h"


UCLASS()
class MYTANKDZ_API ATurret : public APawn , public IDamageTaker
{
	GENERATED_BODY()
	

public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UBoxComponent* Collision;
        	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UStaticMeshComponent* BodyMesh;
        	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UStaticMeshComponent* TurretMesh;
        
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	USphereComponent* TargetRange;
        
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UArrowComponent* CannonAttachment;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UHealthComponent* HealthComponent;


	
	// Sets default values for this actor's properties
	ATurret();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= MovementParams)
	TSubclassOf<ACannon> CannonClass;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= MovementParams)
	float TurretRotationSpeed = 0.1f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= MovementParams)
	float Accuracy = 10;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void TakeDamage(FDamageData Damage) override;

	virtual void Destroyed();
	
private:

	UFUNCTION()
	void OnTargetRangeBeginOverLap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTargetRangeEndOverLap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void FindBestTarget();

	void Targeting();

	bool CanFire();

	void OnDamaged(FDamageData Damage);

	void OnDeath();
	
	UPROPERTY()
	ACannon* Cannon;

	TArray<TWeakObjectPtr<AActor>>Targets;
	TWeakObjectPtr<AActor>CurrentTarget;

};
