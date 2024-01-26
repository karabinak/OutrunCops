#include "VehiclePawn.h"

// Engine
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraShake.h"
#include "ChaosVehicleMovementComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SplineComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Custom
#include "OutrunCops/Saves/MySaveGame.h"
#include "OutrunCops/GameInstance/MyGameInstance.h"
#include "OutrunCops/Gamemodes/GameplayGamemode.h"

//////////////////////////////////////////////////////


AVehiclePawn::AVehiclePawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	SetRootComponent(GetMesh());
	SpringArm->SetupAttachment(GetRootComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetSimulatePhysics(true);
	SpringArm->TargetArmLength = SpringArmBaseLenght;
	SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 3.f;
	SpringArm->CameraLagSpeed = 5.f;

	VehicleWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("VehicleWidget"));
	VehicleWidget->SetupAttachment(GetRootComponent());
	VehicleWidget->SetWidgetSpace(EWidgetSpace::Screen);
	VehicleWidget->SetDrawSize(FVector2D(100.f, 50.f));
	VehicleWidget->SetPivot(FVector2D(0.f, 1.f));


// ------------------------------------------------ VEHICLE PARTS ------------------------------------------------ //
	WheelFL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FL_Wheel"));
	WheelFR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FR_Wheel"));
	WheelRL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RL_Wheel"));
	WheelRR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RR_Wheel"));

	FrontBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontBumper"));
	RearBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearBumper"));

	FrontLightR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontLightRight"));
	FrontLightL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontLightLeft"));
	BackLightR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackLightRight"));
	BackLightL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackLightLeft"));

	MirrorR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MirrorR"));
	MirrorL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MirrorL"));

	FenderR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FenderRight"));
	FenderL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FenderLeft"));

	Engine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Engine"));
	Hood = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hood"));

	Trunk = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trunk"));
	BackWing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackWing"));

// --------------------------------------------- VEHICLE ATTACHMENTS --------------------------------------------- //
	WheelFL->SetupAttachment(GetMesh(), TEXT("FL"));
	WheelFR->SetupAttachment(GetMesh(), TEXT("FR"));
	WheelRL->SetupAttachment(GetMesh(), TEXT("RL"));
	WheelRR->SetupAttachment(GetMesh(), TEXT("RR"));

	FrontBumper->SetupAttachment(GetMesh());
	RearBumper->SetupAttachment(GetMesh());

	FrontLightR->SetupAttachment(GetMesh());
	FrontLightL->SetupAttachment(GetMesh());
	BackLightR->SetupAttachment(GetMesh());
	BackLightL->SetupAttachment(GetMesh());

	MirrorR->SetupAttachment(GetMesh());
	MirrorL->SetupAttachment(GetMesh());

	FenderR->SetupAttachment(GetMesh());
	FenderL->SetupAttachment(GetMesh());

	Engine->SetupAttachment(GetMesh());
	Hood->SetupAttachment(GetMesh());

	Trunk->SetupAttachment(GetMesh());
	BackWing->SetupAttachment(Trunk);

// ----------------------------------------------------------------------------------------------------------- //
}

void AVehiclePawn::BeginPlay()
{
	Super::BeginPlay();

	SetVehicleState(EVehicleState::EVS_Inactive);
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	HitPoints = MaxHealth;

	EngineRef = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement());

	GetMesh()->OnComponentHit.AddDynamic(this, &AVehiclePawn::OnHit);

	PopulateMeshArray();

	ActiveParts = AllVehicleParts.Num();
	OnePartHitPoints = MaxHealth / ActiveParts;

	LoadVehicle();

}

