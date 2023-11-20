// Fill out your copyright notice in the Description page of Project Settings.


#include "SmallBuddhaAIController.h"

ASmallBuddhaAIController::ASmallBuddhaAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	SightConfiguration = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Configuration"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	SightConfiguration->SightRadius = SightRadius;
	SightConfiguration->LoseSightRadius = LoseSightRadius;
	SightConfiguration->PeripheralVisionAngleDegrees = FieldOfView;
	SightConfiguration->SetMaxAge(SightAge);
	SightConfiguration->DetectionByAffiliation.bDetectEnemies = true;
	SightConfiguration->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfiguration->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfiguration->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*SightConfiguration);
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ASmallBuddhaAIController::OnSensesUpdated);
	
	TargetPlayer = nullptr;
}

void ASmallBuddhaAIController::BeginPlay()
{
	Super::BeginPlay();
	if(!AIBlackboard)
	return;
	if(!ensure(BehaviorTree))return;
	UseBlackboard(AIBlackboard, BlackboardComponent);
	RunBehaviorTree(BehaviorTree);
	
}

void ASmallBuddhaAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ASmallBuddhaAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(TargetPlayer)
    {
		BlackboardComponent->SetValueAsVector("PlayerPosition", TargetPlayer->GetActorLocation());
    }
}

FRotator ASmallBuddhaAIController::GetControlRotation() const
{
	if(GetPawn())
	{
		return FRotator(0, GetPawn()->GetActorRotation().Yaw, 0);
	}
	return FRotator::ZeroRotator;
}

void ASmallBuddhaAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
}

void ASmallBuddhaAIController::OnSensesUpdated(AActor* UpdatedActor, FAIStimulus Stimulus)
{
	APawn* TemporaryPawn = Cast<APawn>(UpdatedActor);
	if(TemporaryPawn && TemporaryPawn->IsPlayerControlled())
	{
		if(Stimulus.WasSuccessfullySensed())
		{
			UE_LOG(LogTemp, Warning, TEXT("Set Actor Location"));
			TargetPlayer = TemporaryPawn;
			BlackboardComponent->SetValueAsBool("ChasePlayer", true);
			BlackboardComponent->SetValueAsVector("PlayerPosition", TargetPlayer->GetActorLocation());
		} else
		{
			TargetPlayer = nullptr;
			BlackboardComponent->ClearValue("ChasePlayer");
		}
	}
}


void ASmallBuddhaAIController::GenerateNewRandomLocation()
{
	NavigationSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
	if(NavigationSystem)
	{
		FNavLocation ReturnLocation;
		NavigationSystem->GetRandomPointInNavigableRadius(GetPawn()->GetActorLocation(), 2000,ReturnLocation);
		BlackboardComponent->SetValueAsVector("PatrolPoint", ReturnLocation.Location);
	}
}
