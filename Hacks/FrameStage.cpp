#include "main.h"

void hkFrameStage(void* thisptr, ClientFrameStage_t curStage) {
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(!local)
        return;
    
    Vector* PointerPunch = nullptr;
    Vector* PointerView = nullptr;
    
    Vector VecPunch, VecView;
    
    if (curStage == ClientFrameStage_t::FRAME_RENDER_START && (pEngine->IsConnected() && pEngine->IsInGame())) {
        if(local->GetLifeState() == LIFE_ALIVE) {
            if(vars.misc.thirdpersonmode) {
                *reinterpret_cast<Vector*>(reinterpret_cast<uintptr_t>(local) + offsets.DT_BasePlayer.deadflag + 0x4) = tpangles;
            }
        }
    }
    
    if(curStage == ClientFrameStage_t::FRAME_RENDER_START && vars.misc.enabled && vars.misc.novisualrecoil) {
        if(local) {
            if(local->GetLifeState() == LIFE_ALIVE) {
                
                PointerPunch = (Vector*)((uintptr_t)local + offsets.DT_BasePlayer.m_aimPunchAngle);
                PointerView = (Vector*)((uintptr_t)local + offsets.DT_BasePlayer.m_viewPunchAngle);
                
                
                VecPunch = *PointerPunch;
                VecView = *PointerView;
                
                PointerPunch->Init();
                PointerView->Init();
            }
        }
    }
   
    clientvmt->GetOriginalMethod<tFrameStage>(36)(thisptr, curStage);
    
    if(curStage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
        for(int i = 1; i < 64; i++) {
            auto* entity = pEntList->GetClientEntity(i);
            
            if(!entity) continue;
            if(entity->GetLifeState() != 0) continue;
            if(entity->GetHealth() < 1) continue;
            if(entity->GetDormant()) continue;
            if(entity == local) continue;
            if(!gCorrections[entity->GetIndex()].resolved) continue;
            
            *(float*)((uintptr_t)entity + offsets.DT_BasePlayer.m_angRotation1) = AAA_Pitch(entity);
            *(float*)((uintptr_t)entity + offsets.DT_BasePlayer.m_angRotation2) = AAA_Yaw(entity);
        }
    }
    
    if(PointerPunch && PointerView) {
        *PointerPunch = VecPunch;
        *PointerView = VecView;
    }
}
