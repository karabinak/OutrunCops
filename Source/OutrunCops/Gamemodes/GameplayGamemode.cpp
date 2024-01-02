#include "GameplayGamemode.h"

// Engine
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ChaosVehicleMovementComponent.h"

// Custom
#include "OutrunCops/Vehicles/VehiclePawn.h"
#include "OutrunCops/GameInstance/MyGameInstance.h"
#include "OutrunCops/Controllers/MyPlayerController.h"
#include "OutrunCops/Inventory/InventoryComponent.h"
#include "OutrunCops/Enemies/Enemy.h"
#include "OutrunCops/Cutscenes/CutsceneCameraDesert.h"

//////////////////////////////////////////////////////

AGameplayGamemode::AGameplayGamemode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AGameplayGamemode::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	SpawnPlayerVehicle();
	SpawnCutsceneCamera();


	// Setting Basic Currency
	PC->SetPlayerBasicCurrency(GameInstance->GetBasicCurrencyInstance());
	GameInstance->LoadGame();

	CreateGameplayWidget();
	CreatePauseWidget();
	CreateEndRunWidget();

	if (GameplayWidget)
	{
		GameplayWidget->AddToViewport();
	}
}

void AGameplayGamemode::SpawnCutsceneCamera()
{
	if (CutsceneCamera)
	{
		FActorSpawnParameters CameraActorSpawnParameters;
		GetWorld()->SpawnActor<ACutsceneCameraDesert>(CutsceneCamera->GetDefaultObject()->GetClass(), CameraSpawnLocation, FRotator(0.f, 0.f, 0.f), CameraActorSpawnParameters);
	}
}

void AGameplayGamemode::SpawnPlayerVehicle()
{
	if (GameInstance->GetVehicleClassInstance())
	{
		FActorSpawnParameters ActorSpawnParameters;
		PlayerVehicle = GetWorld()->SpawnActor<AVehiclePawn>(GameInstance->GetVehicleClassInstance(), FVector(10100.f, 1050.f, 10.f), FRotator(0.f, 0.f, 0.f), ActorSpawnParameters);
		PC->Possess(PlayerVehicle);
		UE_LOG(LogTemp, Warning, TEXT("Works"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Nope"));
	}
}

void AGameplayGamemode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	WastedTimers();
}

void AGameplayGamemode::WastedTimers()
{
	if (!PlayerVehicle) return;
	bool bChasersInSphere = AmountOfChasersInSphere > 0;
	bool bWastedSpeed = PlayerVehicle->GetVehicleMovement()->GetForwardSpeedMPH() * 1.609344 <= MinSpeedToGetWasted &&
		PlayerVehicle->GetVehicleMovement()->GetForwardSpeedMPH() * 1.609344 >= -MinSpeedToGetWasted;

	if (bChasersInSphere && bWastedSpeed && !bPlayerWasted)
	{
		ElapsedTimeWasted = GetWorldTimerManager().GetTimerElapsed(WastedTimer);
		if (!GetWorldTimerManager().IsTimerActive(WastedTimer))
		{
			GetWorldTimerManager().SetTimer(WastedTimer, this, &AGameplayGamemode::EndRun, TimeToGetWasted);
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(WastedTimer);
		ElapsedTimeWasted = 0.f;
	}
}

void AGameplayGamemode::SpawnPoliceCar()
{
	if (PoliceAmount < MaxPolice)
	{
		FActorSpawnParameters Spawnparameters;

		for (int i = 0; i < 5; i++)
		{
			AEnemy* PoliceCar = GetWorld()->SpawnActor<AEnemy>(BasicPoliceCar.Get(), PoliceSpawnTransform, Spawnparameters);
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

void AGameplayGamemode::SetAmountOfChasersInSphere(int32 Amount)
{
	AmountOfChasersInSphere += Amount;
}

void AGameplayGamemode::CreateGameplayWidget()
{
	if (GameplayWidgetClass)
	{
		GameplayWidget = CreateWidget<UUserWidget>(GetWorld(), GameplayWidgetClass);
	}
}

void AGameplayGamemode::CreatePauseWidget()
{
	if (PauseWidgetClass)
	{
		PauseWidget = CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass);
	}
}

void AGameplayGamemode::CreateEndRunWidget()
{
	if (EndRunWidgetClass)
	{
		EndRunWidget = CreateWidget<UUserWidget>(GetWorld(), EndRunWidgetClass);
	}
}

void AGameplayGamemode::AddEndRunToViewport()
{
	if (EndRunWidget)
	{
		EndRunWidget->AddToViewport();
	}
}

void AGameplayGamemode::EndRun()
{
	bPlayerWasted = true;
	ElapsedTimeWasted = TimeToGetWasted;
	AddEndRunToViewport();
}
