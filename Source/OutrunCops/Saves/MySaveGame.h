// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "OutrunCops/Vehicles/VehicleStructs.h"
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
	int32 PlayerBasicCurrency;

	UPROPERTY(VisibleAnywhere)
	TMap<int32, FInventorySlot> Inventory;

	UPROPERTY(VisibleAnywhere)
	TMap<int32, UMaterial*> PaintsInventory;

	UPROPERTY(VisibleAnywhere)
	TMap<int32, UStaticMesh*> WheelsInventory;


};
