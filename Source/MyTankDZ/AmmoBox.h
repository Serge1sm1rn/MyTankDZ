// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GrenadeLauncher.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoBox.generated.h"

class UBoxComponent;



UCLASS()
class MYTANKDZ_API AAmmoBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoBox();

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UBoxComponent* Collision;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UStaticMeshComponent* BodyMesh;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Weapon)
	int AmmoAmount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Weapon)
	FAmmo AmmoType;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnProjectileBeginOverLap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
