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


int UHoudiniBlueprintFunctions::GetHAssetFrame(AHoudiniAssetActor* HoudiniAssetActor)
{
    if (HoudiniAssetActor == nullptr) return -1;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();
    if ( auto* parm = HAC->FindParameterByName("frame") )
        if ( auto* ParmInt = Cast<UHoudiniParameterInt>(parm) )
            return ROpt(ParmInt->GetValue(0), -1);
    return -1;
}

bool UHoudiniBlueprintFunctions::GetHAssetToggle(AHoudiniAssetActor* HoudiniAssetActor)
{
    if (HoudiniAssetActor == nullptr) return false;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();
    if ( auto* parm = HAC->FindParameterByName("extrude") )
        if ( auto* ParmToggle = Cast<UHoudiniParameterToggle>(parm) )
            return ParmToggle->GetValueAt(0);
    return false;
}

float UHoudiniBlueprintFunctions::GetHAssetExtrTemp(AHoudiniAssetActor* HoudiniAssetActor)
{
    if (HoudiniAssetActor == nullptr) return 0;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();
    if ( auto* parm = HAC->FindParameterByName("extr_temp") )
        if ( auto* ParmFloat = Cast<UHoudiniParameterFloat>(parm) )
            return ROpt(ParmFloat->GetValue(0), 0.f);
    return 0;
}

float UHoudiniBlueprintFunctions::GetHAssetExtrVel(AHoudiniAssetActor* HoudiniAssetActor)
{
    if (HoudiniAssetActor == nullptr) return 0;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();
    if ( auto* parm = HAC->FindParameterByName("extr_vel") )
        if ( auto* ParmFloat = Cast<UHoudiniParameterFloat>(parm) )
            return ROpt(ParmFloat->GetValue(0), 0.f);
    return 0;
}

void UHoudiniBlueprintFunctions::GetHAssetPos(AHoudiniAssetActor* HoudiniAssetActor, FVector& ret)
{
    if (HoudiniAssetActor == nullptr) return;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();
    if ( auto* parm = HAC->FindParameterByName("extr_pos") )
        if ( auto* ParmFloat = Cast<UHoudiniParameterFloat>(parm) )
        {
            ret.X = ROpt(ParmFloat->GetValue(0), 0.f);
            ret.Y = ROpt(ParmFloat->GetValue(2), 0.f);
            ret.Z = ROpt(ParmFloat->GetValue(1), 0.f);
        }
}

void UHoudiniBlueprintFunctions::GetHAssetRot(AHoudiniAssetActor* HoudiniAssetActor, FQuat& ret)
{
    if (HoudiniAssetActor == nullptr) return;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();
    if ( auto* parm = HAC->FindParameterByName("extr_rot") )
        if ( auto* ParmFloat = Cast<UHoudiniParameterFloat>(parm) )
        {
            FVector v(ROpt(ParmFloat->GetValue(0), 0.f),
                      ROpt(ParmFloat->GetValue(2), 0.f),
                      ROpt(ParmFloat->GetValue(1), 0.f));
            ret = FQuat::MakeFromEuler(v);
        }
}

void UHoudiniBlueprintFunctions::GetHAssetTransform(AHoudiniAssetActor* HoudiniAssetActor, FTransform& ret)
{
    FVector v;
    GetHAssetPos(HoudiniAssetActor, v);
    FQuat q;
    GetHAssetRot(HoudiniAssetActor, q);

    ret.SetTranslation(v);
    ret.SetRotation(q);
}


void UHoudiniBlueprintFunctions::HAssetAdvanceFrame(AHoudiniAssetActor* HoudiniAssetActor, int num_frames)
{
    if (HoudiniAssetActor == nullptr) return;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();
    if ( auto* parm = HAC->FindParameterByName("frame") )
        if ( auto* ParmInt = Cast<UHoudiniParameterInt>(parm) )
        {
            auto frame = ParmInt->GetValue(0);
            if (!frame) return;
            HOUDINI_LOG_MESSAGE(TEXT("Sim frame number %d -> %d"), *frame, *frame + num_frames);
            ParmInt->SetValueAt(*frame + num_frames, 0);
            MarkChangedNoUpdate(ParmInt);
        }
}

void UHoudiniBlueprintFunctions::HAssetToggleExtrude(AHoudiniAssetActor* HoudiniAssetActor)
{
    if (HoudiniAssetActor == nullptr) return;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();
    if ( auto* parm = HAC->FindParameterByName("extrude") )
    {
        if ( auto* ParmToggle = Cast<UHoudiniParameterToggle>(parm) )
        {
            bool state = ParmToggle->GetValueAt(0);
            ParmToggle->SetValueAt(!state, 0);
            MarkChangedNoUpdate(ParmToggle);
        }
    }
}

