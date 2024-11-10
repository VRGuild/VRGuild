// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWGTileFurnitureButton.h"
#include "CWGTileFurniture.generated.h"

/**
 * 
 */
UCLASS()
class VRGUILD_API UCWGTileFurniture : public UUserWidget
{
	GENERATED_BODY()

public: 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<int, UCWGTileFurnitureButton*> FurnitureButtonBox;
	
};
