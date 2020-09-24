/*
* Copyright (c) <2018> Side Effects Software Inc.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
* 2. The name of Side Effects Software may not be used to endorse or
*    promote products derived from this software without specific prior
*    written permission.
*
* THIS SOFTWARE IS PROVIDED BY SIDE EFFECTS SOFTWARE "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
* NO EVENT SHALL SIDE EFFECTS SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include "HoudiniAssetComponent.h"

#include "UObject/ObjectMacros.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"

#include "HoudiniAssetActor.generated.h"

class UHoudiniPDGAssetLink;

UCLASS(hidecategories = (Input), ConversionRoot, meta = (ChildCanTick), Blueprintable)
class HOUDINIENGINERUNTIME_API AHoudiniAssetActor : public AActor
{
	GENERATED_UCLASS_BODY()

	// Pointer to the root HoudiniAssetComponent
	UPROPERTY(Category = HoudiniAssetActor, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Mesh,Rendering,Physics,Components|HoudiniEngine")/*, AllowPrivateAccess = "true"*/)
	UHoudiniAssetComponent * HoudiniAssetComponent;

	// Cook finished event declaration
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FCookFinished, AHoudiniAssetActor*, HoudiniAssetActor, bool, fluidSimComplete );
    UPROPERTY(BlueprintAssignable, Category="Houdini FDM nozzle")
    FCookFinished CookFinishEvent;

	bool frameChanged = false;

public:

	// Returns the actor's houdini component.
	UHoudiniAssetComponent* GetHoudiniAssetComponent() const;

	bool IsUsedForPreview() const;
	
	// Gets the Houdini PDG asset link associated with this actor, if it has one.
	UHoudiniPDGAssetLink* GetPDGAssetLink() const { return IsValid(HoudiniAssetComponent) ? HoudiniAssetComponent->GetPDGAssetLink() : nullptr; } 

#if WITH_EDITOR

	// Called after a property has been changed
	// Used to forward property changes to the HAC
	virtual void PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent) override;

	// Used by the "Sync to Content Browser" right-click menu option in the editor.
	virtual bool GetReferencedContentObjects(TArray< UObject * >& Objects) const;

/*
public:

	// Called before editor paste, true allow import
	virtual bool ShouldImport(FString * ActorPropString, bool IsMovingLevel) override;

	// Used by the "Sync to Content Browser" right-click menu option in the editor.
	virtual bool GetReferencedContentObjects(TArray< UObject * >& Objects) const;
*/
#endif
};
