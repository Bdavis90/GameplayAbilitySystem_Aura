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

	/**
	 * Vital Attributes
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes|Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes|Mana", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)

	
	/**
	 * Primary Attributes
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes|Strength", ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength)

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes|Intelligence", ReplicatedUsing = OnRep_Intelligence)
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence)

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes|Vigor", ReplicatedUsing = OnRep_Vigor)
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor)

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes|Resilience", ReplicatedUsing = OnRep_Resilience)
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience)

	/**
 * Secondary Attributes
 */

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes|Armor", ReplicatedUsing = OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor)
	
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes|ArmorPenetration", ReplicatedUsing = OnRep_ArmorPenetration)
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration)
	
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes|BlockChance", ReplicatedUsing = OnRep_BlockChance)
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance)
	
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes|CriticalHitChance", ReplicatedUsing = OnRep_CriticalHitChance)
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance)
	
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes|CriticalHitDamage", ReplicatedUsing = OnRep_CriticalHitDamage)
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage)
	
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes|CriticalHitResistance", ReplicatedUsing = OnRep_CriticalHitResistance)
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance)
	
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes|HealthRegeneration", ReplicatedUsing = OnRep_HealthRegeneration)
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration)
	
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes|ManaRegeneration", ReplicatedUsing = OnRep_ManaRegeneration)
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration)

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes|MaxMana", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes|MaxHealth", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)


	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	UFUNCTION()
	virtual void OnRep_Strength(FGameplayAttributeData& OldStrength) const;
	UFUNCTION()
	virtual void OnRep_Intelligence(FGameplayAttributeData& OldIntelligence) const;
	UFUNCTION()
	virtual void OnRep_Vigor(FGameplayAttributeData& OldVigor) const;
	UFUNCTION()
	virtual void OnRep_Resilience(FGameplayAttributeData& OldResilience) const;
	UFUNCTION()
	virtual void OnRep_Armor(FGameplayAttributeData& OldArmor) const;
	UFUNCTION()
	virtual void OnRep_ArmorPenetration(FGameplayAttributeData& OldArmorPenetration) const;
	UFUNCTION()
	virtual void OnRep_BlockChance(FGameplayAttributeData& OldBlockChance) const;
	UFUNCTION()
	virtual void OnRep_CriticalHitChance(FGameplayAttributeData& OldCriticalHitChance) const;
	UFUNCTION()
	virtual void OnRep_CriticalHitDamage(FGameplayAttributeData& OldCriticalHitDamage) const;
	UFUNCTION()
	virtual void OnRep_CriticalHitResistance(FGameplayAttributeData& OldCriticalHitResistance) const;
	UFUNCTION()
	virtual void OnRep_HealthRegeneration(FGameplayAttributeData& OldHealthRegeneration) const;
	UFUNCTION()
	virtual void OnRep_ManaRegeneration(FGameplayAttributeData& OldManaRegeneration) const;

private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectPropertiesEnhanced& Props);
};
