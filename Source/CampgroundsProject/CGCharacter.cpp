#include "CGCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

ACGCharacter::ACGCharacter()
{
	// Set this character to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Create ASC and attribute set
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UCGAttributeSet>(TEXT("AttributeSet"));
}

void ACGCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Optionally initialize attributes with a Gameplay Effect (GE) here
}

void ACGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Optionally update movement speed from attribute
	if (AttributeSet)
	{
		GetCharacterMovement()->MaxWalkSpeed = GetMovementSpeed();
	}
}

void ACGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind ability inputs here if needed
}

UAbilitySystemComponent* ACGCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

float ACGCharacter::GetCurrentHealth() const
{
	return AttributeSet ? AttributeSet->GetCurrentHealth() : 0.f;
}

float ACGCharacter::GetMaxHealth() const
{
	return AttributeSet ? AttributeSet->GetMaxHealth() : 0.f;
}

float ACGCharacter::GetMovementSpeed() const
{
	return AttributeSet ? AttributeSet->GetMovementSpeed() : 600.f;
}

