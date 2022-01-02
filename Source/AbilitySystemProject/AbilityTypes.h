// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilityTypes.generated.h"


UENUM(BlueprintType)
enum class EAbilityCostType : uint8 {
	Health,
	Mana,
	Stamina
};


USTRUCT(BlueprintType)
struct FGameplayAbilityInfo {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CooldownDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAbilityCostType CostType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance* UIMat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UGameplayAbilityBase> AbilityClass;

	FGameplayAbilityInfo();
	FGameplayAbilityInfo(float InCooldownDuration, float InCost, EAbilityCostType InCostType, UMaterialInstance* InUIMat, TSubclassOf<class UGameplayAbilityBase> InAbilityClass);
};