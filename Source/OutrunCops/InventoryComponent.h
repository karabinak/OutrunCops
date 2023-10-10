#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseVehiclePawn.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OUTRUNCOPS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TMap<int32, TSubclassOf<ABaseVehiclePawn>> VehicleInventory;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE TMap<int32, TSubclassOf<ABaseVehiclePawn>> GetVehicleInventory() { return VehicleInventory; }

		
};
