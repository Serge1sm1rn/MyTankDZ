// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "GrenadeLauncher.generated.h"

USTRUCT(BlueprintType)
struct FAmmo
{
	GENERATED_BODY()
	//Count ammo
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= "Weapon")
	int32 Bullets;

	//Clip count
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= "Weapon")
	int32 Clips;
	
	//Endless ammo or not
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= "Weapon")
	bool infinite;
};

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

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly,Category= Shoots)
	int NumShoot = 3;
	
	// Sets default values for this actor's properties
	AGrenadeLauncher();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= "Weapon")
	FAmmo DefaultAmmo{10,10,false};
	
	void DecreaseAmmo();
	bool IsAmmoEmpty() const;
	bool IsClipEmpty() const;
	void ChangeClip();
	void LogAmmo();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void FireBurst();


private:
	void OnShoots();
	FTimerHandle TimeShoots;
	FTimerHandle ReloadTimer;

	FAmmo CurrentAmmo;
};
