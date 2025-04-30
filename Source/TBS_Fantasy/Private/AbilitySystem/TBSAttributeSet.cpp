// Copyright NeuroGames


#include "AbilitySystem/TBSAttributeSet.h"

#include "Net/UnrealNetwork.h"

UTBSAttributeSet::UTBSAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
	InitStrength(10.f);
	InitDexterity(10.f);
	InitConstitution(10.f);
	InitIntelligence(10.f);
	InitWisdom(10.f);
	InitCharisma(10.f);
}

void UTBSAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UTBSAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTBSAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTBSAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTBSAttributeSet, Dexterity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTBSAttributeSet, Constitution, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTBSAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTBSAttributeSet, Wisdom, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTBSAttributeSet, Charisma, COND_None, REPNOTIFY_Always);
}

void UTBSAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTBSAttributeSet, Health, OldHealth);
	
}

void UTBSAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTBSAttributeSet, MaxHealth, OldMaxHealth);
}

void UTBSAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTBSAttributeSet, Strength, OldStrength);
}

void UTBSAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTBSAttributeSet, Dexterity, OldDexterity);
}

void UTBSAttributeSet::OnRep_Constitution(const FGameplayAttributeData& OldConstitution) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTBSAttributeSet, Constitution, OldConstitution);
}

void UTBSAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTBSAttributeSet, Intelligence, OldIntelligence);
}

void UTBSAttributeSet::OnRep_Wisdom(const FGameplayAttributeData& OldWisdom) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTBSAttributeSet, Wisdom, OldWisdom);
}

void UTBSAttributeSet::OnRep_Charisma(const FGameplayAttributeData& OldCharisma) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTBSAttributeSet, Charisma, OldCharisma);
}
