// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameOffCharacter.h"
#include "Interactable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "LaserBuddha.generated.h"

UCLASS()
class GAMEOFF_API ALaserBuddha : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaserBuddha();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* LaserMeshComponent;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* SecLaserMeshComponent;
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interact)
	void Interact();

	FRotator TargetRotation;

	void RotateToTargetRotation(FRotator Target, float DeltaTime);

	UPROPERTY(EditAnywhere)
	TArray<FRotator> TargetRotationsTemp;

	TArray<FRotator> TargetRotations;

	int CurrIndex = NULL;

	AGameOffCharacter* Player;

	bool bIsRotating = false;

	bool IsRotateClosedToTheTarget();
	
	UFUNCTION()
	void RotateAreaOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void  RotateAreaOverlapOver(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void LaserHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FHitResult HitResult;

	UPROPERTY(EditAnywhere)
	int Range = 5000;

	FCollisionQueryParams TraceParams;

	UWorld* World;

	const FName TraceTag = "MyTraceTag";

	FVector InitiScale;
	FVector CollisionInitiScale;

	UPROPERTY(EditAnywhere, Category = PushForce)
	int PushBackForce = 3000;

	FVector TempLocation;

	

};


