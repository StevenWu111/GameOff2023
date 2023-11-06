// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GiantBuddha.generated.h"

UCLASS()
class GAMEOFF_API AGiantBuddha : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGiantBuddha();

	TArray<AActor> TargetActors;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ConeDetectorComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
