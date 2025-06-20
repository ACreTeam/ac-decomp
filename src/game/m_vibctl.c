#include "m_vibctl.h"

#include "libultra/libultra.h"
#include "padmgr.h"
#include "m_common_data.h"
#include "m_field_info.h"
#include "m_event.h"
#include "dolphin/pad.h"

static const u8 mVW_Non[1] = { PAD_MOTOR_STOP };

static const u8 mVW_FFF[1] = { PAD_MOTOR_RUMBLE };

static const u8 mVW_F[2] = {
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP
};

static const u8 mVW_MF[3] = {
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP
};

static const u8 mVW_MP[4] = {
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP
};

static const u8 mVW_P[5] = {
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP
};

static const u8 mVW_funbari[8] = {
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP_HARD
};

static const u8 mVW_anahori[8] = {
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP
};

static const u8 mVW_anaume[60] = {
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP_HARD
};

static const u8 mVW_impact[9] = {
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP_HARD
};

static const u8 mVW_ki_ga_taoreru[36] = {
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_RUMBLE
};

static const u8 mVW_ki_wo_yusuru[13] = {
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP
};

static const u8 mVW_koronda[14] = {
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP
};

static const u8 mVW_suprise[7] = {
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP
};

static const u8 mVW_dummy_b[1] = { PAD_MOTOR_RUMBLE };

static const u8 mVW_sample[13] = {
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_RUMBLE,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP_HARD,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP,
  PAD_MOTOR_STOP
};

#define VIB_PROG(name) { mVW_##name, ARRAY_SIZE(mVW_##name, u8) }
static const mVibWorkData_c mVW_data[mVibctl_VIB_PROG_NUM] = {
  VIB_PROG(Non),
  VIB_PROG(FFF),
  VIB_PROG(F),
  VIB_PROG(MF),
  VIB_PROG(MP),
  VIB_PROG(P),
  VIB_PROG(funbari),
  VIB_PROG(anahori),
  VIB_PROG(anaume),
  VIB_PROG(impact),
  VIB_PROG(ki_ga_taoreru),
  VIB_PROG(ki_wo_yusuru),
  VIB_PROG(koronda),
  VIB_PROG(suprise),
  VIB_PROG(dummy_b),
  VIB_PROG(sample)
};

static mVibInfo_c mVib_info;

static void mVibElem_move(mVibElem_c* elem) {
  mVibInfo_elem_entry_c* now_entry = elem->entries + elem->now_entry;
  int type = now_entry->type;
  const mVibWorkData_c* work_data = &mVW_data[type];

  elem->entry_frame++;
  elem->frame_intensity = elem->step1 * elem->step0;

  if (elem->now_entry == mVibctl_ELEM_ENTRY_ATTACK) {
    elem->frame_intensity *= (f32)elem->entry_frame * now_entry->step;
  }
  else if (elem->now_entry == mVibctl_ELEM_ENTRY_RELEASE) {
    elem->frame_intensity *= now_entry->step * (now_entry->frames - elem->entry_frame);
  }

  if (work_data->data[elem->state_idx] == PAD_MOTOR_RUMBLE) {
    /* only rumble when our current intensity has reached or surpassed 1.0f */
    elem->now_intensity += elem->frame_intensity;

    if (elem->now_intensity >= 1.0f) {
      elem->command = PAD_MOTOR_RUMBLE;
      elem->now_intensity -= 1.0f;
    }
    else {
      elem->command = PAD_MOTOR_STOP;
    }
  }
  else {
    elem->command = work_data->data[elem->state_idx];
  }

  {
    /* increment current program state index */
    int state_count = work_data->count;
    int now_state = elem->state_idx + 1;
    elem->state_idx = now_state;

    /* check if program state index has rolled over */
    if (now_state >= state_count) {
      elem->state_idx = 0;
    }

    /* check if current stage frames have ended, and if so, advanced to next one */
    if (elem->entry_frame >= now_entry->frames) {
      elem->now_entry++;
      elem->entry_frame = 0;
      elem->state_idx = 0;
    }
  }
}

static void mVibInfo_elem_entry(mVibInfo_c* vib_info, int total_frames, int attack_type, int sustain_type, int release_type, int attack_frames, int sustain_frames, int release_frames, f32 step) {
  if ((attack_frames != 0 || sustain_frames != 0 || release_frames != 0) && (step < 640.0f && vib_info->num_elements < mVibctl_ELEM_NUM)) {
    mVibElem_c* elem = vib_info->elements + vib_info->num_elements;
    bzero(elem, sizeof(mVibElem_c));

    /* set attack phase configuration */
    elem->entries[mVibctl_ELEM_ENTRY_ATTACK].type = attack_type;
    elem->entries[mVibctl_ELEM_ENTRY_ATTACK].frames = attack_frames;
    elem->entries[mVibctl_ELEM_ENTRY_ATTACK].step = (attack_frames > 0) ? (1.0f / (f32)attack_frames) : -1.0f;

    /* set sustain phase configuration */
    elem->entries[mVibctl_ELEM_ENTRY_SUSTAIN].type = sustain_type;
    elem->entries[mVibctl_ELEM_ENTRY_SUSTAIN].frames = sustain_frames;
    elem->entries[mVibctl_ELEM_ENTRY_SUSTAIN].step = (sustain_frames > 0) ? (1.0f / (f32)sustain_frames) : -1.0f;

    /* set release phase configuration */
    elem->entries[mVibctl_ELEM_ENTRY_RELEASE].type = release_type;
    elem->entries[mVibctl_ELEM_ENTRY_RELEASE].frames = release_frames;
    elem->entries[mVibctl_ELEM_ENTRY_RELEASE].step = (release_frames > 0) ? (1.0f / (f32)release_frames) : -1.0f;

    if (attack_frames == 0) {
      if (sustain_frames == 0) {
        elem->now_entry = mVibctl_ELEM_ENTRY_RELEASE;
      }
      else {
        elem->now_entry = mVibctl_ELEM_ENTRY_SUSTAIN;
      }
    }

    elem->step1 = total_frames * 0.01f;

    if (step < 41.0f) {
      elem->step0 = 1.0f;
    }
    else {
      elem->step0 = 1.0f / (step - 40.0f);
    }

    vib_info->num_elements++;
  }
}

