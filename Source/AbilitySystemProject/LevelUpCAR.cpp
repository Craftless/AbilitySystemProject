// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpCAR.h"
#include "Characters/ProjectCharacter.h"
#include "AbilitySystemComponent.h"


bool ULevelUpCAR::CanApplyGameplayEffect_Implementation(const UGameplayEffect* GameplayEffect, const FGameplayEffectSpec& Spec, UAbilitySystemComponent* ASC) const 
{
    AProjectCharacter* ProjectCharacter = Cast<AProjectCharacter>(ASC -> GetOwnerActor());
    if (ProjectCharacter) {
        ProjectCharacter -> AttributePointsAvailable++;
    }
    return true;
}
