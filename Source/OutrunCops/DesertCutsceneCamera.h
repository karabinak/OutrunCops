#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DesertCutsceneCamera.generated.h"

class UCameraComponent;

UCLASS()
class OUTRUNCOPS_API ADesertCutsceneCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	ADesertCutsceneCamera();

protected:
	virtual void BeginPlay() override;

	void ChangeCamera();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CutsceneCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	FRotator CameraBaseRotation = FRotator(-50.f, 0.f, 0.f);

	UPROPERTY()
	FTimerHandle CameraChangeTime;


public:	
	virtual void Tick(float DeltaTime) override;

};
