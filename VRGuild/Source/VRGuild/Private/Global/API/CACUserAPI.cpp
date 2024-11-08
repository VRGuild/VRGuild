#include "Global/API/CACUserAPI.h"
#include "Global/API/BPL/CBPLUser.h"

UCACUserAPI::UCACUserAPI()
{
    PrimaryComponentTick.bCanEverTick = false;
    bWantsInitializeComponent = true;
}

void UCACUserAPI::BeginPlay()
{
    Super::BeginPlay();
}

void UCACUserAPI::InitializeComponent()
{
    Super::InitializeComponent();
}

void UCACUserAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    // Define regex patterns for each endpoint
    FRegexPattern GetUserOwnInfoPattern(TEXT(R"(GET\s+/api/user/epic$)"));
    FRegexPattern GetUserInfoPattern(TEXT(R"(GET\s+/api/user/(\d+)$)"));
    FRegexPattern GetUserMemberPattern(TEXT(R"(GET\s+/api/user/(\d+)/member$)"));

    // Create URL string to match against patterns
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("URL to match: %s"), *UrlToMatch);
    if (FRegexMatcher(GetUserOwnInfoPattern, UrlToMatch).FindNext())
    {
        UE_LOG(LogTemp, Display, TEXT("GET User Own Info"));
        UserOwnInfoGetCallBack(req, res);
    }
    else if (FRegexMatcher(GetUserInfoPattern, UrlToMatch).FindNext())
    {
        FRegexMatcher Matcher(GetUserInfoPattern, UrlToMatch);
        Matcher.FindNext();
        FString UserId = Matcher.GetCaptureGroup(1);
        UE_LOG(LogTemp, Display, TEXT("GET User Info ID: %s"), *UserId);
        UserInfoGetCallBack(req, res);
    }
    else if (FRegexMatcher(GetUserMemberPattern, UrlToMatch).FindNext())
    {
        FRegexMatcher Matcher(GetUserMemberPattern, UrlToMatch);
        Matcher.FindNext();
        FString UserId = Matcher.GetCaptureGroup(1);
        UE_LOG(LogTemp, Display, TEXT("GET User Member Info ID: %s"), *UserId);
        UserMemberInfoGetCallBack(req, res);
    }
}

void UCACUserAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    // Similar pattern matching as OnSuccessAPI
    FRegexPattern GetUserOwnInfoPattern(TEXT(R"(GET\s+/api/user/epic$)"));
    FRegexPattern GetUserInfoPattern(TEXT(R"(GET\s+/api/user/(\d+)$)"));
    FRegexPattern GetUserMemberPattern(TEXT(R"(GET\s+/api/user/(\d+)/member$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    
    if (FRegexMatcher(GetUserOwnInfoPattern, UrlToMatch).FindNext())
    {
        UE_LOG(LogTemp, Display, TEXT("GET User Own Info"));
        OnFailUserOwnInfoGetCallBack();
    }
    else if (FRegexMatcher(GetUserInfoPattern, UrlToMatch).FindNext())
    {
        OnFailUserInfoGetCallBack();
    }
    else if (FRegexMatcher(GetUserMemberPattern, UrlToMatch).FindNext())
    {
        OnFailUserMemberInfoGetCallBack();
    }
}

void UCACUserAPI::UserOwnInfoGetCall()
{
    this->API = FString::Printf(TEXT("api/user/epic"));
    HttpGetCall();
}

void UCACUserAPI::UserOwnInfoGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FUserInfoResponse ParsedResponse = JsonPerse<FUserInfoResponse>(JsonString);

    OnUserOwnInfoGetCallBack(ParsedResponse.data);
}

void UCACUserAPI::UserInfoGetCall(const FString& UserId)
{
    this->API = FString::Printf(TEXT("api/user/%s"), *UserId);
    HttpGetCall();
}

void UCACUserAPI::UserInfoGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FUserInfoResponse ParsedResponse = JsonPerse<FUserInfoResponse>(JsonString);

    OnUserInfoGetCallBack(ParsedResponse.data);
}

void UCACUserAPI::UserMemberInfoGetCall(const FString& UserId)
{
    this->API = FString::Printf(TEXT("api/user/%s/member"), *UserId);
    HttpGetCall();
}

void UCACUserAPI::UserMemberInfoGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FUserMemberInfoResponse ParsedResponse = JsonPerse<FUserMemberInfoResponse>(JsonString);

    OnUserMemberInfoGetCallBack(ParsedResponse.data);
}