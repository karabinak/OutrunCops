
#include "MyGameInstance.h"

// Engine
#include "Kismet/GameplayStatics.h"

// Custom
#include "OutrunCops/Saves/MySaveGame.h"

//////////////////////////////////////////////////////

void UMyGameInstance::Init()
{
	LoadGame();
}

void UMyGameInstance::CreateSaveFile()
{
	UMySaveGame* DataToSave = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	UGameplayStatics::SaveGameToSlot(DataToSave, TEXT("Slot1"), 0);
}

void UMyGameInstance::SaveGame()
{
	UMySaveGame* DataToSave = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Slot1"), 0));

	if (DataToSave != nullptr)
	{
		DataToSave->PlayerBasicCurrency = BasicCurrencyInstance;
		DataToSave->Inventory = InventoryInstance;
		DataToSave->ChosenVehicleInt = VehicleIntInstance;
		UGameplayStatics::SaveGameToSlot(DataToSave, TEXT("Slot1"), 0);

		GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, FString::Printf(TEXT("Game Saved")));
	}
	else if (!UGameplayStatics::DoesSaveGameExist(TEXT("Slot1"), 0))
	{
		CreateSaveFile();
	}
}

void UMyGameInstance::LoadGame()
{
	UMySaveGame* DataToLoad = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Slot1"), 0));

	if (DataToLoad != nullptr)
	{
		BasicCurrencyInstance = DataToLoad->PlayerBasicCurrency;
		InventoryInstance = DataToLoad->Inventory;
		VehicleIntInstance = DataToLoad->ChosenVehicleInt;

		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Game Loaded")));
	}
	else if (!UGameplayStatics::DoesSaveGameExist(TEXT("Slot1"), 0))
	{
		CreateSaveFile();
	}
}

void UMyGameInstance::DeleteSave()
{
	UMySaveGame* DataToLoad = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Slot1"), 0));

	if (DataToLoad != nullptr)
	{
		UGameplayStatics::DeleteGameInSlot(TEXT("Slot1"), 0);
		UKismetSystemLibrary::QuitGame(GetWorld(), 0, EQuitPreference::Quit, false);
	}
}

void UMyGameInstance::SetVehicleIntInstance(int32 CurrentVehicleInt)
{
	VehicleIntInstance = CurrentVehicleInt;
	SaveGame();
}