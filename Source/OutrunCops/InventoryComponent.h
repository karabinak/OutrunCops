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
	TMap<int32, TSubclassOf<ABaseVehiclePawn>> PlayerInventory;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE TMap<int32, TSubclassOf<ABaseVehiclePawn>> GetVehicleInventory() { return PlayerInventory; }
	FORCEINLINE void SetVehicleInventory(TMap<int32, TSubclassOf<ABaseVehiclePawn>> Inventory) { PlayerInventory = Inventory; }

	UFUNCTION(BlueprintCallable)
	void AddToInventory(int32 Value, TSubclassOf<ABaseVehiclePawn> Vehicle);

	UFUNCTION(BlueprintCallable)
	TSubclassOf<ABaseVehiclePawn> GetFromInventory(int32 Value);

	UFUNCTION(BlueprintCallable)
	bool IsInInventory(int32 Value);

		
};
