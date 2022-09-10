// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
#include "MyTank.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "TankFactory.generated.h"

UCLASS()
class MYTANKDZ_API ATankFactory : public AActor, public IDamageTaker
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UBoxComponent* Collision;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UArrowComponent* TankSpawnPoint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UHealthComponent* HealthComponent;
	
	// Sets default values for this actor's properties
	ATankFactory();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly,Category= "Tank Factory")
	TSubclassOf<AMyTank> MyTankClass;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly,Category= "Tank Factory")
	float SpawnRate = 1;

	virtual void TakeDamage(FDamageData Damage) override;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void OnDamaged(FDamageData Damage);
	void OnDeath();
	void OnSpawnTick();
	
	FTimerHandle SpawnTimer;
};
