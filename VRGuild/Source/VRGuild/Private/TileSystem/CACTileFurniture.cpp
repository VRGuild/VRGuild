// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSystem/CACTileFurniture.h"

// Sets default values for this component's properties
UCACTileFurniture::UCACTileFurniture()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UCACTileFurniture::SwitchFurniture(int value)
{
}

// Called when the game starts
void UCACTileFurniture::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCACTileFurniture::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

