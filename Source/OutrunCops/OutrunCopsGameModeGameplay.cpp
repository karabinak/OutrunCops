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
	ABaseVehiclePawn* Vehicle = GetWorld()->SpawnActor<ABaseVehiclePawn>(GameInstance->GetPlayerVehicle_Inst(), FVector(500.f, 0.f, 15.f), FRotator(0.f, 0.f, 0.f), ActorSpawnParameters);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(Vehicle);

	CreateGameplayWidget();
	CreatePauseWidget();
	CreateEndRunWidget();

	if (GameplayWidget)
	{
		GameplayWidget->AddToViewport();
	}
	if (Vehicle)
	{
		Vehicle->SetCanCalculateDistance(true);
	}
}

void AOutrunCopsGameModeGameplay::CreateGameplayWidget()
{
	if (GameplayWidgetClass)
	{
		GameplayWidget = CreateWidget<UUserWidget>(GetWorld(), GameplayWidgetClass);
	}
}

void AOutrunCopsGameModeGameplay::CreatePauseWidget()
{
	if (PauseWidgetClass)
	{
		PauseWidget = CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass);
	}
}

void AOutrunCopsGameModeGameplay::CreateEndRunWidget()
{
	if (EndRunWidgetClass)
	{
		EndRunWidget = CreateWidget<UUserWidget>(GetWorld(), EndRunWidgetClass);
	}
}
