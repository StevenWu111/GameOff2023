// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchingUpdateZone.h"

// Sets default values
ASearchingUpdateZone::ASearchingUpdateZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASearchingUpdateZone::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASearchingUpdateZone::UpdateZoneOverlapBegin);
}

void ASearchingUpdateZone::UpdateZoneOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GiantBuddha)
	{
		if (GiantBuddha->CurrIndex < GiantBuddha->TargetActors.Num())
		{
			GiantBuddha->AreaIndex++;
			this->Destroy();
		}
	}
}


