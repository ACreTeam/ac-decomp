#include "c_keyframe.h"

#include "MSL_C/w_math.h"
#include "graph.h"
#include "libultra/libultra.h"
#include "sys_math3d.h"
#include "sys_matrix.h"

static void cKF_FrameControl_zeroClera(cKF_FrameControl_c* frame_control) {
  bzero(frame_control, sizeof(cKF_FrameControl_c));
  frame_control->max_frames = 1.0f;
  frame_control->current_frame = 1.0f;
  frame_control->speed = 1.0f;
  frame_control->end_frame = 1.0f;
  frame_control->start_frame = 1.0f;
  frame_control->mode = cKF_FRAMECONTROL_STOP;
}

static void cKF_FrameControl_ct(cKF_FrameControl_c* frame_control) {
  cKF_FrameControl_zeroClera(frame_control);
}

static void cKF_FrameControl_setFrame(cKF_FrameControl_c* frame_control,
                                      f32 start_frame, f32 end_frame,
                                      f32 max_frames, f32 current_frame,
                                      f32 speed, int mode) {
  frame_control->start_frame = start_frame;

  if (end_frame < 1.0f) {
    frame_control->end_frame = max_frames;
  } else {
    frame_control->end_frame = end_frame;
  }

  frame_control->max_frames = max_frames;
  frame_control->speed = speed;
  frame_control->current_frame = current_frame;
  frame_control->mode = mode;
}

static int cKF_FrameControl_passCheck(cKF_FrameControl_c* fc, f32 current,
                                      f32* out) {
  f32 cur;
  f32 speed;

  *out = 0.0f;
  cur = fc->current_frame;
  if (cur == current) {
    return 0;
  }

  speed = (fc->start_frame < fc->end_frame) ? fc->speed : -fc->speed;

  if ((speed >= 0.0f && cur < current && cur + speed >= current) ||
      (speed < 0.0f && cur > current && cur + speed <= current)) {
    *out = cur + speed - current;
    return 1;
  }
  return 0;
}

extern int cKF_FrameControl_passCheck_now(cKF_FrameControl_c* fc, f32 current) {
  f32 cur = fc->current_frame;
  f32 speed;
  int ret = 0;
  if (cur != current) {
    speed = (fc->start_frame < fc->end_frame) ? fc->speed : -fc->speed;
    if ((speed >= 0.0f && cur >= current && cur - speed < current) ||
        (speed < 0.0f && cur <= current && cur - speed > current)) {
      ret = 1;
    }
  } else {
    ret = 1;
  }
  return ret;
}

extern int cKF_FrameControl_stop_proc(cKF_FrameControl_c* fc) {
  f32 out;

  if (fc->current_frame == fc->end_frame) {
    return cKF_STATE_STOPPED;
  }
  if (cKF_FrameControl_passCheck(fc, fc->end_frame, &out)) {
    fc->current_frame = fc->end_frame;
    return cKF_STATE_STOPPED;
  }
  if (cKF_FrameControl_passCheck(fc, fc->start_frame, &out)) {
    fc->current_frame = fc->end_frame;
    return cKF_STATE_STOPPED;
  }
  return cKF_STATE_NONE;
}

static int cKF_FrameControl_repeat_proc(cKF_FrameControl_c* fc) {
  f32 out;

  if (cKF_FrameControl_passCheck(fc, fc->end_frame, &out)) {
    fc->current_frame = fc->start_frame + out;
    return cKF_STATE_CONTINUE;
  }
  if (cKF_FrameControl_passCheck(fc, fc->start_frame, &out)) {
    fc->current_frame = fc->end_frame + out;
    return cKF_STATE_CONTINUE;
  }
  return cKF_STATE_NONE;
}

static int cKF_FrameControl_play(cKF_FrameControl_c* fc) {
  int rec;
  f32 frame;

  if (fc->mode == cKF_FRAMECONTROL_STOP) {
    rec = cKF_FrameControl_stop_proc(fc);
  } else {
    rec = cKF_FrameControl_repeat_proc(fc);
  }

  if (rec == cKF_STATE_NONE) {
    frame = (fc->start_frame < fc->end_frame) ? fc->speed : -fc->speed;
    fc->current_frame += frame;
  }
  if (fc->current_frame < 1.0f) {
    fc->current_frame = (fc->current_frame - 1.0f) + fc->max_frames;
  } else if (fc->current_frame > fc->max_frames) {
    fc->current_frame = (fc->current_frame - fc->max_frames) + 1.0f;
  }
  return rec;
}

extern f32 cKF_HermitCalc(f32 t, f32 tension, f32 p0, f32 p1, f32 m0, f32 m1) {
  f32 p;
  f32 sq;
  f32 cb;
  f32 h10;
  f32 h11;

  sq = t * t;
  cb = sq * t;
  p = -(cb * 2.0f) + (3.0f * sq);
  h10 = t + (cb - (sq * 2.0f));
  h11 = cb - sq;

  return (((1.0f - p) * p0) + (p * p1)) + (tension * ((h10 * m0) + (h11 * m1)));
}

