// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Server/CPCBasePlayerController.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemTypes.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSessionSettings.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "Global/Server/CGMBaseServer.h"
#include "Global/CGIGameInstance.h"
#include "GameFramework/PlayerState.h"

ACPCBasePlayerController::ACPCBasePlayerController()
{

}

void ACPCBasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (IsLocalPlayerController())
	{
		NextPort = -1;
		Login();
		//SessionName = FName("TESTSession");//FName(FGuid::NewGuid().ToString());
	}
}

//static TAutoConsoleVariable<bool> CVarVoiceChat(TEXT("jk.DebugVoiceChat"), false, TEXT("Display voicechat debug"), ECVF_Cheat);

void ACPCBasePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TotalTime += DeltaTime;
	if (TotalTime > MaxTime)
	{
		if (VoiceChatUser)
		{
			UE_LOG(LogTemp, Warning, TEXT("Connected to voice chat"));
			if (IOnlineIdentityPtr Identity = Online::GetSubsystem(GetWorld())->GetIdentityInterface())
			{
				//const FUniqueNetIdRepl nice = PlayerState->GetUniqueId();
				//*nice.GetUniqueNetId()
				FString PlayerName = Identity->GetPlayerNickname(0);
				if (PlayerName != "")
				{
					for (FString Channel : VoiceChatUser->GetChannels())
					{
						UE_LOG(LogTemp, Warning, TEXT("------[%s]------"), *Channel);

						for (FString player : VoiceChatUser->GetPlayersInChannel(Channel))
						{
							UE_LOG(LogTemp, Warning, TEXT("[%s] %s"), *Channel, *player);
						}
						UE_LOG(LogTemp, Warning, TEXT("------------"));
					}

					FString name = VoiceChatUser->GetInputDeviceInfo().DisplayName;
					if (VoiceChatUser->GetAudioInputDeviceMuted())
					{
						UE_LOG(LogTemp, Warning, TEXT("Audio device is Muted %s"), *name);
					}
					else UE_LOG(LogTemp, Warning, TEXT("Audio device %s"), *name);

					if (VoiceChatUser->IsPlayerMuted(PlayerName))
					{
						UE_LOG(LogTemp, Warning, TEXT("%s is Muted"), *PlayerName);
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("%s is not Muted"), *PlayerName);
						if (VoiceChatUser->IsPlayerTalking(*PlayerName))
						{
							UE_LOG(LogTemp, Warning, TEXT("%s is Talking"), *PlayerName);
						}
						else UE_LOG(LogTemp, Warning, TEXT("%s is not Talking"), *PlayerName);
					}
				}
				else
				{
					if (PlayerState)
					{
						UE_LOG(LogTemp, Warning, TEXT("Could not get player name with %s"), *PlayerState->GetUniqueId()->ToString());
					}	
					else UE_LOG(LogTemp, Warning, TEXT("PlayerState missing"));
				}
			}
		}
		else UE_LOG(LogTemp, Warning, TEXT("No VoiceChatUser"));
		/*if (CVarVoiceChat.GetValueOnGameThread())
		{

		}*/
		TotalTime = 0;
	}
}

