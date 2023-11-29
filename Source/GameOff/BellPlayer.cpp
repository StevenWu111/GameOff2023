// Fill out your copyright notice in the Description page of Project Settings.


#include "BellPlayer.h"

// Sets default values
ABellPlayer::ABellPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Comp"));

	AudioComp->SetupAttachment(RootComponent);
}

void ABellPlayer::PlaySound()
{
	if (CurrGameState)
	{
		GetWorld()->GetTimerManager().SetTimer(LoopingSoundTimerHandle,this,&ABellPlayer::LoopingSound, 3.0f, true, 0.0f);
		if (CurrIndex > SearchingBuddhaSpawnTime.Num()-1)
		{
			return;
		}
		if (CurrGameState->Minutes == SearchingBuddhaSpawnTime[CurrIndex])
		{
			CurrIndex++;
			const int32 RandIndex = FMath::RandRange(0,SmallBuddhas.Num()-1);
			SmallBuddhas[RandIndex]->SpawnDefaultController();
			SmallBuddhas[RandIndex]->AudioComponent->Play();
			SmallBuddhas.RemoveAt(RandIndex);
		}
	}
}

void ABellPlayer::LoopingSound()
{
	const int32 BellNum = CurrGameState->Minutes;
	if (PlayedNumTemp < BellNum)
	{
		AudioComp->Play();
		PlayedNumTemp++;
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(LoopingSoundTimerHandle);
		PlayedNumTemp = 0;
	}
	
}

// Called when the game starts or when spawned
void ABellPlayer::BeginPlay()
{
	Super::BeginPlay();
	AudioComp->Stop();
	CurrGameState = Cast<AFirstLevelGameStateBase>(GetWorld()->GetGameState());
	GetWorld()->GetTimerManager().SetTimer(StartSoundTimerHandle,this,&ABellPlayer::PlaySound, TriggerTimeInSeconds, true, TriggerTimeInSeconds);
	
}


