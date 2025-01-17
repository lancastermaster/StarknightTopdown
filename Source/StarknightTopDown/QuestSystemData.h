#pragma once

#include "Engine/DataTable.h"
#include "QuestSystemData.generated.h"

UENUM(BlueprintType)
enum class EObjectiveType : uint8
{
	EOT_Location = 0 UMETA(DisplayName = "Location"),
	EOT_Kill = 1 UMETA(DisplayName = "Kill"),
	EOT_Interact = 2 UMETA(DisplayName = "Interact"),
	EOT_Collect = 3 UMETA(DislpayName = "Collect")
};

USTRUCT(BlueprintType)
struct FObjectiveDetails {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest System", meta = (AllowPrivateAccess = "true"))
	FText ObjectiveName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest System", meta = (AllowPrivateAccess = "true"))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest System", meta = (AllowPrivateAccess = "true"))
	EObjectiveType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest System", meta = (AllowPrivateAccess = "true"))
	FString ObjectiveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest System", meta = (AllowPrivateAccess = "true"))
	int Quantity;
};

USTRUCT(BlueprintType)
struct FQuestDetails : public FTableRowBase {
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest System", meta = (AllowPrivateAccess = "true"))
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest System", meta = (AllowPrivateAccess = "true"))
	FText Description;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest System", meta = (AllowPrivateAccess = "true"))
	//TArray<FObjectiveDetails> QuestObjectives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest System", meta = (AllowPrivateAccess = "true"))
	EObjectiveType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest System", meta = (AllowPrivateAccess = "true"))
	int Quantity;
};

USTRUCT(BlueprintType)
struct FQuestSaveData {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest System", meta = (AllowPrivateAccess = "true"))
	TMap<FString, int> QuestProgress;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest System", meta = (AllowPrivateAccess = "true"))
	TMap<FString, bool> IsComplete;
};