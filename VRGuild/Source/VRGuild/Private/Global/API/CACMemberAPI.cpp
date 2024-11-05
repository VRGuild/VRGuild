#include "Global/API/CACMemberAPI.h"
#include "Global/API/BPL/CBPLMember.h"

UCACMemberAPI::UCACMemberAPI()
{
    PrimaryComponentTick.bCanEverTick = false;
    bWantsInitializeComponent = true;
}

void UCACMemberAPI::BeginPlay()
{
    Super::BeginPlay();
}

void UCACMemberAPI::InitializeComponent()
{
    Super::InitializeComponent();
}

void UCACMemberAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI : %s"), *req->GetURL());

    FRegexPattern GetMemberPattern(TEXT(R"(GET\s+/api/member/(\d+)$)"));
    FRegexPattern AcceptMemberPattern(TEXT(R"(GET\s+/api/member/apply/(\d+)$)"));
    FRegexPattern RejectMemberPattern(TEXT(R"(GET\s+/api/member/except/(\d+)$)"));
    FRegexPattern DeleteMemberPattern(TEXT(R"(DELETE\s+/api/member/delete/(\d+)$)"));

    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());
    UE_LOG(LogTemp, Display, TEXT("URL to match: %s"), *UrlToMatch);

    if (FRegexMatcher(GetMemberPattern, UrlToMatch).FindNext())
    {
        MemberGetCallBack(req, res);
    }
    else if (FRegexMatcher(AcceptMemberPattern, UrlToMatch).FindNext())
    {
        MemberAcceptCallBack(req, res);
    }
    else if (FRegexMatcher(RejectMemberPattern, UrlToMatch).FindNext())
    {
        MemberRejectCallBack(req, res);
    }
    else if (FRegexMatcher(DeleteMemberPattern, UrlToMatch).FindNext())
    {
        MemberDeleteCallBack(req, res);
    }
}

void UCACMemberAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString UrlToMatch = req->GetVerb() + TEXT(" /") + GetAPIPath(req->GetURL());

    FRegexPattern GetMemberPattern(TEXT(R"(GET\s+/api/member/(\d+)$)"));
    FRegexPattern AcceptMemberPattern(TEXT(R"(GET\s+/api/member/apply/(\d+)$)"));
    FRegexPattern RejectMemberPattern(TEXT(R"(GET\s+/api/member/except/(\d+)$)"));
    FRegexPattern DeleteMemberPattern(TEXT(R"(DELETE\s+/api/member/delete/(\d+)$)"));

    if (FRegexMatcher(GetMemberPattern, UrlToMatch).FindNext())
    {
        OnFailMemberGetCallBack();
    }
    else if (FRegexMatcher(AcceptMemberPattern, UrlToMatch).FindNext())
    {
        OnFailMemberAcceptCallBack();
    }
    else if (FRegexMatcher(RejectMemberPattern, UrlToMatch).FindNext())
    {
        OnFailMemberRejectCallBack();
    }
    else if (FRegexMatcher(DeleteMemberPattern, UrlToMatch).FindNext())
    {
        FString ErrorMessage = TEXT("알 수 없는 오류가 발생했습니다.");
        if (res->GetResponseCode() == 400)
        {
            FString JsonString = res->GetContentAsString();
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
            if (FJsonSerializer::Deserialize(Reader, JsonObject))
            {
                ErrorMessage = JsonObject->GetStringField(TEXT("message"));
            }
        }
        OnFailMemberDeleteCallBack(ErrorMessage);
    }
}

void UCACMemberAPI::MemberGetCall(const FString& MemberId)
{
    this->API = FString::Printf(TEXT("api/member/%s"), *MemberId);
    HttpGetCall();
}

void UCACMemberAPI::MemberGetCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FMemberDetailResponse ParsedResponse = JsonPerse<FMemberDetailResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnMemberGetCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailMemberGetCallBack();
    }
}

void UCACMemberAPI::MemberAcceptCall(const FString& MemberId)
{
    this->API = FString::Printf(TEXT("api/member/apply/%s"), *MemberId);
    HttpGetCall();
}

void UCACMemberAPI::MemberAcceptCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FMemberDetailResponse ParsedResponse = JsonPerse<FMemberDetailResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnMemberAcceptCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailMemberAcceptCallBack();
    }
}

void UCACMemberAPI::MemberRejectCall(const FString& MemberId)
{
    this->API = FString::Printf(TEXT("api/member/except/%s"), *MemberId);
    HttpGetCall();
}

void UCACMemberAPI::MemberRejectCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    FString JsonString = res->GetContentAsString();
    FMemberDetailResponse ParsedResponse = JsonPerse<FMemberDetailResponse>(JsonString);

    if (ParsedResponse.status == TEXT("success"))
    {
        OnMemberRejectCallBack(ParsedResponse.data);
    }
    else
    {
        OnFailMemberRejectCallBack();
    }
}

void UCACMemberAPI::MemberDeleteCall(const FString& MemberId)
{
    this->API = FString::Printf(TEXT("api/member/delete/%s"), *MemberId);
    HttpDeleteCall();
}

void UCACMemberAPI::MemberDeleteCallBack(FHttpRequestPtr req, FHttpResponsePtr res)
{
    if (res->GetResponseCode() == 200)
    {
        OnMemberDeleteCallBack();
    }
    else
    {
        OnFailMemberDeleteCallBack(TEXT("멤버 삭제에 실패했습니다."));
    }
}