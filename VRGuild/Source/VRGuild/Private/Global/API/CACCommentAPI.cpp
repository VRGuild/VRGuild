#include "Global/API/CACCommentAPI.h"
#include "Global/API/BPL/CBPLComment.h"

UCACCommentAPI::UCACCommentAPI()
{
    PrimaryComponentTick.bCanEverTick = false;
    bWantsInitializeComponent = true;
}

void UCACCommentAPI::BeginPlay()
{
    Super::BeginPlay();
}

void UCACCommentAPI::InitializeComponent()
{
    Super::InitializeComponent();
}

void UCACCommentAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    FRegexPattern CreateCommentPattern(TEXT(R"(POST\s+/api/comment$)"));
    FRegexPattern GetCommentPattern(TEXT(R"(GET\s+/api/comment/(\d+)$)"));
    FRegexPattern UpdateCommentPattern(TEXT(R"(PATCH\s+/api/comment/(\d+)$)"));
    FRegexPattern GetCommentDetailPattern(TEXT(R"(GET\s+/api/comment/detail/(\d+)$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("URL to match: %s"), *UrlToMatch);

    if (FRegexMatcher(CreateCommentPattern, UrlToMatch).FindNext())
    {
        CommentCreateCallBack(req, res);
    }
    else if (FRegexMatcher(GetCommentPattern, UrlToMatch).FindNext())
    {
        CommentGetCallBack(req, res);
    }
    else if (FRegexMatcher(UpdateCommentPattern, UrlToMatch).FindNext())
    {
        CommentUpdateCallBack(req, res);
    }
    else if (FRegexMatcher(GetCommentDetailPattern, UrlToMatch).FindNext())
    {
        CommentDetailGetCallBack(req, res);
    }
}

void UCACCommentAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FRegexPattern CreateCommentPattern(TEXT(R"(POST\s+/api/comment$)"));
    FRegexPattern GetCommentPattern(TEXT(R"(GET\s+/api/comment/(\d+)$)"));
    FRegexPattern UpdateCommentPattern(TEXT(R"(PATCH\s+/api/comment/(\d+)$)"));
    FRegexPattern GetCommentDetailPattern(TEXT(R"(GET\s+/api/comment/detail/(\d+)$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    if (FRegexMatcher(CreateCommentPattern, UrlToMatch).FindNext())
    {
        OnFailCommentCreateCallBack();
    }
    else if (FRegexMatcher(GetCommentPattern, UrlToMatch).FindNext())
    {
        OnFailCommentGetCallBack();
    }
    else if (FRegexMatcher(UpdateCommentPattern, UrlToMatch).FindNext())
    {
        OnFailCommentUpdateCallBack();
    }
    else if (FRegexMatcher(GetCommentDetailPattern, UrlToMatch).FindNext())
    {
        OnFailCommentDetailGetCallBack();
    }
}

void UCACCommentAPI::CommentCreateCall(const FComment& Comment)
{
    this->API = TEXT("api/comment");
    HttpPostCall<FComment>(Comment);
}

void UCACCommentAPI::CommentCreateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FCommentResponse ParsedResponse = JsonPerse<FCommentResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnCommentCreateCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailCommentCreateCallBack();
    }
}

void UCACCommentAPI::CommentGetCall(const FString& CommentId)
{
    this->API = FString::Printf(TEXT("api/comment/%s"), *CommentId);
    HttpGetCall();
}

void UCACCommentAPI::CommentGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FCommentResponse ParsedResponse = JsonPerse<FCommentResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnCommentGetCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailCommentGetCallBack();
    }
}

void UCACCommentAPI::CommentUpdateCall(const FString& CommentId, const FComment& Comment)
{
    this->API = FString::Printf(TEXT("api/comment/%s"), *CommentId);
    HttpPatchCall<FComment>(Comment);
}

void UCACCommentAPI::CommentUpdateCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FCommentResponse ParsedResponse = JsonPerse<FCommentResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnCommentUpdateCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailCommentUpdateCallBack();
    }
}

void UCACCommentAPI::CommentDetailGetCall(const FString& CommentId)
{
    this->API = FString::Printf(TEXT("api/comment/detail/%s"), *CommentId);
    HttpGetCall();
}

void UCACCommentAPI::CommentDetailGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FCommentDetailResponse ParsedResponse = JsonPerse<FCommentDetailResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnCommentDetailGetCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailCommentDetailGetCallBack();
    }
}