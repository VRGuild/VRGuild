// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWDisplayMessage.generated.h"

/**
 * 
 */

class UTextBlock;

UCLASS()
class VRGUILD_API UCWDisplayMessage : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init(FString msg);

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Message;
};