static void mVibInfo_elem_delete(mVibInfo_c* vib_info, int elem_no) {
  int i;
  int n_elems = vib_info->num_elements - 1;

  for (i = elem_no; i < n_elems; i++) {
    mVibElem_c* dst_elem = vib_info->elements + (i + 1);
    mVibElem_c* src_elem = vib_info->elements + i;
    bcopy(dst_elem, src_elem, sizeof(mVibElem_c));
  }

  bzero(vib_info->elements + n_elems, sizeof(mVibElem_c));
  vib_info->num_elements--;
}

static void mVibInfo_set_force_stop(mVibInfo_c* vib_info, int force_stop) {
  vib_info->force_stop |= force_stop;
}

static void mVibInfo_clr_force_stop(mVibInfo_c* vib_info, int force_stop) {
  vib_info->force_stop &= ~force_stop;
}

static void mVibInfo_set_target_elem(mVibInfo_c* vib_info) {
  int n_elems = vib_info->num_elements;
  f32 max = -10000.0f;
  mVibElem_c* elem = vib_info->elements;
  mVibElem_c* selected = NULL;
  int i;

  for (i = 0; i < n_elems; i++) {
    if (elem->frame_intensity > max) {
      max = elem->frame_intensity;
      selected = elem;
    }
    elem++;
  }

  vib_info->target_elem = selected;
}

static void mVibInfo_force(mVibInfo_c* vib_info) {
  if (Save_Get(config.vibration_disabled)) {
    mVibInfo_set_force_stop(vib_info, mVibctl_FLAG_FORCE_STOP0);
  }
  else {
    mVibInfo_clr_force_stop(vib_info, mVibctl_FLAG_FORCE_STOP0);
  }

  if (vib_info->force_stop != mVibctl_FLAG_FORCE_STOP_NONE && vib_info->last_force_stop == mVibctl_FLAG_FORCE_STOP_NONE) {
    padmgr_force_stop_ON();
  }
  else if (vib_info->force_stop == mVibctl_FLAG_FORCE_STOP_NONE && vib_info->last_force_stop != mVibctl_FLAG_FORCE_STOP_NONE) {
    padmgr_force_stop_OFF();
  }

  vib_info->last_force_stop = vib_info->force_stop;
}

static void mVibInfo_set_motor(mVibInfo_c* vib_info) {
  if (vib_info->target_elem != NULL) {
    padmgr_RumbleSet(PAD0, vib_info->target_elem->command);
  }
  else {
    padmgr_RumbleSet(PAD0, PAD_MOTOR_STOP);
  }
}

static void mVibInfo_move(mVibInfo_c* vib_info) {
  int i;

  mVibInfo_force(vib_info);

  for (i = 0; i < vib_info->num_elements; i++) {
    mVibElem_move(vib_info->elements + i);
  }

  for (i = vib_info->num_elements - 1; i >= 0; i--) {
    if (vib_info->elements[i].now_entry >= mVibctl_ELEM_ENTRY_END) {
      mVibInfo_elem_delete(vib_info, i);
    }
  }

  mVibInfo_set_target_elem(vib_info);

  if (vib_info->force_stop == mVibctl_FLAG_FORCE_STOP_NONE) {
    mVibInfo_set_motor(vib_info);
  }
}

static void mVibctl_check_title_demo() {
  if (mFI_CheckFieldData() && mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELDTYPE_FG && mEv_IsTitleDemo()) {
    mVibctl_set_force_stop(mVibctl_FLAG_FORCE_STOP2);
  }
  else {
    mVibctl_clr_force_stop(mVibctl_FLAG_FORCE_STOP2);
  }
}

static void mVibctl_callback(void* arg) {
  mVibctl_check_title_demo();
  mVibInfo_move(&mVib_info);
}

extern void mVibctl_ct() {
  bzero(&mVib_info, sizeof(mVibInfo_c));
}

extern void mVibctl_init0() {
  mVibctl_ct();
}

extern void mVibctl_init() {
  padmgr_setClient(&mVibctl_callback, NULL);
}

extern void mVibctl_cleanup() {
  padmgr_removeClient(&mVibctl_callback, NULL);
}

extern void mVibctl_reset() {
  mVibctl_clr_force_stop(mVibctl_FLAG_FORCE_STOP_ALL);
  mVibctl_set_force_stop(mVibctl_FLAG_FORCE_STOP3);
}

extern void mVibctl_entry(int total_frames, int attack_type, int sustain_type, int release_type, int attack_frames, int sustain_frames, int release_frames, f32 step) {
  mVibInfo_elem_entry(&mVib_info, total_frames, attack_type, sustain_type, release_type, attack_frames, sustain_frames, release_frames, step);
}

extern void mVibctl_simple_entry(int total_frames, int type, int attack_frames, int sustain_frames, int release_frames, f32 step) {
  mVibInfo_elem_entry(&mVib_info, total_frames, type, type, type, attack_frames, sustain_frames, release_frames, step);
}

extern void mVibctl_set_force_stop(int force_stop) {
  mVibInfo_set_force_stop(&mVib_info, force_stop);
}

extern void mVibctl_clr_force_stop(int force_stop) {
  mVibInfo_clr_force_stop(&mVib_info, force_stop);
}
