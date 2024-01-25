#pragma once

#include "CoreMinimal.h"
#include "VehicleStructs.generated.h"

class AVehiclePawn;

USTRUCT(BlueprintType)
struct FCustomizations
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* BodyPaint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Wheel;

};

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AVehiclePawn> VehicleClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCustomizations VehicleCustomization;

};