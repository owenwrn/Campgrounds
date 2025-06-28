


#include "StaminaWidget.h"
#include "CampgroundsProject/CGAttributeSet.h"
#include "CampgroundsProject/CGPlayerState.h"

void UStaminaWidget::BindToAttributes()
{
	const ACGPlayerState* CGPlayerState = Cast<ACGPlayerState>(GetOwningPlayerState());
	if (!CGPlayerState) return;

	UAbilitySystemComponent* ASC = CGPlayerState->GetAbilitySystemComponent();
	const UCGAttributeSet* CGAS = CGPlayerState->GetAttributeSet();

	StaminaPerecent = NUMERIC_VALUE(CGAS, CurrentStamina) / NUMERIC_VALUE(CGAS, MaxStamina);

	ASC->GetGameplayAttributeValueChangeDelegate(CGAS->GetCurrentStaminaAttribute()).AddLambda(
		[this, CGAS](const FOnAttributeChangeData& Data)->void
		{
			StaminaPerecent = Data.NewValue / NUMERIC_VALUE(CGAS, MaxStamina);
		});
}
