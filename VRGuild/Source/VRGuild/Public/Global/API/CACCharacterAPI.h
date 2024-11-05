#pragma once

#include "CoreMinimal.h"
#include "Global/API/CACBaseAPI.h"
#include "CACCharacterAPI.generated.h"

struct FCharacterDetailResponse;
struct FCharacterInfo;


UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRGUILD_API UCACCharacterAPI : public UCACBaseAPI
{
    GENERATED_BODY()

public:
    UCACCharacterAPI();

protected:
    virtual void BeginPlay() override;
    virtual void InitializeComponent() override;
    virtual void OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;
    virtual void OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res) override;

    // Create Character
    UFUNCTION(BlueprintCallable, Category = "Character API")
    void CharacterCreateCall(const FCharacterInfo& CharacterInfo);
    void CharacterCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Character API")
    void OnCharacterCreateCallBack(const FCharacterInfo& CharacterInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Character API")
    void OnFailCharacterCreateCallBack();

    // Get Character
    UFUNCTION(BlueprintCallable, Category = "Character API")
    void CharacterGetCall(const FString& CharacterId);
    void CharacterGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Character API")
    void OnCharacterGetCallBack(const FCharacterInfo& CharacterInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Character API")
    void OnFailCharacterGetCallBack();

    // Update Character
    UFUNCTION(BlueprintCallable, Category = "Character API")
    void CharacterUpdateCall(const FString& CharacterId, const FCharacterInfo& CharacterInfo);
    void CharacterUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Character API")
    void OnCharacterUpdateCallBack(const FCharacterInfo& CharacterInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Character API")
    void OnFailCharacterUpdateCallBack();

    // Get Character By UserId
    UFUNCTION(BlueprintCallable, Category = "Character API")
    void CharacterGetByUserIdCall(const FString& UserId);
    void CharacterGetByUserIdCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Character API")
    void OnCharacterGetByUserIdCallBack(const FCharacterInfo& CharacterInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Character API")
    void OnFailCharacterGetByUserIdCallBack();

    // Get Character By Nickname
    UFUNCTION(BlueprintCallable, Category = "Character API")
    void CharacterGetByNicknameCall(const FString& Nickname);
    void CharacterGetByNicknameCallBack(FHttpRequestPtr req, FHttpResponsePtr res);
    UFUNCTION(BlueprintImplementableEvent, Category = "Character API")
    void OnCharacterGetByNicknameCallBack(const FCharacterInfo& CharacterInfo);
    UFUNCTION(BlueprintImplementableEvent, Category = "Character API")
    void OnFailCharacterGetByNicknameCallBack();
};