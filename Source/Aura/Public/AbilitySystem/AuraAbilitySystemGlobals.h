// Copyright Pinnacle Gaming Studios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "AuraAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

	// Used to instantiate our custom EffectContext
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
