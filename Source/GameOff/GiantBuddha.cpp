// Fill out your copyright notice in the Description page of Project Settings.


#include "GiantBuddha.h"

// Sets default values
AGiantBuddha::AGiantBuddha()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = defualt
}

// Called when the game starts or when spawned
void AGiantBuddha::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGiantBuddha::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

