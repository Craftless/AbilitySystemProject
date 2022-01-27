// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectCustomApplicationRequirement.h"
#include "LevelUpCAR.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEMPROJECT_API ULevelUpCAR : public UGameplayEffectCustomApplicationRequirement
{
	GENERATED_BODY()

public:
	virtual bool CanApplyGameplayEffect_Implementation(const UGameplayEffect* GameplayEffect, const FGameplayEffectSpec& Spec, UAbilitySystemComponent* ASC) const;
	
};
