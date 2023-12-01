// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameOffGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStart);

UCLASS(minimalapi)
class AGameOffGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameOffGameMode();

	FGameStart StartGameDelegate;
};



