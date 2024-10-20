// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAProjectNotice.generated.h"

UCLASS()
class VRGUILD_API ACAProjectNotice : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACAProjectNotice();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector2D WidgetDrawSize = { 400,440 };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* RootSceneComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UWidgetComponent* FrontSideComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UWidgetComponent* BackSideComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> WidgetFrontSide;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> WidgetBackSide;

};
