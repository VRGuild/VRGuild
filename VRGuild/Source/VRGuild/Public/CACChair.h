// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CACChair.generated.h"

UCLASS()
class VRGUILD_API ACACChair : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACACChair();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	class USceneComponent* ChairArrow;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	class UBoxComponent* BoxComp;
};
