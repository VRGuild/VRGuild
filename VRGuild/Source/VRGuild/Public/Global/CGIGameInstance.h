﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionDelegates.h"

#include "CGIGameInstance.generated.h"


class UCACCharacterPartBase;

USTRUCT()
struct FCharacterCustomData
{
	GENERATED_BODY()
public:
	TArray<int> Selections;
	/* index 0: Head
	* index 1: Body
	* index 2: Lower
	*/
};

UCLASS()
class VRGUILD_API UCGIGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	virtual void Init() override;

	virtual void Shutdown() override;
		
	FDelegateHandle DestroySessionDelegateHandle;
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	

public:
	// 토큰을 저장하기 위한 변수 입니다.
	FString TokenID;

	FCharacterCustomData CustomData;

	UFUNCTION(BlueprintCallable)
	void AttachCustomSelections(ACharacter* NewCharacter);

	UPROPERTY(EditDefaultsOnly, Category=Settings)
	TArray<TSubclassOf<UActorComponent>> CharacterPartComponents;
};
