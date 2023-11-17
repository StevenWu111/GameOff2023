// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserBuddha.h"

#include "GameOffCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ALaserBuddha::ALaserBuddha()
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
void ALaserBuddha::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ALaserBuddha::RotateAreaOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this,&ALaserBuddha::ALaserBuddha::RotateAreaOverlapOver);

	for (auto RotationTemp:TargetRotationsTemp)
	{
		TargetRotations.Add(this->GetActorRotation()+RotationTemp);
	}
}

// Called every frame
void ALaserBuddha::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsRotateClosedToTheTarget())
	{
		RotateToTargetRotation(TargetRotations[CurrIndex],DeltaTime);
	}
}

void ALaserBuddha::RotateToTargetRotation(FRotator Target, float DeltaTime)
{
	const FRotator NextRotation = UKismetMathLibrary::RInterpTo(this->GetActorRotation(),Target, DeltaTime, 0.9f);
	
	this->SetActorRotation(NextRotation);
	
}

void ALaserBuddha::RotateAreaOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Player = Cast<AGameOffCharacter>(OtherActor);
	if (Player)
	{
		Player->InteractableActor = this;
		if (Player->PressEUI)
		{
			WidgetInstance = CreateWidget(GetWorld(), Player->PressEUI);
			if (WidgetInstance)
			{
				WidgetInstance->AddToViewport();
			}
		}
	}
}

void ALaserBuddha::RotateAreaOverlapOver(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Player)
	{
		Player->InteractableActor = nullptr;
		if (WidgetInstance)
		{
			WidgetInstance->RemoveFromParent();
			WidgetInstance = nullptr;
		}
		Player = nullptr;
	}
}

void ALaserBuddha::Interact_Implementation()
{
	IInteractable::Interact_Implementation();

	if (CurrIndex == NULL)
	{
		CurrIndex = 0;
	}
	if (IsRotateClosedToTheTarget())
	{
		if (CurrIndex == TargetRotations.Num()-1)
		{
			CurrIndex = 0;
		}
		else
		{
			CurrIndex++;
		}

		
		if (Player)
		{
			Player->InteractableActor = nullptr;
			if (WidgetInstance)
			{
				WidgetInstance->RemoveFromParent();
				WidgetInstance = nullptr;
			}
		}
	}
}

bool ALaserBuddha::IsRotateClosedToTheTarget()
{
	if (CurrIndex == NULL)
	{
		return true;
	}
	const FVector CurrDirection = this->GetActorForwardVector().GetSafeNormal();
	const FVector TargetVector = TargetRotations[CurrIndex].Vector();
	const float Angle = FMath::Acos(FVector::DotProduct(CurrDirection,TargetVector)) * (180/3.1415926);
	if (Angle >= 1)
	{
		return false;
	}
	this->SetActorRotation(TargetRotations[CurrIndex]);
	UE_LOG(LogTemp,Warning,TEXT("%f"), Angle);
	return true;
}

