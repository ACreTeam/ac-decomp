#include "types.h"
#include "m_player.h"

/*
 * These tables dictate which animation will play for a given joint.
 * The player has two main animation states. 0 uses PLAYER_ACTOR::keyframe0,
 * and 1 uses PLAYER_ACTOR::keyframe1. This is essentially a barebones
 * animation overlay system.
 */

// clang-format off
s8 BOY_part_data[][mPlayer_JOINT_NUM + 1] = {
    /* Normal */
    {
        0, /* Base translation */
        0, /* mPlayer_JOINT_ROOT */
        0, /* mPlayer_JOINT_BASE */
        0, /* mPlayer_JOINT_LFOOT_BASE */
        0, /* mPlayer_JOINT_LFOOT1 */
        0, /* mPlayer_JOINT_LFOOT2 */
        0, /* mPlayer_JOINT_LFOOT3 */
        0, /* mPlayer_JOINT_RFOOT_BASE */
        0, /* mPlayer_JOINT_RFOOT1 */
        0, /* mPlayer_JOINT_RFOOT2 */
        0, /* mPlayer_JOINT_RFOOT3 */
        0, /* mPlayer_JOINT_TAIL_BASE */
        0, /* mPlayer_JOINT_TAIL1 */
        0, /* mPlayer_JOINT_TAIL2 */
        0, /* mPlayer_JOINT_CHEST */
        0, /* mPlayer_JOINT_LARM_BASE */
        0, /* mPlayer_JOINT_LARM1 */
        0, /* mPlayer_JOINT_LARM2 */
        0, /* mPlayer_JOINT_RARM_BASE */
        0, /* mPlayer_JOINT_RARM1 */
        0, /* mPlayer_JOINT_RARM2 */
        0, /* mPlayer_JOINT_HAND */
        0, /* mPlayer_JOINT_HEAD_BASE */
        0, /* mPlayer_JOINT_MOUTH_BASE */
        0, /* mPlayer_JOINT_MOUTH */
        0, /* mPlayer_JOINT_HEAD */
        0, /* mPlayer_JOINT_FEEL */
    },
    /* Axe */
    {
        0, /* Base translation */
        0, /* mPlayer_JOINT_ROOT */
        0, /* mPlayer_JOINT_BASE */
        0, /* mPlayer_JOINT_LFOOT_BASE */
        0, /* mPlayer_JOINT_LFOOT1 */
        0, /* mPlayer_JOINT_LFOOT2 */
        0, /* mPlayer_JOINT_LFOOT3 */
        0, /* mPlayer_JOINT_RFOOT_BASE */
        0, /* mPlayer_JOINT_RFOOT1 */
        0, /* mPlayer_JOINT_RFOOT2 */
        0, /* mPlayer_JOINT_RFOOT3 */
        0, /* mPlayer_JOINT_TAIL_BASE */
        0, /* mPlayer_JOINT_TAIL1 */
        0, /* mPlayer_JOINT_TAIL2 */
        0, /* mPlayer_JOINT_CHEST */
        1, /* mPlayer_JOINT_LARM_BASE */
        1, /* mPlayer_JOINT_LARM1 */
        1, /* mPlayer_JOINT_LARM2 */
        1, /* mPlayer_JOINT_RARM_BASE */
        1, /* mPlayer_JOINT_RARM1 */
        1, /* mPlayer_JOINT_RARM2 */
        1, /* mPlayer_JOINT_HAND */
        0, /* mPlayer_JOINT_HEAD_BASE */
        0, /* mPlayer_JOINT_MOUTH_BASE */
        0, /* mPlayer_JOINT_MOUTH */
        0, /* mPlayer_JOINT_HEAD */
        0, /* mPlayer_JOINT_FEEL */
    },
    /* Pickup */
    {
        0, /* Base translation */
        0, /* mPlayer_JOINT_ROOT */
        0, /* mPlayer_JOINT_BASE */
        0, /* mPlayer_JOINT_LFOOT_BASE */
        0, /* mPlayer_JOINT_LFOOT1 */
        0, /* mPlayer_JOINT_LFOOT2 */
        0, /* mPlayer_JOINT_LFOOT3 */
        0, /* mPlayer_JOINT_RFOOT_BASE */
        0, /* mPlayer_JOINT_RFOOT1 */
        0, /* mPlayer_JOINT_RFOOT2 */
        0, /* mPlayer_JOINT_RFOOT3 */
        0, /* mPlayer_JOINT_TAIL_BASE */
        0, /* mPlayer_JOINT_TAIL1 */
        0, /* mPlayer_JOINT_TAIL2 */
        0, /* mPlayer_JOINT_CHEST */
        0, /* mPlayer_JOINT_LARM_BASE */
        0, /* mPlayer_JOINT_LARM1 */
        0, /* mPlayer_JOINT_LARM2 */
        1, /* mPlayer_JOINT_RARM_BASE */
        1, /* mPlayer_JOINT_RARM1 */
        1, /* mPlayer_JOINT_RARM2 */
        1, /* mPlayer_JOINT_HAND */
        0, /* mPlayer_JOINT_HEAD_BASE */
        0, /* mPlayer_JOINT_MOUTH_BASE */
        0, /* mPlayer_JOINT_MOUTH */
        0, /* mPlayer_JOINT_HEAD */
        0, /* mPlayer_JOINT_FEEL */
    },
    /* Net */
    {
        0, /* Base translation */
        0, /* mPlayer_JOINT_ROOT */
        0, /* mPlayer_JOINT_BASE */
        0, /* mPlayer_JOINT_LFOOT_BASE */
        0, /* mPlayer_JOINT_LFOOT1 */
        0, /* mPlayer_JOINT_LFOOT2 */
        0, /* mPlayer_JOINT_LFOOT3 */
        0, /* mPlayer_JOINT_RFOOT_BASE */
        0, /* mPlayer_JOINT_RFOOT1 */
        0, /* mPlayer_JOINT_RFOOT2 */
        0, /* mPlayer_JOINT_RFOOT3 */
        0, /* mPlayer_JOINT_TAIL_BASE */
        0, /* mPlayer_JOINT_TAIL1 */
        0, /* mPlayer_JOINT_TAIL2 */
        0, /* mPlayer_JOINT_CHEST */
        0, /* mPlayer_JOINT_LARM_BASE */
        0, /* mPlayer_JOINT_LARM1 */
        0, /* mPlayer_JOINT_LARM2 */
        1, /* mPlayer_JOINT_RARM_BASE */
        1, /* mPlayer_JOINT_RARM1 */
        1, /* mPlayer_JOINT_RARM2 */
        1, /* mPlayer_JOINT_HAND */
        0, /* mPlayer_JOINT_HEAD_BASE */
        0, /* mPlayer_JOINT_MOUTH_BASE */
        0, /* mPlayer_JOINT_MOUTH */
        0, /* mPlayer_JOINT_HEAD */
        0, /* mPlayer_JOINT_FEEL */
    },
    /* Fan */
    {
        1, /* Base translation */
        1, /* mPlayer_JOINT_ROOT */
        1, /* mPlayer_JOINT_BASE */
        1, /* mPlayer_JOINT_LFOOT_BASE */
        1, /* mPlayer_JOINT_LFOOT1 */
        1, /* mPlayer_JOINT_LFOOT2 */
        1, /* mPlayer_JOINT_LFOOT3 */
        1, /* mPlayer_JOINT_RFOOT_BASE */
        1, /* mPlayer_JOINT_RFOOT1 */
        1, /* mPlayer_JOINT_RFOOT2 */
        1, /* mPlayer_JOINT_RFOOT3 */
        1, /* mPlayer_JOINT_TAIL_BASE */
        1, /* mPlayer_JOINT_TAIL1 */
        1, /* mPlayer_JOINT_TAIL2 */
        1, /* mPlayer_JOINT_CHEST */
        1, /* mPlayer_JOINT_LARM_BASE */
        1, /* mPlayer_JOINT_LARM1 */
        1, /* mPlayer_JOINT_LARM2 */
        0, /* mPlayer_JOINT_RARM_BASE */
        0, /* mPlayer_JOINT_RARM1 */
        0, /* mPlayer_JOINT_RARM2 */
        0, /* mPlayer_JOINT_HAND */
        0, /* mPlayer_JOINT_HEAD_BASE */
        1, /* mPlayer_JOINT_MOUTH_BASE */
        1, /* mPlayer_JOINT_MOUTH */
        1, /* mPlayer_JOINT_HEAD */
        1, /* mPlayer_JOINT_FEEL */
    },
};
// clang-format on
