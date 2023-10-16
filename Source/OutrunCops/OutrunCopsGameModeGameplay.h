// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OutrunCopsGameModeGameplay.generated.h"

UCLASS()
class OUTRUNCOPS_API AOutrunCopsGameModeGameplay : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	void CreateGameplayWidget();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> GameplayWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	UUserWidget* GameplayWidget;
	
};