void UHoudiniBlueprintFunctions::HAssetChangePos(AHoudiniAssetActor* HoudiniAssetActor, float dx, float dy, float dz)
{
    if (HoudiniAssetActor == nullptr) return;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();
    if ( auto* parm = HAC->FindParameterByName("extr_pos") )
        if ( auto* ParmFloat = Cast<UHoudiniParameterFloat>(parm) )
        {
            float x = ROpt(ParmFloat->GetValue(0), 0.f);
            float y = ROpt(ParmFloat->GetValue(2), 0.f);
            float z = ROpt(ParmFloat->GetValue(1), 0.f);

            ParmFloat->SetValueAt(x + dx, 0);
            ParmFloat->SetValueAt(y + dy, 2);
            ParmFloat->SetValueAt(z + dz, 1);
            MarkChangedNoUpdate(ParmFloat);
        }
}

void UHoudiniBlueprintFunctions::HAssetSetFrame(AHoudiniAssetActor* HoudiniAssetActor, int frame)
{
    if (HoudiniAssetActor == nullptr) return;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();
    if ( auto* parm = HAC->FindParameterByName("frame") )
        if ( auto* ParmInt = Cast<UHoudiniParameterInt>(parm) )
        {
            ParmInt->SetValueAt(frame, 0);
            MarkChangedNoUpdate(ParmInt);
        }
}

void UHoudiniBlueprintFunctions::HAssetSetExtrude(AHoudiniAssetActor* HoudiniAssetActor, bool state)
{
    if (HoudiniAssetActor == nullptr) return;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();
    if ( auto* parm = HAC->FindParameterByName("extrude") )
        if ( auto* ParmToggle = Cast<UHoudiniParameterToggle>(parm) )
        {
            ParmToggle->SetValueAt(state, 0);
            MarkChangedNoUpdate(ParmToggle);
        }
}

void UHoudiniBlueprintFunctions::HAssetSetExtrTemp(AHoudiniAssetActor* HoudiniAssetActor, float temp)
{
    if (HoudiniAssetActor == nullptr) return;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();
    if ( auto* parm = HAC->FindParameterByName("extr_temp") )
        if ( auto* ParmFloat = Cast<UHoudiniParameterFloat>(parm) )
        {
            ParmFloat->SetValueAt(temp, 0);
            MarkChangedNoUpdate(ParmFloat);
        }
}

void UHoudiniBlueprintFunctions::HAssetSetExtrVel(AHoudiniAssetActor* HoudiniAssetActor, float vel)
{
    if (HoudiniAssetActor == nullptr) return;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();
    if ( auto* parm = HAC->FindParameterByName("extr_vel") )
        if ( auto* ParmFloat = Cast<UHoudiniParameterFloat>(parm) )
        {
            ParmFloat->SetValueAt(vel, 0);
            MarkChangedNoUpdate(ParmFloat);
        }
}

void UHoudiniBlueprintFunctions::HAssetSetPos(AHoudiniAssetActor* HoudiniAssetActor, const FVector& pos)
{
    if (HoudiniAssetActor == nullptr) return;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();
    if ( auto* parm = HAC->FindParameterByName("extr_pos") )
        if ( auto* ParmFloat = Cast<UHoudiniParameterFloat>(parm) )
        {
            ParmFloat->SetValueAt(pos.X, 0);
            ParmFloat->SetValueAt(pos.Y, 2);
            ParmFloat->SetValueAt(pos.Z, 1);
            MarkChangedNoUpdate(ParmFloat);
        }
}

void UHoudiniBlueprintFunctions::HAssetSetRot(AHoudiniAssetActor* HoudiniAssetActor, const FQuat& quat)
{
    if (HoudiniAssetActor == nullptr) return;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();
    if ( auto* parm = HAC->FindParameterByName("extr_rot") )
        if ( auto* ParmFloat = Cast<UHoudiniParameterFloat>(parm) )
        {
            FVector v = quat.Euler();
            ParmFloat->SetValueAt(v.X, 0);
            ParmFloat->SetValueAt(v.Y, 2);
            ParmFloat->SetValueAt(v.Z, 1);
            MarkChangedNoUpdate(ParmFloat);
        }
}

void UHoudiniBlueprintFunctions::HAssetSetTransform(AHoudiniAssetActor* HoudiniAssetActor, const FTransform& trans)
{
    HAssetSetPos(HoudiniAssetActor, trans.GetTranslation());
    HAssetSetRot(HoudiniAssetActor, trans.GetRotation());
}


void UHoudiniBlueprintFunctions::HAssetCook(AHoudiniAssetActor* HoudiniAssetActor)
{
    if (HoudiniAssetActor == nullptr) return;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();

	for (int32 ParamIdx = 0; ParamIdx < HAC->GetNumParameters(); ParamIdx++)
    {
        auto* Parm = HAC->GetParameterAt(ParamIdx);
        if (Parm->HasChanged()) Parm->SetNeedsToTriggerUpdate(true);
    }

    if (auto* aa = Cast<AHoudiniAssetActor>(HAC->GetOuter()) )
    {
        HOUDINI_LOG_MESSAGE(TEXT("woohoo! :)"));
    }
}
