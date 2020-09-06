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

    UFUNCTION(BlueprintCallable, Category="Houdini Functions")
    static void HAssetAdvanceFrame(AHoudiniAssetActor* HoudiniAssetActor, int num_frames);

    // UFUNCTION(BlueprintCallable, Category="Houdini Functions")
    // static void HAssetCook(AHoudiniAssetActor* HoudiniAssetActor);
};
