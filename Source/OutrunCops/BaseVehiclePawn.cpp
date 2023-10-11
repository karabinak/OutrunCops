#include "BaseVehiclePawn.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ChaosVehicleMovementComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"

#include "Kismet/GameplayStatics.h"

ABaseVehiclePawn::ABaseVehiclePawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	SetRootComponent(GetMesh());
	SpringArm->SetupAttachment(GetRootComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetSimulatePhysics(true);
	SpringArm->TargetArmLength = 800.f;
	SpringArm->SetRelativeRotation(FRotator(0.f, -25.f, 0.f));

}

void ABaseVehiclePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseVehiclePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


}

void ABaseVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("Throttle", this, &ABaseVehiclePawn::Throttle);
	PlayerInputComponent->BindAxis("Brake", this, &ABaseVehiclePawn::Brake);
	PlayerInputComponent->BindAxis("Steer", this, &ABaseVehiclePawn::Steer);
}

void ABaseVehiclePawn::Throttle(float AxisValue)
{
	GetVehicleMovement()->SetThrottleInput(AxisValue);
}

void ABaseVehiclePawn::Brake(float AxisValue)
{
	GetVehicleMovement()->SetBrakeInput(AxisValue);
}

void ABaseVehiclePawn::Steer(float AxisValue)
{
	GetVehicleMovement()->SetSteeringInput(AxisValue);
}