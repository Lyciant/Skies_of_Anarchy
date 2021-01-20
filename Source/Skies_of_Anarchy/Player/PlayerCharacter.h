// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class SKIES_OF_ANARCHY_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**********************************************************/
	/* Camera Components */
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* CameraSpringArm;
	class UCameraComponent* PlayerCamera;
	
	/* Camera Variables */
	bool bIsInFirstPerson;

	/* Camera Functions */
	void CameraZoom(float AxisInput);
	void ChangeCameraPerspective();

	/**********************************************************/
	/* Grappling hook components */
	bool bIsGrappling;
	class UGrapplingGunComponent* GrapplingGun;
	

	/* Grappling hook Functions */
	void PressedGrapplehook();
	void ReleasedGrapplehook();
	void RealInGrapplehook(float AxisInput);
	void RealOutGrapplehook(float AxisInput);

	/**********************************************************/
	/* Action Bindings */
	void PressedJump();
	void ReleasedJump();
	void PressedShoot();
	void ReleasedShoot();


	/**********************************************************/
	/* GUI bindings */
	void Interact();
	void OpenInventory();
	

	/**********************************************************/
	// Axis Bindings relating to character movement
	void MoveForward(float AxisInput);
	void Moveright(float AxisInput);
	void CameraPitch(float AxisInput);
	void CameraYaw(float AxisInput);


	/**********************************************************/
};
