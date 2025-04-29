// Copyright NeuroGames


#include "Character/CharacterBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
{ 	
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Weapon->SetupAttachment(GetMesh(), FName(TEXT("RHMeleeWeaponSocket")));

	Shield = CreateDefaultSubobject<USkeletalMeshComponent>("Shield");
	Shield->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Shield->SetupAttachment(GetMesh(), FName(TEXT("LHShieldSocket")));
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
