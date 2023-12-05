// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MySaveGame.h"

void UBaseGameInstance::Init()
{
	LoadGame();
}

void UBaseGameInstance::CreateSaveFile()
{
	UMySaveGame* DataToSave = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	UGameplayStatics::SaveGameToSlot(DataToSave, TEXT("Slot1"), 0);
}

void UBaseGameInstance::SaveGame()
{
	UMySaveGame* DataToSave = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Slot1"), 0));

	if (DataToSave != nullptr)
	{
		DataToSave->PlayerBasicCurrency = PlayerBasicCurrency_Inst;
		DataToSave->Inventory = PlayerInventory_Inst;
		UGameplayStatics::SaveGameToSlot(DataToSave, TEXT("Slot1"), 0);

		GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, FString::Printf(TEXT("Game Saved")));
	}
	else if (!UGameplayStatics::DoesSaveGameExist(TEXT("Slot1"), 0))
	{
		CreateSaveFile();
	}
}

void UBaseGameInstance::LoadGame()
{
	UMySaveGame* DataToLoad = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Slot1"), 0));

	if (DataToLoad != nullptr)
	{
		PlayerBasicCurrency_Inst = DataToLoad->PlayerBasicCurrency;
		PlayerInventory_Inst = DataToLoad->Inventory;

		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Game Loaded")));
	}
	else if (!UGameplayStatics::DoesSaveGameExist(TEXT("Slot1"), 0))
	{
		CreateSaveFile();
	}
}
