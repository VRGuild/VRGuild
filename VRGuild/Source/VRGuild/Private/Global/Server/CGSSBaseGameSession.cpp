// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Server/CGSSBaseGameSession.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemTypes.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "GameFramework/PlayerState.h"
#include "Global/Server/CGMBaseServer.h"

ACGSSBaseGameSession::ACGSSBaseGameSession()
{

}

void ACGSSBaseGameSession::BeginPlay()
{
    Super::BeginPlay();

    if (IsRunningDedicatedServer() && !bSessionExists)
    {
        FParse::Value(FCommandLine::Get(), TEXT("Value="), KeyValueStr);
        
        //SessionName = FName(FGuid::NewGuid().ToString());

        if (KeyValueStr != TEXT(""))
        {
            UE_LOG(LogTemp, Warning, TEXT("URL LOCAL: %s"), *GetWorld()->GetLocalURL());
            UE_LOG(LogTemp, Warning, TEXT("URL Address: %s"), *GetWorld()->GetAddressURL());
            UE_LOG(LogTemp, Warning, TEXT("KeyValue passed in to CommandLine: %s"), *KeyValueStr);
            CreateSession("KeyName", KeyValueStr);
        }
    }
}

bool ACGSSBaseGameSession::ProcessAutoLogin()
{
    // Tutorial 3: Overide base function as players need to login before joining the session. We don't want to call AutoLogin on server.
    return true;
}

void ACGSSBaseGameSession::CreateSession(FName KeyName, FString KeyValue)
{
    // Tutorial 3: This function will create an EOS Session.

    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface(); // Retrieve the generic session interface. 

    // Bind delegate to callback function
    CreateSessionDelegateHandle =
        Session->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionCompleteDelegate::CreateUObject(
            this,
            &ThisClass::HandleCreateSessionCompleted));

    // Set session settings 
    TSharedRef<FOnlineSessionSettings> SessionSettings = MakeShared<FOnlineSessionSettings>();
    SessionSettings->bShouldAdvertise = true; //This creates a public match and will be searchable. This will set the session as joinable via presence. 
    SessionSettings->bUsesPresence = false;   //No presence on dedicated server. This requires a local user.
    SessionSettings->bAllowJoinViaPresence = false; // superset by bShouldAdvertise and will be true on the backend
    SessionSettings->bAllowJoinViaPresenceFriendsOnly = false; // superset by bShouldAdvertise and will be true on the backend
    SessionSettings->bAllowInvites = false;    //Allow inviting players into session. This requires presence and a local user. 
    SessionSettings->bAllowJoinInProgress = true; //Once the session is started, no one can join.
    SessionSettings->bIsDedicated = true; //Session created on dedicated server.
    SessionSettings->bUseLobbiesIfAvailable = false; //This is an EOS Session not an EOS Lobby as they aren't supported on Dedicated Servers.
    SessionSettings->bUseLobbiesVoiceChatIfAvailable = false;
    SessionSettings->bUsesStats = true; //Needed to keep track of player stats.
    SessionSettings->NumPublicConnections = MaxNumberOfPlayersInSession;
    // This custom attribute will be used in searches on GameClients. 


    auto GM = GetWorld()->GetAuthGameMode<ACGMBaseServer>();
    if (GM)
    {
        SessionSettings->Settings.Add("Port", FOnlineSessionSetting(GM->GetNextPort(), EOnlineDataAdvertisementType::ViaOnlineService));
    }
    
    SessionSettings->Settings.Add(KeyName, FOnlineSessionSetting((KeyValue), EOnlineDataAdvertisementType::ViaOnlineService));

    // Create session.
    UE_LOG(LogTemp, Log, TEXT("Creating session..."));

    if (!Session->CreateSession(0, SessionName, *SessionSettings))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to create session!"));
        //Session->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionDelegateHandle);
        CreateSessionDelegateHandle.Reset();
    }
}

void ACGSSBaseGameSession::HandleCreateSessionCompleted(FName EOSSessionName, bool bWasSuccessful) // Dedicated Server Only
{
    // Tutorial 3: This function is triggered via the callback we set in CreateSession once the session is created (or there is a failure to create)
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface(); // Retrieve the generic session interface. 

    // Nothing special here, simply log that the session is created.
    if (bWasSuccessful)
    {
        bSessionExists = true;
        UE_LOG(LogTemp, Log, TEXT("Session: %s Created!"), *EOSSessionName.ToString());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to create session!"));
    }

    // Clear our handle and reset the delegate. 
    Session->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionDelegateHandle);
    CreateSessionDelegateHandle.Reset();
}

