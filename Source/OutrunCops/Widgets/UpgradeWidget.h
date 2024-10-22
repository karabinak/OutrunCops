// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeWidget.generated.h"

class UMenuWidget;
class AGarage;

USTRUCT(BlueprintType)
struct FWheel
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wheels", meta = (AllowPrivateAccess = "true"))
	UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wheels", meta = (AllowPrivateAccess = "true"))
	int32 Price;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wheels", meta = (AllowPrivateAccess = "true"))
	UTexture2D* Image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wheels", meta = (AllowPrivateAccess = "true"))
	FName Name;
};

USTRUCT(BlueprintType)
struct FPaint
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paints", meta = (AllowPrivateAccess = "true"))
	UMaterial* Paint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paints", meta = (AllowPrivateAccess = "true"))
	int32 Price;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paints", meta = (AllowPrivateAccess = "true"))
	UTexture2D* Image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paints", meta = (AllowPrivateAccess = "true"))
	FName Name;
};

UCLASS()
class OUTRUNCOPS_API UUpgradeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	void SelectPaint(UMaterial* NewMaterial, int32 Value);
	UFUNCTION(BlueprintCallable)
	bool BuyPaint(UMaterial* NewMaterial, int32 Price, int32 Value);

	UFUNCTION(BlueprintCallable)
	void SelectWheels(UStaticMesh* NewWheels, int32 Value);

	UFUNCTION(BlueprintCallable)
	bool BuyWheels(UStaticMesh* NewWheels, int32 Price, int32 Value);

	UFUNCTION(BlueprintCallable)
	void Return();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wheels", meta = (AllowPrivateAccess = "true"))
	TMap<int32, FWheel> Wheels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wheels", meta = (AllowPrivateAccess = "true"))
	TMap<int32, FPaint> Paints;
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Garage", meta = (AllowPrivateAccess = "true"))
	AGarage* GarageRef;

public:

	void SetGarageRef(AGarage* Garage) { GarageRef = Garage; }
};
