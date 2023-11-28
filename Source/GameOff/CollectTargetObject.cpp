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
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ACollectTargetObject::CollectAreaOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this,&ACollectTargetObject::CollectAreaOverlapOver);
}

void ACollectTargetObject::CollectAreaOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Player = Cast<AGameOffCharacter>(OtherActor);
	if (Player)
	{
		Player->InteractableActor = this;
		Player->AddInteractUI();
	}
}

void ACollectTargetObject::CollectAreaOverlapOver(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
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
void ACollectTargetObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollectTargetObject::Interact_Implementation()
{
	IInteractable::Interact_Implementation();
	if (Player)
	{
		Player->CollectedObjects.Add(this->ObjectType);
	}
	this->Destroy();
}

