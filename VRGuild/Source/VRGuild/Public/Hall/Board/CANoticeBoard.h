// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CANoticeBoard.generated.h"

struct FProjectNotice;

UCLASS()
class VRGUILD_API ACANoticeBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACANoticeBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	UStaticMeshComponent* BoardMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* BoardMesh;
	
	UFUNCTION(BlueprintCallable)
	void PostProjectNotice(FVector position, FProjectNotice projectNotice);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ACAProjectNotice> ProjectNoticeClass;
};
