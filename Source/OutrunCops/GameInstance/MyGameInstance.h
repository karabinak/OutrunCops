// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OutrunCops/Vehicles/VehicleStructs.h"
#include "MyGameInstance.generated.h"

class ABaseVehiclePawn;

UCLASS()
class OUTRUNCOPS_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	virtual void Init() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UClass* VehicleClassInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TMap<int32, FInventorySlot> InventoryInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int32 VehicleIntInstance = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int32 BasicCurrencyInstance = 50999;


public:
	
	// Getter/Setter

	FORCEINLINE void SetVehicleClassInstance(UClass* Vehicle) { VehicleClassInstance = Vehicle; }
	FORCEINLINE UClass* GetVehicleClassInstance() { return VehicleClassInstance;}

	FORCEINLINE void SetInventoryInstance(TMap<int32, FInventorySlot> Inventory) { InventoryInstance = Inventory; }
	FORCEINLINE TMap<int32, FInventorySlot> GetInventoryInstance() { return InventoryInstance; }

	FORCEINLINE void SetBasicCurrencyInstance(int32 BasicCurrency) { BasicCurrencyInstance = BasicCurrency; }
	FORCEINLINE int32 GetBasicCurrencyInstance() { return BasicCurrencyInstance; }


	UFUNCTION(BlueprintCallable)
	void SetVehicleIntInstance(int32 VehicleInt);
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetVehicleIntInstance() { return VehicleIntInstance; }

	// Public functions

	void CreateSaveFile();
	void SaveGame();
	void LoadGame();


	// TO REMOVE
	UFUNCTION(BlueprintCallable)
	void DeleteSave();

	
};
