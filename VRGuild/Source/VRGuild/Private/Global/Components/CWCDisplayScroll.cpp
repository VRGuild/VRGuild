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
	UE_LOG(LogTemp, Warning, TEXT("Nice"));
}

void UCWCDisplayScroll::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCWCDisplayScroll, TestVar);
}

void UCWCDisplayScroll::OnRep_TestVar()
{
	UE_LOG(LogTemp, Warning, TEXT("SUCCESS! %s"), *GetNameSafe(TestVar));
}
