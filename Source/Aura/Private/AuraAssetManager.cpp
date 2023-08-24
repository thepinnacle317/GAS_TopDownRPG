// Copyright Pinnacle Gaming Studios


#include "AuraAssetManager.h"
#include "AbilitySystemGlobals.h"
#include "AuraGameplayTags.h"

// Singleton that is set in the Engine Config file
UAuraAssetManager& UAuraAssetManager::Get()
{
	
	check(GEngine);
	// Store the AuraAssetManager 
	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	// Dereference the pointer to match the return type
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	// Loading of the native tags
	FAuraGameplayTags::InitializeNativeGameplayTags();

	// This is very important in order to be able to use Target Data. /* Requirement */
	// This function initializes Target Data Script Struct Cache.  This has to do with Data Serialization.
	UAbilitySystemGlobals::Get().InitGlobalData();
}
