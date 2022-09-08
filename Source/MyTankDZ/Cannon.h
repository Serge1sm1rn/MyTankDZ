// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "Projectile.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"
UENUM()
enum class ECannonType
{
	Projectile,
	Trace
	
};

USTRUCT(BlueprintType)
struct FAmmoData
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

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category= Components)
	UParticleSystemComponent* ParticlesEffect;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category= Components)
	UAudioComponent* AudioEffect;
	
	// Sets default values for this actor's properties
	ACannon();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly,Category= Canon)
	ECannonType CannonType = ECannonType::Projectile;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly,Category= Canon)
	float ReloadTime = 1;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly,Category= Canon)
	float TimeShoot = 0.1f;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly,Category= Canon)
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly,Category= Canon)
	float TraceDistance = 1000;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly,Category= Canon)
	float TraceDamage = 1;
	//Variable
	
	 void Shoot();
	 void StartFire();
	 void StopFire();
	

protected:
	//Assigning parameters ammo
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= "Weapon")
	FAmmoData DefaultAmmo{10,10,false};

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

private:

	//Variable
	void OnReload();
	
	bool IsReadyToShoot = true;
	
	void OnShoots();
	
	//Timers
	FTimerHandle TimeShoots;
	
	FTimerHandle ReloadTimer;

	//Struct
	FAmmoData CurrentAmmo;
};
