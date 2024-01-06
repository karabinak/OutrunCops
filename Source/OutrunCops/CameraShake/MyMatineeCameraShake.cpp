// Fill out your copyright notice in the Description page of Project Settings.


#include "OutrunCops/CameraShake/MyMatineeCameraShake.h"

UMyMatineeCameraShake::UMyMatineeCameraShake()
{
    OscillationDuration = 0.25f;
    OscillationBlendInTime = 0.05f;
    OscillationBlendOutTime = 0.05f;

    RotOscillation.Pitch.Amplitude = FMath::RandRange(2.0f, 5.0f);
    RotOscillation.Pitch.Frequency = FMath::RandRange(5.0f, 15.0f);

    RotOscillation.Yaw.Amplitude = FMath::RandRange(2.0f, 5.0f);
    RotOscillation.Yaw.Frequency = FMath::RandRange(5.0f, 15.0f);
}