void ACPCBasePlayerController::Login()
{
	/*
	Tutorial 2: This function will access the EOS OSS via the OSS identity interface to log first into Epic Account Services, and then into Epic Game Services.
	It will bind a delegate to handle the callback event once login call succeeeds or fails.
	All functions that access the OSS will have this structure: 1-Get OSS interface, 2-Bind delegate for callback and 3-Call OSS interface function (which will call the correspongin EOS OSS function)
	*/
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface(); // This is the generic OSS interface that will access the EOS OSS.

	// If you're logged in, don't try to login again.
	// This can happen if your player travels to a dedicated server or different maps as BeginPlay() will be called each time.

	FUniqueNetIdPtr NetId = Identity->GetUniquePlayerId(0);
	if (NetId != nullptr && Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Already Logged in to EOS"));
		OnLoginAPICall();

		return;
	}

	/* This binds a delegate so we can run our function when the callback completes. 0 represents the player number.
	You should parametrize this Login function and pass the parameter here for splitscreen.
	*/
	LoginDelegateHandle =
		Identity->AddOnLoginCompleteDelegate_Handle(
			0,
			FOnLoginCompleteDelegate::CreateUObject(this, &ThisClass::HandleLoginCompleted)
		);

	// Grab command line parameters. If empty call hardcoded login function - Hardcoded login function useful for Play In Editor. 
	FString AuthType;
	FParse::Value(FCommandLine::Get(), TEXT("AUTH_TYPE="), AuthType);

	if (!AuthType.IsEmpty()) //If parameter is NOT empty we can autologin.
	{
		/*
		In most situations you will want to automatically log a player in using the parameters passed via CLI.
		For example, using the exchange code for the Epic Games Store.
		*/
		UE_LOG(LogTemp, Log, TEXT("[1] Logging into EOS...")); // Log to the UE logs that we are trying to log in. 

		if (!Identity->AutoLogin(0))
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to login... ")); // Log to the UE logs that we are trying to log in.
			// Clear our handle and reset the delegate.
			Identity->ClearOnLoginCompleteDelegate_Handle(0, LoginDelegateHandle);
			LoginDelegateHandle.Reset();
		}
	}
	else
	{
		/*
		Fallback if the CLI parameters are empty.Useful for PIE.
		The type here could be developer if using the DevAuthTool, ExchangeCode if the game is launched via the Epic Games Launcher, etc...
		*/
		FOnlineAccountCredentials Credentials("AccountPortal", "", "");

		UE_LOG(LogTemp, Log, TEXT("[2] Logging into EOS...")); // Log to the UE logs that we are trying to log in. 

		if (!Identity->Login(0, Credentials))
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to login... ")); // Log to the UE logs that we are trying to log in.
			// Clear our handle and reset the delegate. 
			Identity->ClearOnLoginCompleteDelegate_Handle(0, LoginDelegateHandle);
			LoginDelegateHandle.Reset();
		}
	}
}

void ACPCBasePlayerController::ConnectToServer()
{
	UE_LOG(LogTemp, Log, TEXT("Searching for a session..."));
	// Maybe via button or player action? Maybe add parameters here
	FindSessions();
}

void ACPCBasePlayerController::TravelToNextServer()
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	DestroySessionDelegateHandle =
		Session->AddOnDestroySessionCompleteDelegate_Handle(FOnDestroySessionCompleteDelegate::CreateUObject(
			this,
			&ThisClass::OnDestroySessionComplete));

	if (!Session->DestroySession(SessionName))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to destroy session in PlayerController."));
	}
}

void ACPCBasePlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	StartVoiceChat();
}

void ACPCBasePlayerController::StartVoiceChat()
{
	if (IVoiceChat* voiceChat = IVoiceChat::Get())
	{
		if (voiceChat->Initialize())
		{
			voiceChat->Connect(FOnVoiceChatConnectCompleteDelegate::CreateLambda([this, voiceChat](const FVoiceChatResult& Result)
				{
					if (Result.IsSuccess())
					{
						const FPlatformUserId platformUserId = FPlatformMisc::GetPlatformUserForUserIndex(0);

						IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
						IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();

						FString playerName = Identity->GetPlayerNickname(0);
						UE_LOG(LogTemp, Warning, TEXT("Getting EOS Room token with name %s"), *playerName);

						VoiceChatUser = voiceChat->CreateUser();

						VoiceChatUser->Login(platformUserId, playerName, "", FOnVoiceChatLoginCompleteDelegate::CreateLambda([this](const FString& playerName, const FVoiceChatResult& result)
							{
								if (result.IsSuccess())
								{
									GetEOSRoomToken(VoiceChatUser->GetLoggedInPlayerName());
								}
								else UE_LOG(LogTemp, Warning, TEXT("Voice chat login fail"));
							}
						)
						);
					}
					else UE_LOG(LogTemp, Warning, TEXT("Voice chat connect unsuccessful"));

				})
			);
		}
		else UE_LOG(LogTemp, Warning, TEXT("Voice chat Initialize fail"));
	}
	else UE_LOG(LogTemp, Warning, TEXT("Voice chat get fail"));
}

