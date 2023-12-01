// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirstLevelGameStateBase.h"
#include "SmallSearchingBuddha.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "BellPlayer.generated.h"

UCLASS()
class GAMEOFF_API ABellPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABellPlayer();

	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere)
	float TriggerTimeInSeconds = 60.5f;

	int32 PlayedNumTemp = 1;

	int32 CurrPlayNum = 0;
	void PlaySound();

	void LoopingSound();
	
	FTimerHandle StartSoundTimerHandle;

	FTimerHandle LoopingSoundTimerHandle;

	AFirstLevelGameStateBase* CurrGameState;

	UPROPERTY(EditAnywhere, Category = SmallBuddha)
	TArray<ASmallSearchingBuddha*> SmallBuddhas;

	UPROPERTY(EditAnywhere, Category = SmallBuddha)
	TArray<int32> SearchingBuddhaSpawnTime;

	int32 CurrIndex = 0;

	UFUNCTION()
	void GameStartTrigger();
	

	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

};
