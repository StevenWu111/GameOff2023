// Fill out your copyright notice in the Description page of Project Settings.


#include "BuddhaHand.h"

// Sets default values
ABuddhaHand::ABuddhaHand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMestComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	MeshComponent->SetupAttachment(RootComponent);
	BoxComponent->SetupAttachment(MeshComponent);
}

// Called when the game starts or when spawned
void ABuddhaHand::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABuddhaHand::SelfDestroy, 5.0f, false, 5.0f);
	
}

// Called every frame
void ABuddhaHand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CurrLocation = this->GetActorLocation();
	const FVector Direction = this->GetActorForwardVector();
	CurrLocation += Direction * Speed * DeltaTime;
	this->SetActorLocation(CurrLocation);
}

void ABuddhaHand::SelfDestroy()
{
	this->Destroy();
}

void ABuddhaHand::DetectorOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