void ACPCBasePlayerController::GetEOSRoomToken(FString playerName)
{
	UE_LOG(LogTemp, Warning, TEXT("Voice chat login success: PlayerName: %s"), *playerName);

	FString ConfigDeploymentId;
	FString ConfigClientId;
	FString ConfigClientSecret;
	FString ConfigProductId;
	FString VoiceRoomName = TEXT("VoiceRoomName");

	GConfig->GetString(TEXT("EOSVoiceChat"), TEXT("DeploymentId"), ConfigDeploymentId, GEngineIni);
	GConfig->GetString(TEXT("EOSVoiceChat"), TEXT("ClientId"), ConfigClientId, GEngineIni);
	GConfig->GetString(TEXT("EOSVoiceChat"), TEXT("ClientSecret"), ConfigClientSecret, GEngineIni);
	GConfig->GetString(TEXT("EOSVoiceChat"), TEXT("ProductId"), ConfigProductId, GEngineIni);

	auto HttpRequest = FHttpModule::Get().CreateRequest();
	const FString Base64Credentials = FBase64::Encode(FString::Printf(TEXT("%s:%s"), *ConfigClientId, *ConfigClientSecret));
	const FString ContentString = FString::Printf(TEXT("grant_type=client_credentials&deployment_id=%s"), *ConfigDeploymentId);

	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpRequest->AppendToHeader(TEXT("Accept"), TEXT("application/json"));
	HttpRequest->AppendToHeader(TEXT("Authorization"), *FString::Printf(TEXT("Basic %s"), *Base64Credentials));
	HttpRequest->SetContentAsString(ContentString);
	HttpRequest->SetURL("https://api.epicgames.dev/auth/v1/oauth/token");
	HttpRequest->SetVerb("POST");

	HttpRequest->OnProcessRequestComplete().BindLambda([this, ConfigDeploymentId, playerName, VoiceRoomName](FHttpRequestPtr RequestPtr, FHttpResponsePtr ResponsePtr, bool bConnectedSuccessfully)
		{
			UE_LOG(LogTemp, Warning, TEXT("Response -> %s"), *ResponsePtr->GetContentAsString());
			FString AccessTokenString;
			TSharedPtr<FJsonObject> JsonObject;

			if (bConnectedSuccessfully && FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(ResponsePtr->GetContentAsString()), JsonObject) && JsonObject.IsValid())
			{
				TSharedPtr<FJsonValue> AccessTokenObject = JsonObject->TryGetField(TEXT("access_token"));
				AccessTokenString = AccessTokenObject ? AccessTokenObject->AsString() : FString();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Voice chat login not successful"));
				return;
			}

			if (AccessTokenString.IsEmpty())
			{
				UE_LOG(LogTemp, Warning, TEXT("Voice chat login not successful"));
				return;
			}

			auto RoomTokenRequest = FHttpModule::Get().CreateRequest();

			RoomTokenRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
			RoomTokenRequest->AppendToHeader(TEXT("Accept"), TEXT("application/json"));
			RoomTokenRequest->AppendToHeader(TEXT("Authorization"), *FString::Printf(TEXT("Bearer %s"), *AccessTokenString));

			const FString ProductUserId = playerName;
			UE_LOG(LogTemp, Warning, TEXT("ProductUserId :%s"), *ProductUserId);
			bool bHardMuted = false;

			const FString JsonRequestString = FString::Printf(TEXT("{\"participants\":[{\"puid\":\"%s\",\"clientIp\":\"%s\",\"hardMuted\":%s}] }"), *ProductUserId, TEXT("10.0.0.1"), bHardMuted ? TEXT("true") : TEXT("false"));
			RoomTokenRequest->SetContentAsString(JsonRequestString);
			RoomTokenRequest->SetURL(FString::Printf(TEXT("https://api.epicgames.dev/rtc/v1/%s/room/%s"), *ConfigDeploymentId, *VoiceRoomName));
			RoomTokenRequest->SetVerb("POST");

			RoomTokenRequest->OnProcessRequestComplete().BindLambda([this, VoiceRoomName, playerName](FHttpRequestPtr HttpRequestPtr, FHttpResponsePtr HttpResponsePtr, bool bConnectedSuccessfully)
				{
					UE_LOG(LogTemp, Warning, TEXT("Response -> %s"), *HttpResponsePtr->GetContentAsString());
					FString TokenString, ClientBaseUrlString;

					if (!bConnectedSuccessfully)
					{
						UE_LOG(LogTemp, Warning, TEXT("Voice chat login not successful"));
						return;
					}

					TSharedPtr<FJsonObject> JsonObject;
					const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(HttpResponsePtr->GetContentAsString());
					if (!FJsonSerializer::Deserialize(JsonReader, JsonObject) || !JsonObject.IsValid())
					{
						UE_LOG(LogTemp, Warning, TEXT("Voice chat login not successful"));
						return;
					}

					const TSharedPtr<FJsonValue> ClientBaseUrlObject = JsonObject->TryGetField(TEXT("clientBaseUrl"));
					const TSharedPtr<FJsonValue> ParticipantsObject = JsonObject->TryGetField(TEXT("participants"));

					if (!ParticipantsObject)
					{
						UE_LOG(LogTemp, Warning, TEXT("Voice chat login not successful"));
						return;
					}


					ClientBaseUrlString = ClientBaseUrlObject->AsString();
					UE_LOG(LogTemp, Warning, TEXT("ClientUrl -> %s"), *ClientBaseUrlString);
					TArray<TSharedPtr<FJsonValue>> ParticipantsArray = ParticipantsObject->AsArray();

					for (const auto& Element : ParticipantsArray)
					{
						if (Element->Type != EJson::Object)
							continue;

						auto& Object = Element->AsObject();
						TokenString = Object->TryGetField(TEXT("token"))->AsString();
						UE_LOG(LogTemp, Warning, TEXT("Token -> %s"), *TokenString);
					}

					if (TokenString.IsEmpty())
					{
						UE_LOG(LogTemp, Warning, TEXT("Voice chat login not successful"));
					}

					FEVIKChannelCredentials ChannelCredentials;
					ChannelCredentials.OverrideUserId = playerName;
					ChannelCredentials.ClientBaseUrl = ClientBaseUrlString;
					ChannelCredentials.ParticipantToken = TokenString;
					UE_LOG(LogTemp, Warning, TEXT("Voice chat login successful %s"), *ChannelCredentials.ToJson());

					JoinChannel(VoiceRoomName, true, ChannelCredentials.ToJson(false));
				});

			RoomTokenRequest->ProcessRequest();
		});

	HttpRequest->ProcessRequest();
}

