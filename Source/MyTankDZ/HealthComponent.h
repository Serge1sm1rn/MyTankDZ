// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageTaker.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYTANKDZ_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
	
	DECLARE_EVENT(UHealthComponent, FOnDeath);
	DECLARE_EVENT_OneParam(UHealthComponent, FOnDamaged, FDamageData);
	
public:
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly,Category= Health)
	float MaxHealth = 10;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= Health)
	float CurrentHealth;
	
	// Sets default values for this component's properties
	UHealthComponent();
	
	void TakeDamage(FDamageData Damage);

	FOnDeath OnDeath;
	FOnDamaged OnDamaged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
