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
	UClass* PlayerVehicle_Inst;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TMap<int32, FInventorySlot> PlayerInventory_Inst;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int32 VehicleInt_Inst = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int32 PlayerBasicCurrency_Inst = 50999;


public:

	FORCEINLINE void SetPlayerVehicle_Inst(UClass* Vehicle) { PlayerVehicle_Inst = Vehicle; }
	FORCEINLINE UClass* GetPlayerVehicle_Inst() { return PlayerVehicle_Inst;}

	FORCEINLINE void SetPlayerInventory_Inst(TMap<int32, FInventorySlot> Inventory) { PlayerInventory_Inst = Inventory; }
	FORCEINLINE TMap<int32, FInventorySlot> GetPlayerInventory_Inst() { return PlayerInventory_Inst; }

	UFUNCTION(BlueprintCallable)
	void SetVehicleInt_Inst(int32 CurrentVehicleInt);
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetVehicleInt_Inst() { return VehicleInt_Inst; }

	FORCEINLINE void SetPlayerBasicCurrency_Inst(int32 BasicCurrency) { PlayerBasicCurrency_Inst = BasicCurrency; }
	FORCEINLINE int32 GetPlayerBasicCurrency_Inst() { return PlayerBasicCurrency_Inst; }

	
	void CreateSaveFile();

	void SaveGame();

	void LoadGame();


	// TO REMOVE
	UFUNCTION(BlueprintCallable)
	void DeleteSave();

	
};
