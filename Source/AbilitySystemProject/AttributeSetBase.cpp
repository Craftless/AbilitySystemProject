// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "Characters/ProjectCharacter.h"


UAttributeSetBase::UAttributeSetBase() : Health(100.f), MaxHealth(100.f), Mana(100.f), MaxMana(100.f), Stamina(100.f), MaxStamina(100.f)
{
    Health = MaxHealth;
    Mana = MaxMana;
    Stamina = MaxStamina;
}

void UAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData & Data) 
{
    Super::PostGameplayEffectExecute(Data);

    Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));
    Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.f, MaxHealth.GetCurrentValue()));
    if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Health))) {
        OnHealthChanged.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue(), Health.GetCurrentValue() == MaxHealth.GetCurrentValue());
    }

    Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.f, MaxMana.GetCurrentValue()));
    Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(), 0.f, MaxMana.GetCurrentValue()));
    if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Mana))) {
        OnManaChanged.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
        UE_LOG(LogTemp, Warning, TEXT("Hello"));
    }

    Stamina.SetCurrentValue(FMath::Clamp(Stamina.GetCurrentValue(), 0.f, MaxStamina.GetCurrentValue()));
    Stamina.SetBaseValue(FMath::Clamp(Stamina.GetBaseValue(), 0.f, MaxStamina.GetCurrentValue()));
    if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Stamina))) {
        OnStaminaChanged.Broadcast(Stamina.GetCurrentValue(), MaxStamina.GetCurrentValue());
    }
}
