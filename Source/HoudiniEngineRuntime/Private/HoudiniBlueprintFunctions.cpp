// copyright bla bla bla

#include "HoudiniBlueprintFunctions.h"

#include "HoudiniParameterInt.h"

void UHoudiniBlueprintFunctions::HAssetAdvanceFrame(AHoudiniAssetActor* HoudiniAssetActor, int num_frames)
{
    if (HoudiniAssetActor == nullptr) return;
    auto* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();
    auto* parm = HAC->FindParameterByName("frame");
    if (parm == nullptr) return;

    if ( auto* ParmInt = Cast<UHoudiniParameterInt>(parm) )
    {
        auto frameOpt = ParmInt->GetValue(0);
        if (!frameOpt.IsSet()) return;
        int frame = frameOpt.GetValue();
        HOUDINI_LOG_MESSAGE(TEXT("Sim frame number %d -> %d"), frame, frame + num_frames);
        ParmInt->SetValueAt(frame + num_frames, 0);
    }
}
