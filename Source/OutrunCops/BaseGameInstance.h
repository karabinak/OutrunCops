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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABaseVehiclePawn> CurrentVehicle;

public:

	FORCEINLINE void SetCurrentVehicle(TSubclassOf<ABaseVehiclePawn> Vehicle) { CurrentVehicle = Vehicle; }
	FORCEINLINE TSubclassOf<ABaseVehiclePawn> GetCurrentVehicle() { return CurrentVehicle;}
	
};
