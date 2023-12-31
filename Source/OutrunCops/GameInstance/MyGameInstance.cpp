
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
		DataToSave->PlayerBasicCurrency = PlayerBasicCurrency_Inst;
		DataToSave->Inventory = PlayerInventory_Inst;
		DataToSave->ChosenVehicleInt = VehicleInt_Inst;
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
		PlayerBasicCurrency_Inst = DataToLoad->PlayerBasicCurrency;
		PlayerInventory_Inst = DataToLoad->Inventory;
		VehicleInt_Inst = DataToLoad->ChosenVehicleInt;

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

void UMyGameInstance::SetVehicleInt_Inst(int32 CurrentVehicleInt)
{
	VehicleInt_Inst = CurrentVehicleInt;
	SaveGame();
}