// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserBuddha.h"

// Sets default values
ALaserBuddha::ALaserBuddha()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALaserBuddha::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaserBuddha::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALaserBuddha::Interact_Implementation()
{
	IInteractable::Interact_Implementation();
}

