// Fill out your copyright notice in the Description page of Project Settings.


#include "GrapplingGunComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

//For Debugging the hook raycast
#include "DrawDebugHelpers.h"

UGrapplingGunComponent::UGrapplingGunComponent()
{
	//USceneComponent* AttachmentPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
}

void UGrapplingGunComponent::FireHook()
{
	FHitResult Hit(ForceInit);
	FCollisionQueryParams HookParamaters;
	HookParamaters.AddIgnoredActor(GetAttachmentRootActor());
	FVector StartingPoint = GetAttachmentRootActor()->GetActorLocation();
	FVector ForwardsVector = GetForwardVector();
	FVector EndPoint = StartingPoint + (ForwardsVector * 3000);
	

	GetWorld()->LineTraceSingleByChannel(Hit, StartingPoint, EndPoint, ECC_Visibility, HookParamaters);
	DrawDebugLine(GetWorld(), StartingPoint, EndPoint, FColor::Green, false, 5.0f, false, 2.0f);
}

void UGrapplingGunComponent::AttachHook()
{
}

void UGrapplingGunComponent::DetachHook()
{
}
