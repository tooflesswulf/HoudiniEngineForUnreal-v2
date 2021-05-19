// copyright bla bla bla

#include "HoudiniBlueprintFunctions.h"

#include "HoudiniParameterInt.h"
#include "HoudiniParameterFloat.h"
#include "HoudiniParameterToggle.h"

template <class T>
inline T ROpt(const TOptional<T>& opt, T default0)
{
    if (!opt) return default0;
    return *opt;
}

inline void MarkChangedNoUpdate(UHoudiniParameter* param)
{
    param->MarkChanged(true);
    param->SetNeedsToTriggerUpdate(false);
}

UHoudiniParameter* GetParmByName(AHoudiniAssetActor* HoudiniAssetActor, const FString& name)
{
    if (HoudiniAssetActor == nullptr) return nullptr;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();
    return HAC->FindParameterByName(name);
}

int UHoudiniBlueprintFunctions::GetHInt(AHoudiniAssetActor* HoudiniAssetActor, const FString& name)
{
    if ( auto* parm = GetParmByName(HoudiniAssetActor, name) )
        if ( auto* ParmInt = Cast<UHoudiniParameterInt>(parm) )
            return ROpt(ParmInt->GetValue(0), -1);
    return -1;
}

void UHoudiniBlueprintFunctions::SetHInt(AHoudiniAssetActor* HoudiniAssetActor, const FString& name, int val)
{
    if ( auto* parm = GetParmByName(HoudiniAssetActor, name) )
        if ( auto* ParmInt = Cast<UHoudiniParameterInt>(parm) )
        {
            ParmInt->SetValueAt(val, 0);
            MarkChangedNoUpdate(ParmInt);
        }
}

bool UHoudiniBlueprintFunctions::GetHBool(AHoudiniAssetActor* HoudiniAssetActor, const FString& name)
{
    if ( auto* parm = GetParmByName(HoudiniAssetActor, name) )
        if ( auto* ParmToggle = Cast<UHoudiniParameterToggle>(parm) )
            return ParmToggle->GetValueAt(0);
    return false;
}

void UHoudiniBlueprintFunctions::SetHBool(AHoudiniAssetActor* HoudiniAssetActor, const FString& name, bool state)
{
    if ( auto* parm = GetParmByName(HoudiniAssetActor, name) )
        if ( auto* ParmToggle = Cast<UHoudiniParameterToggle>(parm) )
        {
            ParmToggle->SetValueAt(state, 0);
            MarkChangedNoUpdate(ParmToggle);
        }
}

void UHoudiniBlueprintFunctions::ToggleHBool(AHoudiniAssetActor* HoudiniAssetActor, const FString& name)
{
    if ( auto* parm = GetParmByName(HoudiniAssetActor, name) )
        if ( auto* ParmToggle = Cast<UHoudiniParameterToggle>(parm) )
        {
            bool state = ParmToggle->GetValueAt(0);
            ParmToggle->SetValueAt(!state, 0);
            MarkChangedNoUpdate(ParmToggle);
        }
}

float UHoudiniBlueprintFunctions::GetHFloat(AHoudiniAssetActor* HoudiniAssetActor, const FString& name)
{
    if ( auto* parm = GetParmByName(HoudiniAssetActor, name) )
        if ( auto* ParmFloat = Cast<UHoudiniParameterFloat>(parm) )
            return ROpt(ParmFloat->GetValue(0), 0.f);
    return 0.f;
}

void UHoudiniBlueprintFunctions::SetHFloat(AHoudiniAssetActor* HoudiniAssetActor, const FString& name, float val)
{
    if ( auto* parm = GetParmByName(HoudiniAssetActor, name) )
        if ( auto* ParmFloat = Cast<UHoudiniParameterFloat>(parm) )
        {
            ParmFloat->SetValueAt(val, 0);
            MarkChangedNoUpdate(ParmFloat);
        }
}

void UHoudiniBlueprintFunctions::GetHVector(AHoudiniAssetActor* HoudiniAssetActor, const FString& name, FVector& ret)
{
    if ( auto* parm = GetParmByName(HoudiniAssetActor, name) )
        if ( auto* ParmFloat = Cast<UHoudiniParameterFloat>(parm) )
        {
            ret.X = ROpt(ParmFloat->GetValue(0), 0.f);
            ret.Y = ROpt(ParmFloat->GetValue(2), 0.f);
            ret.Z = ROpt(ParmFloat->GetValue(1), 0.f);
        }
}

void UHoudiniBlueprintFunctions::SetHVector(AHoudiniAssetActor* HoudiniAssetActor, const FString& name, const FVector& vec)
{
    if ( auto* parm = GetParmByName(HoudiniAssetActor, name) )
        if ( auto* ParmFloat = Cast<UHoudiniParameterFloat>(parm) )
        {
            ParmFloat->SetValueAt(vec.X, 0);
            ParmFloat->SetValueAt(vec.Y, 2);
            ParmFloat->SetValueAt(vec.Z, 1);
            MarkChangedNoUpdate(ParmFloat);
        }
}

