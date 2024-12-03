#pragma once

UENUM(BlueprintType)
enum class EStatusEffect :uint8 {
	ESE_Burnt = 0 UMETA(DisplayName = "Burnt"),
	ESE_Stunned = 1 UMETA(DisplayName = "Stunned"),
	ESE_Slowed = 2 UMETA(DisplayName = "Slowed"),

	ESE_Max = 7 UMETA(DisplayName = "DefaultMAX")
};