// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Road.h"
#include "StartingRoad.generated.h"

class USplineComponent;
class ARoad;

UCLASS()
class OUTRUNCOPS_API AStartingRoad : public ARoad
{
	GENERATED_BODY()

public:
	AStartingRoad();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnAnimationOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnAnimationEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ActiveAnimationBox();

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline", meta = (AllowPrivateAccess = "true"))
	USplineComponent* SplineComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* AnimationTrigger;
	
	UPROPERTY()
	FTimerHandle TriggerDelay;

	
};
