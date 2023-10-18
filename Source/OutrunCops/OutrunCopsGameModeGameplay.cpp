// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGameInstance.h"
#include "BaseVehiclePawn.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "OutrunCopsGameModeGameplay.h"

void AOutrunCopsGameModeGameplay::BeginPlay()
{
	Super::BeginPlay();

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());

	FActorSpawnParameters ActorSpawnParameters;
	ABaseVehiclePawn* Vehicle = GetWorld()->SpawnActor<ABaseVehiclePawn>(GameInstance->GetPlayerVehicle_Inst(), FVector(500.f, 0.f, 50.f), FRotator(0.f, 0.f, 0.f), ActorSpawnParameters);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(Vehicle);

	CreateGameplayWidget();

	if (GameplayWidget)
	{
		GameplayWidget->AddToViewport();
	}
}

void AOutrunCopsGameModeGameplay::CreateGameplayWidget()
{
	if (GameplayWidgetClass)
	{
		GameplayWidget = CreateWidget<UUserWidget>(GetWorld(), GameplayWidgetClass);
	}
}