// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectCharacter.h"
#include "AbilitySystemComponent.h"
#include "../AttributeSetBase.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Abilities/GameplayAbility.h"
#include "../GameplayAbilityBase.h"
#include "../PlayerControllerBase.h"


// Sets default values
AProjectCharacter::AProjectCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(FName("Ability System Component"));
	AttributeSetBase = CreateDefaultSubobject<UAttributeSetBase>(FName("Attribute Set Base Component"));

}

// Called when the game starts or when spawned
void AProjectCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (ensure(AttributeSetBase)) {
		AttributeSetBase -> OnHealthChanged.AddDynamic(this, &AProjectCharacter::OnHealthChanged);
		AttributeSetBase -> OnManaChanged.AddDynamic(this, &AProjectCharacter::OnManaChanged);
		AttributeSetBase -> OnStaminaChanged.AddDynamic(this, &AProjectCharacter::OnStaminaChanged);
		AttributeSetBase -> OnExperienceChanged.AddDynamic(this, &AProjectCharacter::OnExperienceChanged);
		AttributeSetBase -> OnMainAttributeChanged.AddDynamic(this, &AProjectCharacter::OnMainAttributeChanged);
	}
	bIsDead = false;
	MeleeComboCount = 1;
	GetAbilitySystemComponent() -> OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this, &AProjectCharacter::OnActiveGameplayEffectAddedCallback);
}



// Called every frame
void AProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent -> BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent -> BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent -> BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent -> BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent -> BindAxis("MoveForward", this, &AProjectCharacter::MoveForward);
	PlayerInputComponent -> BindAxis("MoveRight", this, &AProjectCharacter::MoveRight);
	
}

void AProjectCharacter::AcquireAbility(TSubclassOf<UGameplayAbility> AbilityToAcquire) 
{
	if (!ensure(SystemComp)) return;
	if (!HasAuthority()) return;
	if (AbilityToAcquire) {
		FGameplayAbilitySpecDef SpecDef = FGameplayAbilitySpecDef();
		SpecDef.Ability = AbilityToAcquire;
		FGameplayAbilitySpec Spec = FGameplayAbilitySpec(SpecDef, 1);
		SystemComp -> GiveAbility(Spec);
	}
	SystemComp -> InitAbilityActorInfo(this, this);
}

void AProjectCharacter::AcquireAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToAcquire) 
{
	if (HasAuthority()) {
		for (TSubclassOf<UGameplayAbility> AbilityClass : AbilitiesToAcquire) {
			AcquireAbility(AbilityClass);
			if (AbilityClass -> IsChildOf(UGameplayAbilityBase::StaticClass())) {

				TSubclassOf<UGameplayAbilityBase> AbilityBaseClass = *AbilityClass;
				if (AbilityBaseClass) {
					AddAbilityToUI(AbilityBaseClass);
				}
			}
		}
	}
}

bool AProjectCharacter::IsOtherActorHostile(AActor* ActorToCheck) 
{
	return IsOtherHostile(ActorToCheck);
}

void AProjectCharacter::ApplyGameplayEffectToTargetByTargetData(const FGameplayEffectSpecHandle& GESpecHandle, const FGameplayAbilityTargetDataHandle& TargetDataHandle) 
{
	for (TSharedPtr<FGameplayAbilityTargetData> Data : TargetDataHandle.Data) {
		Data -> ApplyGameplayEffectSpec(*GESpecHandle.Data.Get());
	}
}


void AProjectCharacter::MoveForward(float Value) 
{
	if (Value == 0 || !ensure(GetController())) return;
	FRotator YawRotation(0, GetController() -> GetControlRotation().Yaw, 0);

	FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(ForwardVector, Value);
}

void AProjectCharacter::MoveRight(float Value) 
{
	if (Value == 0 || !ensure(GetController())) return;
	FRotator YawRotation(0, GetController() -> GetControlRotation().Yaw, 0);

	FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}

void AProjectCharacter::OnHealthChanged(float Health, float MaxHealth, bool FullHealth, float PreviousHealth, AActor* EffectInstigator) 
{
	if (bIsDead) return;
	if (FullHealth) {
		AddGameplayTag(FullHealthTag);
	}
	else {
		RemoveGameplayTag(FullHealthTag);
	}
	BP_OnHealthChanged(Health, MaxHealth, FullHealth, PreviousHealth, EffectInstigator);


	if (Health <= 0.f) {
		BP_OnDeath();
		bIsDead = true;
	}
}

void AProjectCharacter::OnManaChanged(float Mana, float MaxMana) 
{
	BP_OnManaChanged(Mana, MaxMana);
}

void AProjectCharacter::OnStaminaChanged(float Stamina, float MaxStamina) 
{
	BP_OnStaminaChanged(Stamina, MaxStamina);
}

void AProjectCharacter::OnExperienceChanged(float Experience, float MaxExperience) 
{
	BP_OnExperienceChanged(Experience, MaxExperience);
}

void AProjectCharacter::OnMainAttributeChanged(EAttributeType Type, float CurrentAttributeValue) 
{

	BP_OnMainAttributeChanged(Type, CurrentAttributeValue);
}



