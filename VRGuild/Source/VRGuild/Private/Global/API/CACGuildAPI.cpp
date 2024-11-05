#include "Global/API/CACGuildAPI.h"
#include "Global/API/BPL/CBPLGuild.h"

UCACGuildAPI::UCACGuildAPI()
{
    PrimaryComponentTick.bCanEverTick = false;
    bWantsInitializeComponent = true;
}

void UCACGuildAPI::BeginPlay()
{
    Super::BeginPlay();
}

void UCACGuildAPI::InitializeComponent()
{
    Super::InitializeComponent();
}

void UCACGuildAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    FRegexPattern CreateGuildPattern(TEXT(R"(POST\s+/api/guild$)"));
    FRegexPattern GetGuildPattern(TEXT(R"(GET\s+/api/guild/(\d+)$)"));
    FRegexPattern UpdateGuildPattern(TEXT(R"(PATCH\s+/api/guild/(\d+)$)"));
    FRegexPattern ApplyGuildPattern(TEXT(R"(GET\s+/api/guild/apply/(\d+)$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("URL to match: %s"), *UrlToMatch);

    if (FRegexMatcher(CreateGuildPattern, UrlToMatch).FindNext())
    {
        GuildCreateCallBack(req, res);
    }
    else if (FRegexMatcher(GetGuildPattern, UrlToMatch).FindNext())
    {
        GuildGetCallBack(req, res);
    }
    else if (FRegexMatcher(UpdateGuildPattern, UrlToMatch).FindNext())
    {
        GuildUpdateCallBack(req, res);
    }
    else if (FRegexMatcher(ApplyGuildPattern, UrlToMatch).FindNext())
    {
        GuildApplyCallBack(req, res);
    }
}

void UCACGuildAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    FRegexPattern CreateGuildPattern(TEXT(R"(POST\s+/api/guild$)"));
    FRegexPattern GetGuildPattern(TEXT(R"(GET\s+/api/guild/(\d+)$)"));
    FRegexPattern UpdateGuildPattern(TEXT(R"(PATCH\s+/api/guild/(\d+)$)"));
    FRegexPattern ApplyGuildPattern(TEXT(R"(GET\s+/api/guild/apply/(\d+)$)"));

    if (FRegexMatcher(CreateGuildPattern, UrlToMatch).FindNext())
    {
        OnFailGuildCreateCallBack();
    }
    else if (FRegexMatcher(GetGuildPattern, UrlToMatch).FindNext())
    {
        OnFailGuildGetCallBack();
    }
    else if (FRegexMatcher(UpdateGuildPattern, UrlToMatch).FindNext())
    {
        OnFailGuildUpdateCallBack();
    }
    else if (FRegexMatcher(ApplyGuildPattern, UrlToMatch).FindNext())
    {
        FString ErrorMessage = TEXT("알 수 없는 오류가 발생했습니다.");
        if (res->GetResponseCode() == 400 || res->GetResponseCode() == 401)
        {
            FString JsonString = res->GetContentAsString();
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
            if (FJsonSerializer::Deserialize(Reader, JsonObject))
            {
                ErrorMessage = JsonObject->GetStringField(TEXT("message"));
            }
        }
        OnFailGuildApplyCallBack(ErrorMessage);
    }
}

void UCACGuildAPI::GuildCreateCall(const FGuildInfo& GuildInfo)
{
    this->API = TEXT("api/guild");
    HttpPostCall<FGuildInfo>(GuildInfo);
}

void UCACGuildAPI::GuildCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FGuildDetailResponse ParsedResponse = JsonPerse<FGuildDetailResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnGuildCreateCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailGuildCreateCallBack();
    }
}

void UCACGuildAPI::GuildGetCall(const FString& GuildId)
{
    this->API = FString::Printf(TEXT("api/guild/%s"), *GuildId);
    HttpGetCall();
}

void UCACGuildAPI::GuildGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FGuildDetailResponse ParsedResponse = JsonPerse<FGuildDetailResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnGuildGetCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailGuildGetCallBack();
    }
}

void UCACGuildAPI::GuildUpdateCall(const FString& GuildId, const FGuildInfo& GuildInfo)
{
    this->API = FString::Printf(TEXT("api/guild/%s"), *GuildId);
    HttpPatchCall<FGuildInfo>(GuildInfo);
}

void UCACGuildAPI::GuildUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FGuildDetailResponse ParsedResponse = JsonPerse<FGuildDetailResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnGuildUpdateCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailGuildUpdateCallBack();
    }
}

void UCACGuildAPI::GuildApplyCall(const FString& GuildId)
{
    this->API = FString::Printf(TEXT("api/guild/apply/%s"), *GuildId);
    HttpGetCall();
}

void UCACGuildAPI::GuildApplyCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FGuildDetailResponse ParsedResponse = JsonPerse<FGuildDetailResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnGuildApplyCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailGuildApplyCallBack(TEXT("API 호출에 실패했습니다."));
    }
}