void AVehiclePawn::LoadVehicle()
{
	UMySaveGame* DataToLoad = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Slot1"), 0));
	if (DataToLoad != nullptr)
	{
		UMyGameInstance* Instance = Cast<UMyGameInstance>(GetGameInstance());

		if (DataToLoad->Inventory.Contains(Instance->GetVehicleIntInstance()))
		{
			// Change Materials on every part
			GetMesh()->SetMaterial(0, DataToLoad->Inventory.Find(Instance->GetVehicleIntInstance())->VehicleCustomization.BodyPaint);

			for (int i = 0; i < AllVehicleParts.Num(); i++)
			{
				if (AllVehicleParts[i])
				{
					AllVehicleParts[i]->SetMaterial(0, DataToLoad->Inventory.Find(Instance->GetVehicleIntInstance())->VehicleCustomization.BodyPaint);
				}
			}

			if (DataToLoad->Inventory.Find(Instance->GetVehicleIntInstance())->VehicleCustomization.Wheel != nullptr)
			{
				WheelFL->SetStaticMesh(DataToLoad->Inventory.Find(Instance->GetVehicleIntInstance())->VehicleCustomization.Wheel);
				WheelFR->SetStaticMesh(DataToLoad->Inventory.Find(Instance->GetVehicleIntInstance())->VehicleCustomization.Wheel);
				WheelRL->SetStaticMesh(DataToLoad->Inventory.Find(Instance->GetVehicleIntInstance())->VehicleCustomization.Wheel);
				WheelRR->SetStaticMesh(DataToLoad->Inventory.Find(Instance->GetVehicleIntInstance())->VehicleCustomization.Wheel);
			}
		}
	}
}

void AVehiclePawn::PopulateMeshArray()
{

	// Populate AllVehicleParts Array
	if (FrontBumper->IsValidLowLevelFast()) { AllVehicleParts.Add(FrontBumper); }
	if (RearBumper->IsValidLowLevelFast()) { AllVehicleParts.Add(RearBumper); }

	if (FrontLightR->IsValidLowLevelFast()) { AllVehicleParts.Add(FrontLightR); }
	if (FrontLightL->IsValidLowLevelFast()) { AllVehicleParts.Add(FrontLightL); }
	if (BackLightR->IsValidLowLevelFast()) { AllVehicleParts.Add(BackLightR); }
	if (BackLightL->IsValidLowLevelFast()) { AllVehicleParts.Add(BackLightL); }

	if (MirrorR->IsValidLowLevelFast()) { AllVehicleParts.Add(MirrorR); }
	if (MirrorL->IsValidLowLevelFast()) { AllVehicleParts.Add(MirrorL); }

	if (FenderR->IsValidLowLevelFast()) { AllVehicleParts.Add(FenderR); }
	if (FenderL->IsValidLowLevelFast()) { AllVehicleParts.Add(FenderL); }

	if (Hood->IsValidLowLevelFast()) { AllVehicleParts.Add(Hood); }
	if (Engine->IsValidLowLevelFast()) { AllVehicleParts.Add(Engine); }

	if (Trunk->IsValidLowLevelFast()) { AllVehicleParts.Add(Trunk); }
	if (BackWing->IsValidLowLevelFast()) { AllVehicleParts.Add(BackWing); }

	// Populate Deatachable parts array ( not everything can detach )
	VehiclePartsToDetach = AllVehicleParts;
	VehiclePartsToDetach.Remove(Engine);
	VehiclePartsToDetach.Remove(BackWing);
}

void AVehiclePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
	CalculateDistance();
	SelfDrive();
}

void AVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("Throttle", this, &AVehiclePawn::Throttle);
	PlayerInputComponent->BindAxis("Brake", this, &AVehiclePawn::Brake);
	PlayerInputComponent->BindAxis("Steer", this, &AVehiclePawn::Steer);

	PlayerInputComponent->BindAction("Interaction", EInputEvent::IE_Pressed, this, &AVehiclePawn::Interaction);
}

void AVehiclePawn::Throttle(float AxisValue)
{
	if (!bCanDrive) return;
	GetVehicleMovement()->SetThrottleInput(AxisValue);
}

void AVehiclePawn::Brake(float AxisValue)
{
	if (!bCanDrive) return;
	GetVehicleMovement()->SetBrakeInput(AxisValue);
}

void AVehiclePawn::Steer(float AxisValue)
{
	if (!bCanDrive) return;
	GetVehicleMovement()->SetSteeringInput(AxisValue);
}

void AVehiclePawn::CalculateDistance()
{
	if (!bCanCalculateDistance) return;
	const FVector CurrentLocation = GetActorLocation();
	double DistanceOneSec = FVector::Dist(CurrentLocation, LastFrameVector);

	Distance += DistanceOneSec / 100;
	LastFrameVector = CurrentLocation;
}

void AVehiclePawn::ChangeCamera(float ChangeValue, bool Tunnel)
{
	//FRotator NewCameraRot = SpringArm->GetRelativeRotation() + FRotator(0.f, ChangeValue, 0.f);
	FRotator NewCameraRot = FRotator(SpringArm->GetRelativeRotation().Pitch, ChangeValue, SpringArm->GetRelativeRotation().Roll);
	SpringArm->SetRelativeRotation(NewCameraRot);
	SpringArmLastRotation = NewCameraRot;
	if (Tunnel)
	{
		SpringArm->SetRelativeRotation(FRotator(-15.f, NewCameraRot.Yaw, NewCameraRot.Roll));
		SpringArm->TargetArmLength = 600.f;
	}
}