static s16 cKF_KeyCalc(s16 index, s16 next_index, s16* data_src, f32 frame) {
  int j;
  int i;
  f32 sub;
  s_xyz* s_vec = (s_xyz*)&data_src[index * 3];
  int key;

  if (s_vec->x >= frame) {
    return s_vec->y;
  }
  if (s_vec[next_index - 1].x <= frame) {
    return s_vec[next_index - 1].y;
  }

  for (j = 0, i = 1; 1; j++, i++) {
    if (s_vec[i].x > frame) {
      sub = s_vec[i].x - s_vec[j].x;

      if (!(F32_IS_ZERO(sub))) {
        f32 t = (frame - s_vec[j].x) / sub;
        f32 tension = sub * (1.0f / 30.0f);
        f32 calc = cKF_HermitCalc(t, tension, s_vec[j].y, s_vec[i].y, s_vec[j].z, s_vec[i].z);
        key = calc + 0.5;
        
        return key;
      } else {
        return s_vec[j].y;
      }
    }
  }
}

extern void cKF_SkeletonInfo_subRotInterpolation(f32 t, s16* out, s16 rot1,
                                                 s16 rot2) {
  u16 urot1 = rot1;
  s32 pad;
  u16 urot2 = rot2;
  f32 f1 = rot1;
  f32 signedDiff = rot2 - f1;
  f32 f2 = urot1;
  f32 unsignedDiff = urot2 - f2;

  if (fabsf(signedDiff) < fabsf(unsignedDiff)) {
    *out = f1 + signedDiff * t;
  } else {
    *out = f2 + unsignedDiff * t;
  }
}

static void cKF_SkeletonInfo_morphST(s16* now, s16* target, f32 step) {
  int i;

  for (i = 0; i < 3; i++) {
    if (*now != *target) {
      f32 now_f = (f32)*now;
      f32 target_f = (f32)*target;
      f32 diff = (target_f - now_f);
      *now = (diff * step) + now_f;
    }

    now++;
    target++;
  }
}

static void cKF_SkeletonInfo_R_zeroClear(cKF_SkeletonInfo_R_c* keyframe) {
  bzero(keyframe, sizeof(cKF_SkeletonInfo_R_c));
}

extern void cKF_SkeletonInfo_R_ct(cKF_SkeletonInfo_R_c* keyframe,
                                  cKF_Skeleton_R_c* skeleton,
                                  cKF_Animation_R_c* animation,
                                  s_xyz* work_table, s_xyz* target_table) {
  cKF_SkeletonInfo_R_zeroClear(keyframe);
  cKF_FrameControl_ct(&keyframe->frame_control);

  keyframe->skeleton = skeleton;
  keyframe->animation = animation;
  keyframe->current_joint = work_table;
  keyframe->target_joint = target_table;
}

extern void cKF_SkeletonInfo_R_dt(cKF_SkeletonInfo_R_c* keyframe) {}

extern void cKF_SkeletonInfo_R_init_standard_stop(
    cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation,
    s_xyz* rotation_diff_table) {
  cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, animation, 1.0f,
                          animation->frames, 1.0f, 0.5f, 0.0f,
                          cKF_FRAMECONTROL_STOP, rotation_diff_table);
}

extern void cKF_SkeletonInfo_R_init_standard_stop_morph(
    cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation,
    s_xyz* rotation_diff_table, f32 morph) {
  cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, animation, 1.0f,
                          animation->frames, 1.0f, 0.5f, morph,
                          cKF_FRAMECONTROL_STOP, rotation_diff_table);
}

extern void cKF_SkeletonInfo_R_init_standard_repeat(
    cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation,
    s_xyz* rotation_diff_table) {
  cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, animation, 1.0f,
                          animation->frames, 1.0f, 0.5f, 0.0f,
                          cKF_FRAMECONTROL_REPEAT, rotation_diff_table);
}

extern void cKF_SkeletonInfo_R_init_standard_repeat_morph(
    cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation,
    s_xyz* rotation_diff_table, f32 morph) {
  cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, animation, 1.0f,
                          animation->frames, 1.0f, 0.5f, morph,
                          cKF_FRAMECONTROL_REPEAT, rotation_diff_table);
}

extern void cKF_SkeletonInfo_R_init(cKF_SkeletonInfo_R_c* keyframe,
                                    cKF_Skeleton_R_c* skeleton,
                                    cKF_Animation_R_c* animation,
                                    f32 start_frame, f32 end_frame,
                                    f32 current_frame, f32 frame_speed,
                                    f32 morph_counter, int mode,
                                    s_xyz* rotation_diff_table) {
  keyframe->morph_counter = morph_counter;
  keyframe->skeleton = skeleton;
  keyframe->animation = animation;

  cKF_FrameControl_setFrame(&keyframe->frame_control, start_frame, end_frame,
                            keyframe->animation->frames, current_frame,
                            frame_speed, mode);
  keyframe->rotation_diff_table = rotation_diff_table;
}

