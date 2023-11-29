// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "GameFramework/Character.h"
#include "SmallSearchingBuddha.generated.h"

UCLASS()
class GAMEOFF_API ASmallSearchingBuddha : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASmallSearchingBuddha();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	UGeometryCollectionComponent* GCComponent;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioComponent;

	UFUNCTION()
	void ActorOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
