// Copyright Brandon Davis


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(25.f);
	InitMaxMana(50.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always)
}

// Changes to the base value
void UAuraAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if(Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}

	if(Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectPropertiesEnhanced& Props)
{
	// Source = causer of the effect, Target = target of the effect (owner of this AS)
	
	*Props.ContextHandle = Data.EffectSpec.GetContext();
	Props.SourceProperties->AbilitySystemComponent = Props.ContextHandle.Get()->GetOriginalInstigatorAbilitySystemComponent();

	if(IsValid(Props.SourceProperties->AbilitySystemComponent) && Props.SourceProperties->AbilitySystemComponent->AbilityActorInfo.IsValid() && Props.SourceProperties->AbilitySystemComponent->AbilityActorInfo.IsValid() && Props.SourceProperties->AbilitySystemComponent->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceProperties->AvatarActor = Props.SourceProperties->AbilitySystemComponent->AbilityActorInfo->AvatarActor.Get();
		
		Props.SourceProperties->Controller = Props.SourceProperties->AbilitySystemComponent->AbilityActorInfo->PlayerController.Get();
		if(!Props.SourceProperties->Controller && Props.SourceProperties->AvatarActor)
		{
			if(APawn* Pawn = Cast<APawn>(Props.SourceProperties->AvatarActor))
			{
				Props.SourceProperties->Controller = Pawn->GetController();
			}
		}

		if(Props.SourceProperties->Controller)
		{
			ACharacter* SourceCharacter = Cast<ACharacter>(Props.SourceProperties->Controller->GetPawn());
		}

		if(Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
		{
			Props.TargetProperties->AvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
			Props.TargetProperties->Controller = Data.Target.AbilityActorInfo->PlayerController.Get();
			Props.TargetProperties->Character = Cast<ACharacter>(Props.TargetProperties->AvatarActor);
			Props.TargetProperties->AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetProperties->AvatarActor);
		}
	}
}


void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectPropertiesEnhanced Props;
	SetEffectProperties(Data, Props);
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

