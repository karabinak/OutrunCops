// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeWidget.generated.h"

class UMenuWidget;
class AGarage;

UCLASS()
class OUTRUNCOPS_API UUpgradeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	void ChangeColor(UMaterial* NewMaterial);

	UFUNCTION(BlueprintCallable)
	void Return();
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Garage", meta = (AllowPrivateAccess = "true"))
	AGarage* GarageRef;

public:

	void SetGarageRef(AGarage* Garage) { GarageRef = Garage; }
};
