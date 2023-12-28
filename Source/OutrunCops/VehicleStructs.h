#pragma once

#include "CoreMinimal.h"
#include "BaseVehiclePawn.h"
#include "VehicleStructs.generated.h"

USTRUCT(BlueprintType)
struct FCustomizations
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* BodyPaint;

};

USTRUCT(BlueprintType)
struct FUpgrades
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxTorque;

};

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseVehiclePawn> VehicleClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCustomizations VehicleCustomization;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUpgrades VehicleUpgrades;

};