void ACPCBasePlayerController::JoinChannel(FString voiceRoomName, bool bEnableEcho, FString channelCredentialsJson)
{
	FVoiceChatChannel3dProperties Properties;
	Properties.AttenuationModel = EVoiceChatAttenuationModel::InverseByDistance;
	Properties.MaxDistance = 100.f;
	Properties.MinDistance = 1.f;
	Properties.Rolloff = 0.5f;

	TSharedPtr<FJsonObject> ChannelCredentialsObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(channelCredentialsJson);
	if (!FJsonSerializer::Deserialize(JsonReader, ChannelCredentialsObject) || !ChannelCredentialsObject.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to parse channelCredentialsJson"));
	}

	FString ClientBaseUrl = ChannelCredentialsObject->GetStringField(TEXT("client_base_url"));
	FString ParticipantToken = ChannelCredentialsObject->GetStringField(TEXT("participant_token"));
	EVoiceChatChannelType ChannelType = EVoiceChatChannelType::Positional;

	if (bEnableEcho)
	{
		ChannelType = EVoiceChatChannelType::Echo;
		UE_LOG(LogTemp, Warning, TEXT("Setting Echo -> %hhd"), bEnableEcho);
	}
	UE_LOG(LogTemp, Warning, TEXT("bEnableEcho -> %hhd"), bEnableEcho);

	VoiceChatUser->JoinChannel(voiceRoomName, channelCredentialsJson, ChannelType, FOnVoiceChatChannelJoinCompleteDelegate::CreateLambda([this](const FString& ChannelName, const FVoiceChatResult& JoinResult)
		{
			if (JoinResult.IsSuccess())
			{
				UE_LOG(LogTemp, Warning, TEXT("JoinVoiceServer Successful %s"), *ChannelName);

				for (FString Channel : VoiceChatUser->GetChannels())
				{
					UE_LOG(LogTemp, Warning, TEXT("------[%s]------"), *Channel);

					for (FString player : VoiceChatUser->GetPlayersInChannel(Channel))
					{
						UE_LOG(LogTemp, Warning, TEXT("[%s] %s"), *Channel, *player);
					}
					UE_LOG(LogTemp, Warning, TEXT("------------"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("JoinVoiceServer Fail"))
			}
		}),
		Properties
	);
}

void ACPCBasePlayerController::OnDestroySessionComplete(FName sessionName, bool bWasSuccessful)
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Destroyed session [%s], succesfully."), *sessionName.ToString());

		if (GetWorld()) ServerGetPort();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to destroy session."));
	}

	Session->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionDelegateHandle);
	DestroySessionDelegateHandle.Reset();
}

