// CATileFloor.h
#pragma once

#include "CoreMinimal.h"
#include "CATileSpace.h"
#include "CATileFloor.generated.h"

UCLASS()
class VRGUILD_API ACATileFloor : public ACATileSpace
{
    GENERATED_BODY()

public:
    ACATileFloor();

    // Existing components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USceneComponent> BasePivotComp;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> BaseFloorComp;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> NorthWallComp;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> SouthWallComp;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> EastWallComp;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> WestWallComp;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> CeilingComp;

    // Existing mesh lists
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
    TArray<UStaticMesh*> BaseFloorMeshList;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
    TArray<UStaticMesh*> NorthWallMeshList;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
    TArray<UStaticMesh*> SouthWallMeshList;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
    TArray<UStaticMesh*> EastWallMeshList;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
    TArray<UStaticMesh*> WestWallMeshList;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
    TArray<UStaticMesh*> CeilingMeshList;

protected:
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;
    virtual void CreateDefualtSpace() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(ReplicatedUsing = OnRep_WallVisibility)
    uint8 SurfaceVisibilityFlags = 0x3F;

    static constexpr uint8 WALL_NORTH = 1 << 0;
    static constexpr uint8 WALL_SOUTH = 1 << 1;
    static constexpr uint8 WALL_EAST = 1 << 2;
    static constexpr uint8 WALL_WEST = 1 << 3;
    static constexpr uint8 SURFACE_FLOOR = 1 << 4;
    static constexpr uint8 SURFACE_CEILING = 1 << 5;
    
    UFUNCTION()
    void OnRep_WallVisibility();

    UFUNCTION()
    void ApplySurfaceVisibility();

    UFUNCTION(NetMulticast, Reliable)
    void MulticastUpdateSurfaceVisibility(uint8 NewFlags);
    void MulticastUpdateSurfaceVisibility_Implementation(uint8 NewFlags);

public:
    virtual ACATileSpace* Clone() override;
    virtual void AttachSpace(FHitResult HitResult, ACATileSpace* newTileSpace) override;
    virtual void AttachPostision(FVector position, ACATileSpace* newTileSpace) override;
    void UpdateSurfaceVisible();

    virtual void Delete() override;
};