// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomSoundActor.h"

// Sets default values
ARandomSoundActor::ARandomSoundActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Comp"));

	AudioComp->SetupAttachment(RootComponent);

}

void ARandomSoundActor::PlaySound()
{
	GetWorld()->GetTimerManager().ClearTimer(SoundTimerHandle);
	AudioComp->Play();
	const double RandTime = FMath::RandRange(MinTime, MaxTime);
	GetWorld()->GetTimerManager().SetTimer(SoundTimerHandle,this,&ARandomSoundActor::PlaySound, RandTime, false, RandTime);
}

// Called when the game starts or when spawned
void ARandomSoundActor::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(SoundTimerHandle,this,&ARandomSoundActor::PlaySound, 3.0f, false, 0.0f);
}


