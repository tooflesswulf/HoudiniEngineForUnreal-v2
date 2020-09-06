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

    // Getters/Accessors
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static int GetHAssetFrame(AHoudiniAssetActor* HoudiniAssetActor);

    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static bool GetHAssetToggle(AHoudiniAssetActor* HoudiniAssetActor);
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static float GetHAssetExtrTemp(AHoudiniAssetActor* HoudiniAssetActor);
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static float GetHAssetExtrVel(AHoudiniAssetActor* HoudiniAssetActor);

    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
    static void GetHAssetPos(AHoudiniAssetActor* HoudiniAssetActor, FVector& ret);
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
    static void GetHAssetRot(AHoudiniAssetActor* HoudiniAssetActor, FQuat& ret);
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
    static void GetHAssetTransform(AHoudiniAssetActor* HoudiniAssetActor, FTransform& ret);

    // Mutators - prefer using setters.
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
    static void HAssetAdvanceFrame(AHoudiniAssetActor* HoudiniAssetActor, int num_frames);
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetToggleExtrude(AHoudiniAssetActor* HoudiniAssetActor);
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetChangePos(AHoudiniAssetActor* HoudiniAssetActor, float dx, float dy, float dz);

    // Setters
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetSetFrame(AHoudiniAssetActor* HoudiniAssetActor, int frame);

    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetSetExtrude(AHoudiniAssetActor* HoudiniAssetActor, bool state);
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetSetExtrTemp(AHoudiniAssetActor* HoudiniAssetActor, float temp);
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetSetExtrVel(AHoudiniAssetActor* HoudiniAssetActor, float vel);

    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetSetPos(AHoudiniAssetActor* HoudiniAssetActor, const FVector& pos);
	UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetSetRot(AHoudiniAssetActor* HoudiniAssetActor, const FQuat& quat);
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
	static void HAssetSetTransform(AHoudiniAssetActor* HoudiniAssetActor, const FTransform& trans);

    // HAssetCook needs to be called to ask Houdini to cook the asset.
    UFUNCTION(BlueprintCallable, Category="Houdini FDM nozzle")
    static void HAssetCook(AHoudiniAssetActor* HoudiniAssetActor);
};
