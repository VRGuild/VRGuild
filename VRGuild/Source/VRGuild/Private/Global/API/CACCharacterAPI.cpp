#include "Global/API/CACCharacterAPI.h"
#include "Global/API/BPL/CBPLCharacter.h"

UCACCharacterAPI::UCACCharacterAPI()
{
    PrimaryComponentTick.bCanEverTick = false;
    bWantsInitializeComponent = true;
}

void UCACCharacterAPI::BeginPlay()
{
    Super::BeginPlay();
}

void UCACCharacterAPI::InitializeComponent()
{
    Super::InitializeComponent();
}

void UCACCharacterAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    // Define regex patterns for each endpoint
    FRegexPattern CreateCharacterPattern(TEXT(R"(POST\s+/api/character$)"));
    FRegexPattern GetCharacterPattern(TEXT(R"(GET\s+/api/character/(\d+)$)"));
    FRegexPattern UpdateCharacterPattern(TEXT(R"(PATCH\s+/api/character/(\d+)$)"));
    FRegexPattern GetCharacterByUserIdPattern(TEXT(R"(GET\s+/api/character/user/(\d+)$)"));
    FRegexPattern GetCharacterByNicknamePattern(TEXT(R"(GET\s+/api/character/nickname/([^/]+)$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("URL to match: %s"), *UrlToMatch);

    if (FRegexMatcher(CreateCharacterPattern, UrlToMatch).FindNext())
    {
        CharacterCreateCallBack(req, res);
    }
    else if (FRegexMatcher(GetCharacterPattern, UrlToMatch).FindNext())
    {
        CharacterGetCallBack(req, res);
    }
    else if (FRegexMatcher(UpdateCharacterPattern, UrlToMatch).FindNext())
    {
        CharacterUpdateCallBack(req, res);
    }
    else if (FRegexMatcher(GetCharacterByUserIdPattern, UrlToMatch).FindNext())
    {
        CharacterGetByUserIdCallBack(req, res);
    }
    else if (FRegexMatcher(GetCharacterByNicknamePattern, UrlToMatch).FindNext())
    {
        CharacterGetByNicknameCallBack(req, res);
    }
}

void UCACCharacterAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    FRegexPattern CreateCharacterPattern(TEXT(R"(POST\s+/api/character$)"));
    FRegexPattern GetCharacterPattern(TEXT(R"(GET\s+/api/character/(\d+)$)"));
    FRegexPattern UpdateCharacterPattern(TEXT(R"(PATCH\s+/api/character/(\d+)$)"));
    FRegexPattern GetCharacterByUserIdPattern(TEXT(R"(GET\s+/api/character/user/(\d+)$)"));
    FRegexPattern GetCharacterByNicknamePattern(TEXT(R"(GET\s+/api/character/nickname/([^/]+)$)"));

    if (FRegexMatcher(CreateCharacterPattern, UrlToMatch).FindNext())
    {
        OnFailCharacterCreateCallBack();
    }
    else if (FRegexMatcher(GetCharacterPattern, UrlToMatch).FindNext())
    {
        OnFailCharacterGetCallBack();
    }
    else if (FRegexMatcher(UpdateCharacterPattern, UrlToMatch).FindNext())
    {
        OnFailCharacterUpdateCallBack();
    }
    else if (FRegexMatcher(GetCharacterByUserIdPattern, UrlToMatch).FindNext())
    {
        OnFailCharacterGetByUserIdCallBack();
    }
    else if (FRegexMatcher(GetCharacterByNicknamePattern, UrlToMatch).FindNext())
    {
        OnFailCharacterGetByNicknameCallBack();
    }
}

void UCACCharacterAPI::CharacterCreateCall(const FCharacterInfo& CharacterInfo)
{
    this->API = TEXT("api/character");
    HttpPostCall<FCharacterInfo>(CharacterInfo);
}


void UCACCharacterAPI::CharacterCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FCharacterDetailResponse ParsedResponse = JsonPerse<FCharacterDetailResponse>(JsonString);

    if (ParsedResponse.status == "success")
    {
        OnCharacterCreateCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailCharacterCreateCallBack();
    }
}

void UCACCharacterAPI::CharacterGetCall(const FString& CharacterId)
{
    this->API = FString::Printf(TEXT("api/character/%s"), *CharacterId);
    HttpGetCall();
}

void UCACCharacterAPI::CharacterGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FCharacterDetailResponse ParsedResponse = JsonPerse<FCharacterDetailResponse>(JsonString);

    if (ParsedResponse.status == "success")
    {
        OnCharacterGetCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailCharacterGetCallBack();
    }
}

void UCACCharacterAPI::CharacterUpdateCall(const FString& CharacterId, const FCharacterInfo& CharacterInfo)
{
    this->API = FString::Printf(TEXT("api/character/%s"), *CharacterId);
    HttpPatchCall<FCharacterInfo>(CharacterInfo);
}

void UCACCharacterAPI::CharacterUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FCharacterDetailResponse ParsedResponse = JsonPerse<FCharacterDetailResponse>(JsonString);

    if (ParsedResponse.status == "success")
    {
        OnCharacterUpdateCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailCharacterUpdateCallBack();
    }
}

void UCACCharacterAPI::CharacterGetByUserIdCall(const FString& UserId)
{
    this->API = FString::Printf(TEXT("api/character/user/%s"), *UserId);
    HttpGetCall();
}

void UCACCharacterAPI::CharacterGetByUserIdCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FCharacterDetailResponse ParsedResponse = JsonPerse<FCharacterDetailResponse>(JsonString);

    if (ParsedResponse.status == "success")
    {
        OnCharacterGetByUserIdCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailCharacterGetByUserIdCallBack();
    }
}

void UCACCharacterAPI::CharacterGetByNicknameCall(const FString& Nickname)
{
    this->API = FString::Printf(TEXT("api/character/nickname/%s"), *Nickname);
    HttpGetCall();
}

void UCACCharacterAPI::CharacterGetByNicknameCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FCharacterDetailResponse ParsedResponse = JsonPerse<FCharacterDetailResponse>(JsonString);

    if (ParsedResponse.status == "success")
    {
        OnCharacterGetByNicknameCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailCharacterGetByNicknameCallBack();
    }
}