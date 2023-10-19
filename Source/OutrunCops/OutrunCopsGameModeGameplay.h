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

	virtual void BeginPlay() override;

	void CreateGameplayWidget();
	void CreatePauseWidget();
	void CreateEndRunWidget();

private:
	// Gameplay Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> GameplayWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	UUserWidget* GameplayWidget;

	// Pause Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PauseWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	UUserWidget* PauseWidget;

	// EndRun Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> EndRunWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	UUserWidget* EndRunWidget;

public:
	
	FORCEINLINE UUserWidget* GetPauseWidget() { return PauseWidget; }
};
