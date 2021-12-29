// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectCharacter.h"
#include "AbilitySystemComponent.h"
#include "../AttributeSetBase.h"


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
	}
	bIsDead = false;
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

void AProjectCharacter::AcquireAbility(TSubclassOf<class UGameplayAbility> AbilityToAcquire) 
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

bool AProjectCharacter::IsOtherActorHostile(AActor* ActorToCheck) 
{
	return IsOtherHostile(ActorToCheck);
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

void AProjectCharacter::OnHealthChanged(float Health, float MaxHealth, bool FullHealth) 
{
	if (bIsDead) return;
	if (Health <= 0.f) {
		BP_OnDeath();
		bIsDead = true;
	}
	if (FullHealth) {
		AddGameplayTag(FullHealthTag);
	}
	else {
		RemoveGameplayTag(FullHealthTag);
	}
	BP_OnHealthChanged(Health, MaxHealth, FullHealth);
}

void AProjectCharacter::OnManaChanged(float Mana, float MaxMana) 
{
	BP_OnManaChanged(Mana, MaxMana);
}

void AProjectCharacter::OnStaminaChanged(float Stamina, float MaxStamina) 
{
	BP_OnStaminaChanged(Stamina, MaxStamina);
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