static void cKF_SkeletonInfo_R_morphJoint(cKF_SkeletonInfo_R_c* keyframe) {
  f32 step;
  int i;
  s_xyz* current_joint = keyframe->current_joint;
  s_xyz* target_joint = keyframe->target_joint;

  if (!(F32_IS_ZERO(keyframe->morph_counter))) {
    step = 0.5f / fabsf(keyframe->morph_counter);
  } else {
    step = 0.0f;
  }

  cKF_SkeletonInfo_morphST(&current_joint->x, &target_joint->x, step);

  current_joint++;
  target_joint++;

  for (i = 0; i < keyframe->skeleton->num_joints; i++) {
    s16 next_joint_x = current_joint->x;
    s16 next_target_x = target_joint->x;

    s16 next_joint_y = current_joint->y;
    s16 next_joint_z = current_joint->z;

    s16 next_target_y = target_joint->y;
    s16 next_target_z = target_joint->z;

    if (next_joint_x != next_target_x || next_joint_y != next_target_y ||
        next_joint_z != next_target_z) {
      f32 difxyz = fabsf((f32)next_target_x - (f32)next_joint_x) +
                   fabsf((f32)next_target_y - (f32)next_joint_y) +
                   fabsf((f32)next_target_z - (f32)next_joint_z);

      s16 temp_vec_x = 0x7FFF + next_joint_x;
      s16 temp_vec_y = 0x7FFF - next_joint_y;
      s16 temp_vec_z = 0x7FFF + next_joint_z;

      f32 dif_xyz2 = fabsf((f32)next_target_x - (f32)temp_vec_x) +
                     fabsf((f32)next_target_y - (f32)temp_vec_y) +
                     fabsf((f32)next_target_z - (f32)temp_vec_z);

      if (difxyz < dif_xyz2) {
        cKF_SkeletonInfo_subRotInterpolation(step, &current_joint->x,
                                             next_joint_x, next_target_x);
        cKF_SkeletonInfo_subRotInterpolation(step, &current_joint->y,
                                             next_joint_y, next_target_y);
        cKF_SkeletonInfo_subRotInterpolation(step, &current_joint->z,
                                             next_joint_z, next_target_z);
      } else {
        cKF_SkeletonInfo_subRotInterpolation(step, &current_joint->x,
                                             temp_vec_x, next_target_x);
        cKF_SkeletonInfo_subRotInterpolation(step, &current_joint->y,
                                             temp_vec_y, next_target_y);
        cKF_SkeletonInfo_subRotInterpolation(step, &current_joint->z,
                                             temp_vec_z, next_target_z);
      }
    }
    target_joint++;
    current_joint++;
  }
}

inline u8* cKF_Animation_R_getFlagTable(cKF_Animation_R_c* keyframe) {
  return keyframe->flag_table;
}

inline s16* cKF_Animation_R_getFixedTable(cKF_Animation_R_c* keyframe) {
  return keyframe->fixed_table;
}

inline s16* cKF_Animation_R_getKeyTable(cKF_Animation_R_c* keyframe) {
  return keyframe->key_table;
}

inline s16* cKF_Animation_R_getDataTable(cKF_Animation_R_c* keyframe) {
  return keyframe->data_table;
}

extern int cKF_SkeletonInfo_R_play(cKF_SkeletonInfo_R_c* keyframe) {
  int ret;
  int s;
  s_xyz* c_joint;
  s16 j_fix_tbl;
  s16* cur_joint;
  cKF_Animation_R_c* key_an;
  int i;
  f32 calc_joint;
  s16* an_tblp;

  int j = 0;
  int t = 0;

  int index = 0;
  s16* joint = (F32_IS_ZERO(keyframe->morph_counter))
                   ? &keyframe->current_joint->x
                   : &keyframe->target_joint->x;
  int joint_num = 32;

  s16* an_fix_tbl = cKF_Animation_R_getFixedTable(keyframe->animation);
  s16* an_key_tbl = cKF_Animation_R_getKeyTable(keyframe->animation);
  s16* an_data_tbl = cKF_Animation_R_getDataTable(keyframe->animation);
  u8* an_flag_tbl = cKF_Animation_R_getFlagTable(keyframe->animation);

  for (i = 0; i < 3; i++) {
    if (*an_flag_tbl & joint_num) {
      an_tblp = &an_key_tbl[j];
      *joint = cKF_KeyCalc(index, *an_tblp, an_data_tbl,
                           keyframe->frame_control.current_frame);
      index += an_key_tbl[j];
      j++;
    } else {
      j_fix_tbl = an_fix_tbl[t];
      t++;
      *joint = j_fix_tbl;
    }

    joint_num = (u32)joint_num >> 1;
    joint += 1;
  }

  for (s = 0; s < keyframe->skeleton->num_joints; s++) {
    joint_num = 4;

    for (i = 0; i < 3; i++) {
      if (joint_num & an_flag_tbl[s]) {
        an_tblp = &an_key_tbl[j];
        *joint = cKF_KeyCalc(index, *an_tblp, an_data_tbl,
                             keyframe->frame_control.current_frame);
        index += an_key_tbl[j];
        j++;
      } else {
        j_fix_tbl = an_fix_tbl[t];
        t++;
        *joint = j_fix_tbl;
      }

      calc_joint = *joint * 0.1f;
      joint_num = (u32)joint_num >> 1;
      *joint =
          (s16)(int)((calc_joint -
                      ((f32)(int)(calc_joint * (1.0f / 360.0f)) * 360.0f)) *
                     (65536.0f / 360.0f));

      joint++;
    }
  }

  if (keyframe->rotation_diff_table != NULL) {
    c_joint = (F32_IS_ZERO(keyframe->morph_counter))
                  ? keyframe->current_joint
                  : keyframe->target_joint;

    c_joint += 1;
    for (i = 0; i < keyframe->skeleton->num_joints; i++) {
      c_joint->x += keyframe->rotation_diff_table[i].x;
      c_joint->y += keyframe->rotation_diff_table[i].y;
      c_joint->z += keyframe->rotation_diff_table[i].z;

      c_joint++;
    }
  }

  if (F32_IS_ZERO(keyframe->morph_counter)) {
    ret = cKF_FrameControl_play(&keyframe->frame_control);
  } else if (keyframe->morph_counter > 0.0f) {
    cKF_SkeletonInfo_R_morphJoint(keyframe);
    keyframe->morph_counter -= 0.5f;
    if (keyframe->morph_counter <= 0.0f) {
      keyframe->morph_counter = 0.0f;
    }
    ret = cKF_STATE_NONE;
  } else {
    cKF_SkeletonInfo_R_morphJoint(keyframe);
    keyframe->morph_counter += 0.5f;
    if (keyframe->morph_counter >= 0.0f) {
      keyframe->morph_counter = 0.0f;
    }
    ret = cKF_FrameControl_play(&keyframe->frame_control);
  }
  return ret;
}