void AProjectCharacter::SetTeamIDByControllerType() 
{
	if (!GetController()) return;
	if (IsPlayerControlled()) {
		TeamID = 0;
	}
	else {
		TeamID = 1;
	}
}

void AProjectCharacter::AddGameplayTag(const FGameplayTag& Tag) 
{
	GetAbilitySystemComponent() -> AddLooseGameplayTag(Tag);
	GetAbilitySystemComponent() -> SetTagMapCount(Tag, 1);
}

void AProjectCharacter::RemoveGameplayTag(const FGameplayTag& Tag) 
{
	GetAbilitySystemComponent() -> RemoveLooseGameplayTag(Tag);
}

void AProjectCharacter::EnableInputControl() 
{
	if (IsPlayerControlled()) {
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		EnableInput(PlayerController);
	}
	else {
		AAIController* AIController = Cast<AAIController>(GetController());
		if (AIController) AIController -> GetBrainComponent() -> RestartLogic();
	}
}

void AProjectCharacter::DisableInputControl() 
{
	if (IsPlayerControlled()) {
			APlayerController* PlayerController = Cast<APlayerController>(GetController());
			DisableInput(PlayerController);
		}
		else {
			AAIController* AIController = Cast<AAIController>(GetController());
			if (AIController) AIController -> GetBrainComponent() -> StopLogic("Stunned");
		}
}

void AProjectCharacter::Stun(float StunDuration) 
{
	// DisableInputControl();
	// GetWorldTimerManager().SetTimer(TimerHandle, this, &AProjectCharacter::EnableInputControl, StunDuration, false);

	// Deprecated function

	BPStun(StunDuration);
}

void AProjectCharacter::AddAbilityToUI(TSubclassOf<UGameplayAbilityBase> AbilityToAdd) 
{
	APlayerControllerBase* Controller = Cast<APlayerControllerBase>(GetController());
	if (Controller) {

		UGameplayAbilityBase* AbilityInstance = AbilityToAdd.Get() -> GetDefaultObject<UGameplayAbilityBase>();
		if (AbilityInstance) {
			FGameplayAbilityInfo AbilityInfo = AbilityInstance -> GetAbilityInfo();
			Controller -> AddAbilityToUI(AbilityInfo, AbilityInstance);
		}
	}
}

void AProjectCharacter::EndCombo() 
{
	MeleeComboCount = 1;
}

bool AProjectCharacter::GameplayEffectSpecContainsTag(const FGameplayEffectSpec& SpecToCheck, FGameplayTag TagToCheck) 
{
	FGameplayTagContainer TagContainer;
	SpecToCheck.GetAllAssetTags(TagContainer);
	return TagContainer.HasTag(TagToCheck);
}

UAbilitySystemComponent* AProjectCharacter::GetInstigatorASC(const FGameplayEffectSpec& InSpec) 
{
	return InSpec.GetContext().GetInstigatorAbilitySystemComponent();
}


bool AProjectCharacter::GetCooldownRemainingForTag(FGameplayTagContainer CooldownTags, float & TimeRemaining, float & CooldownDuration)
{
	if (GetAbilitySystemComponent() && CooldownTags.Num() > 0)
	{
		TimeRemaining = 0.f;
		CooldownDuration = 0.f;

		FGameplayEffectQuery const Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTags);
		TArray< TPair<float, float> > DurationAndTimeRemaining = GetAbilitySystemComponent()->GetActiveEffectsTimeRemainingAndDuration(Query);
		if (DurationAndTimeRemaining.Num() > 0)
		{
			int32 BestIdx = 0;
			float LongestTime = DurationAndTimeRemaining[0].Key;
			for (int32 Idx = 1; Idx < DurationAndTimeRemaining.Num(); ++Idx)
			{
				if (DurationAndTimeRemaining[Idx].Key > LongestTime)
				{
					LongestTime = DurationAndTimeRemaining[Idx].Key;
					BestIdx = Idx;
				}
			}

			TimeRemaining = DurationAndTimeRemaining[BestIdx].Key;
			CooldownDuration = DurationAndTimeRemaining[BestIdx].Value;

			return true;
		}
	}

	return false;
}

float AProjectCharacter::GetCurrentAttackDamage() 
{
	return AttributeSetBase -> AttackDamage.GetCurrentValue();
}


float AProjectCharacter::GetCurrentAttackDamageAccordingToASC1() 
{
	return GetAbilitySystemComponent() -> GetNumericAttribute(UAttributeSetBase::GetAttackDamageAttribute());
}

float AProjectCharacter::GetCurrentAttackDamageAccordingToASC2() 
{
	return GetAbilitySystemComponent() -> GetNumericAttributeBase(UAttributeSetBase::GetAttackDamageAttribute());
}

float AProjectCharacter::GetCurrentAttackDamageAccordingToASC3() 
{
	return GetAbilitySystemComponent() -> GetNumericAttributeChecked(UAttributeSetBase::GetAttackDamageAttribute());
}

float AProjectCharacter::GetCurrentAttackDamageAccordingToAttribute() 
{
	return UAttributeSetBase::GetAttackDamageAttribute().GetNumericValue(AttributeSetBase);
}
