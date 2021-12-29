// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TaggedActor.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTaggedActor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ABILITYSYSTEMPROJECT_API ITaggedActor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	uint8 GetTeamID() { return TeamID; }
	virtual bool IsOtherHostile(AActor* ActorToCheck) { 
		ITaggedActor* TaggedActor = Cast<ITaggedActor>(ActorToCheck);
		if (!TaggedActor) return false;
		if (TaggedActor -> GetTeamID() == GetTeamID()) return false;
		return true;
	}

protected:
	uint8 TeamID = 255;

};
