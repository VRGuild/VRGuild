// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionDelegates.h"
#include "CGIGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API UCGIGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	virtual void Init() override;

	virtual void Shutdown() override;
		
	FDelegateHandle DestroySessionDelegateHandle;
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
};
