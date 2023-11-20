// Fill out your copyright notice in the Description page of Project Settings.


#include "SmallSearchingBuddha.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASmallSearchingBuddha::ASmallSearchingBuddha()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0,5,0);

}

// Called when the game starts or when spawned
void ASmallSearchingBuddha::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASmallSearchingBuddha::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASmallSearchingBuddha::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

