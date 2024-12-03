// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StarknightTopDownGameModeBase.generated.h"

/**
 * 
 */

UCLASS()
class STARKNIGHTTOPDOWN_API AStarknightTopDownGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Win Condition", meta = (AllowPrivateAccess = "true"))
	int EggsTarget;
};
