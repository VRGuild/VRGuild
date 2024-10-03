// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Server/CGMBaseServer.h"
#include "Global/Server/CGSSBaseGameSession.h"

ACGMBaseServer::ACGMBaseServer()
{
	GameSessionClass = ACGSSBaseGameSession::StaticClass();
}
