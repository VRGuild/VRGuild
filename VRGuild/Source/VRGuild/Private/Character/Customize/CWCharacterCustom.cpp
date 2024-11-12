// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Customize/CWCharacterCustom.h"
#include "Components/Button.h"
#include "Character/Customize/CACCharacterHead.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Customize/CACCharacterPartBase.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Character/Customize/CACCharacterBody.h"
#include "Character/Customize/CACCharacterLower.h"
#include "Character/Customize/CACCustomInteraction.h"
#include "ImageUtils.h"
#include "Engine/Texture2D.h"
#include "Engine/TextureRenderTarget2D.h"



void UCWCharacterCustom::NativeConstruct()
{
	Super::NativeConstruct();

	ATP_ThirdPersonCharacter* PlayerCharacter = Cast<ATP_ThirdPersonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		CharacterHeadComponent = PlayerCharacter->FindComponentByClass<UCACCharacterHead>();
		CharacterBodyComponent = PlayerCharacter->FindComponentByClass<UCACCharacterBody>();
		CharacterLowerComponent = PlayerCharacter->FindComponentByClass<UCACCharacterLower>();
		CharacterCustomComponent = PlayerCharacter->FindComponentByClass<UCACCustomInteraction>();
		OnPlayerComponentLoaded();
	}
}

void UCWCharacterCustom::CustomHead(int32 index)
{
	if (nullptr != CharacterHeadComponent)
		CharacterHeadComponent->SwitchSKM(index);
}

void UCWCharacterCustom::CustomBody(int32 index)
{
	if (nullptr != CharacterBodyComponent)
	{
		CharacterBodyComponent->SwitchSKM(index);
	}
}

void UCWCharacterCustom::CustomLower(int32 index)
{
	if (nullptr != CharacterLowerComponent)
	{
		CharacterLowerComponent->SwitchSKM(1);
	}
}

TArray<int32> UCWCharacterCustom::CustomSave()
{
	Data.Selections.Add(CharacterHeadComponent->ValueSelected);
	Data.Selections.Add(CharacterBodyComponent->ValueSelected);
	Data.Selections.Add(CharacterLowerComponent->ValueSelected);
	return (Data.Selections);
}


void UCWCharacterCustom::CustomEnd()
{
	if (nullptr != CharacterCustomComponent)
	{
		CharacterCustomComponent->SaveCustomData(Data);
		this->RemoveFromParent();
	}	
}

TArray<uint8> UCWCharacterCustom::CompressedRenderTargerToPNG(UTextureRenderTarget2D* RenderTarget)
{
	TArray<uint8> CompressedBitmap;

	if (!RenderTarget)
	return CompressedBitmap;

	FTextureRenderTargetResource* RenderResource = RenderTarget->GameThread_GetRenderTargetResource();
	FIntRect Region(220, 160, 420, 480);
	TArray<FColor> Bitmap;

	if (RenderResource->ReadPixels(Bitmap, FReadSurfaceDataFlags(), Region))
	{
		int32 Width = Region.Width();
		int32 Height = Region.Height();
		FImageUtils::CompressImageArray(Width, Height, Bitmap, CompressedBitmap);

	}
	return CompressedBitmap;
}

//UTexture2D* UCWCharacterCustom::CreateTextureFromCompressedData(const TArray<uint8>& CompressedData)
//{
//	// JPEG Data 디코딩 
//	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
//	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
//
//	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(CompressedData.GetData(), CompressedData.Num()))
//	{
//		TArray<uint8> RawData;
//		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, RawData))
//		{
//			int32 Width = ImageWrapper->GetWidth();
//			int32 Height = ImageWrapper->GetHeight();
//
//			UTexture2D* NewTexture = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);
//			if (!NewTexture) { return nullptr;}
//
//			NewTexture->UpdateResource();
//			return NewTexture;
//		}
//	}
//	return nullptr;
//}
