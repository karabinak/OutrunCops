#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OutrunCops/Vehicles/VehicleStructs.h"
#include "MenuWidget.generated.h"

class AGarage;
class AMyPlayerController;
class UMyGameInstance;
class UUpgradeWidget;

UCLASS()
class OUTRUNCOPS_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SaveCurrentVehicleInt(int32 CurrentVehicle);

	UFUNCTION(BlueprintCallable)
	bool AddVehicleInt();

	UFUNCTION(BlueprintCallable)
	bool SubtractVehicleInt();

	UFUNCTION(BlueprintCallable)
	void BuyVehicle();

	//UFUNCTION(BlueprintCallable)
	//void ChangeVehicleColor();


private:
	// REFERENCES
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Garage", meta = (AllowPrivateAccess = "true"))
	AGarage* GarageRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Garage", meta = (AllowPrivateAccess = "true"))
	AMyPlayerController* PlayerControllerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Garage", meta = (AllowPrivateAccess = "true"))
	UMyGameInstance* GameInstanceRef;

	// Widget Values
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Garage", meta = (AllowPrivateAccess = "true"))
	int32 VehicleInt = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Garage", meta = (AllowPrivateAccess = "true"))
	int32 AmountOfVehiclesInCatalog;

public:

	void SetGarageRef(AGarage* Garage) { GarageRef = Garage; }

	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	//FORCEINLINE void SetVehicleStats(ABaseVehiclePawn* CurrentVehicle);

	FORCEINLINE void SetVehicleInt(int32 Value) { VehicleInt = Value; }
	FORCEINLINE int32 GetVehicleInt() { return VehicleInt; }
	FORCEINLINE int32 GetAmountOfVehiclesInCatalog() { return AmountOfVehiclesInCatalog; }

};