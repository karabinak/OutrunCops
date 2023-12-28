#include "OutrunCopsGameModeGameplay.h"

#include "BaseVehiclePawn.h"
#include "BaseGameInstance.h"
#include "BaseVehiclePawn.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "BasePlayerController.h"
#include "InventoryComponent.h"
#include "ChaosVehicleMovementComponent.h"
#include "BaseEnemy.h"
#include "DesertCutsceneCamera.h"

AOutrunCopsGameModeGameplay::AOutrunCopsGameModeGameplay()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AOutrunCopsGameModeGameplay::BeginPlay()
{
	Super::BeginPlay();

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());

	if (GameInstance->GetPlayerVehicle_Inst())
	{
		FActorSpawnParameters ActorSpawnParameters;
		BaseVehicle = GetWorld()->SpawnActor<ABaseVehiclePawn>(GameInstance->GetPlayerVehicle_Inst()->GetClass(), FVector(10100.f, 1050.f, 10.f), FRotator(0.f, 0.f, 0.f), ActorSpawnParameters);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(BaseVehicle);
	}
	if (CutsceneCamera)
	{
		FActorSpawnParameters CameraActorSpawnParameters;
		GetWorld()->SpawnActor<ADesertCutsceneCamera>(CutsceneCamera->GetDefaultObject()->GetClass(), CameraSpawnLocation, FRotator(0.f, 0.f, 0.f), CameraActorSpawnParameters);
	}



	// Setting Basic Currency
	Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->SetPlayerBasicCurrency(GameInstance->GetPlayerBasicCurrency_Inst());
	GameInstance->LoadGame();

	//Cast<ABasePlayerController>(BaseVehicle->GetController())->GetInventory()->SetVehicleInventory(GameInstance->GetPlayerInventory_Inst());

	CreateGameplayWidget();
	CreatePauseWidget();
	CreateEndRunWidget();

	if (GameplayWidget)
	{
		GameplayWidget->AddToViewport();
	}
}

void AOutrunCopsGameModeGameplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AmountOfChasersInSphere > 0 && BaseVehicle->GetVehicleMovement()->GetForwardSpeedMPH() * 1.609344 <= MinSpeedToGetWasted && BaseVehicle->GetVehicleMovement()->GetForwardSpeedMPH() * 1.609344 >= -MinSpeedToGetWasted && !bPlayerWasted)
	{
		ElapsedTimeWasted = GetWorldTimerManager().GetTimerElapsed(WastedTimer);
		if (!GetWorldTimerManager().IsTimerActive(WastedTimer))
		{
			GetWorldTimerManager().SetTimer(WastedTimer, this, &AOutrunCopsGameModeGameplay::EndRun, TimeToGetWasted);
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(WastedTimer);
		ElapsedTimeWasted = 0.f;
	}
}

void AOutrunCopsGameModeGameplay::SpawnPoliceCar()
{
	if (PoliceAmount < MaxPolice)
	{
		FActorSpawnParameters Spawnparameters;

		for (int i = 0; i < 5; i++)
		{
			ABaseEnemy* PoliceCar = GetWorld()->SpawnActor<ABaseEnemy>(BasicPoliceCar.Get(), PoliceSpawnTransform, Spawnparameters);
			if (PoliceCar)
			{
				SetPoliceAmount(1);
				PoliceCar = nullptr;
				return;
			}
			PoliceSpawnTransform.SetLocation(PoliceSpawnTransform.GetLocation() + FVector(-50.f, 0.f, 0.f));
		}
	}
}

void AOutrunCopsGameModeGameplay::SetAmountOfChasersInSphere(int32 Amount)
{
	AmountOfChasersInSphere += Amount;
}

void AOutrunCopsGameModeGameplay::CreateGameplayWidget()
{
	if (GameplayWidgetClass)
	{
		GameplayWidget = CreateWidget<UUserWidget>(GetWorld(), GameplayWidgetClass);
	}
}

void AOutrunCopsGameModeGameplay::CreatePauseWidget()
{
	if (PauseWidgetClass)
	{
		PauseWidget = CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass);
	}
}

void AOutrunCopsGameModeGameplay::CreateEndRunWidget()
{
	if (EndRunWidgetClass)
	{
		EndRunWidget = CreateWidget<UUserWidget>(GetWorld(), EndRunWidgetClass);
	}
}

void AOutrunCopsGameModeGameplay::AddEndRunToViewport()
{
	if (EndRunWidget)
	{
		EndRunWidget->AddToViewport();
	}
}

void AOutrunCopsGameModeGameplay::EndRun()
{
	bPlayerWasted = true;
	ElapsedTimeWasted = TimeToGetWasted;
	AddEndRunToViewport();
}
