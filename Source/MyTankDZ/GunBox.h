// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GunBox.generated.h"


UCLASS()
class MYTANKDZ_API AGunBox : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UBoxComponent* Collision;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	UStaticMeshComponent* BodyMesh;
	// Sets default values for this actor's properties
	AGunBox();

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Components)
	TAssetSubclassOf<ACannon> CannonClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	
	UFUNCTION()
	void OnProjectileBeginOverLap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	


};
