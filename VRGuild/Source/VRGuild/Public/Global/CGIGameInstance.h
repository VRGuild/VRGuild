// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionDelegates.h"

#include "Global/API/BPL/CBPLBase.h"

#include "CGIGameInstance.generated.h"


class UCACCharacterPartBase;
class UCWDisplayMessage;


USTRUCT(BlueprintType)
struct FCharacterCustomData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<int32> Selections;
	/* index 0: Head
	* index 1: Body
	* index 2: Lower
	*/

	UPROPERTY(BlueprintReadWrite)
	TArray<uint8> Pixels;

	UPROPERTY(BlueprintReadOnly)
	FString NickName;

	UPROPERTY(BlueprintReadOnly)
	FSkillCategoryInfo MainSkill;

	UPROPERTY(BlueprintReadOnly)
	int64 UserId;
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


	UPROPERTY(BlueprintReadWrite);
	FString NickName;
	
	UPROPERTY(BlueprintReadWrite);
	int64 UserId;

	UFUNCTION(BlueprintCallable)
	void SetEpicNickNameInstance(FString userNickname);
	UFUNCTION(BlueprintCallable)
	void SetEpicUserIdInstance(int64 EpicUserId);

	UFUNCTION(BlueprintCallable)
	void SetMainSkillCategory(FSkillCategoryInfo mainSkill);

	FCharacterCustomData CustomData;

	UPROPERTY(EditDefaultsOnly, Category=Settings)
	TArray<TSubclassOf<UActorComponent>> CharacterPartComponents;

	UFUNCTION(BlueprintCallable)
	void DisplayTraceMessage(bool bDisplay, FString msg);



private:
	UPROPERTY(EditDefaultsOnly, Category = Settings, meta=(AllowPrivateAccess))
	TSubclassOf<UCWDisplayMessage> DisplayMsgWidgetClass;
	TObjectPtr<UCWDisplayMessage> DisplayWidget;
};
