// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AmmoType.h"
#include "GameFramework/DamageType.h"
#include "StatusEffect.h"
#include "StatusEffectInterface.h"
#include "StatusEffectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARKNIGHTTOPDOWN_API UStatusEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusEffectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TMap<EStatusEffect, bool> StatusEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* StunnedEffect;

	class UNiagaraComponent* ActiveStunEffect;
	//UNiagaraSystem* BurnEffect;
	//UNiagaraSystem* SlowEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TMap<EStatusEffect, float> StatusEffectMax;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION()
	void SetStatusEffect(EStatusEffect NewStatus, bool IsActive);

	UFUNCTION()
	bool QueryStatusEffects(EStatusEffect Query);

	UFUNCTION()
	bool IsStatusActive(EStatusEffect Query);

	UFUNCTION(BlueprintCallable)
	void ResetStunned();

	UFUNCTION(BlueprintCallable)
	void IncreaseStun(float Increase);
	
	void IncreaseBurn(float Increase);
	
	UFUNCTION()
	void IncreaseStatusValue(float InDamage, EStatusEffect InStatusEffect);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float StunValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float BurnValue;
};
