// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilityBase.h"


FGameplayAbilityInfo UGameplayAbilityBase::GetAbilityInfo() 
{
    UGameplayEffect* CDEffect = GetCooldownGameplayEffect();
    UGameplayEffect* CostEffect = GetCostGameplayEffect();
    if (CDEffect && CostEffect) {
        float CD;
        CDEffect -> DurationMagnitude.GetStaticMagnitudeIfPossible(1, CD);
        float Cost;
        EAbilityCostType CostType = EAbilityCostType::Mana;
        if (CostEffect -> Modifiers.Num() > 0) {
            FGameplayModifierInfo CostEffectInfo = CostEffect -> Modifiers[0];
            CostEffectInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost);
            FGameplayAttribute CostAttr = CostEffectInfo.Attribute;
            FString AttrName = CostAttr.AttributeName;
            if (AttrName == TEXT("Health")) {
                CostType = EAbilityCostType::Health;
            }
            else if (AttrName == TEXT("Mana")) {
                CostType = EAbilityCostType::Mana;
            }
            else if (AttrName == TEXT("Stamina")) {
                CostType = EAbilityCostType::Stamina;
            }
            return FGameplayAbilityInfo(CD, Cost, CostType, UIMaterial, GetClass());
        }
    }
    return FGameplayAbilityInfo();
}