void ACPCBasePlayerController::HandleLoginCompleted(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	/*
	Tutorial 2: This function handles the callback from logging in. You should not proceed with any EOS features until this function is called.
	This function will remove the delegate that was bound in the Login() function.
	*/
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();

	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Login callback completed!"));;

		//UE_LOG(LogTemp, Log, TEXT("Searching for a session..."));
		//// Maybe via button or player action? Maybe add parameters here
		//FindSessions();

		//
		
		//APICall Check
		OnLoginAPICall();
	}
	else //Login failed
	{
		// If your game is online only, you may want to return an errror to the user and return to a menu that uses a different GameMode/PlayerController.

		UE_LOG(LogTemp, Warning, TEXT("EOS login failed.")); //Print sign in failure in logs as a warning.
	}

	Identity->ClearOnLoginCompleteDelegate_Handle(LocalUserNum, LoginDelegateHandle);
	LoginDelegateHandle.Reset();
}

void ACPCBasePlayerController::ServerGetPort_Implementation()
{
	auto GM = GetWorld()->GetAuthGameMode<ACGMBaseServer>();
	if (GM)
	{
		ClientGetPort(GM->GetNextPort());
	}
}

void ACPCBasePlayerController::ClientGetPort_Implementation(int64 nextPort)
{
	NextPort = nextPort;
	FindSessions();
}

void ACPCBasePlayerController::FindSessions(FString searchValue, FName searchKey) //put default value for example 
{
	// Tutorial 4: This function will find our EOS Session that was created by our DedicatedServer. 

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
	TSharedRef<FOnlineSessionSearch> Search = MakeShared<FOnlineSessionSearch>();

	// Remove the default search parameters that FOnlineSessionSearch sets up.
	Search->QuerySettings.SearchParams.Empty();

	FString searchValueStr;

	if (searchValue == TEXT(""))
	{
		FParse::Value(FCommandLine::Get(), TEXT("SearchValue="), searchValueStr);
		if (searchValueStr == TEXT(""))
		{
			UE_LOG(LogTemp, Log, TEXT("Could not find SearchValue in Commandline .\n Default value \"KeyValue\" added for SearchValueStr"));
			searchValueStr = "KeyValue";
		}
	}
	else searchValueStr = searchValue;

	Search->QuerySettings.Set(searchKey, searchValueStr, EOnlineComparisonOp::Equals); // Seach using our Key/Value pair

	if (NextPort != -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Searching port : %d"), NextPort);
		Search->QuerySettings.Set("Port", NextPort, EOnlineComparisonOp::Equals); // Search for next server's port number;
	}


	FindSessionsDelegateHandle =
		Session->AddOnFindSessionsCompleteDelegate_Handle(FOnFindSessionsCompleteDelegate::CreateUObject(
			this,
			&ThisClass::HandleFindSessionsCompleted,
			Search));

	UE_LOG(LogTemp, Log, TEXT("Finding session: %s."), *searchValueStr);

	if (!Session->FindSessions(0, Search))
	{
		UE_LOG(LogTemp, Warning, TEXT("Find session failed"));
	}
}