extern void cKF_Si3_draw_SV_R_child(GAME* game, cKF_SkeletonInfo_R_c* keyframe,
                                    int* joint_num,
                                    cKF_draw_callback prerender_callback,
                                    cKF_draw_callback postrender_callback,
                                    void* arg, Mtx** mtxpp) {
  int i;
  int an_flag;
  Gfx* joint_m;
  Gfx* mjoint_m;
  u8 joint_f;
  xyz_t def_joint;
  s_xyz joint1;
  cKF_Joint_R_c* skel_c_joint;
  s_xyz* cur_joint;
  GRAPH* graph;

  skel_c_joint = keyframe->skeleton->joint_table;
  skel_c_joint += *joint_num;
  cur_joint = &keyframe->current_joint[*joint_num];

  if (*joint_num != 0) {
    def_joint.x = skel_c_joint->translation.x;
    def_joint.y = skel_c_joint->translation.y;
    def_joint.z = skel_c_joint->translation.z;
  } else {
    an_flag = keyframe->animation_enabled;
    if (an_flag & 1) {
      def_joint.x = keyframe->base_model_translation.x;
      def_joint.z = keyframe->base_model_translation.z;
    } else {
      def_joint.x = cur_joint->x;
      def_joint.z = cur_joint->z;
    }
    if (an_flag & 2) {
      def_joint.y = keyframe->base_model_translation.y;
    } else {
      def_joint.y = cur_joint->y;
    }
  }

  joint1 = cur_joint[1];

  if ((joint_num[0] == 0) && (keyframe->animation_enabled & 4)) {
    joint1.x = keyframe->base_model_rotation.x;
    joint1.y = keyframe->updated_base_model_rotation.y;
    joint1.z = keyframe->updated_base_model_rotation.z;
  }
  graph = game->graph;

  OPEN_DISP(graph);
  Matrix_push();
  joint_m = skel_c_joint->model;
  mjoint_m = joint_m;
  joint_f = skel_c_joint->flags;

  if ((prerender_callback == NULL) ||
      ((prerender_callback != NULL) &&
       prerender_callback(game, keyframe, *joint_num, &mjoint_m, &joint_f, arg,
                          &joint1, &def_joint) != 0)) {
    Matrix_softcv3_mult(&def_joint, &joint1);
    if (mjoint_m != NULL) {
      _Matrix_to_Mtx(*mtxpp);
      if (joint_f & 1) {
        gSPMatrix(NOW_POLY_XLU_DISP++, *mtxpp,
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NOW_POLY_XLU_DISP++, mjoint_m);
      } else {
        gSPMatrix(NOW_POLY_OPA_DISP++, *mtxpp,
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NOW_POLY_OPA_DISP++, mjoint_m);
      }
      *mtxpp += 1;
    } else if (joint_m != NULL) {
      _Matrix_to_Mtx(*mtxpp);
      gSPMatrix(NOW_POLY_OPA_DISP++, *mtxpp,
                G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
      *mtxpp += 1;
    }
  }

  CLOSE_DISP(graph);

  if (postrender_callback != NULL) {
    postrender_callback(game, keyframe, *joint_num, &mjoint_m, &joint_f, arg,
                        &joint1, &def_joint);
  }
  i = 0;
  *joint_num += 1;

  for (i; i < skel_c_joint->child; i++) {
    cKF_Si3_draw_SV_R_child(game, keyframe, joint_num, prerender_callback,
                            postrender_callback, arg, mtxpp);
  }
  Matrix_pull();
}

extern void cKF_Si3_draw_R_SV(GAME* game, cKF_SkeletonInfo_R_c* keyframe,
                              Mtx* mtxp, cKF_draw_callback prerender_callback,
                              cKF_draw_callback postrender_callback,
                              void* arg) {
  int joint_num;
  Mtx* mtx_p = mtxp;

  if (mtxp != NULL) {
    GRAPH* graph = game->graph;
    OPEN_DISP(graph);

    /* TODO: these should probably be made into a custom macro somewhere */
    gSPSegment(NOW_POLY_OPA_DISP++, G_MWO_SEGMENT_D,
               mtx_p);  // Load matrix (opaque)
    gSPSegment(NOW_POLY_XLU_DISP++, G_MWO_SEGMENT_D,
               mtx_p);  // Load matrix (translucent)

    CLOSE_DISP(graph);
    joint_num = 0;

    cKF_Si3_draw_SV_R_child(game, keyframe, &joint_num, prerender_callback,
                            postrender_callback, arg, &mtx_p);
  }
}

extern void cKF_SkeletonInfo_R_init_standard_repeat_speedsetandmorph(
    cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation,
    s_xyz* rotation_diff_table, f32 frame_speed, f32 morph_counter) {
  cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, animation, 1.0f,
                          animation->frames, 1.0f, frame_speed, morph_counter,
                          cKF_FRAMECONTROL_REPEAT, rotation_diff_table);
}

