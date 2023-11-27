// Fill out your copyright notice in the Description page of Project Settings.


#include "TheFinalTable.h"

// Sets default values
ATheFinalTable::ATheFinalTable()
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
void ATheFinalTable::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ATheFinalTable::CollectAreaOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this,&ATheFinalTable::CollectAreaOverlapOver);
	
}

void ATheFinalTable::CollectAreaOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Player = Cast<AGameOffCharacter>(OtherActor);
	if (Player)
	{
		Player->InteractableActor = this;
		Player->AddInteractUI();
	}
}

void ATheFinalTable::CollectAreaOverlapOver(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Player)
	{
		Player->InteractableActor = nullptr;
		Player->RemoveInteractUI();
		Player = nullptr;
	}
}

// Called every frame
void ATheFinalTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATheFinalTable::Interact_Implementation()
{
	IInteractable::Interact_Implementation();
}

