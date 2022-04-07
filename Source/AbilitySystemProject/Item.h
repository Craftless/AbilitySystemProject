// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemStructs.h"
#include "ItemStack.h"
#include "GameplayEffect.h"
#include "Item.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFinishedUsingDelegate, bool, bSuccess);

/**
 * 
 */
UCLASS( BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class ABILITYSYSTEMPROJECT_API UItem : public UObject
{
	GENERATED_BODY()
	
public:
	UItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FItemInfo ItemInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* MeshToDisplay = nullptr;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void GetEffectSpecToApply(class UAbilitySystemComponent* ASC, bool& HasSpec, FGameplayEffectSpecHandle& OutSpec);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ExecuteUse(AProjectCharacter* User);

	UFUNCTION(BlueprintImplementableEvent)
	void UseItem(AProjectCharacter* User);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnFinishedUsingDelegate FOnFinishedUsing;

	// static UItem* GetNone(UObject* Outer);
};
