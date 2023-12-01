// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "RandomSoundActor.generated.h"

UCLASS()
class GAMEOFF_API ARandomSoundActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARandomSoundActor();

	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioComp;

	FTimerHandle SoundTimerHandle;

	void PlaySound();

	UPROPERTY(EditAnywhere)
	double MinTime = 10.00;

	UPROPERTY(EditAnywhere)
	double MaxTime = 20.00;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

};
