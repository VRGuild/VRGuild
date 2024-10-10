// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "CPCBasePlayerController.generated.h"

/**
 * 
 */

class FOnlineSessionSearch;
class FOnlineSessionSearchResult;

UCLASS()
class VRGUILD_API ACPCBasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ACPCBasePlayerController();
	
	UFUNCTION(BlueprintCallable)
	void ConnectToServer();
	UFUNCTION(BlueprintCallable)
	void TravelToNextServer();

protected:
	// Function called when play begins
	virtual void BeginPlay();

	//Function to sign into EOS Game Services
	void Login();

	//Callback function. This function is ran when signing into EOS Game Services completes. 
	void HandleLoginCompleted(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

	//Delegate to bind callback event for login. 
	FDelegateHandle LoginDelegateHandle;

	UFUNCTION(Server, Reliable)
	void ServerGetPort();
	UFUNCTION(Client, Reliable)
	void ClientGetPort(int64 nextPort);
	int32 NextPort = -1;

	// Function to find EOS sessions. Hardcoded attribute key/value pair to keep things simple
	UFUNCTION(BlueprintCallable)
	void FindSessions(FString searchValue = "", FName searchKey = "KeyName");

	// Callback function. This function will run when the session is found.
	void HandleFindSessionsCompleted(bool bWasSuccessful, TSharedRef<FOnlineSessionSearch> Search);

	//Delegate to bind callback event for when sessions are found.
	FDelegateHandle FindSessionsDelegateHandle;

	// This is the connection string for the client to connect to the dedicated server.
	FString ConnectString;

	// This is used to store the session to join information from the search. You could pass it as a paramter to JoinSession() instead. 
	FOnlineSessionSearchResult* SessionToJoin;

	// Function to join the EOS session. 
	void JoinSession();

	// Callback function. This function will run when the session is joined. 
	void HandleJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	// Delegate to bind callback event for join session.
	FDelegateHandle JoinSessionDelegateHandle;

	void OnTravelError(UWorld* World, ETravelFailure::Type ErrorType, const FString& ErrorString);

	// API Call
	UFUNCTION(BlueprintImplementableEvent)
	void OnLoginAPICall();

private:
	FDelegateHandle DestroySessionDelegateHandle;
	virtual void OnDestroySessionComplete(FName sessionName, bool bWasSuccessful);
	FName SessionName = "TESTSession";
};