void ACGSSBaseGameSession::RegisterPlayer(APlayerController* NewPlayer, const FUniqueNetIdRepl& UniqueId, bool bWasFromInvite)
{
    // Tutorial 3: Override base function to register player in EOS Session
    Super::RegisterPlayer(NewPlayer, UniqueId, bWasFromInvite);

    if (IsRunningDedicatedServer()) // Only run this on the dedicated server
    {
        IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
        IOnlineSessionPtr Session = Subsystem->GetSessionInterface(); // Retrieve the generic session interface.

        // Bind delegate to callback function
        RegisterPlayerDelegateHandle =
            Session->AddOnRegisterPlayersCompleteDelegate_Handle(FOnRegisterPlayersCompleteDelegate::CreateUObject(
                this,
                &ACGSSBaseGameSession::HandleRegisterPlayerCompleted));

        if (!Session->RegisterPlayer(SessionName, *UniqueId, false))
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to Register Player!"));
            Session->ClearOnRegisterPlayersCompleteDelegate_Handle(RegisterPlayerDelegateHandle);
            RegisterPlayerDelegateHandle.Reset();
        }
    }
}

void ACGSSBaseGameSession::HandleRegisterPlayerCompleted(FName EOSSessionName, const TArray<FUniqueNetIdRef>& PlayerIds, bool bWasSuccesful)
{
    // Tutorial 3: This function is triggered via the callback we set in RegisterPlayer once the player is registered (or there is a failure)
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    if (bWasSuccesful)
    {
        UE_LOG(LogTemp, Log, TEXT("Player registered in EOS Session!"));
        NumberOfPlayersInSession++; // Keep track of players registered in session 
        if (NumberOfPlayersInSession == MaxNumberOfPlayersInSession)
        {
            StartSession(); // Start the session when we've reached the max number of players 
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to register player! (From Callback)"));
    }

    // Clear and reset delegates
    Session->ClearOnRegisterPlayersCompleteDelegate_Handle(RegisterPlayerDelegateHandle);
    RegisterPlayerDelegateHandle.Reset();
}

void ACGSSBaseGameSession::StartSession()
{
    // Tutorial 3: This function is called once all players are registered. It will mark the EOS Session as started. 
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    // Bind delegate to callback function
    StartSessionDelegateHandle =
        Session->AddOnStartSessionCompleteDelegate_Handle(FOnStartSessionCompleteDelegate::CreateUObject(
            this,
            &ACGSSBaseGameSession::HandleStartSessionCompleted));

    if (!Session->StartSession(SessionName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to start session!"));
        Session->ClearOnStartSessionCompleteDelegate_Handle(StartSessionDelegateHandle);
        StartSessionDelegateHandle.Reset();
    }
}

void ACGSSBaseGameSession::HandleStartSessionCompleted(FName EOSSessionName, bool bWasSuccessful)
{
    // Tutorial 3: This function is triggered via the callback we set in StartSession once the session is started (or there is a failure).
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    // Just log, clear and reset delegate. 
    if (bWasSuccessful)
    {
        UE_LOG(LogTemp, Log, TEXT("Session Started!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to start session! (From Callback)"));
    }

    Session->ClearOnStartSessionCompleteDelegate_Handle(StartSessionDelegateHandle);
    StartSessionDelegateHandle.Reset();
}

void ACGSSBaseGameSession::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
}

void ACGSSBaseGameSession::UnregisterPlayer(const APlayerController* ExitingPlayer)
{
    Super::UnregisterPlayer(ExitingPlayer);

    if (IsRunningDedicatedServer())
    {
        IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
        IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
        IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

        if (ExitingPlayer->PlayerState) // If the player leaves ungracefully this could be null
        {
            // Bind delegate to callback function
            UnregisterPlayerDelegateHandle =
                Session->AddOnUnregisterPlayersCompleteDelegate_Handle(FOnUnregisterPlayersCompleteDelegate::CreateUObject(
                    this,
                    &ThisClass::HandleUnregisterPlayerCompleted));

            if (!Session->UnregisterPlayer(SessionName, *ExitingPlayer->PlayerState->GetUniqueId()))
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to Unregister Player!"));
                Session->ClearOnUnregisterPlayersCompleteDelegate_Handle(UnregisterPlayerDelegateHandle);
                UnregisterPlayerDelegateHandle.Reset();
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to Unregister Player!"));
            Session->ClearOnUnregisterPlayersCompleteDelegate_Handle(UnregisterPlayerDelegateHandle);
            UnregisterPlayerDelegateHandle.Reset();
        }
    }
}

void ACGSSBaseGameSession::HandleUnregisterPlayerCompleted(FName EOSSessionName, const TArray<FUniqueNetIdRef>& PlayerIds, bool bWasSuccesful)
{
    // Tutorial 3: This function is triggered via the callback we set in UnregisterPlayer once the player is unregistered (or there is a failure).

    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    // Just log, clear and reset delegate. 
    if (bWasSuccesful)
    {
        UE_LOG(LogTemp, Log, TEXT("Player unregistered in EOS Session!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to unregister player! (From Callback)"));
    }
    Session->ClearOnUnregisterPlayersCompleteDelegate_Handle(UnregisterPlayerDelegateHandle);
    UnregisterPlayerDelegateHandle.Reset();
}

void ACGSSBaseGameSession::NotifyLogout(const APlayerController* ExitingPlayer)
{
    // Tutorial 3: Overide base function to handle players leaving EOS Session. 
    Super::NotifyLogout(ExitingPlayer); //This calls UnregisterPlayer

    // When players leave the dedicated server we need to check how many players are left. If 0 players are left, session is destroyed.  
    if (IsRunningDedicatedServer())
    {
        NumberOfPlayersInSession--; // Keep track of players as they leave
        // No one left in session. End session. end regardless if UnregisterPlayer failed. 
        if (NumberOfPlayersInSession == 0)
        {
            //DestroySession();
            EndSession();
        }
    }
}

void ACGSSBaseGameSession::EndSession()
{
    // Tutorial 3: This function is called once all players have left the session. It will mark the EOS Session as ended. 
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    // Bind delegate to callback function
    EndSessionDelegateHandle =
        Session->AddOnEndSessionCompleteDelegate_Handle(FOnEndSessionCompleteDelegate::CreateUObject(
            this,
            &ACGSSBaseGameSession::HandleEndSessionCompleted));

    if (!Session->EndSession(SessionName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to end session!"));
        Session->ClearOnEndSessionCompleteDelegate_Handle(StartSessionDelegateHandle);
        EndSessionDelegateHandle.Reset();
    }
}


void ACGSSBaseGameSession::HandleEndSessionCompleted(FName EOSSessionName, bool bWasSuccessful)
{
    // Tutorial 3: This function is triggered via the callback we set in EndSession once the session is ended (or there is a failure).
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    // Just log, clear and reset delegate. 
    if (bWasSuccessful)
    {
        UE_LOG(LogTemp, Log, TEXT("Session ended!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to end session! (From Callback)"));
    }

    Session->ClearOnEndSessionCompleteDelegate_Handle(EndSessionDelegateHandle);
    EndSessionDelegateHandle.Reset();
}

void ACGSSBaseGameSession::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // Tutorial 3: Overide base function to destroy session at end of play. This happens on both dedicated server and client
    Super::EndPlay(EndPlayReason);
}

void ACGSSBaseGameSession::DestroySession()
{
    // Tutorial 3: This function is called when all players leave the dedicated server. It will destroy the EOS Session which will remove it from the EOS backend.  

    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    DestroySessionDelegateHandle =
        Session->AddOnDestroySessionCompleteDelegate_Handle(FOnDestroySessionCompleteDelegate::CreateUObject(
            this,
            &ThisClass::HandleDestroySessionCompleted));

    if (!Session->DestroySession(SessionName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to destroy session.")); // Log to the UE logs that we are trying to log in. 
        Session->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionDelegateHandle);
        DestroySessionDelegateHandle.Reset();
    }
}

void ACGSSBaseGameSession::HandleDestroySessionCompleted(FName EOSSessionName, bool bWasSuccesful)
{
    // Tutorial 3: This function is triggered via the callback we set in DestroySession once the session is destroyed (or there is a failure).

    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

    if (bWasSuccesful)
    {
        bSessionExists = false; // Mark that the session doesn't exist. This way next time BeginPlay is called a new session will be created. 
        UE_LOG(LogTemp, Log, TEXT("Destroyed session succesfully."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to destroy session."));
    }

    Session->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionDelegateHandle);
    DestroySessionDelegateHandle.Reset();
}

