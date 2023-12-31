#include "InventoryComponent.h"

// Engine
#include "Kismet/GameplayStatics.h"

// Custom
#include "OutrunCops/Vehicles/VehiclePawn.h"
#include "OutrunCops/GameInstance/MyGameInstance.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInventoryComponent::AddToInventory(int32 Value, FInventorySlot Vehicle)
{
	PlayerInventory.Add(Value, Vehicle);
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->SetPlayerInventory_Inst(PlayerInventory);
	GameInstance->SaveGame();
}

UClass* UInventoryComponent::GetFromInventory(int32 Value)
{
	if (PlayerInventory.Contains(Value))
	{
		return PlayerInventory.FindRef(Value).VehicleClass;
	}
	return nullptr;
}

bool UInventoryComponent::IsInInventory(int32 Value)
{
	return PlayerInventory.Contains(Value);
}

