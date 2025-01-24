#pragma once

UENUM(BlueprintType)
enum class EEnemyAIState :uint8 {
	EEAS_Dead = 0 UMETA(DisplayName = "Dead"),
	EEAS_Relaxed = 1 UMETA(DisplayName = "Relaxed"),
	EEAS_Alert = 2 UMETA(DisplayName = "Alert"),
	EEAS_Combat = 3 UMETA(DisplayName = "Combat"),
	EEAS_Flee = 4 UMETA(DisplayName = "Flee"),

	EEAS_Max = 7 UMETA(DisplayName = "Max")
};