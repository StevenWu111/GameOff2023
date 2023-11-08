// Fill out your copyright notice in the Description page of Project Settings.


#include "HidingZone.h"

#include "GameOffCharacter.h"

// Sets default values
AHidingZone::AHidingZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHidingZone::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AHidingZone::SafeAreaOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AHidingZone::SafeAreaOverlapOver);
}

void AHidingZone::SafeAreaOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AGameOffCharacter* Player = Cast<AGameOffCharacter>(OtherActor))
	{
		if (bIdCrouchNeeded && Player->bIsCrouch)
		{
			Player->bIsHiding = true;
		}
		else
		{
			Player->bIsHiding = true;
		}
	}
}

void AHidingZone::SafeAreaOverlapOver(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AGameOffCharacter* Player = Cast<AGameOffCharacter>(OtherActor))
	{
		Player->bIsHiding = false;
	}
}


