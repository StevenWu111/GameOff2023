// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserBuddha.h"

#include "GameOffCharacter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ALaserBuddha::ALaserBuddha()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMestComponent"));
	LaserMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserMestComponent"));
	SecLaserMeshComponent= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondLaserMestComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	MeshComponent->SetupAttachment(RootComponent);
	BoxComponent->SetupAttachment(MeshComponent);
	LaserMeshComponent->SetupAttachment(MeshComponent);
	SecLaserMeshComponent->SetupAttachment(MeshComponent);
}

// Called when the game starts or when spawned
void ALaserBuddha::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ALaserBuddha::RotateAreaOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this,&ALaserBuddha::ALaserBuddha::RotateAreaOverlapOver);

	SecLaserMeshComponent->OnComponentHit.AddDynamic(this,&ALaserBuddha::LaserHit);

	for (auto RotationTemp:TargetRotationsTemp)
	{
		TargetRotations.Add(this->GetActorRotation()+RotationTemp);
	}
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	const FCollisionQueryParams Temp(FName(TEXT("Trace"), true, true));
	TraceParams = Temp;
	// Should we simple or complex collision?
    TraceParams.bTraceComplex = true;
    // We don't need Physics materials
    TraceParams.bReturnPhysicalMaterial = false;
    // Add our ActorsToIgnore
    TraceParams.AddIgnoredActors(IgnoreActors);
	TraceParams.TraceTag = TraceTag;

	InitiScale = LaserMeshComponent->GetComponentScale();
	CollisionInitiScale = SecLaserMeshComponent->GetComponentScale();

}

// Called every frame
void ALaserBuddha::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsRotateClosedToTheTarget())
	{
		RotateToTargetRotation(TargetRotations[CurrIndex],DeltaTime);
	}
	if (!World)
	{
		return;
	}
	const FVector StartLocation = this->GetActorLocation() + this->GetActorForwardVector()*2;
	const FVector EndLocation = this->GetActorLocation() + this->GetActorForwardVector()*Range;
	World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, TraceParams);
	World->DebugDrawTraceTag = TraceTag;
	if (HitResult.GetActor() != nullptr)
	{
		const float XScale = HitResult.Distance /20.0f;
		LaserMeshComponent->SetWorldScale3D(FVector(XScale,InitiScale.Y,InitiScale.Z));
		SecLaserMeshComponent->SetWorldScale3D(FVector(CollisionInitiScale.X,CollisionInitiScale.Y,XScale/5));
	}
	else
	{
		LaserMeshComponent->SetWorldScale3D(FVector(Range,InitiScale.Y,InitiScale.Z));
		SecLaserMeshComponent->SetWorldScale3D(FVector(CollisionInitiScale.X,CollisionInitiScale.Y,Range));
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
		Player->AddInteractUI();
	}
}

void ALaserBuddha::RotateAreaOverlapOver(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Player)
	{
		Player->InteractableActor = nullptr;
		Player->RemoveInteractUI();
		Player = nullptr;
	}
}

void ALaserBuddha::LaserHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (AGameOffCharacter* OverlapPlayer = Cast<AGameOffCharacter>(OtherActor))
	{
		const FVector CollisionLocation = Hit.Location;
		FVector Direction = OverlapPlayer->GetActorLocation() - CollisionLocation;
		Direction.Normalize();
		Direction = Direction*PushBackForce;
		OverlapPlayer->LaunchCharacter(Direction, true, true);
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
			Player->RemoveInteractUI();
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

