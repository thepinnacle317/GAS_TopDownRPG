// Copyright Pinnacle Gaming Studios


#include "Player/AuraPlayerState.h"

AAuraPlayerState::AAuraPlayerState()
{
	// How often the server will try to update the clients.  Used for replication.
	NetUpdateFrequency = 100.f;
}
