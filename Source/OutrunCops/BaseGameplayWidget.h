// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseGameplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class OUTRUNCOPS_API UBaseGameplayWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	void OpenMenuLevel();
};
