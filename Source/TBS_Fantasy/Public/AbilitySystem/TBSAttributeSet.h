// Copyright NeuroGames

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TBSAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class TBS_FANTASY_API UTBSAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UTBSAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/***************** ATTRIBUTE DEFINITIONS ***************************/

	// Health
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Health, Category="Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UTBSAttributeSet, Health)
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	// MaxHealth
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxHealth, Category="Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UTBSAttributeSet, MaxHealth)
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	// Strength
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Strength, Category="Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UTBSAttributeSet, Strength)
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	// Dexterity
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Dexterity, Category="Attributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UTBSAttributeSet, Dexterity)
	UFUNCTION()
	void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const;

	// Constitution
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Constitution, Category="Attributes")
	FGameplayAttributeData Constitution;
	ATTRIBUTE_ACCESSORS(UTBSAttributeSet, Constitution)
	UFUNCTION()
	void OnRep_Constitution(const FGameplayAttributeData& OldConstitution) const;

	// Intelligence
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Intelligence, Category="Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UTBSAttributeSet, Intelligence)
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	// Wisdom
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Wisdom, Category="Attributes")
	FGameplayAttributeData Wisdom;
	ATTRIBUTE_ACCESSORS(UTBSAttributeSet, Wisdom)
	UFUNCTION()
	void OnRep_Wisdom(const FGameplayAttributeData& OldWisdom) const;

	// Charisma
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Charisma, Category="Attributes")
	FGameplayAttributeData Charisma;
	ATTRIBUTE_ACCESSORS(UTBSAttributeSet, Charisma)
	UFUNCTION()
	void OnRep_Charisma(const FGameplayAttributeData& OldCharisma) const;

};
