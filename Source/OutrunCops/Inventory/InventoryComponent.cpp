#include "InventoryComponent.h"

// Engine
#include "Kismet/GameplayStatics.h"

// Custom
#include "OutrunCops/Vehicles/VehiclePawn.h"
#include "OutrunCops/GameInstance/MyGameInstance.h"

//////////////////////////////////////////////////////


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
	Inventory.Add(Value, Vehicle);
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->SetInventoryInstance(Inventory);
	GameInstance->SaveGame();
}

UClass* UInventoryComponent::GetFromInventory(int32 Value)
{
	if (Inventory.Contains(Value))
	{
		return Inventory.FindRef(Value).VehicleClass;
	}
	return nullptr;
}

bool UInventoryComponent::IsInInventory(int32 Value)
{
	return Inventory.Contains(Value);
}

