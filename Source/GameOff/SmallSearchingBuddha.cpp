// Fill out your copyright notice in the Description page of Project Settings.


#include "SmallSearchingBuddha.h"

#include "GameOffCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASmallSearchingBuddha::ASmallSearchingBuddha()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0,5,0);
	GCComponent = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GCComponent"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	GCComponent->SetupAttachment(this->GetCapsuleComponent());
	AudioComponent->SetupAttachment(GCComponent);
	SphereComponent->SetupAttachment(this->GetCapsuleComponent());
	

}

// Called when the game starts or when spawned
void ASmallSearchingBuddha::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&ASmallSearchingBuddha::ActorOverlapBegin);
	AudioComponent->Stop();
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

void ASmallSearchingBuddha::ActorOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AController* ControllerTemp = this->GetController())
	{
		if (Cast<AGameOffCharacter>(OtherActor))
		{
			if (UCapsuleComponent* CapsuleComponentTemp = this->GetCapsuleComponent())
			{
				AudioComponent->Stop();
				CapsuleComponentTemp->OnComponentBeginOverlap.RemoveDynamic(this,&ASmallSearchingBuddha::ActorOverlapBegin);
				CapsuleComponentTemp->SetCollisionResponseToChannels(ECR_Ignore);
				GCComponent->SetSimulatePhysics(true);
				ControllerTemp->Destroy();
				this->UnPossessed();
			}
			Cast<AGameOffCharacter>(OtherActor)->UpdateHealth(-Damage);
			Cast<AGameOffCharacter>(OtherActor)->AddDamageUI();
		}
	}
}


