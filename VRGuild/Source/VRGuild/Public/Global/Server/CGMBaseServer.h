﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CGMBaseServer.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API ACGMBaseServer : public AGameModeBase
{
	GENERATED_BODY()
public:
	ACGMBaseServer();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void HandleSeamlessTravelPlayer(AController*& C) override;
	int32 GetNextPort();

	int32 NextPort;
};
