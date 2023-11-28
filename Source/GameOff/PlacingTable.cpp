// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacingTable.h"

// Sets default values
APlacingTable::APlacingTable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MainMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMestComponent"));
	FirstObjectMeshComponent= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstObjectMeshComponent"));
	SecondObjectMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondObjectMeshComponent"));
	ThirdObjectMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ThirdObjectMeshComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	MainMeshComponent->SetupAttachment(RootComponent);
	FirstObjectMeshComponent->SetupAttachment(RootComponent);
	SecondObjectMeshComponent->SetupAttachment(RootComponent);
	ThirdObjectMeshComponent->SetupAttachment(RootComponent);
	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlacingTable::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&APlacingTable::InteractAreaOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this,&APlacingTable::InteractAreaOverlapOver);

	FirstObjectMeshComponent->SetVisibility(false);
	SecondObjectMeshComponent->SetVisibility(false);
	ThirdObjectMeshComponent->SetVisibility(false);

	MeshComponents.Add(FirstObjectMeshComponent);
	MeshComponents.Add(SecondObjectMeshComponent);
	MeshComponents.Add(ThirdObjectMeshComponent);
	
}

void APlacingTable::InteractAreaOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Player = Cast<AGameOffCharacter>(OtherActor);
	if (Player)
	{
		Player->InteractableActor = this;
		Player->AddInteractUI();
	}
}

void APlacingTable::InteractAreaOverlapOver(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Player)
	{
		Player->RemoveInteractUI();
		Player->InteractableActor = nullptr;
		Player = nullptr;
	}
}

void APlacingTable::Interact_Implementation()
{
	IInteractable::Interact_Implementation();
	if (Player && !Player->CollectedObjects.IsEmpty())
	{
		for (const auto CurrCollectObjects:Player->CollectedObjects)
		{
			switch (CurrCollectObjects)
			{
			case ECollectObjectType::ECOT_First:
				FirstObjectMeshComponent->SetVisibility(true);
				break;
			case ECollectObjectType::ECOT_Second:
				SecondObjectMeshComponent->SetVisibility(true);
				break;
			case ECollectObjectType::ECOT_Third:
				ThirdObjectMeshComponent->SetVisibility(true);
				break;
			default:
				break;
			}
		}
		Player->CollectedObjects.Empty();
		if (!MeshComponents.IsEmpty())
		{
			for (const auto Mesh:MeshComponents)
			{
				if (!Mesh->IsVisible())
				{
					return;
				}
			}
		}
		GetWorld()->GetFirstPlayerController()->SetPause(true);
		
	}
}

// Called every frame
void APlacingTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

