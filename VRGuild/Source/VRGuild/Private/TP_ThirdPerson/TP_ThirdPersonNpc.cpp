// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_ThirdPerson/TP_ThirdPersonNpc.h"

// Sets default values
ATP_ThirdPersonNpc::ATP_ThirdPersonNpc()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATP_ThirdPersonNpc::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATP_ThirdPersonNpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATP_ThirdPersonNpc::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

