// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Turret.generated.h"


UCLASS()
class MYTANKDZ_API ATurret : public APawn
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
        	
	// Sets default values for this actor's properties
	ATurret();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= MovementParams)
	TSubclassOf<ACannon> CannonClass;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY()
	ACannon* Cannon;
};
