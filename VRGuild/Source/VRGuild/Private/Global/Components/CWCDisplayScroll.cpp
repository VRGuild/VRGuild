// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Components/CWCDisplayScroll.h"
#include "Net/UnrealNetwork.h"

UCWCDisplayScroll::UCWCDisplayScroll()
{
	SetIsReplicatedByDefault(true);
	TestVar = nullptr;
}

void UCWCDisplayScroll::ServerTest_Implementation()
{
	FHitResult Result;
	Result.GetComponent();

	UE_LOG(LogTemp, Warning, TEXT("Nice"));
}

void UCWCDisplayScroll::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCWCDisplayScroll, TestVar);
}

bool UCWCDisplayScroll::CanTrace(ACharacter* Initiator) const
{	
	return TestVar != nullptr;
}

bool UCWCDisplayScroll::CanInteract(ACharacter* Initiator) const
{

	return false;
}

void UCWCDisplayScroll::BeginTrace(ACharacter* Initiator)
{
}

void UCWCDisplayScroll::EndTrace(ACharacter* Initiator)
{
}

void UCWCDisplayScroll::BeginInteract(ACharacter* Initiator)
{
}

void UCWCDisplayScroll::EndInteract(ACharacter* Initiator)
{
}

void UCWCDisplayScroll::Set(AActor* actorTest)
{
	TestVar = actorTest;
}

void UCWCDisplayScroll::OnRep_TestVar()
{
	UE_LOG(LogTemp, Warning, TEXT("SUCCESS! %s"), *GetNameSafe(TestVar));
}
