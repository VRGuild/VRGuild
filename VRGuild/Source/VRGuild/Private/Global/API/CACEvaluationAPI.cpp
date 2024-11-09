#include "Global/API/CACEvaluationAPI.h"
#include "Global/API/BPL/CBPLEvaluation.h"

UCACEvaluationAPI::UCACEvaluationAPI()
{
    PrimaryComponentTick.bCanEverTick = false;
    bWantsInitializeComponent = true;
}

void UCACEvaluationAPI::BeginPlay()
{
    Super::BeginPlay();
}

void UCACEvaluationAPI::InitializeComponent()
{
    Super::InitializeComponent();
}

void UCACEvaluationAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    FRegexPattern CreateEvaluationPattern(TEXT(R"(POST\s+/api/evaluation$)"));
    FRegexPattern GetEvaluationPattern(TEXT(R"(GET\s+/api/evaluation/(\d+)/([^/]+)$)"));
    FRegexPattern UpdateEvaluationPattern(TEXT(R"(PATCH\s+/api/evaluation$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("URL to match: %s"), *UrlToMatch);

    if (FRegexMatcher(CreateEvaluationPattern, UrlToMatch).FindNext())
    {
        EvaluationCreateCallBack(req, res);
    }
    else if (FRegexMatcher(GetEvaluationPattern, UrlToMatch).FindNext())
    {
        EvaluationGetCallBack(req, res);
    }
    else if (FRegexMatcher(UpdateEvaluationPattern, UrlToMatch).FindNext())
    {
        EvaluationUpdateCallBack(req, res);
    }
}

void UCACEvaluationAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    FString ErrorMessage = TEXT("알 수 없는 오류가 발생했습니다.");

    if (res->GetResponseCode() == 400 || res->GetResponseCode() == 401 || res->GetResponseCode() == 404)
    {
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(res->GetContentAsString());
        if (FJsonSerializer::Deserialize(Reader, JsonObject))
        {
            ErrorMessage = JsonObject->GetStringField(TEXT("message"));
        }
    }

    FRegexPattern CreateEvaluationPattern(TEXT(R"(POST\s+/api/evaluation$)"));
    FRegexPattern GetEvaluationPattern(TEXT(R"(GET\s+/api/evaluation/(\d+)/([^/]+)$)"));
    FRegexPattern UpdateEvaluationPattern(TEXT(R"(PATCH\s+/api/evaluation$)"));

    if (FRegexMatcher(CreateEvaluationPattern, UrlToMatch).FindNext())
    {
        OnFailEvaluationCreateCallBack(ErrorMessage);
    }
    else if (FRegexMatcher(GetEvaluationPattern, UrlToMatch).FindNext())
    {
        OnFailEvaluationGetCallBack(ErrorMessage);
    }
    else if (FRegexMatcher(UpdateEvaluationPattern, UrlToMatch).FindNext())
    {
        OnFailEvaluationUpdateCallBack(ErrorMessage);
    }
}

void UCACEvaluationAPI::EvaluationCreateCall(const FEvaluationCreateRequest& Request)
{
    this->API = TEXT("api/evaluation");
    HttpPostCall<FEvaluationCreateRequest>(Request);
}

void UCACEvaluationAPI::EvaluationCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FEvaluationResponse ParsedResponse = JsonPerse<FEvaluationResponse>(JsonString);

    OnEvaluationCreateCallBack(ParsedResponse.data);
}

void UCACEvaluationAPI::EvaluationGetCall(const FString& UserId, const FString& categoryEvaluation)
{
    this->API = FString::Printf(TEXT("api/evaluation/%s/%s"), *UserId, *categoryEvaluation);
    HttpGetCall();
}

void UCACEvaluationAPI::EvaluationGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FEvaluationListResponse ParsedResponse = JsonPerse<FEvaluationListResponse>(JsonString);
    
    OnEvaluationGetCallBack(ParsedResponse.data);
}

void UCACEvaluationAPI::EvaluationUpdateCall(const FEvaluation& Evaluation)
{
    this->API = TEXT("api/evaluation");
    HttpPatchCall<FEvaluation>(Evaluation);
}

void UCACEvaluationAPI::EvaluationUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FEvaluationResponse ParsedResponse = JsonPerse<FEvaluationResponse>(JsonString);

    OnEvaluationUpdateCallBack(ParsedResponse.data);
}