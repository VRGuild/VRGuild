// Fill out your copyright notice in the Description page of Project Settings.


#include "CACChair.h"
#include "Components/BoxComponent.h"

// Sets default values
ACACChair::ACACChair()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);

	ChairArrow = CreateDefaultSubobject<USceneComponent>(TEXT("ChairArrow"));
	ChairArrow->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACACChair::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACACChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