void UHoudiniBlueprintFunctions::GetHQuat(AHoudiniAssetActor* HoudiniAssetActor, const FString& name, FQuat& ret)
{
    if ( auto* parm = GetParmByName(HoudiniAssetActor, name) )
        if ( auto* ParmFloat = Cast<UHoudiniParameterFloat>(parm) )
        {
            FVector v(ROpt(ParmFloat->GetValue(0), 0.f),
                      ROpt(ParmFloat->GetValue(2), 0.f),
                      ROpt(ParmFloat->GetValue(1), 0.f));
            ret = FQuat::MakeFromEuler(v);
        }
}

void UHoudiniBlueprintFunctions::SetHQuat(AHoudiniAssetActor* HoudiniAssetActor, const FString& name, const FQuat& quat)
{
    if ( auto* parm = GetParmByName(HoudiniAssetActor, name) )
        if ( auto* ParmFloat = Cast<UHoudiniParameterFloat>(parm) )
        {
            FVector v = quat.Euler();
            ParmFloat->SetValueAt(v.X, 0);
            ParmFloat->SetValueAt(v.Y, 2);
            ParmFloat->SetValueAt(v.Z, 1);
            MarkChangedNoUpdate(ParmFloat);
        }
}

void UHoudiniBlueprintFunctions::HAssetGetExtrTransform(AHoudiniAssetActor* HoudiniAssetActor, FTransform& ret)
{
    FVector v;
    FQuat q;
    HAssetGetExtrPos(HoudiniAssetActor, v);
    HAssetGetExtrRot(HoudiniAssetActor, q);

    ret.SetTranslation(v);
    ret.SetRotation(q);
}

void UHoudiniBlueprintFunctions::HAssetGetRemoverTransform(AHoudiniAssetActor* HoudiniAssetActor, FTransform& ret)
{
    FVector v;
    FQuat q;
    HAssetGetRemoverPos(HoudiniAssetActor, v);
    HAssetGetRemoverRot(HoudiniAssetActor, q);

    ret.SetTranslation(v);
    ret.SetRotation(q);
}


void UHoudiniBlueprintFunctions::HAssetAdvanceFrame(AHoudiniAssetActor* HoudiniAssetActor, int num_frames)
{
    if ( auto* parm = GetParmByName(HoudiniAssetActor, "frame") )
        if ( auto* ParmInt = Cast<UHoudiniParameterInt>(parm) )
        {
            auto frame = ParmInt->GetValue(0);
            if (!frame) return;
            HOUDINI_LOG_MESSAGE(TEXT("Sim frame number %d -> %d"), *frame, *frame + num_frames);
            ParmInt->SetValueAt(*frame + num_frames, 0);
            MarkChangedNoUpdate(ParmInt);
        }
}

// void UHoudiniBlueprintFunctions::HAssetChangePos(AHoudiniAssetActor* HoudiniAssetActor, float dx, float dy, float dz)
// {
//     if ( auto* parm = GetParmByName(HoudiniAssetActor, "extr_pos") )
//         if ( auto* ParmFloat = Cast<UHoudiniParameterFloat>(parm) )
//         {
//             float x = ROpt(ParmFloat->GetValue(0), 0.f);
//             float y = ROpt(ParmFloat->GetValue(2), 0.f);
//             float z = ROpt(ParmFloat->GetValue(1), 0.f);

//             ParmFloat->SetValueAt(x + dx, 0);
//             ParmFloat->SetValueAt(y + dy, 2);
//             ParmFloat->SetValueAt(z + dz, 1);
//             MarkChangedNoUpdate(ParmFloat);
//         }
// }

void UHoudiniBlueprintFunctions::HAssetSetExtrTransform(AHoudiniAssetActor* HoudiniAssetActor, const FTransform& trans)
{
    HAssetSetExtrPos(HoudiniAssetActor, trans.GetTranslation());
    HAssetSetExtrRot(HoudiniAssetActor, trans.GetRotation());
}

void UHoudiniBlueprintFunctions::HAssetSetRemoverTransform(AHoudiniAssetActor* HoudiniAssetActor, const FTransform& trans)
{
    HAssetSetRemoverPos(HoudiniAssetActor, trans.GetTranslation());
    HAssetSetRemoverRot(HoudiniAssetActor, trans.GetRotation());
}


void UHoudiniBlueprintFunctions::HAssetCook(AHoudiniAssetActor* HoudiniAssetActor)
{
    if (HoudiniAssetActor == nullptr) return;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();

	for (int32 ParamIdx = 0; ParamIdx < HAC->GetNumParameters(); ParamIdx++)
    {
        auto* Parm = HAC->GetParameterAt(ParamIdx);
        if (Parm->HasChanged()) {
            Parm->SetNeedsToTriggerUpdate(true);
            if (Parm->GetParameterName() == "frame") {
                HOUDINI_LOG_MESSAGE(TEXT("Set true! :)"));
                HoudiniAssetActor->frameChanged = true;
            }
        }
    }

    // if (auto* aa = Cast<AHoudiniAssetActor>(HAC->GetOuter()) )
    // {
    //     HOUDINI_LOG_MESSAGE(TEXT("woohoo! :)"));
    // }
}