extern void cKF_SkeletonInfo_R_init_standard_repeat_setframeandspeedandmorph(
    cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation,
    s_xyz* rotation_diff_table, f32 frame, f32 frame_speed, f32 morph_counter) {
  cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, animation, 1.0f,
                          animation->frames, frame, frame_speed, morph_counter,
                          cKF_FRAMECONTROL_REPEAT, rotation_diff_table);
}

extern void cKF_SkeletonInfo_R_init_standard_setframeandspeedandmorphandmode(
    cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation,
    s_xyz* rotation_diff_table, f32 frame, f32 frame_speed, f32 morph_counter,
    int mode) {
  cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, animation, 1.0f,
                          animation->frames, frame, frame_speed, morph_counter,
                          mode, rotation_diff_table);
}

extern void cKF_SkeletonInfo_R_init_reverse_setspeedandmorphandmode(
    cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* animation,
    s_xyz* rotation_diff_table, f32 frame_speed, f32 morph_counter, int mode) {
  cKF_SkeletonInfo_R_init(
      keyframe, keyframe->skeleton, animation, animation->frames, 1.0f,
      animation->frames, frame_speed, morph_counter, mode, rotation_diff_table);
}

extern void cKF_SkeletonInfo_R_combine_work_set(
    cKF_SkeletonInfo_R_combine_work_c* combine,
    cKF_SkeletonInfo_R_c* keyframe) {
  combine->keyframe = keyframe;
  combine->anm_const_val_tbl = keyframe->animation->fixed_table;
  combine->anm_key_num = keyframe->animation->key_table;
  combine->anm_data_src = keyframe->animation->data_table;
  combine->anm_check_bit_tbl = keyframe->animation->flag_table;
  combine->anm_key_num_idx = 0;
  combine->anm_const_val_tbl_idx = 0;
  combine->anm_data_src_idx = 0;
}

extern void cKF_SkeletonInfo_R_combine_translation(
    s16** joint, int* flag, cKF_SkeletonInfo_R_combine_work_c* combine,
    s8* cwork_num) {
  int i = 0;

  for (i; i < 3; i++) {
    switch (*cwork_num) {
      case 0:

        if (*combine[0].anm_check_bit_tbl & *flag) {
          (**joint) =
              cKF_KeyCalc(combine[0].anm_data_src_idx,
                          combine[0].anm_key_num[combine[0].anm_key_num_idx],
                          combine[0].anm_data_src,
                          combine[0].keyframe->frame_control.current_frame);
        } else {
          (**joint) =
              combine[0].anm_const_val_tbl[combine[0].anm_const_val_tbl_idx];
        }

        break;
      case 1:

        if (*combine[1].anm_check_bit_tbl & *flag) {
          (**joint) =
              cKF_KeyCalc(combine[1].anm_data_src_idx,
                          combine[1].anm_key_num[combine[1].anm_key_num_idx],
                          combine[1].anm_data_src,
                          combine[1].keyframe->frame_control.current_frame);
        } else {
          (**joint) =
              combine[1].anm_const_val_tbl[combine[1].anm_const_val_tbl_idx];
        }

        break;
      case 2:

        if (*combine[2].anm_check_bit_tbl & *flag) {
          (**joint) =
              cKF_KeyCalc(combine[2].anm_data_src_idx,
                          combine[2].anm_key_num[combine[2].anm_key_num_idx],
                          combine[2].anm_data_src,
                          combine[2].keyframe->frame_control.current_frame);
        } else {
          (**joint) =
              combine[2].anm_const_val_tbl[combine[2].anm_const_val_tbl_idx];
        }

        break;
    }

    if (*combine[0].anm_check_bit_tbl & *flag) {
      combine[0].anm_data_src_idx +=
          combine[0].anm_key_num[combine[0].anm_key_num_idx];
      combine[0].anm_key_num_idx++;
    } else {
      combine[0].anm_const_val_tbl_idx++;
    }
    if (*combine[1].anm_check_bit_tbl & *flag) {
      combine[1].anm_data_src_idx +=
          combine[1].anm_key_num[combine[1].anm_key_num_idx];
      combine[1].anm_key_num_idx++;
    } else {
      combine[1].anm_const_val_tbl_idx++;
    }
    if (*combine[2].anm_check_bit_tbl & *flag) {
      combine[2].anm_data_src_idx +=
          combine[2].anm_key_num[combine[2].anm_key_num_idx];
      combine[2].anm_key_num_idx++;
    } else {
      combine[2].anm_const_val_tbl_idx++;
    }

    *flag = (u32)*flag >> 1;
    *joint += 1;
  }
}
extern void cKF_SkeletonInfo_R_combine_rotation(
    s16** joint, int* flag, cKF_SkeletonInfo_R_combine_work_c* combine,
    s8* cwork_num) {
  int i = 0;
  int j;
  s16* temp;
  f32 calc_joint;

  for (i; i < combine->keyframe->skeleton->num_joints; i++) {
    *flag = 4;

    for (j = 0; j < 3; j++) {
      switch (cwork_num[i + 1]) {
        case 0:
          if (*flag & combine[0].anm_check_bit_tbl[i]) {
            (**joint) =
                cKF_KeyCalc(combine[0].anm_data_src_idx,
                            combine[0].anm_key_num[combine[0].anm_key_num_idx],
                            combine[0].anm_data_src,
                            combine[0].keyframe->frame_control.current_frame);
          } else {
            (**joint) =
                combine[0].anm_const_val_tbl[combine[0].anm_const_val_tbl_idx];
          }
          break;

        case 1:
          if (*flag & combine[1].anm_check_bit_tbl[i]) {
            (**joint) =
                cKF_KeyCalc(combine[1].anm_data_src_idx,
                            combine[1].anm_key_num[combine[1].anm_key_num_idx],
                            combine[1].anm_data_src,
                            combine[1].keyframe->frame_control.current_frame);
          } else {
            (**joint) =
                combine[1].anm_const_val_tbl[combine[1].anm_const_val_tbl_idx];
          }
          break;

        case 2:
          if (*flag & combine[2].anm_check_bit_tbl[i]) {
            (**joint) =
                cKF_KeyCalc(combine[2].anm_data_src_idx,
                            combine[2].anm_key_num[combine[2].anm_key_num_idx],
                            combine[2].anm_data_src,
                            combine[2].keyframe->frame_control.current_frame);
          } else {
            (**joint) =
                combine[2].anm_const_val_tbl[combine[2].anm_const_val_tbl_idx];
          }
          break;
      }
      if (*flag & combine[0].anm_check_bit_tbl[i]) {
        combine[0].anm_data_src_idx +=
            combine[0].anm_key_num[combine[0].anm_key_num_idx];
        combine[0].anm_key_num_idx++;
      } else {
        combine[0].anm_const_val_tbl_idx++;
      }
      if (*flag & combine[1].anm_check_bit_tbl[i]) {
        combine[1].anm_data_src_idx +=
            combine[1].anm_key_num[combine[1].anm_key_num_idx];
        combine[1].anm_key_num_idx++;
      } else {
        combine[1].anm_const_val_tbl_idx++;
      }
      if (*flag & combine[2].anm_check_bit_tbl[i]) {
        combine[2].anm_data_src_idx +=
            combine[2].anm_key_num[combine[2].anm_key_num_idx];
        combine[2].anm_key_num_idx++;
      } else {
        combine[2].anm_const_val_tbl_idx++;
      }

      temp = *joint;
      calc_joint = 0.1f * (*temp);
      **joint = (s16)(int)((calc_joint -
                            ((f32)(int)(calc_joint * 0.0027777778f) * 360.0f)) *
                           182.04445f);

      *flag = (u32)*flag >> 1;
      *joint += 1;
    }
  }
}

