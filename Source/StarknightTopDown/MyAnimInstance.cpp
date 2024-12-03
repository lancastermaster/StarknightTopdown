// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"

void UMyAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (InstanceOwner == nullptr)
	{
		InstanceOwner = Cast<ACharacter>(TryGetPawnOwner());
	}

	if (InstanceOwner)
	{
		FVector Velocity{ InstanceOwner -> GetVelocity() };
		Velocity.Z = 0;
		SpeedX = Velocity.X;
		SpeedY = Velocity.Y;
	}
}
