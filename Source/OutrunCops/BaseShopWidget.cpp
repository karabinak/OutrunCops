// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseShopWidget.h"

#include "BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "BaseGarage.h"
#include "BasePlayerController.h"

void UBaseShopWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerControllerRef = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	GameInstanceRef = Cast<UBaseGameInstance>(GetGameInstance());

	AmountOfVehiclesInCatalog = GarageRef->GetVehicleCatalog().Num();

	VehicleInt = GameInstanceRef->GetVehicleInt_Inst();
}

void UBaseShopWidget::SaveCurrentVehicleInt(int32 CurrentVehicle)
{
	GameInstanceRef->SetVehicleInt_Inst(CurrentVehicle);
}

bool UBaseShopWidget::AddVehicleInt()
{
	if (VehicleInt + 1 > AmountOfVehiclesInCatalog - 1) return false;

	VehicleInt++;
	return true;
}

bool UBaseShopWidget::SubtractVehicleInt()
{
	if (VehicleInt - 1 < 0) return false;

	VehicleInt--;
	return true;
}
