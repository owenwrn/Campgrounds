


#include "EconomyWidget.h"
#include "CampgroundsProject/AbilitySystem/AttributeSets/EconomyAttributeSet.h"
#include "CampgroundsProject/CGGameStateBase.h"

void UEconomyWidget::BindToAttributes()
{
	const ACGGameStateBase* GS = GetWorld()->GetGameState<ACGGameStateBase>();
	if (!GS) return;

	UAbilitySystemComponent* ASC = GS->GetAbilitySystemComponent();
	const UEconomyAttributeSet* AS = GS->GetAttributeSet();

	SetMoney(NUMERIC_VALUE(AS, Money));
	SetQuota(NUMERIC_VALUE(AS, Quota));

	ASC->GetGameplayAttributeValueChangeDelegate(AS->GetMoneyAttribute()).AddLambda(
		[this, AS](const FOnAttributeChangeData& Data)->void
		{
			SetMoney(Data.NewValue);
		});
	ASC->GetGameplayAttributeValueChangeDelegate(AS->GetQuotaAttribute()).AddLambda(
		[this, AS](const FOnAttributeChangeData& Data)->void
		{
			SetQuota(Data.NewValue);
		});


}
