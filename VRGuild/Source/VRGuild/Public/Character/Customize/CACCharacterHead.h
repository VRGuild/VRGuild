// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Customize/CACCharacterPartBase.h"
#include "CACCharacterHead.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRGUILD_API UCACCharacterHead : public UCACCharacterPartBase
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCACCharacterHead();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
