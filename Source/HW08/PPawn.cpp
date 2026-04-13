// Fill out your copyright notice in the Description page of Project Settings.
#include "PPawn.h"
#include "EnhancedInputComponent.h"
#include "PPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"



// Sets default values
APPawn::APPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(CapsuleComp);
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComp->SetupAttachment(CapsuleComp);
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(CapsuleComp);
	SpringArmComp->bUsePawnControlRotation = true;
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void APPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*FVector NewLocation = CapsuleComp->GetComponentLocation();
	FRotator NewRotation = CapsuleComp->GetComponentRotation();

	FVector SpringArmSoketL = SpringArmComp->GetSocketLocation(USpringArmComponent::SocketName);
	FRotator SpringArmSoketR = SpringArmComp->GetSocketRotation(USpringArmComponent::SocketName);
	SpringArmComp->SetWorldLocation(NewLocation);
	SpringArmComp->SetWorldRotation(NewRotation);

	CameraComp->SetWorldLocation((NewLocation + FVector(0.0f, SpringArmComp->TargetArmLength, 50.0f)));
	CameraComp->SetWorldRotation(SpringArmSoketR);*/
}

// Called to bind functionality to input
void APPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (APPlayerController* PlayerController = Cast<APPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&APPawn::Move
				);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&APPawn::Look
				);
			}
		}
	}
}

void APPawn::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();
	FVector MoveFront = GetActorForwardVector() * MoveSpeed * MoveInput.X;
	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddActorLocalOffset(MoveFront);
		//AddActorLocalOffset(GetActorForwardVector());
	}
	FVector MoveRight = GetActorRightVector() * MoveSpeed * MoveInput.Y;
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddActorLocalOffset(MoveRight);
		//AddActorLocalOffset(GetActorForwardVector());
	}
}
void APPawn::Look(const FInputActionValue& value)
{

	FVector2D LookInput = value.Get<FVector2D>();
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);

	/*	FVector2D LookInput = value.Get<FVector2D>();
		FRotator LookYaw = FRotator(0.0f, 5.0f, 0.0f) * LookInput.X;
		AddActorLocalRotation(LookYaw);
		FRotator LookPitch = FRotator(5.0f, 0.0f, 0.0f) * LookInput.Y;
		AddActorLocalRotation(LookPitch);
		*/
}