// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGamemode.generated.h"

class ABaseVehiclePawn;

UCLASS()
class OUTRUNCOPS_API AMainGamemode : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	AMainGamemode();

protected:
	virtual void BeginPlay() override;

private:


public:


};
