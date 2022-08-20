// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class MYTANKDZ_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UBoxComponent* Collision;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UStaticMeshComponent* ProjectileMesh;
	
	// Sets default values for this actor's properties
	AProjectile();

	UPROPERTY(BlueprintDefaultOnly, EditAnywhere,Category= Components)
	float MovementSpeed = 800;
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
	void OnBeginOverLap(UPrimitiveComponent*, AActor*, UPrimitiveComponent*, int, bool,const FHitResult&)
	{
		
	}
};