void ACPCBasePlayerController::HandleFindSessionsCompleted(bool bWasSuccessful, TSharedRef<FOnlineSessionSearch> Search)
{
	// Tutorial 4: This function is triggered via the callback we set in FindSession once the session is found (or there is a failure)

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	bool bSuccess = false;
	int count = 0;
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Found session: %d"), Search->SearchResults.Num());

		for (auto SessionInSearchResult : Search->SearchResults)
		{
			UE_LOG(LogTemp, Log, TEXT("[%d] [%s] Owning Username: %s"), count,
				*SessionInSearchResult.Session.SessionInfo->GetSessionId().ToString(), *SessionInSearchResult.Session.OwningUserName);
			;

			if (SessionInSearchResult.IsSessionInfoValid())
			{
				// Typically you want to check if the session is valid before joining. There is a bug in the EOS OSS where IsValid() returns false when the session is created on a DS. 
				// Instead of customizing the engine for this tutorial, we're simply not checking if the session is valid. The code below should go in this if statement once the bug is fixed. 
				/*
				if (SessionInSearchResult.IsValid())
				{
				}
				*/
				//Ensure the connection string is resolvable and store the info in ConnectInfo and in SessionToJoin
				if (Session->GetResolvedConnectString(SessionInSearchResult, NAME_GamePort, ConnectString))
				{
					SessionToJoin = &SessionInSearchResult;
					bSuccess = true;

					if (NextPort != -1)
					{
						TArray<FString> Parts;
						ConnectString.ParseIntoArray(Parts, TEXT(":"), true);
						Parts[1] = FString::FromInt(NextPort);
						ConnectString = Parts[0] + TEXT(":") + Parts[1];
					}

					UE_LOG(LogTemp, Log, TEXT("[%d] ConnectString: %s"), count,
						*ConnectString);
				}
			}
			else UE_LOG(LogTemp, Log, TEXT("[%d] Invalid Session in search"), count);

			// For the tutorial we will join the first session found automatically. Usually you would loop through all the sessions and determine which one is best to join. 
			//break;
			count++;
		}

		if (bSuccess)
		{
			JoinSession();
		}
		else UE_LOG(LogTemp, Warning, TEXT("Could not find Session"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Find Sessions failed.")); //print warning in logs of failure
	}

	Session->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsDelegateHandle);
	FindSessionsDelegateHandle.Reset();
}

void ACPCBasePlayerController::JoinSession()
{
	// Tutorial 4: Join the session. 

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	JoinSessionDelegateHandle =
		Session->AddOnJoinSessionCompleteDelegate_Handle(FOnJoinSessionCompleteDelegate::CreateUObject(
			this,
			&ThisClass::HandleJoinSessionCompleted));

	UE_LOG(LogTemp, Log, TEXT("Joining session: %s"), *SessionToJoin->GetSessionIdStr());
	if (!Session->JoinSession(0, SessionName, *SessionToJoin))
	{
		UE_LOG(LogTemp, Warning, TEXT("Join session failed"));
	}
}

void ACPCBasePlayerController::HandleJoinSessionCompleted(FName sessionName, EOnJoinSessionCompleteResult::Type Result)
{
	// Tutorial 4: This function is triggered via the callback we set in JoinSession once the session is joined (or there is a failure)

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		if (GEngine)
		{
			// For the purposes of this tutorial overriding the ConnectString to point to localhost as we are testing locally. In a real game no need to override. Make sure you can connect over UDP to the ip:port of your server!
			//ConnectString = "127.0.0.1:7777";

			UE_LOG(LogTemp, Log, TEXT("Joined session [%s] with ConnectString %s."), *sessionName.ToString(), *ConnectString);


			FString DedicatedServerJoinError;
			auto DedicatedServerJoinStatus =

				GEngine->OnTravelFailure().AddUObject(this, &ThisClass::OnTravelError);
			ClientTravel(ConnectString, ETravelType::TRAVEL_Partial);

			//FURL DedicatedServerURL(nullptr, *ConnectString, TRAVEL_Absolute);
			//GEngine->Browse(GEngine->GetWorldContextFromWorldChecked(GetWorld()), DedicatedServerURL, DedicatedServerJoinError);	
			/*if (DedicatedServerJoinStatus == EBrowseReturnVal::Failure)
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to browse for dedicated server. Error is: %s"), *DedicatedServerJoinError);
			}*/

			// To be thorough here you should modify your derived UGameInstance to handle the NetworkError and TravelError events. 
			// As we are testing locally, and for the purposes of keeping this tutorial simple, this is omitted. 
			// API Call Login
		}
	}
	Session->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionDelegateHandle);
	JoinSessionDelegateHandle.Reset();
}

void ACPCBasePlayerController::OnTravelError(UWorld* World, ETravelFailure::Type ErrorType, const FString& ErrorString)
{
	UE_LOG(LogTemp, Warning, TEXT("Travel Error: %s"), *UEnum::GetValueAsString(ErrorType));
}
