// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectablePaper.h"

#include "Blueprint/UserWidget.h"

// Sets default values
ACollectablePaper::ACollectablePaper()
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
void ACollectablePaper::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ACollectablePaper::CollectAreaOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this,&ACollectablePaper::CollectAreaOverlapOver);
}

void ACollectablePaper::CollectAreaOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Player = Cast<AGameOffCharacter>(OtherActor);
	if (Player)
	{
		Player->InteractableActor = this;
		Player->AddInteractUI();
	}
}

void ACollectablePaper::CollectAreaOverlapOver(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Player)
	{
		Player->InteractableActor = nullptr;
		Player->RemoveInteractUI();
		Player = nullptr;
	}
}

void ACollectablePaper::Interact_Implementation()
{
	IInteractable::Interact_Implementation();
	if (TextUIClass)
	{
		UUserWidget* UITemp =  CreateWidget(GetWorld(), TextUIClass);
		UITemp->AddToViewport();
		if (Player)
		{
			APlayerController* CurrPlayerController = GetWorld()->GetFirstPlayerController();
			CurrPlayerController->SetShowMouseCursor(true);
			CurrPlayerController->SetPause(true);
			
		}
		this->Destroy();
	}
}

// Called every frame
void ACollectablePaper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

