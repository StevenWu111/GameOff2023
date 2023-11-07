// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameOffCharacter.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Actor.h"
#include "GiantBuddha.generated.h"

enum GiantBuddhaStatus
{
	Searching,
	Tracking
};
UCLASS()
class GAMEOFF_API AGiantBuddha : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGiantBuddha();

	UPROPERTY(EditAnywhere)
	TArray<AActor*> TargetActors;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ConeDetectorComponent;

	GiantBuddhaStatus CurrStatus = Searching;

	UPROPERTY(EditAnywhere)
	USpotLightComponent* LightComponent;

	void RotateToAPoint(const AActor* TargetActor, float DeltaTime);

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 10.0f;

	UPROPERTY(EditAnywhere)
	float LightChangeIntensity = 1500;

	int32 CurrIndex = 0;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void DetectorOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	AGameOffCharacter* MainPlayer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
