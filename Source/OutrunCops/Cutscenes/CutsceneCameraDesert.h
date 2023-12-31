#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CutsceneCameraDesert.generated.h"

class UCameraComponent;
class AVehiclePawn;
class AMyPlayerController;

UCLASS()
class OUTRUNCOPS_API ACutsceneCameraDesert : public AActor
{
	GENERATED_BODY()
	
public:	
	ACutsceneCameraDesert();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void ChangeCamera();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CutsceneCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	FRotator CameraBaseRotation = FRotator(-50.f, 0.f, 0.f);

	UPROPERTY()
	FTimerHandle CameraChangeTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	AMyPlayerController* PC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	AVehiclePawn* PlayerPawn;

public:	


};
