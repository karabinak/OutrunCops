// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "BaseEnemy.generated.h"

class ABaseVehiclePawn;
class USphereComponent;
class AOutrunCopsGameModeGameplay;


UCLASS()
class OUTRUNCOPS_API ABaseEnemy : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:

	ABaseEnemy();
	virtual void BeginPlay() override;

protected:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OverlappingWithPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void StopOverlappingWithPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	ABaseVehiclePawn* BaseVehicle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	USphereComponent* ArrestedZone;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float DespawnDistance = 8000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float SpawnForce = 3000000.f;

	AOutrunCopsGameModeGameplay* Gamemode;

	// Vehicle Parts
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelFL;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelFR;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelRL;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WheelRR;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FrontBumper;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Siren;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mirrors;

public:

};