// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameTrigger.h"

#include "GameOffCharacter.h"
#include "GameOffGameMode.h"
#include "Components/BoxComponent.h"

// Sets default values
AStartGameTrigger::AStartGameTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AStartGameTrigger::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AStartGameTrigger::CollectAreaOverlapBegin);
	
	
}

// Called every frame
void AStartGameTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStartGameTrigger::CollectAreaOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AGameOffCharacter>(OtherActor))
	{
		if (AGameOffGameMode* CurrGameMode = Cast<AGameOffGameMode>(GetWorld()->GetAuthGameMode()))
		{
			CurrGameMode->StartGameDelegate.Broadcast();
			this->Destroy();
		}
	}
}

