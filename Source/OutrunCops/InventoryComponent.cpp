#include "InventoryComponent.h"
#include "BaseVehiclePawn.h"

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

void UInventoryComponent::AddToInventory(int32 Value, TSubclassOf<ABaseVehiclePawn> Vehicle)
{
	PlayerInventory.Add(Value, Vehicle);
}

TSubclassOf<ABaseVehiclePawn> UInventoryComponent::GetFromInventory(int32 Value)
{
	if (PlayerInventory.Contains(Value))
	{
		return PlayerInventory.FindRef(Value);
	}
	return nullptr;
}

bool UInventoryComponent::IsInInventory(int32 Value)
{
	return PlayerInventory.Contains(Value);
}

