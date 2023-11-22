// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

class ABaseVehiclePawn;

UCLASS()
class OUTRUNCOPS_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	ABaseVehiclePawn* PlayerVehicle_Inst;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TMap<int32, ABaseVehiclePawn*> PlayerInventory_Inst;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int32 VehicleInt_Inst = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int32 PlayerBasicCurrency_Inst = 26000;


public:

	FORCEINLINE void SetPlayerVehicle_Inst(ABaseVehiclePawn* Vehicle) { PlayerVehicle_Inst = Vehicle; }
	FORCEINLINE ABaseVehiclePawn* GetPlayerVehicle_Inst() { return PlayerVehicle_Inst;}

	FORCEINLINE void SetPlayerInventory_Inst(TMap<int32, ABaseVehiclePawn*> Inventory) { PlayerInventory_Inst = Inventory; }
	FORCEINLINE TMap<int32, ABaseVehiclePawn*> GetPlayerInventory_Inst() { return PlayerInventory_Inst; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetVehicleInt_Inst(int32 CurrentVehicleInt) { VehicleInt_Inst = CurrentVehicleInt; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetVehicleInt_Inst() { return VehicleInt_Inst; }

	FORCEINLINE void SetPlayerBasicCurrency_Inst(int32 BasicCurrency) { PlayerBasicCurrency_Inst = BasicCurrency; }
	FORCEINLINE int32 GetPlayerBasicCurrency_Inst() { return PlayerBasicCurrency_Inst; }


	
};
