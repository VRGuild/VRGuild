#include "Global/API/CACDeveloperAPI.h"
#include "Global/API/BPL/CBPLDeveloper.h"

UCACDeveloperAPI::UCACDeveloperAPI()
{
    PrimaryComponentTick.bCanEverTick = false;
    bWantsInitializeComponent = true;
}

void UCACDeveloperAPI::BeginPlay()
{
    Super::BeginPlay();
}

void UCACDeveloperAPI::InitializeComponent()
{
    Super::InitializeComponent();
}

void UCACDeveloperAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    // Define regex patterns for each endpoint
    FRegexPattern CreateDeveloperPattern(TEXT(R"(POST\s+/api/epic/developer$)"));
    FRegexPattern GetDeveloperPattern(TEXT(R"(GET\s+/api/epic/developer$)"));
    FRegexPattern UpdateDeveloperPattern(TEXT(R"(PATCH\s+/api/epic/developer$)"));
    FRegexPattern GetDeveloperByUserIdPattern(TEXT(R"(GET\s+/api/epic/developer/users/(\d+)$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("URL to match: %s"), *UrlToMatch);

    if (FRegexMatcher(CreateDeveloperPattern, UrlToMatch).FindNext())
    {
        DeveloperCreateCallBack(req, res);
    }
    else if (FRegexMatcher(GetDeveloperPattern, UrlToMatch).FindNext())
    {
        DeveloperGetCallBack(req, res);
    }
    else if (FRegexMatcher(UpdateDeveloperPattern, UrlToMatch).FindNext())
    {
        DeveloperUpdateCallBack(req, res);
    }
    else if (FRegexMatcher(GetDeveloperByUserIdPattern, UrlToMatch).FindNext())
    {
        FRegexMatcher Matcher(GetDeveloperByUserIdPattern, UrlToMatch);
        Matcher.FindNext();
        FString UserId = Matcher.GetCaptureGroup(1);
        UE_LOG(LogTemp, Display, TEXT("GET Developer By User ID: %s"), *UserId);
        DeveloperGetByUserIdCallBack(req, res);
    }
}

void UCACDeveloperAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FRegexPattern CreateDeveloperPattern(TEXT(R"(POST\s+/api/epic/developer$)"));
    FRegexPattern GetDeveloperPattern(TEXT(R"(GET\s+/api/epic/developer$)"));
    FRegexPattern UpdateDeveloperPattern(TEXT(R"(PATCH\s+/api/epic/developer$)"));
    FRegexPattern GetDeveloperByUserIdPattern(TEXT(R"(GET\s+/api/epic/developer/users/(\d+)$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    if (FRegexMatcher(CreateDeveloperPattern, UrlToMatch).FindNext())
    {
        OnFailDeveloperCreateCallBack();
    }
    else if (FRegexMatcher(GetDeveloperPattern, UrlToMatch).FindNext())
    {
        OnFailDeveloperGetCallBack();
    }
    else if (FRegexMatcher(UpdateDeveloperPattern, UrlToMatch).FindNext())
    {
        OnFailDeveloperUpdateCallBack();
    }
    else if (FRegexMatcher(GetDeveloperByUserIdPattern, UrlToMatch).FindNext())
    {
        OnFailDeveloperGetByUserIdCallBack();
    }
}

void UCACDeveloperAPI::DeveloperCreateCall(const FDeveloperRequest& Request)
{
    this->API = TEXT("api/epic/developer");
    HttpPostCall<FDeveloperRequest>(Request);
}

void UCACDeveloperAPI::DeveloperCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FDeveloperResponse ParsedResponse = JsonPerse<FDeveloperResponse>(JsonString);

    if (ParsedResponse.status == "success")
    {
        OnDeveloperCreateCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailDeveloperCreateCallBack();
    }
}

void UCACDeveloperAPI::DeveloperGetCall()
{
    this->API = TEXT("api/epic/developer");
    HttpGetCall();
}

void UCACDeveloperAPI::DeveloperGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FDeveloperResponse ParsedResponse = JsonPerse<FDeveloperResponse>(JsonString);

    if (ParsedResponse.status == "success")
    {
        OnDeveloperGetCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailDeveloperGetCallBack();
    }
}

void UCACDeveloperAPI::DeveloperUpdateCall(const FDeveloperRequest& Request)
{
    this->API = TEXT("api/epic/developer");
    HttpPatchCall<FDeveloperRequest>(Request);
}

void UCACDeveloperAPI::DeveloperUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FDeveloperResponse ParsedResponse = JsonPerse<FDeveloperResponse>(JsonString);

    if (ParsedResponse.status == "success")
    {
        OnDeveloperUpdateCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailDeveloperUpdateCallBack();
    }
}

void UCACDeveloperAPI::DeveloperGetByUserIdCall(const FString& UserId)
{
    this->API = FString::Printf(TEXT("api/epic/developer/users/%s"), *UserId);
    HttpGetCall();
}

void UCACDeveloperAPI::DeveloperGetByUserIdCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FDeveloperResponse ParsedResponse = JsonPerse<FDeveloperResponse>(JsonString);

    if (ParsedResponse.status == "success")
    {
        OnDeveloperGetByUserIdCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailDeveloperGetByUserIdCallBack();
    }
}