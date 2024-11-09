// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Image.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CBPLDynamicWidget.generated.h"


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class VRGUILD_API UCBPLDynamicWidget : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	static void SetImageTexture(UImage* image, UTexture2D* texture);

	UFUNCTION(BlueprintCallable, Category = "Tools")
	static void SetImageSize(UImage* image, FVector2D imageSize);
};
