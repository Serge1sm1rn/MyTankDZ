// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class MYTANKDZ_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	USphereComponent* Collision;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UStaticMeshComponent* ProjectileMesh;
	
	// Sets default values for this actor's properties
	AProjectile();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly,Category= Components)
	float MovementSpeed = 800;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly,Category= Components)
	float FlyDistance = 2000;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly,Category= Components)
	float Damage = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	
	FVector StartLocation;
	
	UFUNCTION()
	void OnProjectileBeginOverLap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};