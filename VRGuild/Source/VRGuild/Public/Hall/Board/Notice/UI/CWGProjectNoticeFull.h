// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/UI/API/CWGProjectAPI.h"
#include "CWGProjectNoticeFull.generated.h"

/**
 * 
 */

class UCWGProjectNotice;

UCLASS()
class VRGUILD_API UCWGProjectNoticeFull : public UCWGProjectAPI
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCWGProjectNotice> ProjectNoticeFrontSide;
};
