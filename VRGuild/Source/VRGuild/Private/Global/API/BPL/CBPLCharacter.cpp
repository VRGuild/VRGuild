// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/API/BPL/CBPLCharacter.h"

FCharacterInfo UCBPLCharacter::SetCharacterCustom(FCharacterInfo target, TArray<FCustomInfo> CustomInfoList)
{
	target.customList.Empty();

	for (auto custominfo : CustomInfoList)
	{
		target.customList.Add(custominfo);
	}
	return target;
}

FCharacterInfo UCBPLCharacter::SetCharacterPicture(FCharacterInfo target, TArray<FLinearColor> CustomCharacterPicture)
{
	//target.characterPicture.Empty();

	for (auto characterPixel : CustomCharacterPicture)
	{
		//target.characterPicture.Add(characterPixel);
	}
	return target;
}
