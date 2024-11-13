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
    FRegexPattern GetDeveloperReviewPattern(TEXT(R"(GET\s+/api/epic/developer/all\?page=(\d+)$)"));

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
    else if (FRegexMatcher(GetDeveloperReviewPattern, UrlToMatch).FindNext())
    {
        DeveloperReviewGetCallBack(req, res);
    }
}

void UCACDeveloperAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FRegexPattern CreateDeveloperPattern(TEXT(R"(POST\s+/api/epic/developer$)"));
    FRegexPattern GetDeveloperPattern(TEXT(R"(GET\s+/api/epic/developer$)"));
    FRegexPattern UpdateDeveloperPattern(TEXT(R"(PATCH\s+/api/epic/developer$)"));
    FRegexPattern GetDeveloperByUserIdPattern(TEXT(R"(GET\s+/api/epic/developer/users/(\d+)$)"));
    FRegexPattern GetDeveloperReviewPattern(TEXT(R"(GET\s+/api/epic/developer/all\?page=(\d+)$)"));

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
    else if (FRegexMatcher(GetDeveloperReviewPattern, UrlToMatch).FindNext())
    {
        OnFailDeveloperReviewGetCallBack();
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

    OnDeveloperCreateCallBack(ParsedResponse.data);
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

    OnDeveloperGetCallBack(ParsedResponse.data);
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

    OnDeveloperUpdateCallBack(ParsedResponse.data);
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

    OnDeveloperGetByUserIdCallBack(ParsedResponse.data);
}

void UCACDeveloperAPI::DeveloperReviewGetCall(const int32& page)
{
    this->API = FString::Printf(TEXT("api/epic/developer/all?page=%d"), page);
    HttpGetCall();
}

void UCACDeveloperAPI::DeveloperReviewGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FDeveloperListResponse ParsedResponse = JsonPerse<FDeveloperListResponse>(JsonString);

    OnDeveloperReviewGetCallBack(ParsedResponse);
}
