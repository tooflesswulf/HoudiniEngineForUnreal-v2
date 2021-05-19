// copyright bla bla bla

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HoudiniAssetActor.h"
#include "HoudiniBlueprintFunctions.generated.h"


/**
 * 
 */
UCLASS()
class HOUDINIENGINERUNTIME_API UHoudiniBlueprintFunctions : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    static int GetHInt(AHoudiniAssetActor* HoudiniAssetActor, const FString& name);
    static void SetHInt(AHoudiniAssetActor* HoudiniAssetActor, const FString& name, int val);
    static bool GetHBool(AHoudiniAssetActor* HoudiniAssetActor, const FString& name);
    static void SetHBool(AHoudiniAssetActor* HoudiniAssetActor, const FString& name, bool state);
    static float GetHFloat(AHoudiniAssetActor* HoudiniAssetActor, const FString& name);
    static void SetHFloat(AHoudiniAssetActor* HoudiniAssetActor, const FString& name, float val);
    static void GetHVector(AHoudiniAssetActor* HoudiniAssetActor, const FString& name, FVector& ret);
    static void SetHVector(AHoudiniAssetActor* HoudiniAssetActor, const FString& name, const FVector& vec);
    static void GetHQuat(AHoudiniAssetActor* HoudiniAssetActor, const FString& name, FQuat& ret);
    static void SetHQuat(AHoudiniAssetActor* HoudiniAssetActor, const FString& name, const FQuat& ret);

    // Getters/Accessors
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static int GetHAssetFrame(AHoudiniAssetActor* HoudiniAssetActor) { return GetHInt(HoudiniAssetActor, "frame"); }

    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static bool GetHAssetExtrToggle(AHoudiniAssetActor* HoudiniAssetActor) { return GetHBool(HoudiniAssetActor, "extrude"); }
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static float GetHAssetExtrTemp(AHoudiniAssetActor* HoudiniAssetActor) { return GetHFloat(HoudiniAssetActor, "extr_temp"); }
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static float GetHAssetExtrVel(AHoudiniAssetActor* HoudiniAssetActor) { return GetHFloat(HoudiniAssetActor, "extr_vel"); }

    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
    static void GetHAssetExtrPos(AHoudiniAssetActor* HoudiniAssetActor, FVector& ret) { return GetHVector(HoudiniAssetActor, "extr_pos", ret); }
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
    static void GetHAssetExtrRot(AHoudiniAssetActor* HoudiniAssetActor, FQuat& ret) { return GetHQuat(HoudiniAssetActor, "extr_rot", ret); }
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
    static void GetHAssetExtrTransform(AHoudiniAssetActor* HoudiniAssetActor, FTransform& ret);

    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static bool GetHAssetRemoverToggle(AHoudiniAssetActor* HoudiniAssetActor) { return GetHBool(HoudiniAssetActor, "remove"); }
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
    static void GetHAssetRemoverPos(AHoudiniAssetActor* HoudiniAssetActor, FVector& ret) { return GetHVector(HoudiniAssetActor, "remr_pos", ret); }
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
    static void GetHAssetRemoverRot(AHoudiniAssetActor* HoudiniAssetActor, FQuat& ret) { return GetHQuat(HoudiniAssetActor, "remr_rot", ret); }
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
    static void GetHAssetRemoverTransform(AHoudiniAssetActor* HoudiniAssetActor, FTransform& ret);


    // Mutators - prefer using setters.
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
    static void HAssetAdvanceFrame(AHoudiniAssetActor* HoudiniAssetActor, int num_frames);
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetToggleExtrude(AHoudiniAssetActor* HoudiniAssetActor);
    // UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	// static void HAssetChangePos(AHoudiniAssetActor* HoudiniAssetActor, float dx, float dy, float dz);

    // Setters
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetSetFrame(AHoudiniAssetActor* HoudiniAssetActor, int frame) { SetHInt(HoudiniAssetActor, "frame", frame); }

    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetSetExtrude(AHoudiniAssetActor* HoudiniAssetActor, bool state) { SetHBool(HoudiniAssetActor, "extrude", state); }
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetSetExtrTemp(AHoudiniAssetActor* HoudiniAssetActor, float temp) { SetHFloat(HoudiniAssetActor, "extr_temp", temp); }
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetSetExtrVel(AHoudiniAssetActor* HoudiniAssetActor, float vel) { SetHFloat(HoudiniAssetActor, "extr_vel", vel); }

    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetSetExtrPos(AHoudiniAssetActor* HoudiniAssetActor, const FVector& pos) { SetHVector(HoudiniAssetActor, "extr_pos", pos); }
	UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetSetExtrRot(AHoudiniAssetActor* HoudiniAssetActor, const FQuat& quat) { SetHQuat(HoudiniAssetActor, "extr_rot", quat); }
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetSetExtrTransform(AHoudiniAssetActor* HoudiniAssetActor, const FTransform& trans);

    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetSetRemove(AHoudiniAssetActor* HoudiniAssetActor, bool state) { SetHBool(HoudiniAssetActor, "remove", state); }
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetSetRemoverPos(AHoudiniAssetActor* HoudiniAssetActor, const FVector& pos) { SetHVector(HoudiniAssetActor, "remr_pos", pos); }
	UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetSetRemoverRot(AHoudiniAssetActor* HoudiniAssetActor, const FQuat& quat) { SetHQuat(HoudiniAssetActor, "remr_rot", quat); }
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetSetRemoverTransform(AHoudiniAssetActor* HoudiniAssetActor, const FTransform& trans);

    // HAssetCook needs to be called to ask Houdini to cook the asset.
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
    static void HAssetCook(AHoudiniAssetActor* HoudiniAssetActor);
};
