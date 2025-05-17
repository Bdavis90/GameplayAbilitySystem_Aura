// Copyright Brandon Davis


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo)

	for(FAuraAttributeInfo& Tag : AttributeInfo.Get()->AttributeInformation)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Tag.AttributeGetter).AddLambda([this, Tag, AS](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Tag, AS);
		});
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FAuraAttributeInfo& Tag, UAttributeSet* AS)
{

	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Tag.AttributeTag);
	Info.AttributeValue = Tag.AttributeGetter.GetNumericValue(AS);
	AttributeInfoDelegate.Broadcast(Info);
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo)

	
	for (FAuraAttributeInfo& Tag : AttributeInfo.Get()->AttributeInformation)
	{
		BroadcastAttributeInfo(Tag, AS);
	}
}
