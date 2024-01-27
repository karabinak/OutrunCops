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

AVehiclePawn* UInventoryComponent::GetFromInventory(int32 Value)
{
	if (Inventory.Contains(Value))
	{
		return Inventory.FindRef(Value).VehicleClass.GetDefaultObject();
	}
	return nullptr;
}

bool UInventoryComponent::IsInInventory(int32 Value)
{
	return Inventory.Contains(Value);
}

void UInventoryComponent::AddToWheelsInventory(int32 Value, UStaticMesh* Wheel)
{
	WheelsInventory.Add(Value, Wheel);
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->SetWheelsInventoryInstance(WheelsInventory);
	GameInstance->SaveGame();
}

UStaticMesh* UInventoryComponent::GetFromWheelsInventory(int32 Value)
{
	if (WheelsInventory.Contains(Value))
	{
		return WheelsInventory.FindRef(Value);
	}
	return nullptr;
}

bool UInventoryComponent::IsInWheelsInventory(int32 Value)
{
	return WheelsInventory.Contains(Value);
}

void UInventoryComponent::AddToPaintsInventoryInventory(int32 Value, UMaterial* Paint)
{
	PaintsInventory.Add(Value, Paint);
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->SetPaintsInventoryInstance(PaintsInventory);
	GameInstance->SaveGame();
}

UMaterial* UInventoryComponent::GetFromPaintsInventoryInventory(int32 Value)
{
	if (PaintsInventory.Contains(Value))
	{
		return PaintsInventory.FindRef(Value);
	}
	return nullptr;
}

bool UInventoryComponent::IsInPaintsInventoryInventory(int32 Value)
{
	return PaintsInventory.Contains(Value);
}

