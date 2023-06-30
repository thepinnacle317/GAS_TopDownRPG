// Copyright Pinnacle Gaming Studios


#include "AuraAssetManager.h"
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
}
