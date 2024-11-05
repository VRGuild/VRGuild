// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Global/API/BPL/CBPLBase.h"
#include "CWGGuildList.generated.h"

struct FGuildInfo;
/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGGuildList : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetGuildInfo(FGuildInfo guildInfo);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGuildInfo GuildInfo;
	
};
