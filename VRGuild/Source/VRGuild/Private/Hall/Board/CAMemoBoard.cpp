// Fill out your copyright notice in the Description page of Project Settings.


#include "Hall/Board/CAMemoBoard.h"

// Sets default values
ACAMemoBoard::ACAMemoBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACAMemoBoard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACAMemoBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACAMemoBoard::StickBoard(AActor* Memo, FVector relativePosition)
{
	if (!Memo)
	{
		CreateMemo(relativePosition);
		return ;
	}
	Memo->AttachToActor(this,FAttachmentTransformRules::KeepRelativeTransform);
	Memo->SetActorRelativeLocation(relativePosition);
	Memo->SetActorRelativeRotation(FRotator(0));
}