extern int cKF_SkeletonInfo_R_combine_play(cKF_SkeletonInfo_R_c* info1,
                                           cKF_SkeletonInfo_R_c* info2,
                                           s8* flag) {
  int combinet;
  s16* joint;

  cKF_SkeletonInfo_R_combine_work_c combine1;
  cKF_SkeletonInfo_R_combine_work_c combine2;
  cKF_SkeletonInfo_R_combine_work_c combine3;

  int i;
  int j;

  s_xyz* joint2;
  s_xyz* applyjoint;

  if ((info1 == NULL) || (info2 == NULL) || (flag == NULL)) {
    return 0;
  }
  joint = (F32_IS_ZERO(info1->morph_counter)) ? &info1->current_joint->x
                                                 : &info1->target_joint->x;

  if (info1 != NULL) {
    cKF_SkeletonInfo_R_combine_work_set(&combine3, info1);
  }
  if (info2 != NULL) {
    cKF_SkeletonInfo_R_combine_work_set(&combine2, info2);
    cKF_SkeletonInfo_R_combine_work_set(&combine1, info2);
  }
  combinet = 0x20;
  cKF_SkeletonInfo_R_combine_translation(&joint, &combinet, &combine3, flag);
  cKF_SkeletonInfo_R_combine_rotation(&joint, &combinet, &combine3, flag);

  if (info1->rotation_diff_table != NULL) {
    applyjoint = (F32_IS_ZERO(info1->morph_counter)) ? info1->current_joint
                                                        : info1->target_joint;

    applyjoint += 1;
    for (i = 0, j = 0; i < info1->skeleton->num_joints; i++, j++) {
      applyjoint->x += info1->rotation_diff_table[j].x;
      applyjoint->y += info1->rotation_diff_table[j].y;
      applyjoint->z += info1->rotation_diff_table[j].z;

      applyjoint++;
    }
  }
  if (F32_IS_ZERO(info1->morph_counter)) {
    cKF_FrameControl_play(&info2->frame_control);
    return cKF_FrameControl_play(&info1->frame_control);
  }
  if (info1->morph_counter > 0.0f) {
    cKF_SkeletonInfo_R_morphJoint(info1);
    info1->morph_counter -= 0.5f;
    if (info1->morph_counter <= 0.0f) {
      info1->morph_counter = 0.0f;
    }
    return 0;
  }
  cKF_SkeletonInfo_R_morphJoint(info1);
  info1->morph_counter += 0.5f;
  if (info1->morph_counter >= 0.0f) {
    info1->morph_counter = 0.0f;
  }
  cKF_FrameControl_play(&info2->frame_control);
  return cKF_FrameControl_play(&info1->frame_control);
}

