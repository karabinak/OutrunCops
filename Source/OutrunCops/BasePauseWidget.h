// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BasePauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class OUTRUNCOPS_API UBasePauseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	void OpenMenuLevel();
	
};
