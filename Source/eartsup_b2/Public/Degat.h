// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Degat.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDegat : public UInterface
{
	GENERATED_BODY()
};



/**
 * 
 */
class EARTSUP_B2_API IDegat
{
	GENERATED_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Degat)
	void PrendreDegat(int degat);
};
