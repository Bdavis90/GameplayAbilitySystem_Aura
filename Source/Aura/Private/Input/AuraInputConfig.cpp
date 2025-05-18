// Copyright Brandon Davis


#include "Input/AuraInputConfig.h"

#include "InputAction.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
                                                                   bool bLogNotFound) const
{
	for(auto& AuraInput : AbilityInputActions)
	{
		if(AuraInput.InputTag.MatchesTag(InputTag))
		{
			return AuraInput.InputAction;
		}
	}

	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find AbilityInputAction for InputTag %s, on InputConfig %s"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
