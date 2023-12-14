// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "VehicleStructs.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class OUTRUNCOPS_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UMySaveGame();

	UPROPERTY(VisibleAnywhere)
	int32 ChosenVehicleInt;

	UPROPERTY(VisibleAnywhere)
	TMap<int32, FInventorySlot> Inventory;

	UPROPERTY(VisibleAnywhere)
	int32 PlayerBasicCurrency;
};
