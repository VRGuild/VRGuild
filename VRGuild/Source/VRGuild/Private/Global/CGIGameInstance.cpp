// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/CGIGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemTypes.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

void UCGIGameInstance::Shutdown()
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	//Session->OnDestroySessionCompleteDelegates.AddUObject(this, &UCGIGameInstance::OnDestroySessionComplete);
		Session->OnDestroySessionCompleteDelegates.AddUObject(
			this, &ThisClass::OnDestroySessionComplete);

	Session->DestroySession("TestSession");
	Super::Shutdown();
}

void UCGIGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Destroy Session [%s] Success"), *SessionName.ToString());
	}
	else UE_LOG(LogTemp, Warning, TEXT("We failed to destroy [%s] session bois"), *SessionName.ToString());

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	Session->ClearOnDestroySessionCompleteDelegates(this);
}
