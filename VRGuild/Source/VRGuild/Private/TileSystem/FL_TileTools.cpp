// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSystem/FL_TileTools.h"

FVector UFL_TileTools::SnapGridVector(FVector vector, float gridSize)
{
	FVector gridVector = FVector(
		FMath::GridSnap(vector.X, gridSize),
		FMath::GridSnap(vector.Y, gridSize),
		FMath::GridSnap(vector.Z, gridSize)
	);
	return gridVector;
}

AActor* UFL_TileTools::SpawnTileObject(UWorld* World, const FTileObjectInfo& ObjectInfo)
{
    // 필수 검증
    if (!World || ObjectInfo.objectClassName.IsEmpty() || ObjectInfo.objectName.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid parameters: World: %d, ClassName: %s, Name: %s"),
            !!World, *ObjectInfo.objectClassName, *ObjectInfo.objectName);
        return nullptr;
    }

    // 클래스 로드 및 검증 
    // LoadedClass = FindObject<UClass>(ANY_PACKAGE, *ObjectInfo.objectClassName);
    UClass* LoadedClass = Cast<UClass>(StaticFindObject(UClass::StaticClass(), nullptr, *ObjectInfo.objectClassName, false));
    if (!LoadedClass)
    {
        LoadedClass = StaticLoadClass(AActor::StaticClass(), nullptr, *ObjectInfo.objectClassName);
    }
    if (!LoadedClass || !LoadedClass->IsChildOf(AActor::StaticClass()))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load valid actor class: %s"), *ObjectInfo.objectClassName);
        return nullptr;
    }

    // Transform 검증
    FTransform SpawnTransform(ObjectInfo.rotator, ObjectInfo.postition);
    if (!SpawnTransform.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid transform, using default"));
        SpawnTransform = FTransform::Identity;
    }

    // 스폰 파라미터 설정
    FActorSpawnParameters SpawnParams;
    SpawnParams.Name = FName(*ObjectInfo.objectName);
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    SpawnParams.ObjectFlags = RF_Transient | RF_DuplicateTransient;

    // 액터 스폰 시도
    AActor* SpawnedActor = nullptr;

    SpawnedActor = World->SpawnActor<AActor>(LoadedClass, SpawnTransform);
    if (SpawnedActor)
    {
        SpawnedActor->SetReplicates(true);
        SpawnedActor->SetReplicateMovement(true);

        if (UStaticMeshComponent* MeshComp = SpawnedActor->FindComponentByClass<UStaticMeshComponent>())
        {
            MeshComp->SetIsReplicated(true);
            MeshComp->SetVisibility(true);
        }

        //SpawnedActor->SetActorLabel(ObjectInfo.objectName);
        SpawnedActor->Tags.Add(FName(*FString::Printf(TEXT("ObjectId_%lld"), ObjectInfo.objectId)));
        UE_LOG(LogTemp, Display, TEXT("Successfully spawned actor: %s"), *SpawnedActor->GetName());
    }

    /*try
    {
       
    }
    catch (const std::exception& e)
    {
        UE_LOG(LogTemp, Error, TEXT("Spawn failed with exception: %s"), UTF8_TO_TCHAR(e.what()));
    }*/

    return SpawnedActor;
}

TArray<AActor*> UFL_TileTools::SpawnTileObjects(UWorld* World, const TArray<FTileObjectInfo>& ObjectInfoList)
{
    TArray<AActor*> SpawnedActors;

    for (const FTileObjectInfo& ObjectInfo : ObjectInfoList)
    {
        if (AActor* SpawnedActor = SpawnTileObject(World, ObjectInfo))
        {
            SpawnedActors.Add(SpawnedActor);
        }
    }

    return SpawnedActors;
}

FTileObjectInfo UFL_TileTools::CreateTileObjectInfo(AActor* Actor)
{
    FTileObjectInfo ObjectInfo;

    if (Actor)
    {
        // 기본 정보 설정
        ObjectInfo.objectName = Actor->GetName();
        ObjectInfo.objectClassName = Actor->GetClass()->GetPathName();
        ObjectInfo.postition = Actor->GetActorLocation();
        ObjectInfo.rotator = Actor->GetActorRotation();

        // objectId 찾기 (만약 태그로 저장되어 있다면)
        //for (const FName& Tag : Actor->Tags)
        //{
        //    FString TagString = Tag.ToString();
        //    if (TagString.StartsWith(TEXT("ObjectId_")))
        //    {
        //        FString IdString = TagString.RightChop(9); // "ObjectId_" 이후의 문자열
        //        ObjectInfo.objectId = FCString::Atoi64(*IdString);
        //        break;
        //    }
        //}
    }

    return ObjectInfo;
}

