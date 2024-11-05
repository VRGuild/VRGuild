#include "Global/API/CACBusinessAPI.h"
#include "Global/API/BPL/CBPLBusiness.h"

UCACBusinessAPI::UCACBusinessAPI()
{
    PrimaryComponentTick.bCanEverTick = false;
    bWantsInitializeComponent = true;
}

void UCACBusinessAPI::BeginPlay()
{
    Super::BeginPlay();
}

void UCACBusinessAPI::InitializeComponent()
{
    Super::InitializeComponent();
}

void UCACBusinessAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    // Define regex pattern for business endpoint
    FRegexPattern GetBusinessInfoPattern(TEXT(R"(GET\s+/api/epic/business/(\d+)$)"));

    // Create URL string to match against pattern
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("URL to match: %s"), *UrlToMatch);

    if (FRegexMatcher(GetBusinessInfoPattern, UrlToMatch).FindNext())
    {
        FRegexMatcher Matcher(GetBusinessInfoPattern, UrlToMatch);
        Matcher.FindNext();
        FString BusinessId = Matcher.GetCaptureGroup(1);
        UE_LOG(LogTemp, Display, TEXT("GET Business Info ID: %s"), *BusinessId);
        BusinessInfoGetCallBack(req, res);
    }
}

void UCACBusinessAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FRegexPattern GetBusinessInfoPattern(TEXT(R"(GET\s+/api/epic/business/(\d+)$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    if (FRegexMatcher(GetBusinessInfoPattern, UrlToMatch).FindNext())
    {
        OnFailBusinessInfoGetCallBack();
    }
}

void UCACBusinessAPI::BusinessInfoGetCall(const FString& BusinessId)
{
    this->API = FString::Printf(TEXT("api/epic/business/%s"), *BusinessId);
    HttpGetCall();
}

void UCACBusinessAPI::BusinessInfoGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FBusinessInfoResponse ParsedResponse = JsonPerse<FBusinessInfoResponse>(JsonString);

    if (ParsedResponse.status == "success")
    {
        OnBusinessInfoGetCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailBusinessInfoGetCallBack();
    }
}