extern void cKF_SkeletonInfo_R_T_combine_play(int* arg1, int* arg2, int* arg3,
                                              cKF_SkeletonInfo_R_c* info1,
                                              cKF_SkeletonInfo_R_c* info2,
                                              cKF_SkeletonInfo_R_c* info3,
                                              s8* flag) {
  int combinet;
  s16* joint;

  cKF_SkeletonInfo_R_combine_work_c combine1;
  cKF_SkeletonInfo_R_combine_work_c combine2;
  cKF_SkeletonInfo_R_combine_work_c combine3;
  int i;
  int j;

  s_xyz* joint2;
  s_xyz* applyjoint;

  if ((info1 == NULL) || (info2 == NULL) || (info3 == NULL) || (flag == NULL)) {
    return;
  }

  joint = (F32_IS_ZERO(info1->morph_counter)) ? &info1->current_joint->x
                                                 : &info1->target_joint->x;

  if (info1 != NULL) {
    cKF_SkeletonInfo_R_combine_work_set(&combine3, info1);
  }
  if (info2 != NULL) {
    cKF_SkeletonInfo_R_combine_work_set(&combine2, info2);
  }
  if (info3 != NULL) {
    cKF_SkeletonInfo_R_combine_work_set(&combine1, info3);
  }

  combinet = 0x20;
  cKF_SkeletonInfo_R_combine_translation(&joint, &combinet, &combine3, flag);
  cKF_SkeletonInfo_R_combine_rotation(&joint, &combinet, &combine3, flag);

  if (info1->rotation_diff_table != NULL) {
    applyjoint = (F32_IS_ZERO(info1->morph_counter)) ? info1->current_joint
                                                        : info1->target_joint;

    applyjoint += 1;
    for (i = 0, j = 0; i < info1->skeleton->num_joints; i++, j++) {
      applyjoint->x += info1->rotation_diff_table[j].x;
      applyjoint->y += info1->rotation_diff_table[j].y;
      applyjoint->z += info1->rotation_diff_table[j].z;

      applyjoint++;
    }
  }
  if (F32_IS_ZERO(info1->morph_counter)) {
    *arg1 = cKF_FrameControl_play(&info1->frame_control);
    *arg2 = cKF_FrameControl_play(&info2->frame_control);
    *arg3 = cKF_FrameControl_play(&info3->frame_control);
    return;
  }
  if (info1->morph_counter > 0.0f) {
    cKF_SkeletonInfo_R_morphJoint(info1);
    info1->morph_counter -= 0.5f;
    if (info1->morph_counter <= 0.0f) {
      info1->morph_counter = 0.0f;
    }
    *arg1 = 0;
    *arg2 = 0;
    *arg3 = 0;
    return;
  }
  cKF_SkeletonInfo_R_morphJoint(info1);
  info1->morph_counter += 0.5f;
  if (info1->morph_counter >= 0.0f) {
    info1->morph_counter = 0.0f;
  }
  *arg1 = cKF_FrameControl_play(&info1->frame_control);
  *arg2 = cKF_FrameControl_play(&info2->frame_control);
  *arg3 = cKF_FrameControl_play(&info3->frame_control);
}

extern void cKF_SkeletonInfo_R_Animation_Set_base_shape_trs(
    f32 transx, f32 transy, f32 transz, cKF_SkeletonInfo_R_c* keyframe,
    s16 anglex, s16 angley, s16 anglez) {
  keyframe->base_model_translation.x = transx;
  keyframe->base_model_translation.y = transy;
  keyframe->base_model_translation.z = transz;

  keyframe->base_model_rotation.x = anglex;
  keyframe->updated_base_model_rotation.x = anglex;

  keyframe->base_model_rotation.y = angley;
  keyframe->updated_base_model_rotation.y = angley;

  keyframe->base_model_rotation.z = anglez;
  keyframe->updated_base_model_rotation.z = anglez;
}

extern void cKF_SkeletonInfo_R_AnimationMove_ct_base(
    f32 counter, xyz_t* basepos, xyz_t* correctpos, s16 ybase, s16 yidle,
    cKF_SkeletonInfo_R_c* keyframe, int an_flag) {
  int sub;

  keyframe->animation_enabled = an_flag;

  keyframe->fixed_counter = (counter >= 0.0f) ? counter : -counter;

  keyframe->base_world_position = ZeroVec;
  keyframe->model_world_position_correction = ZeroVec;

  if (basepos != NULL) {
    if (correctpos == NULL) {
      correctpos = basepos;
    }
    if (an_flag & 1) {
      keyframe->base_world_position.x = correctpos->x;
      keyframe->base_world_position.z = correctpos->z;
      keyframe->model_world_position_correction.x = basepos->x - correctpos->x;
      keyframe->model_world_position_correction.z = basepos->z - correctpos->z;
    }
    if (an_flag & 2) {
      keyframe->base_world_position.y = correctpos->y;
      keyframe->model_world_position_correction.y = basepos->y - correctpos->y;
    }
  }
  keyframe->base_angle_y = yidle;
  keyframe->model_angle_correction = 0;

  if (an_flag & 4) {
    sub = ybase - yidle;
    if (sub > 0x8000) {
      sub = -(0x10000 - sub);
    } else if (sub < -0x8000) {
      sub += 0x10000;
    }
    keyframe->base_angle_y = yidle;
    keyframe->model_angle_correction = sub;
  }
}

