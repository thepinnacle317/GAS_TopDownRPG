// Copyright Pinnacle Gaming Studios


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"


UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	// New Local object that holds the owning ability of the actor that is instigating it.
	// This is standard format from how the built in ability tasks do this.
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		// Bind the Delegate to the Callback when the Target Data is Set.  This only works if the Target Data is set and then Activate() is called.
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this, &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);

		if (!bCalledDelegate)
		{
			// Tells the server to wait for the Target Data to be set
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	/*
	 * This creates a window locally in this function that allows the client to run everything here
	 * with the servers permission.
	 */
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
	// Get the player controller for access to the HitResultUnderCursor
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	// Creates a handle to package Data to be sent to the server
	FGameplayAbilityTargetDataHandle DataHandle;
	
	// This returns a hit result for a single target that will be needed for replication on the server.
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);
	
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		// Broadcast the valid data on the client
		ValidData.Broadcast(DataHandle);
	}
}

// Called when the replicated data on the server is received
void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag ActivationTag)
{
	// Target data has been received and the server does not need to cache it or clear it if it is cached.
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		// Broadcast the valid data on the client
		ValidData.Broadcast(DataHandle);
	}
}
