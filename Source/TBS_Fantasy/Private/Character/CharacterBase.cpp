// Copyright NeuroGames


#include "Character/CharacterBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
{ 	
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Shield = CreateDefaultSubobject<USkeletalMeshComponent>("Shield");
	
	Weapon->SetupAttachment(GetMesh(), FName(TEXT("RHMeleeWeaponSocket")));
	Shield->SetupAttachment(GetMesh(), FName(TEXT("LHShieldSocket")));
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
