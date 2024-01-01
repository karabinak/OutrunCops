#pragma once

#include "CoreMinimal.h"
#include "Outruncops/Vehicles/VehicleStructs.h"
#include "InventoryComponent.generated.h"

class ABaseVehiclePawn;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OUTRUNCOPS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TMap<int32, FInventorySlot> Inventory;

public:	

	FORCEINLINE TMap<int32, FInventorySlot> GetInventory() { return Inventory; }
	FORCEINLINE void SetInventory(TMap<int32, FInventorySlot> NewInventory) { Inventory = NewInventory; }

	UFUNCTION(BlueprintCallable)
	void AddToInventory(int32 Value, FInventorySlot Vehicle);

	UFUNCTION(BlueprintCallable)
	UClass* GetFromInventory(int32 Value);

	UFUNCTION(BlueprintCallable)
	bool IsInInventory(int32 Value);

		
};
