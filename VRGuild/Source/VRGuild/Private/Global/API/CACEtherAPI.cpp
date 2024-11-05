#include "Global/API/CACEtherAPI.h"
#include "Global/API/BPL/CBPLEther.h"

UCACEtherAPI::UCACEtherAPI()
{
    PrimaryComponentTick.bCanEverTick = false;
    bWantsInitializeComponent = true;
}

void UCACEtherAPI::BeginPlay()
{
    Super::BeginPlay();
}

void UCACEtherAPI::InitializeComponent()
{
    Super::InitializeComponent();
}

void UCACEtherAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    FRegexPattern CreateEtherPattern(TEXT(R"(POST\s+/api/ether$)"));
    FRegexPattern GetEtherPattern(TEXT(R"(GET\s+/api/ether/(\d+)$)"));
    FRegexPattern GetEtherListPattern(TEXT(R"(GET\s+/api/ether/list$)"));
    FRegexPattern GetEtherHistoryPattern(TEXT(R"(GET\s+/api/ether/history/(\d+)$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("URL to match: %s"), *UrlToMatch);

    if (FRegexMatcher(CreateEtherPattern, UrlToMatch).FindNext())
    {
        EtherCreateCallBack(req, res);
    }
    else if (FRegexMatcher(GetEtherPattern, UrlToMatch).FindNext())
    {
        EtherGetCallBack(req, res);
    }
    else if (FRegexMatcher(GetEtherListPattern, UrlToMatch).FindNext())
    {
        EtherListGetCallBack(req, res);
    }
    else if (FRegexMatcher(GetEtherHistoryPattern, UrlToMatch).FindNext())
    {
        EtherHistoryGetCallBack(req, res);
    }
}

void UCACEtherAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    FString ErrorMessage = TEXT("알 수 없는 오류가 발생했습니다.");

    // Parse error message from response
    if (res->GetResponseCode() == 400 || res->GetResponseCode() == 401 || res->GetResponseCode() == 404)
    {
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(res->GetContentAsString());
        if (FJsonSerializer::Deserialize(Reader, JsonObject))
        {
            ErrorMessage = JsonObject->GetStringField(TEXT("message"));
        }
    }

    FRegexPattern CreateEtherPattern(TEXT(R"(POST\s+/api/ether$)"));
    FRegexPattern GetEtherPattern(TEXT(R"(GET\s+/api/ether/(\d+)$)"));
    FRegexPattern GetEtherListPattern(TEXT(R"(GET\s+/api/ether/list$)"));
    FRegexPattern GetEtherHistoryPattern(TEXT(R"(GET\s+/api/ether/history/(\d+)$)"));

    if (FRegexMatcher(CreateEtherPattern, UrlToMatch).FindNext())
    {
        OnFailEtherCreateCallBack(ErrorMessage);
    }
    else if (FRegexMatcher(GetEtherPattern, UrlToMatch).FindNext())
    {
        OnFailEtherGetCallBack(ErrorMessage);
    }
    else if (FRegexMatcher(GetEtherListPattern, UrlToMatch).FindNext())
    {
        OnFailEtherListGetCallBack();
    }
    else if (FRegexMatcher(GetEtherHistoryPattern, UrlToMatch).FindNext())
    {
        OnFailEtherHistoryGetCallBack();
    }
}

void UCACEtherAPI::EtherCreateCall(const FEther& Ether)
{
    this->API = TEXT("api/ether");
    HttpPostCall<FEther>(Ether);
}

void UCACEtherAPI::EtherCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FEtherResponse ParsedResponse = JsonPerse<FEtherResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnEtherCreateCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailEtherCreateCallBack(TEXT("에테르 생성에 실패했습니다."));
    }
}

void UCACEtherAPI::EtherGetCall(const FString& EtherId)
{
    this->API = FString::Printf(TEXT("api/ether/%s"), *EtherId);
    HttpGetCall();
}

void UCACEtherAPI::EtherGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FEtherResponse ParsedResponse = JsonPerse<FEtherResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnEtherGetCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailEtherGetCallBack(TEXT("에테르 조회에 실패했습니다."));
    }
}

void UCACEtherAPI::EtherListGetCall()
{
    this->API = TEXT("api/ether/list");
    HttpGetCall();
}

void UCACEtherAPI::EtherListGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FEtherListResponse ParsedResponse = JsonPerse<FEtherListResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnEtherListGetCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailEtherListGetCallBack();
    }
}

void UCACEtherAPI::EtherHistoryGetCall(const FString& UserId)
{
    this->API = FString::Printf(TEXT("api/ether/history/%s"), *UserId);
    HttpGetCall();
}

void UCACEtherAPI::EtherHistoryGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FEtherBalanceResponse ParsedResponse = JsonPerse<FEtherBalanceResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnEtherHistoryGetCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailEtherHistoryGetCallBack();
    }
}