// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameOffCharacter.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "CollectablePaper.generated.h"

UCLASS()
class GAMEOFF_API ACollectablePaper : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectablePaper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
void CollectAreaOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void  CollectAreaOverlapOver(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	AGameOffCharacter* Player;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interact)
	void Interact();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> TextUIClass;

};