extern void cKF_SkeletonInfo_R_AnimationMove_dt(
    cKF_SkeletonInfo_R_c* keyframe) {
  int an_flag = keyframe->animation_enabled;
  s_xyz* cur_joint = keyframe->current_joint;

  if (an_flag & 1) {
    cur_joint->x = keyframe->base_model_translation.x;
    cur_joint->z = keyframe->base_model_translation.z;
  }
  if (an_flag & 2) {
    cur_joint->y = keyframe->base_model_translation.y;
  }
  if (an_flag & 4) {
    cur_joint = keyframe->current_joint;
    cur_joint[1].x = keyframe->base_model_rotation.x;
    cur_joint[1].y = keyframe->base_model_rotation.y;
    cur_joint[1].z = keyframe->base_model_rotation.z;
  }
  keyframe->animation_enabled = 0;
}

extern void cKF_SkeletonInfo_R_AnimationMove_base(
    xyz_t* base, s_xyz* sbase, xyz_t* move, s16 yidle,
    cKF_SkeletonInfo_R_c* keyframe) {
  f32 fc = keyframe->fixed_counter;
  f32 count = 1.0f + fc;
  int an_flag = keyframe->animation_enabled;
  f32 correct_y;
  f32 mangle_y;
  s16 angley;
  s16 angle_c;
  s_xyz* update_base;
  s16 base_x;
  s_xyz* cur_joint;
  s16 sub;
  f32 trans_x;
  f32 trans_z;
  f32 move_x;
  f32 move_z;
  f32 temp;
  f32 sin, cos;

  if (count > 0.5f) {
    correct_y = 0.5f / count;
  } else {
    correct_y = 0.0f;
  }

  if (an_flag & 4) {
    mangle_y = keyframe->model_angle_correction;
    if (count > 0.5f) {
      keyframe->model_angle_correction -= (s16)(int)(mangle_y * correct_y);
    } else {
      keyframe->model_angle_correction = 0;
    }
  }

  if (count > 0.5f) {
    if (an_flag & 1) {
      f32 cx, cz;

      cx = keyframe->model_world_position_correction.x;
      cx *= correct_y;

      cz = keyframe->model_world_position_correction.z;
      cz *= correct_y;

      keyframe->model_world_position_correction.x -= cx;
      keyframe->model_world_position_correction.z -= cz;
    }
    if (an_flag & 2) {
      f32 cy;

      cy = keyframe->model_world_position_correction.y;
      cy *= correct_y;

      keyframe->model_world_position_correction.y -= cy;
    }
  } else {
    keyframe->model_world_position_correction.x = 0.0f;
    keyframe->model_world_position_correction.y = 0.0f;
    keyframe->model_world_position_correction.z = 0.0f;
  }
  if ((sbase != NULL) && (an_flag & 4)) {
    angley = keyframe->base_angle_y;
    angle_c = keyframe->model_angle_correction;
    base_x = keyframe->base_model_rotation.x;
    update_base = &keyframe->updated_base_model_rotation;
    Matrix_push();
    Matrix_rotateXYZ(keyframe->current_joint[1].x, keyframe->current_joint[1].y,
                     keyframe->current_joint[1].z, 0);
    Matrix_to_rotate2_new(get_Matrix_now(), update_base, 0);
    Matrix_pull();
    sbase->x = angley + angle_c + (update_base->x - base_x);
  }

  if (base != NULL) {
    cur_joint = keyframe->current_joint;
    sub = 0;
    if (sbase != NULL) {
      sub = sbase->x - yidle;
    }
    if (an_flag & 1) {
      f32 move_x, move_z;
      f32 base_x, base_z;
      f32 temp2;
      f32 temp1;

      trans_x = keyframe->base_model_translation.x;
      trans_z = keyframe->base_model_translation.z;

      sin = sin_s(sub);
      cos = cos_s(sub);

      temp1 = (trans_x * cos) + (trans_z * sin);
      move_x = move->x * (cur_joint->x - temp1);
      temp1 = (-trans_x * sin) + (trans_z * cos);
      move_z = move->z * (cur_joint->z - temp1);

      sin = sin_s(yidle);
      cos = cos_s(yidle);

      base_x = keyframe->model_world_position_correction.x;
      base_z = keyframe->model_world_position_correction.z;
      temp2 = (move_x * cos) + (move_z * sin);
      base->x = temp2 + (keyframe->base_world_position.x + base_x);
      temp2 = (-move_x * sin) + (move_z * cos);
      base->z = temp2 + (keyframe->base_world_position.z + base_z);
    }
    if (an_flag & 2) {
      base->y = move->y * (cur_joint->y - keyframe->base_model_translation.y) +
                (keyframe->base_world_position.y +
                 keyframe->model_world_position_correction.y);
    }
  }
  count = fc - 0.5f;
  if (count < 0.0f) {
    count = 0.0f;
  }
  keyframe->fixed_counter = count;
}

extern void cKF_SkeletonInfo_R_AnimationMove_CulcTransToWorld(
    f32 calcx, f32 calcy, f32 calcz, xyz_t* base, xyz_t* calcp, s16 val,
    xyz_t* trans, cKF_SkeletonInfo_R_c* keyframe, int animation_flag) {
  f32 sin, cos;
  f32 j_x, j_z;
  s_xyz* cur_joint = keyframe->current_joint;

  if (animation_flag & 1) {
    j_x = cur_joint->x - calcx;
    j_z = cur_joint->z - calcz;

    sin = sin_s(val);
    cos = cos_s(val);

    base->x = calcp->x + trans->x * ((j_x * cos) + (j_z * sin));
    base->z = calcp->z + trans->z * ((-j_x * sin) + (j_z * cos));
  }
  if (animation_flag & 2) {
    base->y = calcp->y + trans->y * (cur_joint->y - calcy);
  }
}
