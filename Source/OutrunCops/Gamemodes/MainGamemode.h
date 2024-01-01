// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGamemode.generated.h"

class AMyPlayerController;
class UMyGameInstance;

UCLASS()
class OUTRUNCOPS_API AMainGamemode : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	AMainGamemode();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properites", meta = (AllowPrivateAccess = "true"));
	AMyPlayerController* PC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properites", meta = (AllowPrivateAccess = "true"));
	UMyGameInstance* GameInstance;

public:


};
