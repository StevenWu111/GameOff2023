// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameOffCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Interactable.h"
#include "Blueprint/UserWidget.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AGameOffCharacter

AGameOffCharacter::AGameOffCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	LightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("LightComponent"));
	LightComponent->SetupAttachment(this->GetFirstPersonCameraComponent());

	CrouchEyeOffset = FVector(0.0f);
	CrouchSpeed = 12.0f;

}

void AGameOffCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	if (HalfHeightAdjust == 0.0f)
	{
		return;
	}
	
	const float StartBaseEyeHeight = BaseEyeHeight;
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	CrouchEyeOffset.Z += StartBaseEyeHeight - BaseEyeHeight + HalfHeightAdjust;
	GetFirstPersonCameraComponent()->SetRelativeLocation(FVector(0.0f,0.0f, BaseEyeHeight), false);
}

void AGameOffCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	if (HalfHeightAdjust == 0.0f)
	{
		return;
	}
	const float StartBaseEyeHeight = BaseEyeHeight;
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	CrouchEyeOffset.Z += StartBaseEyeHeight - BaseEyeHeight - HalfHeightAdjust;
	GetFirstPersonCameraComponent()->SetRelativeLocation(FVector(0.0f,0.0f, BaseEyeHeight), false);
}

void AGameOffCharacter::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	GetFirstPersonCameraComponent()->GetCameraView(DeltaTime,OutResult);
	OutResult.Location += CrouchEyeOffset;
}

void AGameOffCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

void AGameOffCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	float CrouchInterpTime = FMath::Min(1.0f, CrouchSpeed * DeltaSeconds);
	CrouchEyeOffset = CrouchEyeOffset * FVector3d(1.0f - CrouchInterpTime);

	ScaleSize(DeltaSeconds);
}

void AGameOffCharacter::ScaleSize(float DeltaTime)
{
	const float CurrentScale = this->GetActorScale().X;
	FVector NextScale;
	const FVector TargetScaleDownSize = FVector3d(ScaleDownSize);
	const FVector TargetScaleUpSize = FVector3d(1.0f);
	switch (CurrScaleStatus)
	{
	case ScaleDown:
		if (abs(CurrentScale-ScaleDownSize) <= 0.02 )
		{
			this->SetActorScale3D(TargetScaleDownSize);
			CurrScaleStatus = SmallScale;
		}
		else
		{
			NextScale = this->GetActorScale() - FVector3d(1.0f) * FVector3d(ScaleSpeed) * FVector3d(DeltaTime);
			this->SetActorScale3D(NextScale);
		}
		break;
	case ScaleUp:
		if (abs(CurrentScale-1.0f) <= 0.02)
		{
			this->SetActorScale3D(TargetScaleUpSize);
			CurrScaleStatus = BigScale;
		}
		else
		{
			NextScale = this->GetActorScale() + FVector3d(1.0f) * FVector3d(ScaleSpeed) * FVector3d(DeltaTime);
			this->SetActorScale3D(NextScale);
		}
		break;
		default:
			break;
	}
	
	
}

//////////////////////////////////////////////////////////////////////////// Input

void AGameOffCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGameOffCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGameOffCharacter::Look);

		// Toggle the flash light
		EnhancedInputComponent->BindAction(FlashLightAction, ETriggerEvent::Started, this, &AGameOffCharacter::ToggleFlashLight);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AGameOffCharacter::CrouchFunction);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AGameOffCharacter::StartInteract);

		EnhancedInputComponent->BindAction(SwitchSize, ETriggerEvent::Started, this, &AGameOffCharacter::StartSwitchSize);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


/*
 * The functions that will be called when player input something
 */
void AGameOffCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	if(CurrScaleStatus == ScaleUp || CurrScaleStatus == ScaleDown)
	{
		return;
	}
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AGameOffCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGameOffCharacter::ToggleFlashLight(const FInputActionValue& Value)
{
	if (bIsFlashLightOpen)
	{
		LightComponent->SetVisibility(false);
	}
	else
	{
		LightComponent->SetVisibility(true);
	}
	bIsFlashLightOpen = !bIsFlashLightOpen;
}

void AGameOffCharacter::CrouchFunction(const FInputActionValue& Value)
{
	if (CurrScaleStatus == SmallScale)
	{
		return;
	}
	if (bIsCrouch)
	{
		this->UnCrouch();
	}
	else
	{
		this->Crouch();
	}
	bIsCrouch = !bIsCrouch;
}


void AGameOffCharacter::StartInteract(const FInputActionValue& Value)
{
	if (!InteractableActor)
	{
		return;
	}
	if (InteractableActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		IInteractable::Execute_Interact(InteractableActor);
	}
}

void AGameOffCharacter::StartSwitchSize(const FInputActionValue& Value)
{
	if (CurrScaleStatus != SmallScale && CurrScaleStatus != BigScale)
	{
		return;
	}
	if (this->GetActorScale() == FVector3d(1.0f))
	{
		if (bIsCrouch)
		{
			CrouchFunction(NULL);
		}
		CurrScaleStatus = ScaleDown;
	}
	else
	{
		CurrScaleStatus = ScaleUp;
	}
}


void AGameOffCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AGameOffCharacter::GetHasRifle()
{
	return bHasRifle;
}

