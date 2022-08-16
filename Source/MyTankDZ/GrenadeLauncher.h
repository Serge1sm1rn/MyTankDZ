// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "GrenadeLauncher.generated.h"

UCLASS()
class MYTANKDZ_API AGrenadeLauncher : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	USceneComponent* DefaultRoot;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UStaticMeshComponent* GrenadeLauncherBody;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UArrowComponent* GrenadeSpawnPoint;

	

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly,Category= Shoots)
	float ReloadTime = 1;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly,Category= Shoots)
	float TimeShoot = 0.1f;
	
	// Sets default values for this actor's properties
	AGrenadeLauncher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void FireBust();


private:
	
	FTimerHandle ReloadTimer;
	
};
