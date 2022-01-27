// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemSlot.generated.h"

/**
 * 
 */
class UItemStack;
class UTexture2D;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABILITYSYSTEMPROJECT_API UItemSlot : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemStack* ItemStack;
	UFUNCTION(BlueprintCallable)
	bool GetIsEmpty();

	UTexture2D* GetTexture();
	
	int32 GetStackSize();

};
