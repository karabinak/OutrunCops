#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VehicleStructs.h"
#include "BaseShopWidget.generated.h"

class ABaseGarage;
class ABasePlayerController;
class UBaseGameInstance;

UCLASS()
class OUTRUNCOPS_API UBaseShopWidget : public UUserWidget
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

	UFUNCTION(BlueprintCallable)
	void ChangeVehicleColor();

private:
	// REFERENCES
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Garage", meta = (AllowPrivateAccess = "true"))
	ABaseGarage* GarageRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Garage", meta = (AllowPrivateAccess = "true"))
	ABasePlayerController* PlayerControllerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Garage", meta = (AllowPrivateAccess = "true"))
	UBaseGameInstance* GameInstanceRef;

	// Widget Values
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Garage", meta = (AllowPrivateAccess = "true"))
	int32 VehicleInt = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Garage", meta = (AllowPrivateAccess = "true"))
	int32 AmountOfVehiclesInCatalog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Garage", meta = (AllowPrivateAccess = "true"))
	UMaterial* Material;

public:

	void SetGarageRef(ABaseGarage* BaseGarage) { GarageRef = BaseGarage; }

	FORCEINLINE void SetVehicleInt(int32 Value) { VehicleInt = Value; }
	FORCEINLINE int32 GetVehicleInt() { return VehicleInt; }
	FORCEINLINE int32 GetAmountOfVehiclesInCatalog() { return AmountOfVehiclesInCatalog; }

};