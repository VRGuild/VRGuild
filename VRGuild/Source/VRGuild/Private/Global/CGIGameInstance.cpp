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

void UCGIGameInstance::AttachCustomSelections(ACharacter* NewCharacter)
{
    if (NewCharacter)
    {
        for (int i = 0; i < CharacterPartComponents.Num(); ++i)
        {
             NewCharacter->AddComponentByClass(CharacterPartComponents[i], 1, NewCharacter->GetTransform(), 0);
        }
    }
}

void UCGIGameInstance::DisplayTraceMessage(bool bDisplay, FString msg)
{
    if (!DisplayWidget)
    {
        if (!ensure(DisplayMsgWidgetClass)) return;

        DisplayWidget = CreateWidget<UCWDisplayMessage>(GetWorld(), DisplayMsgWidgetClass);
        
        if (!DisplayWidget) return;

        DisplayWidget->Init(msg);

        DisplayWidget->AddToViewport();
    }
    
    if (bDisplay)
    {
        DisplayWidget->SetVisibility(ESlateVisibility::Visible);
    }
    else DisplayWidget->SetVisibility(ESlateVisibility::Hidden);
}