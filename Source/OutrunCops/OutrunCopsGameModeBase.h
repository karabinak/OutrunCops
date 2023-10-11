// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OutrunCopsGameModeBase.generated.h"

class ABaseVehiclePawn;

UCLASS()
class OUTRUNCOPS_API AOutrunCopsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	AOutrunCopsGameModeBase();

protected:
	virtual void BeginPlay() override;

private:

	// Inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TMap<int32, TSubclassOf<ABaseVehiclePawn>> VehicleInventory;

public:

	// Inventory
	UFUNCTION(BlueprintCallable)
	void IsInInventory();

	UFUNCTION(BlueprintCallable)
	void AddToInventory();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TMap<int32, TSubclassOf<ABaseVehiclePawn>> GetVehicleInventory() { return VehicleInventory; }
};
