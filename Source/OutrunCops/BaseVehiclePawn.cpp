#include "BaseVehiclePawn.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ChaosVehicleMovementComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Components/WidgetComponent.h"

#include "Kismet/GameplayStatics.h"

ABaseVehiclePawn::ABaseVehiclePawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	SetRootComponent(GetMesh());
	SpringArm->SetupAttachment(GetRootComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetSimulatePhysics(true);
	SpringArm->TargetArmLength = 1500.f;
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));

	VehicleWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("VehicleWidget"));
	VehicleWidget->SetupAttachment(GetRootComponent());
	VehicleWidget->SetWidgetSpace(EWidgetSpace::Screen);
	VehicleWidget->SetDrawSize(FVector2D(200.f, 50.f));
	VehicleWidget->SetPivot(FVector2D(0.f, 1.f));


	// CAR PARTS
	WheelFL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FL_Wheel"));
	WheelFR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FR_Wheel"));
	WheelRL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RL_Wheel"));
	WheelRR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RR_Wheel"));

	FrontBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontBumper"));
	FrontBumperCover = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontBumperCover"));
	RearBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearBumper"));
	RearBumperCover = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearBumperCover"));
	MirrorR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MirrorR"));
	MirrorL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MirrorL"));
	Hood = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hood"));
	Trunk = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trunk"));

	WheelFL->SetupAttachment(GetMesh(), TEXT("FL"));
	WheelFR->SetupAttachment(GetMesh(), TEXT("FR"));
	WheelRL->SetupAttachment(GetMesh(), TEXT("RL"));
	WheelRR->SetupAttachment(GetMesh(), TEXT("RR"));

	FrontBumper->SetupAttachment(GetMesh());
	FrontBumperCover->SetupAttachment(GetMesh());
	RearBumper->SetupAttachment(GetMesh());
	RearBumperCover->SetupAttachment(GetMesh());
	MirrorR->SetupAttachment(GetMesh());
	MirrorL->SetupAttachment(GetMesh());
	Hood->SetupAttachment(GetMesh());
	Trunk->SetupAttachment(GetMesh());
}

void ABaseVehiclePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseVehiclePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CalculateDistance();
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

void ABaseVehiclePawn::CalculateDistance()
{
	if (!bCanCalculateDistance) return;
	const FVector CurrentLocation = GetActorLocation();
	double DistanceOneSec = FVector::Dist(CurrentLocation, LastFrameVector);

	Distance += DistanceOneSec / 100;
	LastFrameVector = CurrentLocation;
}

void ABaseVehiclePawn::ChangeCamera(float Axis)
{
	FRotator NewCameraRot = SpringArm->GetRelativeRotation() + FRotator(0.f, Axis, 0.f);
	SpringArm->SetRelativeRotation(NewCameraRot);
}
