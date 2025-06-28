


#include "CampgroundsProject/Characters/CGCharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "CampgroundsProject/CGCharacter.h"
#include "GameplayTagContainer.h"

UCGCharacterMovementComponent::UCGCharacterMovementComponent()
{
	SprintSpeedMultiplier = 1.4f;
}

float UCGCharacterMovementComponent::GetMaxSpeed() const
{
	ACGCharacter* Owner = Cast<ACGCharacter>(GetOwner());
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() No Owner"), *FString(__FUNCTION__));
		return Super::GetMaxSpeed();
	}

	if (!Owner->IsAlive())
	{
		return 0.0f;
	}

	if (Owner->GetAbilitySystemComponent()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun"))))
	{
		return 0.0f;
	}

	if (RequestToStartSprinting)
	{
		return Owner->GetMovementSpeed() * SprintSpeedMultiplier;
	}

	return Owner->GetMovementSpeed();
}

void UCGCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	//The Flags parameter contains the compressed input flags that are stored in the saved move.
	//UpdateFromCompressed flags simply copies the flags from the saved move into the movement component.
	//It basically just resets the movement component to the state when the move was made so it can simulate from there.
	RequestToStartSprinting = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
}

FNetworkPredictionData_Client* UCGCharacterMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner != NULL);

	if (!ClientPredictionData)
	{
		UCGCharacterMovementComponent* MutableThis = const_cast<UCGCharacterMovementComponent*>(this);

		MutableThis->ClientPredictionData = new FCGNetworkPredictionData_Client(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
	}

	return ClientPredictionData;
}

void UCGCharacterMovementComponent::StartSprinting()
{
	RequestToStartSprinting = true;
}

void UCGCharacterMovementComponent::StopSprinting()
{
	RequestToStartSprinting = false;
}

void UCGCharacterMovementComponent::FCGSavedMove::Clear()
{
	Super::Clear();

	SavedRequestToStartSprinting = false;
}

uint8 UCGCharacterMovementComponent::FCGSavedMove::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if (SavedRequestToStartSprinting)
	{
		Result |= FLAG_Custom_0;
	}

	return Result;
}

bool UCGCharacterMovementComponent::FCGSavedMove::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const
{
	//Set which moves can be combined together. This will depend on the bit flags that are used.
	if (SavedRequestToStartSprinting != ((FCGSavedMove*)&NewMove)->SavedRequestToStartSprinting)
	{
		return false;
	}

	return Super::CanCombineWith(NewMove, Character, MaxDelta);
}

void UCGCharacterMovementComponent::FCGSavedMove::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	UCGCharacterMovementComponent* CharacterMovement = Cast<UCGCharacterMovementComponent>(Character->GetCharacterMovement());
	if (CharacterMovement)
	{
		SavedRequestToStartSprinting = CharacterMovement->RequestToStartSprinting;
	}
}

void UCGCharacterMovementComponent::FCGSavedMove::PrepMoveFor(ACharacter* Character)
{
	Super::PrepMoveFor(Character);

	UCGCharacterMovementComponent* CharacterMovement = Cast<UCGCharacterMovementComponent>(Character->GetCharacterMovement());
	if (CharacterMovement)
	{
	}
}

UCGCharacterMovementComponent::FCGNetworkPredictionData_Client::FCGNetworkPredictionData_Client(const UCharacterMovementComponent& ClientMovement)
	: Super(ClientMovement)
{
}

FSavedMovePtr UCGCharacterMovementComponent::FCGNetworkPredictionData_Client::AllocateNewMove()
{
	return FSavedMovePtr(new FCGSavedMove());
}



