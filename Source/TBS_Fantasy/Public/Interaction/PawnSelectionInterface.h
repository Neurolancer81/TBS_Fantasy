// Copyright NeuroGames

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnSelectionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPawnSelectionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TBS_FANTASY_API IPawnSelectionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SelectPawn() = 0;
	virtual void HighlightActor() = 0;
	virtual void UnHighlightActor() = 0;
	
};
