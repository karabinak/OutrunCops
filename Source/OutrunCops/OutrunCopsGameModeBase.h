// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OutrunCopsGameModeBase.generated.h"

class ABaseVehiclePawn;

UCLASS()
class OUTRUNCOPS_API AOutrunCopsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	AOutrunCopsGameModeBase();

protected:
	virtual void BeginPlay() override;

private:


public:


};
