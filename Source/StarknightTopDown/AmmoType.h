#pragma once

UENUM(BlueprintType)
enum class EAmmoType :uint8 {
	EAT_AR = 0 UMETA(DisplayName = "AR"),
	EAT_Buckshot = 1 UMETA(DisplayName = "Buckshot"),
	EAT_ThunderRound = 2 UMETA(DisplayName = "Thunder Round"),
	EAT_Plasma = 3 UMETA(DisplayName = "Plasma"),
	EAT_Voltaic = 4 UMETA(DisplayName = "Voltaic"),

	EAT_MAX = 7 UMETA(DisplayName = "DefaultMAX")
};