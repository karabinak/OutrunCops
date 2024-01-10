// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsWidget.generated.h"

class AGarage;

/**
 * 
 */
UCLASS()
class OUTRUNCOPS_API UOptionsWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Garage", meta = (AllowPrivateAccess = "true"))
	AGarage* Garage;

public:

	void SetGarageRef(AGarage* GarageRef) { Garage = GarageRef; }
	
};
