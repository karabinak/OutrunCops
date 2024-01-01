// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UInventoryComponent;

UCLASS()
class OUTRUNCOPS_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* Inventory;

	// Currency
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int32 PlayerBasicCurrency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int32 PlayerPremiumCurrency;

public:

	// Getter/Setter

	FORCEINLINE UInventoryComponent* GetInventory() const { return Inventory; }

	FORCEINLINE void SetPlayerBasicCurrency(int32 Currency) { PlayerBasicCurrency = Currency; }
	FORCEINLINE int32 GetPlayerBasicCurrency() const { return PlayerBasicCurrency; }

	// Public functions

	UFUNCTION(BlueprintCallable)
	void AddBasicCurrency(int32 Currency);
	UFUNCTION(BlueprintCallable)
	void DecreaseBasicCurrency(int32 Currency);

};
