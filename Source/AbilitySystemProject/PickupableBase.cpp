// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupableBase.h"

// Sets default values
APickupableBase::APickupableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickupableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

