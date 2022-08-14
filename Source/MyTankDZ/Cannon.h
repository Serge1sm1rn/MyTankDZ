// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"
UENUM()
enum class ECannonType
{
	Projectile,
	Trace
	
};
UCLASS()
class MYTANKDZ_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	USceneComponent* DefaultRoot;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UStaticMeshComponent* CanonBody;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UArrowComponent* ProjectileSpawnPoint;
	// Sets default values for this actor's properties
	ACannon();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly,Category= Components)
	ECannonType CannonType = ECannonType::Projectile;

	void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
