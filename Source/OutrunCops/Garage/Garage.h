// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OutrunCops/Vehicles/VehicleStructs.h"
#include "Garage.generated.h"

class AVehiclePawn;
class AMyPlayerController;
class UCameraComponent;
class UMenuWidget;
class ULevelSelectorWidget;
class UUpgradeWidget;
class UOptionsWidget;


UENUM(BlueprintType)
enum class EWidgetState : uint8
{
	EWS_Shop UMETA(DisplayName = "Shop"),
	EWS_Upgrade UMETA(DisplayName = "Upgrade"),

	EWS_MAX UMETA(DisplayName = "Default")
};

UCLASS()
class OUTRUNCOPS_API AGarage : public AActor
{
	GENERATED_BODY()
	
public:	
	AGarage();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	void BeginCameraView();

	void WidgetSettings();

	void DestroyPreviousVehicle();
	void SpawnNewVehicle(int32 VehicleValue, bool IsInInventory);

	void CreateMenuWidget();
	void CreateUpgradeWidget();
	void CreateLevelSelector();
	void CreateOptionsWidget();
	void DelayedBeginPlayFunc();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	AMyPlayerController* PC;


	// Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> MenuWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	UMenuWidget* MenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> OptionsWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	UOptionsWidget* OptionsWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> LevelSelectorClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	ULevelSelectorWidget* LevelSelectorWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> UpgradeWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	UUpgradeWidget* UpgradeWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	EWidgetState WidgetState;

	// Shop
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop Properties", meta = (AllowPrivateAccess = "true"))
	TMap<int32, TSubclassOf<AVehiclePawn>> VehicleCatalog;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop Properties", meta = (AllowPrivateAccess = "true"))
	AVehiclePawn* CurrentCatalogVehicle;

	// Garage player spawn Delay
	FTimerHandle SpawnDelayTimer;

	// Garage Meshes

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Garage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* VehicleStand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* GarageMainView;


public:	

	// Getters/Setters

	UFUNCTION(BlueprintCallable)
	FORCEINLINE AVehiclePawn* GetCurrentCatalogVehicle() { return CurrentCatalogVehicle; }


	UFUNCTION(BlueprintCallable)
	AVehiclePawn* SetPreviewVehicle(int32 VehicleValue);

	TMap<int32, TSubclassOf<AVehiclePawn>> GetVehicleCatalog() { return VehicleCatalog; }

	UFUNCTION(BlueprintCallable)
	void OpenLevelSelector();

	UFUNCTION(BlueprintCallable)
	void OpenUpgrade();

	UFUNCTION(BlueprintCallable)
	void RemoveLevelSelector();

	UFUNCTION(BlueprintCallable)
	void SetWidgetState(EWidgetState ChangeWidgetState);

};
