// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGameInstance.h"
#include "BaseVehiclePawn.h"
#include "OutrunCopsGameModeGameplay.h"

void AOutrunCopsGameModeGameplay::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	DefaultPawnClass = GameInstance->GetCurrentVehicle();
}
