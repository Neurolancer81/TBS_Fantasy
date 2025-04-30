// Copyright NeuroGames


#include "Game/PlayerControllers/TBSPlayerState.h"

#include "AbilitySystem/TBSAbilitySystemComponent.h"
#include "AbilitySystem/TBSAttributeSet.h"

ATBSPlayerState::ATBSPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTBSAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UTBSAttributeSet>("AttributeSet");
	SetNetUpdateFrequency(100.0f);
}

UAbilitySystemComponent* ATBSPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
