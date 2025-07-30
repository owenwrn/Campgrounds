// Fill out your copyright notice in the Description page of Project Settings.

#include "CGGEExecutionCalculation.h"
#include "CampgroundsProject/AbilitySystem/CGAbilitySystemComponent.h"
#include "CampgroundsProject/CGAttributeSet.h"

struct  FDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(CurrentHealth);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack);

	FDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCGAttributeSet, Attack, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UCGAttributeSet, CurrentHealth, Target, false);
	}
};

static const FDamageStatics& DamageStatics()
{
	static FDamageStatics DmgStatics;
	return DmgStatics;
}

UCGGEExecutionCalculation::UCGGEExecutionCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().AttackDef);
	RelevantAttributesToCapture.Add(DamageStatics().CurrentHealthDef);
}

void UCGGEExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// Obtain references to the target and source Ability System Component. Each copy of a Gameplay Effect will have one of each.
	UAbilitySystemComponent* TargetABSC = ExecutionParams.GetTargetAbilitySystemComponent();
	AActor* TargetActor = TargetABSC ? TargetABSC->GetAvatarActor() : nullptr;

	UAbilitySystemComponent* SourceABSC = ExecutionParams.GetSourceAbilitySystemComponent();
	AActor* SourceActor = SourceABSC ? SourceABSC->GetAvatarActor() : nullptr;

	// Get the owning GameplayEffect Spec so that you can use its variables and tags.
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// Aggregator Evaluate Parameters used during the attribute capture.
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	//Capturing the weapon damage.

	float BaseDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AttackDef, EvaluationParameters, BaseDamage);
	BaseDamage += FMath::Max<float>(Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), false, -1.0f), 0.0f);


	// Performing the actual damage calculation. 
	float DamageDone = BaseDamage;

	if (DamageDone < 0.f)
	{
		DamageDone = 0.0f;
	}
	
	// Final execution output. We can add more than one AddOutputModifier to change multiple parameters at a time based on more complicated calculations. Here we apply -DamageDone to to Health. Health itself is clamped in the AttributeSet.
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().CurrentHealthProperty, EGameplayModOp::Additive, -DamageDone));
}
