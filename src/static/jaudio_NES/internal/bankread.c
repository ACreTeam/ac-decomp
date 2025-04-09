#include "jaudio_NES/audiostruct.h"

#include "jaudio_NES/connect.h"

static void PTconvert(void** s, u32 ramaddr) {
    u32 ofs = (u32)*s;

    if (ofs >= ramaddr || ofs == 0) {
        return;
    }

    *s = (void*)(ofs + ramaddr);
}

// @nonmatching - regswaps (need to make structs for these)
static Bank* Bank_Test(u8* data) {
    InstBank* ibnk = (InstBank*)data;
    u32 ramaddr = (u32)data;
    Bank* bank = &ibnk->bank;
    u32 i;
    u32 j;
    void** unk_pp;
    u32 k;
    void* unk;
    void** inst_p;
    void* inst;

    if (bank->magic != 'BANK') {
        return NULL;
    }

    for (i = 0; i < ARRAY_COUNT(bank->part0); i++) {
        inst_p = (void**)&bank->part0[i];
        PTconvert(inst_p, ramaddr);

        inst = *inst_p;
        if (inst != NULL) {
            for (j = 0; j < 2; j++) {
                unk_pp = (void**)((u32)inst + j * 4 + 0x10);
                PTconvert((void**)(unk_pp), ramaddr);
                PTconvert((void**)((u32)inst + j * 4 + 0x18), ramaddr);
                PTconvert((void**)((u32)inst + j * 4 + 0x20), ramaddr);
                
                if (*unk_pp != NULL) {
                    PTconvert((void**)((u32)*unk_pp + 0x08), ramaddr);
                    PTconvert((void**)((u32)*unk_pp + 0x0C), ramaddr);
                }
            }

            for (j = 0; j < *((u32*)inst + 0x28); j++) {
                unk_pp = (void**)((u32)inst + j * 4 + 0x2C);
                
                PTconvert(unk_pp, ramaddr);
                for (k = 0; k < *(u32*)((u32)*unk_pp + 4); k++) {
                    PTconvert((void**)((u32)*unk_pp + k * 4 + 8), ramaddr);
                }
            }
        }
    }

    for (i = 0; i < ARRAY_COUNT(bank->part1); i++) {
        inst_p = (void**)&bank->part1[i];

        PTconvert(inst_p, ramaddr);
        inst = *inst_p;

        if (inst != NULL) {
            for (j = 0; j < *((u32*)inst + 0x08); j++) {
                void** unk = (void**)((u32)inst + j * 4 + 0x0C);
                
                PTconvert(unk, ramaddr);
            }
        }
    }

    for (i = 0; i < ARRAY_COUNT(bank->part2); i++) {
        inst_p = (void**)&bank->part2[i];
        inst;

        PTconvert(inst_p, ramaddr);

        inst = *inst_p;
        if (inst != NULL) {
            for (j = 0; j < 128; j++) {
                unk_pp = (void**)((u32)inst + j * 4 + 0x88);

                PTconvert(unk_pp, ramaddr);

                unk = *unk_pp;
                if (unk != NULL) {
                    PTconvert((void**)((u32)unk + 0x08), ramaddr);
                    PTconvert((void**)((u32)unk + 0x0C), ramaddr);

                    for (k = 0; k < *(u32*)((u32)unk + 0x10); k++) {
                        PTconvert((void**)((u32)unk + k * 4 + 0x14), ramaddr);
                    }
                }
            }
        }
    }

    return bank;
}

static Bank* bankp[256];

static BOOL __Bank_Regist_Inner(u8* bank, u32 pid, u32 vid) {
    Jac_BnkConnectTableSet(vid, pid);
    bankp[pid] = Bank_Test(bank);

    if (bankp[pid] != NULL) {
        return TRUE;
    }

    return FALSE;
}

BOOL Bank_Regist(void* bank, u32 pid) {
    InstBank* ibnk = (InstBank*)bank;

    return __Bank_Regist_Inner((u8*)bank, pid, ibnk->vid);
}

void Bank_Init(void) {
    int i;

    for (i = 0; i < ARRAY_COUNT(bankp); i++) {
        bankp[i] = NULL;
    }
}

Bank* Bank_Get(u32 pid) {
    if (pid >= ARRAY_COUNT(bankp)) {
        return NULL;
    }

    return bankp[pid];
}
