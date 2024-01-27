#pragma once

#include "CoreMinimal.h"
#include "Outruncops/Vehicles/VehicleStructs.h"
#include "InventoryComponent.generated.h"

class AVehiclePawn;


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TMap<int32, UMaterial*> PaintsInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TMap<int32, UStaticMesh*> WheelsInventory;

public:	
	// VEHICLES INVENTORY //
	FORCEINLINE TMap<int32, FInventorySlot> GetInventory() { return Inventory; }
	FORCEINLINE void SetInventory(TMap<int32, FInventorySlot> NewInventory) { Inventory = NewInventory; }

	UFUNCTION(BlueprintCallable)
	void AddToInventory(int32 Value, FInventorySlot Vehicle);

	UFUNCTION(BlueprintCallable)
	AVehiclePawn* GetFromInventory(int32 Value);

	UFUNCTION(BlueprintCallable)
	bool IsInInventory(int32 Value);

	// WHEELS INVENTORY //
	FORCEINLINE TMap<int32, UStaticMesh*> GetWheelsInventory() { return WheelsInventory; }
	FORCEINLINE void SetWheelsInventory(TMap<int32, UStaticMesh*> NewInventory) { WheelsInventory = NewInventory; }

	UFUNCTION(BlueprintCallable)
	void AddToWheelsInventory(int32 Value, UStaticMesh* Wheel);

	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetFromWheelsInventory(int32 Value);

	UFUNCTION(BlueprintCallable)
	bool IsInWheelsInventory(int32 Value);

	// PAINTS INVENTORY //

	FORCEINLINE TMap<int32, UMaterial*> GetPaintsInventory() { return PaintsInventory; }
	FORCEINLINE void SetPaintsInventory(TMap<int32, UMaterial*> NewInventory) { PaintsInventory = NewInventory; }

	UFUNCTION(BlueprintCallable)
	void AddToPaintsInventoryInventory(int32 Value, UMaterial* Paint);

	UFUNCTION(BlueprintCallable)
	UMaterial* GetFromPaintsInventoryInventory(int32 Value);

	UFUNCTION(BlueprintCallable)
	bool IsInPaintsInventoryInventory(int32 Value);
};
