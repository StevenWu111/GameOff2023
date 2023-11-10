// Fill out your copyright notice in the Description page of Project Settings.


#include "HidingZone.h"

#include "GameOffCharacter.h"

// Sets default values
AHidingZone::AHidingZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		Character = Player;
		if (bIdCrouchNeeded)
		{
			if (Player->bIsCrouch)
			{
				Player->bIsHiding = true;
				//Safety check
				if (GhostVolume)
				{
					GhostVolume->bEnabled = true;
				}
			}
		}
		else
		{
			Player->bIsHiding = true;
			//Safety check
			if (GhostVolume)
			{
				GhostVolume->bEnabled = true;
			}
		}
	}
}

void AHidingZone::SafeAreaOverlapOver(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AGameOffCharacter* Player = Cast<AGameOffCharacter>(OtherActor))
	{
		Player->bIsHiding = false;
		//Safety check
		if (GhostVolume)
		{
			GhostVolume->bEnabled = false;
		}
		Character = nullptr;
	}
}

inline void AHidingZone::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (Character && bIdCrouchNeeded && GhostVolume)
	{
		if (Character->bIsCrouch)
		{
			Character->bIsHiding = true;
			GhostVolume->bEnabled = true;
		}
		else
		{
			Character->bIsHiding = false;
			GhostVolume->bEnabled = false;
		}
	}
}


