// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VehicleStructs.h"
#include "BaseGarage.generated.h"

class ABaseVehiclePawn;
class UCameraComponent;
class ABasePlayerController;

UENUM(BlueprintType)
enum class EWidgetState : uint8
{
	EWS_Menu UMETA(DisplayName = "Menu"),
	EWS_Shop UMETA(DisplayName = "Shop"),

	EWS_MAX UMETA(DisplayName = "Default")
};

UCLASS()
class OUTRUNCOPS_API ABaseGarage : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseGarage();

protected:
	virtual void BeginPlay() override;

	void DestroyPreviousVehicle();
	void SpawnNewVehicle(int32 VehicleValue, bool IsInInventory);

	void CreateMenuWidget();
	void CreateShopWidget();

private:


	// Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> MenuWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	UUserWidget* MenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> ShopWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	UUserWidget* ShopWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	EWidgetState WidgetState;

	// Shop
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop Properties", meta = (AllowPrivateAccess = "true"))
	TMap<int32, TSubclassOf<ABaseVehiclePawn>> VehicleCatalog;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop Properties", meta = (AllowPrivateAccess = "true"))
	ABaseVehiclePawn* CurrentCatalogVehicle;

	// Garage Meshes

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Garage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* VehicleStand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* GarageMainView;
	
	// PC
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	ABasePlayerController* PlayerController;


public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	ABaseVehiclePawn* SetPreviewVehicle(int32 VehicleValue);
	UFUNCTION(BlueprintCallable)
	void SetWidgetState(EWidgetState ChangeWidgetState);

	TMap<int32, TSubclassOf<ABaseVehiclePawn>> GetVehicleCatalog() { return VehicleCatalog; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE ABaseVehiclePawn* GetCurrentCatalogVehicle() { return CurrentCatalogVehicle; }


};
