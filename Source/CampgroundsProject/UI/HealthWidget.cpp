


#include "HealthWidget.h"
#include "CampgroundsProject/CGAttributeSet.h"
#include "CampgroundsProject/CGPlayerState.h"

void UHealthWidget::BindToAttributes()
{
	const ACGPlayerState* CGPlayerState = Cast<ACGPlayerState>(GetOwningPlayerState());
	if (!CGPlayerState) return;

	UAbilitySystemComponent* ASC = CGPlayerState->GetAbilitySystemComponent();
	const UCGAttributeSet* CGAS = CGPlayerState->GetAttributeSet();

	HealthPerecent = NUMERIC_VALUE(CGAS, CurrentHealth) / NUMERIC_VALUE(CGAS, MaxHealth);

	ASC->GetGameplayAttributeValueChangeDelegate(CGAS->GetCurrentHealthAttribute()).AddLambda(
		[this, CGAS](const FOnAttributeChangeData& Data)->void
		{
			HealthPerecent = Data.NewValue / NUMERIC_VALUE(CGAS, MaxHealth);
		});
}


