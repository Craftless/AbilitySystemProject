// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlot.h"
#include "ItemStack.h"
#include "Item.h"
#include "Engine/Texture2D.h"

bool UItemSlot::GetIsEmpty() 
{
    return ItemStack -> UpdateStackEmptyStatus();
}

UTexture2D* UItemSlot::GetTexture() 
{
    return ItemStack -> Item -> ItemInfo.IconTexture;
}

int32 UItemSlot::GetStackSize() 
{
    return ItemStack -> Amount;
}
