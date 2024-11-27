// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/UI/API/CWGBaseAPI.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"

void UCWGBaseAPI::SetOAuthToken()
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	if (Subsystem)
	{
		IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
		this->OAuthToken = Identity->GetAuthToken(0);
		UE_LOG(LogTemp, Display, TEXT("token : %s"), *this->OAuthToken);
		//this->OAuthToken = "eyJ0IjoiZXBpY19pZCIsImFsZyI6IlJTMjU2Iiwia2lkIjoiV01TN0Vua0lHcGNIOURHWnN2MldjWTl4c3VGblpDdHhaamo0QWhiLV84RSJ9.eyJzdWIiOiIyN2YyZDkyZTQwMjQ0Yjg4ODNhMTM1NmFlNDQyZGIxNiIsInBmc2lkIjoicC11bXdmM24yc2s2c2xrdnZzMnh1dHp0emoyYjk3ZDQiLCJwbHRmbSI6Im90aGVyIiwiaXNzIjoiaHR0cHM6Ly9hcGkuZXBpY2dhbWVzLmRldi9lcGljL29hdXRoL3YxIiwiZG4iOiJzdV95ZW9uaW0iLCJub25jZSI6Im4tWjNnT3pWUFpCRlRXQmFZN2srZ2JJZEh3WS9zPSIsInBmcGlkIjoiOGRjNDg1YWJjZjExNDIwNThjYTJmM2EyYmFiYzNjMTQiLCJzZWMiOjEsImF1ZCI6Inh5emE3ODkxd1NOTzJFeUJRZXFMYlQ4ZG9ZeDNKM1UwIiwicGZkaWQiOiI5MDc0MGFmN2VhMjY0NzFiYTY1OGY1OGU0NmNkODEwMyIsInQiOiJlcGljX2lkIiwic2NvcGUiOiJiYXNpY19wcm9maWxlIGZyaWVuZHNfbGlzdCBwcmVzZW5jZSIsImFwcGlkIjoiZmdoaTQ1NjcwR0l5ZkI2WEFHRTlzNmJlblR0VU1sV1EiLCJleHAiOjE3MzE0ODIxOTAsImlhdCI6MTczMTQ3NDk5MCwianRpIjoiNmNmODRhZjQwZTAwNGM3NDhhN2QzMDZjMWE0ZTk1NGYifQ.cnoXo9PtZGBj0fjDsirQ7qQ3exG6JiIQNIorLgd5a7BMfvIz0_QnXCEKcOp0jKUqPjK8en3Q1WSiMDvaWbgN1a1pebiiCfU5EgSeZ4OaZDdX7UNIJv7hDrN93GouvXw464VkzcbOwkkF5ZGQTlnFbhkrlO-nnka3ZQ-elZhxDMJ8gOsMFq7LnWyI-VxD9hG_gprMFPSF7aI5EV2emKWLYfhKT0qt6e73pNTHcui-DY4TckiXR-FB5rfW50FBsUyaSV3lsLtdHKkFKEHXLndJshomMpL64iyc5Z5lH6WBCxu76JQ45kOHv1rBtqxUmGvVctEehr6D-Y1lxfKPJbJnWA";
	}
}

bool UCWGBaseAPI::CheckCallBackAPI(FHttpRequestPtr req, FString api)
{
	api = api.TrimChar('/');
	if (!(this->URL + api).Compare(req->GetURL()))
		return true;
	return false;
}

FString UCWGBaseAPI::GetAPIPath(const FString& FullURL)
{
	// Remove base URL to get just the API path
	return FullURL.RightChop(this->URL.Len());
}

void UCWGBaseAPI::HttpCallBack(FHttpRequestPtr req, FHttpResponsePtr res, bool bConnectedSuccessfully)
{
	UE_LOG(LogTemp, Warning, TEXT("HttpCallBack"));
	bHttpWaitResponse = false;
	if (bConnectedSuccessfully && 200 <= res->GetResponseCode() && res->GetResponseCode() < 300)
	{
		OnSuccessAPI(req, res);
	}
	else
	{
		// 실패 했을때
		OnFailAPI(req, res);
	}
}

void UCWGBaseAPI::OnSuccessAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("OnSuccessAPI %s"), *req->GetURL());
}

void UCWGBaseAPI::OnFailAPI(FHttpRequestPtr req, FHttpResponsePtr res)
{
	UE_LOG(LogTemp, Display, TEXT("OnFailAPI %s"), *req->GetURL());
}
