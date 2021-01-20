// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CableComponent.h"
#include "GrapplingGunComponent.generated.h"

/**
 * 
 */
UCLASS()
class SKIES_OF_ANARCHY_API UGrapplingGunComponent : public UCableComponent
{
	GENERATED_BODY()
	
public:
	UGrapplingGunComponent();

	//Setting Up Variables
	float MaxDistance;
	float TravelRate;
	float ReelRate;
	//USceneComponent* AttachmentPoint;

	//Setting up Functionos
	void FireHook();
	void AttachHook();
	void DetachHook();
};
