// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageTaker.generated.h"

USTRUCT(BlueprintType)
struct MYTANKDZ_API FDamageData
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DamageValue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	APawn* Instigator;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* DamageMaker;
	
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageTaker : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYTANKDZ_API IDamageTaker
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void TakeDamage(FDamageData Damage) = 0;
};
