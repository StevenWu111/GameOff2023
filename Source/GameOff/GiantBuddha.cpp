// Fill out your copyright notice in the Description page of Project Settings.


#include "GiantBuddha.h"

#include "GameOffCharacter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGiantBuddha::AGiantBuddha()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMestComponent"));
	ConeDetectorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DetectorMesh"));
	LightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("LightComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	LightComponent->SetupAttachment(MeshComponent);
	ConeDetectorComponent->SetupAttachment(MeshComponent);
}


// Called when the game starts or when spawned
void AGiantBuddha::BeginPlay()
{
	Super::BeginPlay();
	ConeDetectorComponent->OnComponentBeginOverlap.AddDynamic(this,&AGiantBuddha::DetectorOverlapBegin);
}

void AGiantBuddha::DetectorOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AGameOffCharacter* Player = Cast<AGameOffCharacter>(OtherActor))
	{
		MainPlayer = Player;
		CurrStatus = Tracking;
		LightComponent->SetIntensity(LightChangeIntensity);
	}else if (!TargetActors.IsEmpty() && OtherActor == TargetActors[CurrIndex] && CurrStatus == Searching)
	{
		if (CurrIndex == TargetActors.Num()-1)
		{
			CurrIndex = 0;
		}
		else
		{
			CurrIndex++;
		}
	}
}

// Called every frame
void AGiantBuddha::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	switch (CurrStatus)
	{
	case Tracking:
		break;
	default:
		if (!TargetActors.IsEmpty())
		{
			RotateToAPoint(TargetActors[CurrIndex], DeltaTime);
		}
		break;
	}
}

void AGiantBuddha::RotateToAPoint(const AActor* TargetActor, float DeltaTime)
{
	if (TargetActor)
	{
		const FVector CurrLocation = this->GetActorLocation();
		const FVector TargetLocation = TargetActor->GetActorLocation();
		const FRotator RotationBetweenStartNTarget = UKismetMathLibrary::FindLookAtRotation(CurrLocation, TargetLocation);
		const FRotator NextRotation = UKismetMathLibrary::RInterpTo(this->GetActorRotation(),RotationBetweenStartNTarget, DeltaTime, RotationSpeed);
		this->SetActorRotation(NextRotation);
	}
}

