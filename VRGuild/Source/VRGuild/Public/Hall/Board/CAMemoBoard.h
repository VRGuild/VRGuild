// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAMemoBoard.generated.h"

UCLASS()
class VRGUILD_API ACAMemoBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACAMemoBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
	void StickBoard(AActor* Memo, FVector relativePosition);

	UFUNCTION(BlueprintImplementableEvent)
	void CreateMemo(FVector relativePosition);

};