void AVehiclePawn::EndChangCamera(bool Tunnel)
{
	if (Tunnel)
	{
		SpringArm->SetRelativeRotation(SpringArmLastRotation);
		SpringArm->TargetArmLength = SpringArmBaseLenght;
	}
}

void AVehiclePawn::DetachComponent(UStaticMeshComponent* CarPart)
{
	CarPart->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	CarPart->SetSimulatePhysics(true);
	CarPart->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	CarPart->AddImpulse(FVector(0.f, 0.f, 500.f));
}

void AVehiclePawn::AttachComponent(UStaticMeshComponent* CarPart)
{
	CarPart->SetSimulatePhysics(false);
	CarPart->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CarPart->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	CarPart->SetWorldRotation(FRotator::ZeroRotator);
	CarPart->SetRelativeLocation(FVector::ZeroVector);
}

void AVehiclePawn::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!bCanHit) return;
	bCanHit = false;
	GetWorld()->GetTimerManager().SetTimer(HitCooldownTimer, this, &AVehiclePawn::ResetCanHit, 0.3f);

	float Impact = FMath::Floor(NormalImpulse.Length() / 60000.f);
	if (Impact <= 4.f) return;
	HitPoints -= Impact;

	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CameraShake);

	if (HitPoints < ActiveParts * OnePartHitPoints && !VehiclePartsToDetach.IsEmpty())
	{
		int32 Random = FMath::RandRange(0, VehiclePartsToDetach.Num() - 1);
		DetachComponent(VehiclePartsToDetach[Random]);
		VehiclePartsToDetach.RemoveAt(Random);
		ActiveParts--;
	}

	if (HitPoints <= 0.f)
	{
		HitPoints = 0.f;

		AGameplayGamemode* Gamemode = Cast<AGameplayGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
		Gamemode->EndRun();
	}

	UE_LOG(LogTemp, Warning, TEXT("%f"), HitPoints);
}

void AVehiclePawn::ResetCanHit()
{
	bCanHit = true;
}

void AVehiclePawn::Interaction()
{

	AGameplayGamemode* Gamemode = Cast<AGameplayGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
	Gamemode->EndRun();

}

void AVehiclePawn::AddHealth(float HealthAmount)
{
	if (HitPoints + HealthAmount >= MaxHealth)
	{
		HitPoints = MaxHealth;
	}
	else
	{
		HitPoints += HealthAmount;
	}

	UE_LOG(LogTemp, Warning, TEXT("%f"), HitPoints);
}

void AVehiclePawn::SetVehicleState(EVehicleState NewVehicleState)
{
	switch (NewVehicleState)
	{
	case EVehicleState::EVS_Inactive:
		bCanDrive = false;
		bCanCalculateDistance = false;
		break;

	case EVehicleState::EVS_Active:
		Distance = 0.f;
		LastFrameVector = GetActorLocation();
		bCanDrive = true;
		bCanCalculateDistance = true;
		break;

	default:

		break;
	}
}


void AVehiclePawn::PathDriving(USplineComponent* SplineComp)
{
	SplineComponent = SplineComp;
}

void AVehiclePawn::SelfDrive()
{
	if (SplineComponent == nullptr) return;

	FVector ActorLocation = GetActorLocation();
	FVector TangentLocation = SplineComponent->FindTangentClosestToWorldLocation(ActorLocation, ESplineCoordinateSpace::World);
	FVector NormalizedTangent = TangentLocation.GetSafeNormal() * 200.f + ActorLocation;
	FVector TangentNormalizedLocation = SplineComponent->FindLocationClosestToWorldLocation(NormalizedTangent, ESplineCoordinateSpace::World);
	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(ActorLocation, TangentNormalizedLocation);
	FRotator NormalizedDeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(LookAtRot, GetActorRotation());

	double Steering = UKismetMathLibrary::MapRangeClamped(NormalizedDeltaRot.Yaw, -10.f, 10.f, -1.f, 1.f);

	GetVehicleMovement()->SetThrottleInput(0.95f);
	GetVehicleMovement()->SetBrakeInput(0.f);
	GetVehicleMovement()->SetSteeringInput(Steering);
}
