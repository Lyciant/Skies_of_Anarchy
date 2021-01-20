// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GrapplingGunComponent.h"


// DEBUG HELPER
#include "DrawDebugHelpers.h"

 

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating components for and changing default settings for a third person perspective
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->SetRelativeLocationAndRotation(FVector(10.0f, 10.0f, 80.0f), FRotator(0.0f, 0.0f, 0.0f));
	CameraSpringArm->bUsePawnControlRotation = true;
	CameraSpringArm->TargetArmLength = 300.0f;
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	PlayerCamera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
	

	// Creating Grappling Hook Components
	GrapplingGun = CreateDefaultSubobject<UGrapplingGunComponent>(TEXT("GrapplingGun"));
	GrapplingGun->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	//GrapplingGun->SetVisibility(false);
	
	

	// Setting Defaults for grappling hook.
	bIsGrappling = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Binding Action mappings to functions
	{
		// Jumping Action
		InputComponent->BindAction("Spacebar", IE_Pressed, this, &APlayerCharacter::PressedJump);
		InputComponent->BindAction("Spacebar", IE_Released, this, &APlayerCharacter::ReleasedJump);

		// Change Camera Perspective Action
		InputComponent->BindAction("CameraPerspective", IE_Pressed, this, &APlayerCharacter::ChangeCameraPerspective);

		// Weapon Fire Action
		InputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &APlayerCharacter::PressedShoot);
		InputComponent->BindAction("LeftMouseButton", IE_Released, this, &APlayerCharacter::ReleasedShoot);

		// Grapplehook Fire Action
		InputComponent->BindAction("RightMouseButton", IE_Pressed, this, &APlayerCharacter::PressedGrapplehook);
		InputComponent->BindAction("RightMouseButton", IE_Released, this, &APlayerCharacter::ReleasedGrapplehook);

		// Interaction with the world
		InputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
		InputComponent->BindAction("Interact", IE_Released, this, &APlayerCharacter::Interact);

		// Inventory Access
		InputComponent->BindAction("OpenInventory", IE_Pressed, this, &APlayerCharacter::OpenInventory);
	}

	// Binding Axis mappings to functions
	{
		//Forwards and backwards Movement
		InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::Moveright);
		InputComponent->BindAxis("CameraPitch", this, &APlayerCharacter::CameraPitch);
		InputComponent->BindAxis("CameraYaw", this, &APlayerCharacter::CameraYaw);
		InputComponent->BindAxis("MouseWheel", this, &APlayerCharacter::CameraZoom);
	}
}

//Action Mapping Functions
	void APlayerCharacter::PressedJump()
	{
		bPressedJump = true;
	}

	void APlayerCharacter::ReleasedJump()
	{
		bPressedJump = false;
	}

	void APlayerCharacter::PressedShoot()
	{
	}

	void APlayerCharacter::ReleasedShoot()
	{
	}

	void APlayerCharacter::PressedGrapplehook()
	{
		// Creating Variables and Components for grappling hook.
		
		if (!bIsGrappling) {
			GrapplingGun->FireHook();
		}
		
				
	}

	void APlayerCharacter::ReleasedGrapplehook()
	{
		
	}

	void APlayerCharacter::RealInGrapplehook(float AxisInput)
	{
	}

	void APlayerCharacter::RealOutGrapplehook(float AxisInput)
	{
	}

	void APlayerCharacter::Interact()
	{
	}

	void APlayerCharacter::OpenInventory()
	{
	}

	void APlayerCharacter::CameraZoom(float AxisInput)
	{
		if (AxisInput)
		{
			float temp = CameraSpringArm->TargetArmLength + (AxisInput * -20);
			if (temp < 450 && temp > 130)
			{
				CameraSpringArm->TargetArmLength = temp;
			}
		}		
	}

	void APlayerCharacter::ChangeCameraPerspective()
	{
		
		if (bIsInFirstPerson)
		{
			bIsInFirstPerson = false;
			CameraSpringArm->TargetArmLength = 400.0f;	
			PlayerCamera->SetRelativeRotation(FRotator(0.0f,0.0f,0.0f));
		}
		else
		{	
			bIsInFirstPerson = true;
			CameraSpringArm->TargetArmLength = 0.0f;
		}
		
	}

//Axis mapping Functions
void APlayerCharacter::MoveForward(float AxisInput)
{
	if (Controller != nullptr && AxisInput != 0.0f)
	{
		AddMovementInput(PlayerCamera->GetForwardVector(), FMath::Clamp(AxisInput, -1.0f, 1.0f));
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw = Controller->GetControlRotation().Yaw;
		SetActorRotation(NewRotation);		
	}
}

void APlayerCharacter::Moveright(float AxisInput)
{	
	if (Controller != nullptr && AxisInput != 0.0f)
	{
		AddMovementInput(PlayerCamera->GetRightVector(), FMath::Clamp(AxisInput, -1.0f, 1.0f));
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw = Controller->GetControlRotation().Yaw;
		SetActorRotation(NewRotation);
	}
}

void APlayerCharacter::CameraPitch(float AxisInput)
{	
	if (Controller != nullptr && AxisInput != 0.0f)
	{	
		AddControllerPitchInput(-AxisInput);
		if (bIsInFirstPerson) {
			FRotator NewPitch = Controller->GetControlRotation();
			SetActorRotation(NewPitch);
			
		}	
	}
}

void APlayerCharacter::CameraYaw(float AxisInput)
{
	if (Controller != nullptr && AxisInput != 0.0f)
	{
		AddControllerYawInput(AxisInput);
		if (bIsInFirstPerson) {
			FRotator NewYaw = Controller->GetControlRotation();
			SetActorRotation(NewYaw);
		}
	}
}


