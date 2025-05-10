// Copyright Brandon Davis

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(Transient)
	AActor* AvatarActor;

	UPROPERTY(Transient)
	AController* Controller;

	UPROPERTY(Transient)
	ACharacter* Character;
};

USTRUCT()
struct FEffectPropertiesEnhanced
{
	GENERATED_BODY()

	FEffectPropertiesEnhanced()
	{
		ContextHandle = MakeShared<FGameplayEffectContextHandle>();
		SourceProperties = MakeShared<FEffectProperties>();
		TargetProperties = MakeShared<FEffectProperties>();
	}

	TSharedPtr<FGameplayEffectContextHandle> ContextHandle;
	
	TSharedPtr<FEffectProperties> SourceProperties;
	
	TSharedPtr<FEffectProperties> TargetProperties;
};

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes|Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes|MaxHealth", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes|Mana", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes|MaxMana", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectPropertiesEnhanced& Props);
};
