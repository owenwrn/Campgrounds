


#include "CGGameMode.h"
#include "Characters/PlayerCharacter.h"
#include "GameFramework/SpectatorPawn.h"
#include "CGPlayerState.h"
#include "CGAttributeSet.h"
#include "CGGameStateBase.h"

ACGGameMode::ACGGameMode()
{
	RespawnDelay = 5.0f;
}

void ACGGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (ACGGameStateBase* GS = GetGameState<ACGGameStateBase>())
	{
		GS->OnMatchEnd.AddDynamic(this, &ACGGameMode::HandleDayEnd);
	}
}

void ACGGameMode::PlayerDied(AController* Controller)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ASpectatorPawn* SpectatorPawn = GetWorld()->SpawnActor<ASpectatorPawn>(SpectatorClass, Controller->GetPawn()->GetActorTransform(), SpawnParameters);

	Controller->UnPossess();
	Controller->Possess(Cast<APawn>(SpectatorPawn));

	FTimerHandle RespawnTimerHandle;
	FTimerDelegate RespawnDelegate;

	RespawnDelegate = FTimerDelegate::CreateUObject(this, &ACGGameMode::RespawnHero, Controller);
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, RespawnDelegate, RespawnDelay, false);
}

void ACGGameMode::HandleDayEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Day has ended!"));
	
	
}

void ACGGameMode::HandleNextDay()
{
	if (ACGGameStateBase* GS = GetGameState<ACGGameStateBase>())
	{
		GS->Multicast_NextDay();
		GS->StartMatchTimer();
	}

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC)
		{
			ACGPlayerState* PS = PC->GetPlayerState<ACGPlayerState>();
			if (PS)
			{
				RespawnDelay = 0.5f;
				UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
				if (ASC)
				{
					// Apply a mod that sets Health = 0
					ASC->ApplyModToAttribute(
						UCGAttributeSet::GetCurrentHealthAttribute(),
						EGameplayModOp::Override,
						0.0f
					);					
				}
			}
		}
	}
}

void ACGGameMode::RespawnHero(AController* Controller)
{
	if (Controller->IsPlayerController())
	{
		// Respawn player hero
		AActor* PlayerStart = FindPlayerStart(Controller);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		APlayerCharacter* Player = GetWorld()->SpawnActor<APlayerCharacter>(GetDefaultPawnClassForController(Controller), PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), SpawnParameters);

		APawn* OldSpectatorPawn = Controller->GetPawn();
		Controller->UnPossess();
		OldSpectatorPawn->Destroy();
		Controller->Possess(Player);
	}
}
