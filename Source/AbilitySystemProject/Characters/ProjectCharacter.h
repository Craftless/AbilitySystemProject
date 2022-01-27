// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "../TaggedActor.h"
#include "GameplayEffectTypes.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "GameplayEffect.h"
#include "ProjectCharacter.generated.h"


UENUM() 
enum class TeamID : uint8 {

};

UCLASS()
class ABILITYSYSTEMPROJECT_API AProjectCharacter : public ACharacter, public IAbilitySystemInterface, public ITaggedActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AProjectCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const { return SystemComp; }
	UFUNCTION(BlueprintCallable)
	void AcquireAbility(TSubclassOf<class UGameplayAbility> AbilityToAcquire);
	UFUNCTION(BlueprintCallable)
	void AcquireAbilities(TArray<TSubclassOf<class UGameplayAbility>> AbilitiesToAcquire);
	UPROPERTY(BlueprintReadOnly)
	bool bIsDead = false;
	UFUNCTION(BlueprintCallable)
	bool IsOtherActorHostile(AActor* ActorToCheck);
	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffectToTargetByTargetData(const FGameplayEffectSpecHandle& GESpecHandle, const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	UFUNCTION(BlueprintCallable)
	bool GetCooldownRemainingForTag(FGameplayTagContainer CooldownTags, float & TimeRemaining, float & CooldownDuration);
	UPROPERTY(BlueprintReadWrite)
	int32 AttributePointsAvailable;
	UFUNCTION(BlueprintCallable)
	float GetCurrentAttackDamage();
	UFUNCTION(BlueprintCallable)
	float GetCurrentAttackDamageAccordingToASC1();
	float GetCurrentAttackDamageAccordingToASC2();
	float GetCurrentAttackDamageAccordingToASC3();
	float GetCurrentAttackDamageAccordingToAttribute();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAbilitySystemComponent* SystemComp = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ProjectCharacter")
	class UAttributeSetBase* AttributeSetBase;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnHealthChanged"))
	void BP_OnHealthChanged(float Health, float MaxHealth, bool FullHealth, float PreviousHealth, AActor* EffectInstigator);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnManaChanged"))
	void BP_OnManaChanged(float Mana, float MaxMana);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnStaminaChanged"))
	void BP_OnStaminaChanged(float Stamina, float MaxStamina);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnExperienceChanged"))
	void BP_OnExperienceChanged(float Experience, float MaxExperience);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnMainAttributeChanged"))
	void BP_OnMainAttributeChanged(EAttributeType Type, float CurrentAttributeValue);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnDeath"))
	void BP_OnDeath();
	UFUNCTION(BlueprintCallable)
	void SetTeamIDByControllerType();
	UFUNCTION(BlueprintCallable)
	void AddGameplayTag(const struct FGameplayTag& Tag);
	UFUNCTION(BlueprintCallable)
	void RemoveGameplayTag(const FGameplayTag& Tag);
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag FullHealthTag;
	UFUNCTION(BlueprintCallable)
	void EnableInputControl();
	UFUNCTION(BlueprintCallable)
	void DisableInputControl();
	UFUNCTION(BlueprintCallable)
	void Stun(float StunDuration);
	UFUNCTION(BlueprintImplementableEvent)
	void BPStun(float StunDuration);
	void AddAbilityToUI(TSubclassOf<class UGameplayAbilityBase> AbilityToAdd);
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 MeleeComboCount = 1;
	UFUNCTION(BlueprintCallable)
	void EndCombo(); 

	UFUNCTION(BlueprintImplementableEvent)
	void OnActiveGameplayEffectAddedCallback(UAbilitySystemComponent* Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);
	UFUNCTION(BlueprintCallable)
	bool GameplayEffectSpecContainsTag(const FGameplayEffectSpec& SpecToCheck, FGameplayTag TagToCheck);
	UFUNCTION(BlueprintCallable)
	UAbilitySystemComponent* GetInstigatorASC(const FGameplayEffectSpec& InSpec);

private:
	void MoveForward(float Value);
	void MoveRight(float Value);

	UFUNCTION()
	void OnHealthChanged(float Health, float MaxHealth, bool FullHealth, float PreviousHealth, AActor* EffectInstigator);
	UFUNCTION()
	void OnManaChanged(float Mana, float MaxMana);
	UFUNCTION()
	void OnStaminaChanged(float Stamina, float MaxStamina);
	UFUNCTION()
	void OnExperienceChanged(float Experience, float MaxExperience);
	UFUNCTION()
	void OnMainAttributeChanged(EAttributeType Type, float CurrentAttributeValue);


	FTimerHandle TimerHandle;
	

};
