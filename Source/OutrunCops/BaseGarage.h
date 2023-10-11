// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGarage.generated.h"

class ABaseVehiclePawn;
class UCameraComponent;

UCLASS()
class OUTRUNCOPS_API ABaseGarage : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseGarage();

protected:
	virtual void BeginPlay() override;

	void CreateMenuWidget();

private:

	// Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> MenuWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UUserWidget* MenuWidget;

	// Shop
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TMap<int32, TSubclassOf<ABaseVehiclePawn>> VehicleCatalog;

	// Garage Meshes

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Garage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* VehicleStand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* GarageMainView;



public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetPreviewVehicle(int32 CurrentValue);

};
