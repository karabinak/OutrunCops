// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayGamemode.generated.h"

class AVehiclePawn;
class AEnemy;
class ACutsceneCameraDesert;
class UMyGameInstance;
class AMyPlayerController;

//UENUM(BlueprintType)
//enum class EChaseState : uint8
//{
//	ECS_Level1 UMETA(DisplayName = "Level1"),
//	ECS_Level2 UMETA(DisplayName = "Level2"),
//	ECS_Level3 UMETA(DisplayName = "Level3"),
//	ECS_Level4 UMETA(DisplayName = "Level4"),
//	ECS_Level5 UMETA(DisplayName = "Level5"),
//
//	ECS_MAX UMETA(DisplayName = "Default")
//};

UCLASS()
class OUTRUNCOPS_API AGameplayGamemode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AGameplayGamemode();
	virtual void Tick(float DeltaTime) override;

	void WastedTimers();

protected:

	virtual void BeginPlay() override;

	void SpawnCutsceneCamera();

	void SpawnPlayerVehicle();

	void CreateGameplayWidget();
	void CreatePauseWidget();
	void CreateEndRunWidget();

	void AddEndRunToViewport();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properites", meta = (AllowPrivateAccess = "true"));
	AVehiclePawn* PlayerVehicle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properites", meta = (AllowPrivateAccess = "true"));
	UMyGameInstance* GameInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properites", meta = (AllowPrivateAccess = "true"));
	AMyPlayerController* PC;


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ACutsceneCameraDesert> CutsceneCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	FVector CameraSpawnLocation = FVector(2000.f, 0.f, 2500.f);

	// Police functions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properites", meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AEnemy> BasicPoliceCar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properites", meta = (AllowPrivateAccess = "true"))
	int32 PoliceAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properites", meta = (AllowPrivateAccess = "true"))
	int32 MaxPolice = 2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properites", meta = (AllowPrivateAccess = "true"));
	FTransform PoliceSpawnTransform = FTransform(FRotator(0.f, 0.f, 0.f), FVector(500.f, 0.f, 50.f), FVector(1.f, 1.f, 1.f));

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	int32 AmountOfChasersInSphere = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float MinSpeedToGetWasted = 30.f;

	FTimerHandle WastedTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float TimeToGetWasted = 3.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float ElapsedTimeWasted = 0.f;

	bool bPlayerWasted = false;



public:
	
	// Getters/Setters

	FORCEINLINE UUserWidget* GetPauseWidget() { return PauseWidget; }
	FORCEINLINE FTransform SetPoliceSpawnLocation(FTransform SpawnLocation) { return PoliceSpawnTransform = SpawnLocation; }

	FORCEINLINE float GetTimeToGetWasted() { return TimeToGetWasted; }
	FORCEINLINE float GetElapsedTimeWasted() { return ElapsedTimeWasted; }

	FORCEINLINE int32 SetPoliceAmount(int32 Amount) { return PoliceAmount += Amount; }
	FORCEINLINE int32 SetMaxPolice(int32 Amount) { return MaxPolice = Amount; }

	// Public functions

	UFUNCTION(BlueprintCallable)
	void SpawnPoliceCar();

	void SetAmountOfChasersInSphere(int32 Amount);

	void EndRun();
};
