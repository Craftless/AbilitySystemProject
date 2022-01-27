// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "Item.h"
#include "ItemSlot.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < MaxSlots; i++) {
		UItemSlot* Slot = NewObject<UItemSlot>(this, UItemSlot::StaticClass()); 
		Slot -> ItemStack = NewObject<UItemStack>(Slot, UItemStack::StaticClass()); 
		Slot -> ItemStack -> MakeItemStackEmpty();
		Slots.Add(Slot);
	}

	FinishedBeginPlay();
	// ...
	
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<UItemSlot*> UInventory::GetSlots() 
{
	return Slots;
}

TArray<UItemSlot*> UInventory::SetSlots(TArray<UItemSlot*> InSlots) 
{
	Slots = InSlots;
	return Slots;
}

bool UInventory::AddItemStackToSlots(UItemStack* ItemStackToAdd) 
{
	for (UItemSlot* Slot : Slots) {
		if (TryAddItemStackToSlot(Slot, ItemStackToAdd)) return true;
	}
	return false;
}

bool UInventory::TryAddItemStackToSlot(UItemSlot* SlotToCheck, UItemStack* ItemStackToAdd, bool bSimulate) 
{	

	Debug(ItemStackToAdd -> Item -> ItemInfo.MaxStackSize, ItemStackToAdd);
	UE_LOG(LogTemp, Warning, TEXT("FISADOFI, %i"), ItemStackToAdd -> Item -> ItemInfo.MaxStackSize);
	if (bSimulate) {
		if (SlotToCheck -> GetIsEmpty())  return true;
		if (SlotToCheck -> ItemStack -> IsFull()) return false;
		if (SlotToCheck -> ItemStack -> Item -> ItemInfo.ItemClass == ItemStackToAdd -> Item -> ItemInfo.ItemClass) return true;
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("FIRST"));


	if (SlotToCheck -> GetIsEmpty()) {
		UE_LOG(LogTemp, Warning, TEXT("SECOND"));
		int32 LeftoverAmount;
		int32 AmountConsumed;
		bool bIsOver = SlotToCheck -> ItemStack -> LeftoverAmount(ItemStackToAdd, LeftoverAmount, AmountConsumed);
		UE_LOG(LogTemp, Warning, TEXT("THIRD"));
		if (bIsOver) {
			SlotToCheck -> ItemStack -> SetStackItemAndAmount(ItemStackToAdd -> Item, 0);
			UE_LOG(LogTemp, Warning, TEXT("Item: %s, Itemstacktoadd item: %s, LeftoverAmount: %i, AmountConsumed: %i"), *SlotToCheck -> ItemStack -> Item -> ItemInfo.Name, *ItemStackToAdd -> Item -> ItemInfo.Name, LeftoverAmount, AmountConsumed);

			SlotToCheck -> ItemStack -> AddToAmount(AmountConsumed);
			ItemStackToAdd -> AddToAmount(-AmountConsumed);
			return false;
		}
		UE_LOG(LogTemp, Warning, TEXT("FIFTH"));
		SlotToCheck -> ItemStack -> SetStackItemAndAmount(ItemStackToAdd -> Item, 0);
		SlotToCheck -> ItemStack -> AddToAmount(ItemStackToAdd -> Amount);
		return true;
	}

	if (SlotToCheck -> ItemStack -> IsFull()) return false;
	if (SlotToCheck -> ItemStack -> Item -> ItemInfo.ItemClass == ItemStackToAdd -> Item -> ItemInfo.ItemClass) {
		int32 LeftoverAmount;
		int32 AmountConsumed;
		bool bIsOver = SlotToCheck -> ItemStack -> LeftoverAmount(ItemStackToAdd, LeftoverAmount, AmountConsumed);
		if (bIsOver) {
			SlotToCheck -> ItemStack -> AddToAmount(AmountConsumed);
			ItemStackToAdd -> AddToAmount(-AmountConsumed);
			return false;
		}

		SlotToCheck -> ItemStack -> AddToAmount(ItemStackToAdd -> Amount);
		return true;
	}
	return false;
}

bool UInventory::CanContainItemStack(UItemStack* StackToCheck)
{
	for (UItemSlot* Slot : Slots) {
		bool bSuccess = TryAddItemStackToSlot(Slot, StackToCheck, true);
		if (bSuccess) return true;
	}
	return false;
}




