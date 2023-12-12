// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelSelectorWidget.generated.h"

class ABaseGarage;
UCLASS()
class OUTRUNCOPS_API ULevelSelectorWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintCallable)
	void OpenLevel(FName LevelName);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Garage", meta = (AllowPrivateAccess = "true"))
	ABaseGarage* GarageRef;


public:

	void SetGarageRef(ABaseGarage* BaseGarage) { GarageRef = BaseGarage; }
};
