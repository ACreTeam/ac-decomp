#ifndef CONNECT_H
#define CONNECT_H

#include "types.h"

typedef struct WaveArchive_ WaveArchive_;
typedef struct WaveArchiveBank_ WaveArchiveBank_;
typedef struct Ctrl_ Ctrl_;
typedef struct CtrlGroup_ CtrlGroup_;

void Jac_SceneClose(WaveArchiveBank_*, CtrlGroup_*, u32, BOOL);
BOOL Jac_SceneSet(WaveArchiveBank_*, CtrlGroup_*, u32, BOOL);
struct WaveID_* GetSoundHandle(CtrlGroup_*, u32);
u16 Jac_WsVirtualToPhysical(u16);
u16 Jac_BnkVirtualToPhysical(u16);
u16 Jac_BnkPhysicalToVirtual(u16);
u16 Jac_WsPhysicalToVirtual(u16);
void Jac_WsConnectTableSet(u32, u32);
void Jac_BnkConnectTableSet(u32, u32);
void Jac_ConnectTableInit();
struct WaveID_* __GetSoundHandle(CtrlGroup_*, u32, u32);

#endif
