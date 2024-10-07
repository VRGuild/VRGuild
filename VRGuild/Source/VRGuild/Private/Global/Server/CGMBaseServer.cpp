// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Server/CGMBaseServer.h"
#include "Global/Server/CGSSBaseGameSession.h"

ACGMBaseServer::ACGMBaseServer()
{
	GameSessionClass = ACGSSBaseGameSession::StaticClass();
}

void ACGMBaseServer::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	//bUseSeamlessTravel = true;

	FString port;
	FParse::Value(FCommandLine::Get(), TEXT("nextPort="), port);
	if (port != "")
		NextPort = (int32)FCString::Atoi(*port);
	if(NextPort == 0)
		NextPort = -1;
}

void ACGMBaseServer::HandleSeamlessTravelPlayer(AController*& C)
{
	Super::HandleSeamlessTravelPlayer(C);

	UE_LOG(LogTemp, Warning, TEXT("Handle Seamless Travel Player called"));
}

int32 ACGMBaseServer::GetNextPort()
{
	return NextPort;
}
