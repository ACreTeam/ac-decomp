#ifndef M_VIBCTL_H
#define M_VIBCTL_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mVibctl_FLAG_FORCE_STOP_NONE 0
#define mVibctl_FLAG_FORCE_STOP0 (1 << 0) // 1
#define mVibctl_FLAG_FORCE_STOP1 (1 << 1) // 2
#define mVibctl_FLAG_FORCE_STOP2 (1 << 2) // 4
#define mVibctl_FLAG_FORCE_STOP3 (1 << 3) // 8
#define mVibctl_FLAG_FORCE_STOP_ALL \
    (mVibctl_FLAG_FORCE_STOP0 | mVibctl_FLAG_FORCE_STOP1 | mVibctl_FLAG_FORCE_STOP2 | mVibctl_FLAG_FORCE_STOP3) // 15

enum {
    mVibctl_ELEM_ENTRY_ATTACK,  // fade-in program
    mVibctl_ELEM_ENTRY_SUSTAIN, // sustain program
    mVibctl_ELEM_ENTRY_RELEASE, // fade-out program
    mVibctl_ELEM_ENTRY_END,     // program has finished

    mVibctl_ELEM_ENTRY_NUM = mVibctl_ELEM_ENTRY_END
};

enum {
    mVibctl_VIB_PROG_NON, // rumble config attack, shake tree attack
    mVibctl_VIB_PROG_FFF, // fish touch bobber, fishing rod cast, rumble config sustain, Mouth of Truth furniture
                          // interaction attack & sustain, shovel hits soft object, net swing, axe cut attack & release,
                          // trip attack, pick weed sustain & release
    mVibctl_VIB_PROG_F,   // unused?
    mVibctl_VIB_PROG_MF,  // unused?
    mVibctl_VIB_PROG_MP,  // unused?
    mVibctl_VIB_PROG_P,   // rumble config release, shake tree release
    mVibctl_VIB_PROG_FUNBARI,       // unused?
    mVibctl_VIB_PROG_ANAHORI,       // digging with shovel
    mVibctl_VIB_PROG_ANAUME,        // filling hole with shovel
    mVibctl_VIB_PROG_IMPACT,        // fish bite bobber, shovel hits hard object
    mVibctl_VIB_PROG_KI_GA_TAORERU, // axe cut sustain
    mVibctl_VIB_PROG_KI_WO_YUSURU,  // shake tree sustain
    mVibctl_VIB_PROG_KORONODA,      // trip sustain
    mVibctl_VIB_PROG_SURPRISE,      // Mouth of Truth furniture interaction release
    mVibctl_VIB_PROG_DUMMY_B,       // unused?
    mVibctl_VIB_PROG_SAMPLE,        // unused?

    mVibctl_VIB_PROG_NUM
};

#define mVibctl_ELEM_NUM 4

typedef struct vibration_element_entry_s {
    int type;
    int frames;
    f32 step;
} mVibInfo_elem_entry_c;

typedef struct vibration_element_s {
    mVibInfo_elem_entry_c entries[mVibctl_ELEM_ENTRY_NUM];
    f32 step0;
    f32 step1;
    int now_entry;
    int state_idx;
    f32 frame_intensity;
    int entry_frame;
    f32 now_intensity;
    int command; // for padmgr, PAD_MOTOR_*
} mVibElem_c;

typedef struct vibration_info_s {
    mVibElem_c* target_elem;
    mVibElem_c elements[mVibctl_ELEM_NUM];
    int num_elements;
    int force_stop;
    int last_force_stop;
} mVibInfo_c;

typedef struct vibration_work_data_S {
    const u8* data;
    int count;
} mVibWorkData_c;

extern void mVibctl_ct();
extern void mVibctl_init0();
extern void mVibctl_init();
extern void mVibctl_cleanup();
extern void mVibctl_reset();
extern void mVibctl_entry(int total_frames, int attack_type, int sustain_type, int release_type, int attack_frames,
                          int sustain_frames, int release_frames, f32 step);
extern void mVibctl_simple_entry(int total_frames, int type, int attack_frames, int sustain_frames, int release_frames,
                                 f32 step);
extern void mVibctl_set_force_stop(int force_stop);
extern void mVibctl_clr_force_stop(int force_stop);

#ifdef __cplusplus
}
#endif

#endif
