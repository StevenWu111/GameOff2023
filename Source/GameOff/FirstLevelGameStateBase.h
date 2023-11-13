// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FirstLevelGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF_API AFirstLevelGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	AFirstLevelGameStateBase();
	

	UPROPERTY(BlueprintReadOnly)
	int32 Minutes = 0;

	UPROPERTY(BlueprintReadOnly)
	float Seconds = 0.0f;


protected:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
};
