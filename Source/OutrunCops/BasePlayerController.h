// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class UInventoryComponent;

UCLASS()
class OUTRUNCOPS_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int32 PlayerBasicCurrency;

public:

	FORCEINLINE UInventoryComponent* GetInventory() const { return Inventory; }

	FORCEINLINE void SetPlayerBasicCurrency(int32 BasicCurrency) { PlayerBasicCurrency = BasicCurrency; }
	FORCEINLINE int32 GetPlayerBasicCurrency() const { return PlayerBasicCurrency; }

	UFUNCTION(BlueprintCallable)
	void AddBasicCurrency(int32 BasicCurrency);
	UFUNCTION(BlueprintCallable)
	void SubtractBasicCurrency(int32 BasicCurrency);

};
