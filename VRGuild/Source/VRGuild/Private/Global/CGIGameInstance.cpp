// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/CGIGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemTypes.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "GameFramework/GameMode.h"
#include "Global/Server/CGSSBaseGameSession.h"
#include <VRGuild/TP_ThirdPerson/TP_ThirdPersonCharacter.h>
#include "Blueprint/UserWidget.h"
#include "Global/Widgets/CWDisplayMessage.h"
#include "Global/Server/CPCBasePlayerController.h"

void UCGIGameInstance::Init()
{
	Super::Init();
}

void UCGIGameInstance::Shutdown()
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	DestroySessionDelegateHandle =
		Session->AddOnDestroySessionCompleteDelegate_Handle(FOnDestroySessionCompleteDelegate::CreateUObject(
			this,
			&ThisClass::OnDestroySessionComplete));

	UE_LOG(LogTemp, Warning, TEXT("ShutDown Called"));

	FName sessionName = "TESTSession";

	if (auto gM = GetWorld()->GetAuthGameMode())
	{
		if (auto gSession = Cast<ACGSSBaseGameSession>(gM->GameSession))
		{
			sessionName = gSession->GetSessionName();
		}
	}

	if (!Session->DestroySession(sessionName))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to destroy session.")); // Log to the UE logs that we are trying to log in. 
	}

	Session->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionDelegateHandle);
	DestroySessionDelegateHandle.Reset();
	Super::Shutdown();
}

void UCGIGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Destroyed session succesfully."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to destroy session."));
	}

	Session->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionDelegateHandle);
	DestroySessionDelegateHandle.Reset();
}

void UCGIGameInstance::SetEpicNickNameInstance(FString userNickname)
{
	this->NickName = userNickname;

	CustomData.NickName = NickName;
}

void UCGIGameInstance::SetEpicUserIdInstance(int64 EpicUserId)
{
	this->UserId = EpicUserId;
}

void UCGIGameInstance::SetMainSkillCategory(FSkillCategoryInfo mainSkill)
{
	CustomData.MainSkill = mainSkill;
}

void UCGIGameInstance::DisplayTraceMessage(bool bDisplay, FString msg)
{
	if (!DisplayWidget)
	{
		if (!ensure(DisplayMsgWidgetClass)) return;

		DisplayWidget = CreateWidget<UCWDisplayMessage>(GetWorld(), DisplayMsgWidgetClass);

		if (!DisplayWidget) return;

		DisplayWidget->SetMessage(msg);
		DisplayWidget->AddToViewport();
	}

	if (bDisplay)
	{
		DisplayWidget->SetMessage(msg);
		DisplayWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		DisplayWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}