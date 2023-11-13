// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstLevelGameStateBase.h"

AFirstLevelGameStateBase::AFirstLevelGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFirstLevelGameStateBase::BeginPlay()
{
	Super::BeginPlay();
}

void AFirstLevelGameStateBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (GetWorld())
	{
		const float TotalSecond = GetWorld()->GetTimeSeconds();
		Minutes = TotalSecond / 60;
		Seconds = FMath::Fmod(TotalSecond, 60.0f);
	}
}
