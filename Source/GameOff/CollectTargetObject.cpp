// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectTargetObject.h"

// Sets default values
ACollectTargetObject::ACollectTargetObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMestComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	MeshComponent->SetupAttachment(RootComponent);
	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACollectTargetObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectTargetObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

