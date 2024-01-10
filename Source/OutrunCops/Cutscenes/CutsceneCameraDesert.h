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

	virtual void Tick(float DeltaTime) override;


protected:

	virtual void BeginPlay() override;

	void ChangeCamera();
	void CameraAnimation();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	AMyPlayerController* PC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	AVehiclePawn* PlayerPawn;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CutsceneCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	FRotator CameraBaseRotation = FRotator(-35.f, 0.f, 0.f);

	UPROPERTY()
	FTimerHandle CameraChangeTime;

public:	


};
