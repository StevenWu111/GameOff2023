// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GiantBuddha.h"
#include "GameFramework/Actor.h"
#include "SearchingUpdateZone.generated.h"

UCLASS()
class GAMEOFF_API ASearchingUpdateZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASearchingUpdateZone();

	UPROPERTY(EditAnywhere)
	AGiantBuddha* GiantBuddha;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateZoneOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
