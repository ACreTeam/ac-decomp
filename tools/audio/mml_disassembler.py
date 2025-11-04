import argparse
import struct
import re
from typing import List, Dict, Any, Set, Tuple

# Argument types
ARG_U8 = "u8"
ARG_S8 = "s8"
ARG_U16 = "u16"
ARG_S16 = "s16"
ARG_VARLEN = "varlen"
ARG_NOTE = "note"
ARG_ABS_ADDRESS = "abs_address"
ARG_REL_ADDRESS = "rel_address"
ARG_DATA_ADDRESS = "data_address"

class MMLCommand:
    """Represents a single MML command definition."""
    def __init__(self, name: str, opcode: int, args: List[str] = None, context: str = "unknown"):
        self.name = name
        self.opcode = opcode
        self.args = args if args else []
        self.context = context

    def __repr__(self):
        return f'MMLCommand(name="{self.name}", opcode=0x{self.opcode:X}, args={self.args}, context="{self.context}")'

# ==============================================================================
# STATIC COMMAND DEFINITIONS
# ==============================================================================
# This data is generated from parsing audiocommon.h and track.c
# SCOM_TABLE mapping for subtrack commands >= 0xA0 (index = opcode - 0xA0)
# Format: (arg0_type, arg1_type, arg2_type, ...) where types are 'u8' or 's16'
SCOM_TABLE_ARGS = {
    0xA0: ('s16',), 0xA1: (), 0xA2: ('s16',), 0xA3: (), 0xA4: ('u8',), 0xA5: (), 0xA6: ('u8', 's16',), 0xA7: ('u8',),
    0xA8: (), 0xA9: (), 0xAA: (), 0xAB: (), 0xAC: (), 0xAD: (), 0xAE: (), 0xAF: (),
    0xB0: ('s16',), 0xB1: (), 0xB2: ('s16',), 0xB3: ('u8',), 0xB4: (), 0xB5: (), 0xB6: (), 0xB7: ('s16',),
    0xB8: ('u8',), 0xB9: ('u8',), 0xBA: ('u8',), 0xBB: ('u8', 's16',), 0xBC: ('s16',), 0xBD: ('s16',), 0xBE: ('u8',), 0xBF: (),
    0xC0: (), 0xC1: ('u8',), 0xC2: ('abs_address',), 0xC3: (), 0xC4: (), 0xC5: (), 0xC6: ('u8',), 0xC7: ('u8', 's16',),
    0xC8: ('s8',), 0xC9: ('u8',), 0xCA: ('u8',), 0xCB: ('s16',), 0xCC: ('u8',), 0xCD: ('u8',), 0xCE: ('s16',), 0xCF: ('s16',),
    0xD0: ('u8',), 0xD1: ('u8',), 0xD2: ('u8',), 0xD3: ('u8',), 0xD4: ('u8',), 0xD5: ('u8',), 0xD6: ('u8',), 0xD7: ('u8',),
    0xD8: ('u8',), 0xD9: ('u8',), 0xDA: ('s16',), 0xDB: ('u8',), 0xDC: ('u8',), 0xDD: ('u8',), 0xDE: ('s16',), 0xDF: ('u8',),
    0xE0: ('u8',), 0xE1: ('u8', 'u8', 'u8'), 0xE2: ('u8', 'u8', 'u8'), 0xE3: ('u8',), 0xE4: (), 0xE5: ('u8',), 0xE6: ('u8',),
    0xE7: ('s16',), 0xE8: ('u8', 'u8', 'u8'), 0xE9: ('u8',), 0xEA: (), 0xEB: ('u8', 'u8',), 0xEC: (), 0xED: ('u8',), 0xEE: ('u8',),
    0xEF: ('s16', 'u8',), 0xF0: (), 0xF1: ('u8',),
    # Common commands (F2-FF use Convert_Com which uses same table)
    0xF2: ('u8',), 0xF3: ('u8',), 0xF4: ('u8',), 0xF5: ('s16',), 0xF6: (), 0xF7: (), 0xF8: ('u8',),
    0xF9: ('s16',), 0xFA: ('s16',), 0xFB: ('s16',), 0xFC: ('s16',), 0xFD: (), 0xFE: (), 0xFF: (),
}

def get_args_for_subtrack_cmd(opcode):
    """Get argument types for a subtrack command based on SCOM_TABLE."""
    if opcode >= 0xA0:
        # SCOM_TABLE_ARGS uses absolute opcodes as keys, not indices
        return list(SCOM_TABLE_ARGS.get(opcode, ()))
    # Commands < 0xA0 have fixed arguments based on code analysis
    if 0x00 <= opcode <= 0x0F:  # delay commands
        return []
    elif 0x10 <= opcode <= 0x1F:  # voiceload/synthload
        return []
    elif 0x20 <= opcode <= 0x2F:  # start subtrack
        return ['abs_address']
    elif 0x30 <= opcode <= 0x3F:  # write subtrack port
        return ['u8']
    elif 0x40 <= opcode <= 0x4F:  # read subtrack port
        return ['u8']
    elif 0x50 <= opcode <= 0x57:  # macro subtract port
        return []
    elif 0x60 <= opcode <= 0x67:  # macro read port
        return []
    elif 0x70 <= opcode <= 0x77:  # port write macro reg
        return []
    elif 0x78 <= opcode <= 0x7B:  # note start
        return ['s16']
    elif 0x80 <= opcode <= 0x83:  # read note finished
        return []
    elif 0x88 <= opcode <= 0x8B:  # note set pc
        return ['abs_address']
    elif 0x90 <= opcode <= 0x93:  # note stop
        return []
    elif 0x98 <= opcode <= 0x9B:  # note start dyntbl
        return []
    return []

COMMAND_MAPS = {
    'group': {
        # 0x00-0x0F: macro value load subtrack disabled
        **{i: MMLCommand(name=f"grp_macro_value_load_subtrack{i}_disabled",
                         opcode=i, args=[], context="group") for i in range(0x00, 0x10)},
        
        # 0x40-0x4F: disable subtrack
        **{i: MMLCommand(name=f"grp_disable_subtrack{i - 0x40}",
                        opcode=i, args=[], context="group") for i in range(0x40, 0x50)},
        
        # 0x50-0x57: macro value subtract from port
        **{i: MMLCommand(name=f"grp_macro_value_subtract_by_port{i - 0x50}",
                        opcode=i, args=[], context="group") for i in range(0x50, 0x58)},
        
        # 0x60-0x67: async load
        **{i: MMLCommand(name=f"grp_async_load_port{i - 0x60}",
                        opcode=i, args=['u8', 'u8'], context="group") for i in range(0x60, 0x68)},
        
        # 0x70-0x77: macro value write port
        **{i: MMLCommand(name=f"grp_macro_value_write_port{i - 0x70}",
                        opcode=i, args=[], context="group") for i in range(0x70, 0x78)},
        
        # 0x80-0x87: macro value read port
        **{i: MMLCommand(name=f"grp_macro_value_read_port{i - 0x80}",
                        opcode=i, args=[], context="group") for i in range(0x80, 0x88)},
        
        # 0x90-0x9F: start subtrack (absolute address)
        **{i: MMLCommand(name=f"grp_start_subtrack{i - 0x90}",
                        opcode=i, args=['abs_address'], context="group") for i in range(0x90, 0xA0)},
        
        # 0xA0-0xAF: start relative subtrack (reads s16 for relative offset)
        **{i: MMLCommand(name=f"grp_start_relative_subtrack{i - 0xA0}",
                        opcode=i, args=['s16'], context="group") for i in range(0xA0, 0xB0)},
        
        # 0xB0-0xB7: seq load (reads u8 seq_id, u16 data address)
        **{i: MMLCommand(name=f"grp_seq_load_port{i - 0xB0}",
                        opcode=i, args=['u8', 'data_address'], context="group") for i in range(0xB0, 0xB8)},
        
        # 0xBE: callback
        0xBE: MMLCommand(name="grp_callback", opcode=0xBE, args=['u8'], context="group"),
        
        # 0xC1: c1
        0xC1: MMLCommand(name="grp_c1", opcode=0xC1, args=[], context="group"),
        
        # 0xC2: dynamic branch
        0xC2: MMLCommand(name="grp_dynamic_branch", opcode=0xC2, args=['abs_address'], context="group"),
        
        # 0xC3: mute subtracks
        0xC3: MMLCommand(name="grp_mute_subtracks", opcode=0xC3, args=['abs_address'], context="group"),
        
        # 0xC4: start seq
        0xC4: MMLCommand(name="grp_start_seq", opcode=0xC4, args=['u8', 'u8'], context="group"),
        
        # 0xC5: update counter
        0xC5: MMLCommand(name="grp_update_counter", opcode=0xC5, args=['u16'], context="group"),
        
        # 0xC6: stop seq
        0xC6: MMLCommand(name="grp_stop_seq", opcode=0xC6, args=[], context="group"),
        
        # 0xC7: macro value store
        0xC7: MMLCommand(name="grp_macro_value_store", opcode=0xC7, args=['u8', 'abs_address'], context="group"),
        
        # 0xC8: macro value subtract
        0xC8: MMLCommand(name="grp_macro_value_subtract", opcode=0xC8, args=['u8'], context="group"),
        
        # 0xC9: macro value bit and
        0xC9: MMLCommand(name="grp_macro_value_bit_and", opcode=0xC9, args=['u8'], context="group"),
        
        # 0xCA: ca
        0xCA: MMLCommand(name="grp_ca", opcode=0xCA, args=[], context="group"),
        
        # 0xCB: cb
        0xCB: MMLCommand(name="grp_cb", opcode=0xCB, args=[], context="group"),
        
        # 0xCC: macro value load
        0xCC: MMLCommand(name="grp_macro_value_load", opcode=0xCC, args=['u8'], context="group"),
        
        # 0xCD: dyn tbl call
        0xCD: MMLCommand(name="grp_dyn_tbl_call", opcode=0xCD, args=['abs_address'], context="group"),
        
        # 0xCE: macro value random
        0xCE: MMLCommand(name="grp_macro_value_random", opcode=0xCE, args=['u8'], context="group"),
        
        # 0xCF: cf
        0xCF: MMLCommand(name="grp_cf", opcode=0xCF, args=[], context="group"),
        
        # 0xD0: set note alloc policy
        0xD0: MMLCommand(name="grp_set_note_alloc_policy", opcode=0xD0, args=['u8'], context="group"),
        
        # 0xD1: set short note gate time tbl
        0xD1: MMLCommand(name="grp_set_short_note_gate_time_tbl", opcode=0xD1, args=['data_address'], context="group"),
        
        # 0xD2: set short note velocity tbl
        0xD2: MMLCommand(name="grp_set_short_note_velocity_tbl", opcode=0xD2, args=['data_address'], context="group"),
        
        # 0xD3: set mute behavior
        0xD3: MMLCommand(name="grp_set_mute_behavior", opcode=0xD3, args=['u8'], context="group"),
        
        # 0xD4: mute
        0xD4: MMLCommand(name="grp_mute", opcode=0xD4, args=[], context="group"),
        
        # 0xD5: set mute scale
        0xD5: MMLCommand(name="grp_set_mute_scale", opcode=0xD5, args=['u8'], context="group"),
        
        # 0xD6: disable subtracks
        0xD6: MMLCommand(name="grp_disable_subtracks", opcode=0xD6, args=['u16'], context="group"),
        
        # 0xD7: alloc subtracks
        0xD7: MMLCommand(name="grp_alloc_subtracks", opcode=0xD7, args=['u16'], context="group"),
        
        # 0xD8: d8
        0xD8: MMLCommand(name="grp_d8", opcode=0xD8, args=[], context="group"),
        
        # 0xD9: set volume scale
        0xD9: MMLCommand(name="grp_set_volume_scale", opcode=0xD9, args=['u8'], context="group"),
        
        # 0xDA: change volume
        0xDA: MMLCommand(name="grp_change_volume", opcode=0xDA, args=['u8', 'u16'], context="group"),
        
        # 0xDB: set volume
        0xDB: MMLCommand(name="grp_set_volume", opcode=0xDB, args=['u8'], context="group"),
        
        # 0xDC: set tempo change
        0xDC: MMLCommand(name="grp_set_tempo_change", opcode=0xDC, args=['u8'], context="group"),
        
        # 0xDD: set tempo
        0xDD: MMLCommand(name="grp_set_tempo", opcode=0xDD, args=['u8'], context="group"),
        
        # 0xDE: transposition relative
        0xDE: MMLCommand(name="grp_transposition_relative", opcode=0xDE, args=['u8'], context="group"),
        
        # 0xDF: transposition absolute
        0xDF: MMLCommand(name="grp_transposition_absolute", opcode=0xDF, args=[], context="group"),
        
        # 0xEF: ef
        0xEF: MMLCommand(name="grp_ef", opcode=0xEF, args=['u16', 'u8'], context="group"),
        
        # 0xF0: release voices
        0xF0: MMLCommand(name="grp_release_voices", opcode=0xF0, args=[], context="group"),
        
        # 0xF1: reserve voices
        0xF1: MMLCommand(name="grp_reserve_voices", opcode=0xF1, args=['u8'], context="group"),
    },
    'subtrack': {
        # 0x00-0x0F: delay
        **{i: MMLCommand(name="sub_delay_clear" if i == 0 else f"sub_delay_{i}",
                         opcode=i, args=[], context="subtrack") for i in range(0x00, 0x10)},
        
        # 0x10-0x17: voiceload
        **{i: MMLCommand(name=f"sub_voiceload_port{i - 0x10}",
                        opcode=i, args=[], context="subtrack") for i in range(0x10, 0x18)},
        
        # 0x18-0x1F: synthload
        **{i: MMLCommand(name=f"sub_synthload_port{i - 0x18}",
                        opcode=i, args=[], context="subtrack") for i in range(0x18, 0x20)},
        
        # 0x20-0x2F: start subtrack
        **{i: MMLCommand(name=f"sub_start_subtrack{i - 0x20}",
                        opcode=i, args=['abs_address'], context="subtrack") for i in range(0x20, 0x30)},
        
        # 0x30-0x3F: write subtrack port
        **{i: MMLCommand(name=f"sub_write_subtrack{i - 0x30}_port",
                        opcode=i, args=['u8'], context="subtrack") for i in range(0x30, 0x40)},
        
        # 0x40-0x4F: read subtrack port
        **{i: MMLCommand(name=f"sub_read_subtrack{i - 0x40}_port",
                        opcode=i, args=['u8'], context="subtrack") for i in range(0x40, 0x50)},
        
        # 0x50-0x57: macro subtract port
        **{i: MMLCommand(name=f"sub_macro_subtract_port{i - 0x50}",
                        opcode=i, args=[], context="subtrack") for i in range(0x50, 0x58)},
        
        # 0x60-0x67: macro read port
        **{i: MMLCommand(name=f"sub_macro_read_port{i - 0x60}",
                        opcode=i, args=[], context="subtrack") for i in range(0x60, 0x68)},
        
        # 0x70-0x77: port write macro reg
        **{i: MMLCommand(name=f"sub_port{i - 0x70}_write_macro_reg",
                        opcode=i, args=[], context="subtrack") for i in range(0x70, 0x78)},
        
        # 0x78-0x7B: note start (all read s16 relative offset)
        **{i: MMLCommand(name=f"sub_note{i - 0x78}_start",
                        opcode=i, args=['s16'], context="subtrack") for i in range(0x78, 0x7C)},
        
        # 0x80-0x83: read note finished
        **{i: MMLCommand(name=f"sub_read_note{i - 0x80}_finished",
                        opcode=i, args=[], context="subtrack") for i in range(0x80, 0x84)},
        
        # 0x88-0x8B: note set pc
        **{i: MMLCommand(name=f"sub_note{i - 0x88}_set_pc",
                        opcode=i, args=['abs_address'], context="subtrack") for i in range(0x88, 0x8C)},
        
        # 0x90-0x97: note stop
        **{i: MMLCommand(name=f"sub_note{i - 0x90}_stop",
                        opcode=i, args=[], context="subtrack") for i in range(0x90, 0x97)},
        
        # 0x98-0x9B: note start dyntbl
        **{i: MMLCommand(name=f"sub_note{i - 0x98}_start_dyntbl",
                        opcode=i, args=[], context="subtrack") for i in range(0x98, 0x9C)},
        
        # 0xA0-0xFF: Use SCOM_TABLE
        # Map of opcode to command name
        **{i: MMLCommand(name={
               0xA0: "sub_macro_load_from_sfx_state", 0xA1: "sub_macro_load_from_sfx_state_dynval",
               0xA2: "sub_sfx_state_set", 0xA3: "sub_sfx_state_set_dynval", 0xA4: "sub_surround_effect_idx_set",
               0xA5: "sub_macro_add_subtrack_idx", 0xA6: "sub_write_goup_seq_offset_by_subtrack",
               0xA7: "sub_macro_bit_mod", 0xA8: "sub_dynval_special", 0xB0: "sub_set_filter",
               0xB1: "sub_clear_filter", 0xB2: "sub_load_dynval_from_group_seq", 0xB3: "sub_load_filter",
               0xB4: "sub_set_dyntbl_from_group_seq", 0xB5: "sub_load_dynval_from_dyntbl",
               0xB6: "sub_macro_load_from_dyntbl", 0xB7: "sub_random_dynval", 0xB8: "sub_macro_random_val",
               0xB9: "sub_set_vel_random_variance", 0xBA: "sub_set_gate_time_random_variance",
               0xBB: "sub_set_comb_filter_size_gain", 0xBC: "sub_add_dynval", 0xBD: "sub_set_sample_start_pos",
               0xBE: "sub_macro_set_from_callback", 0xC1: "sub_voice_set", 0xC2: "sub_set_dyntbl",
               0xC3: "sub_large_note_on", 0xC4: "sub_large_note_off", 0xC5: "sub_jmp_dyntbl",
               0xC6: "sub_set_instrument_bank", 0xC7: "sub_write_group_seq", 0xC8: "sub_macro_subtract",
               0xC9: "sub_macro_and", 0xCA: "sub_set_mute_flags", 0xCB: "sub_macro_load_from_group_seq",
               0xCC: "sub_macro_set", 0xCD: "sub_disable_subtrack", 0xCE: "sub_set_dynval",
               0xCF: "sub_write_dynval_to_group_seq", 0xD0: "sub_stereo_phase_set",
               0xD1: "sub_set_note_alloc_policy", 0xD2: "sub_set_sustain", 0xD3: "sub_large_bend_pitch",
               0xD4: "sub_set_reverb_vol", 0xD7: "sub_set_vibrato_rate", 0xD8: "sub_set_vibrato_depth",
               0xD9: "sub_set_decay_idx", 0xDA: "sub_set_envelope", 0xDB: "sub_set_transposition",
               0xDC: "sub_set_pan_weight", 0xDD: "sub_set_pan", 0xDE: "sub_set_freq_scale",
               0xDF: "sub_set_vol", 0xE0: "sub_set_vol_scale", 0xE1: "sub_set_vibrato_rate_linear",
               0xE2: "sub_set_vibrato_depth_linear", 0xE3: "sub_set_vibrato_delay", 0xE4: "sub_dyntbl_call",
               0xE5: "sub_set_reverb_idx", 0xE6: "sub_set_book_ofs", 0xE7: "sub_set_env_params_from_group_seq",
               0xE8: "sub_set_env_params", 0xE9: "sub_set_priority", 0xEA: "sub_stop",
               0xEB: "sub_init_instruments", 0xEC: "sub_reset_vibrato", 0xED: "sub_set_gain",
               0xEE: "sub_small_bend_pitch", 0xF0: "sub_dealloc_voices", 0xF1: "sub_alloc_voices",
           }.get(i, f"sub_unknown_{i:02X}"), opcode=i, args=get_args_for_subtrack_cmd(i), context="subtrack")
           for i in range(0xA0, 0x100)},
    },
    'note': {
        # 0xC0: mute
        0xC0: MMLCommand(name="note_mute", opcode=0xC0, args=['varlen'], context="note"),
        
        # 0xC1: set velocity sq
        0xC1: MMLCommand(name="note_set_velocity_sq", opcode=0xC1, args=['u8'], context="note"),
        
        # 0xC2: set transposition
        0xC2: MMLCommand(name="note_set_transposition", opcode=0xC2, args=['u8'], context="note"),
        
        # 0xC3: set short note default delay
        0xC3: MMLCommand(name="note_set_short_note_default_delay", opcode=0xC3, args=['varlen'], context="note"),
        
        # 0xC4: continuous on
        0xC4: MMLCommand(name="note_continuous_on", opcode=0xC4, args=[], context="note"),
        
        # 0xC5: continuous off
        0xC5: MMLCommand(name="note_continuous_off", opcode=0xC5, args=[], context="note"),
        
        # 0xC6: set instrument
        0xC6: MMLCommand(name="note_set_instrument", opcode=0xC6, args=['u8'], context="note"),
        
        # 0xC7: enable sweep
        0xC7: MMLCommand(name="note_enable_sweep", opcode=0xC7, args=['u8', 'u8', 'varlen'], context="note"),
        
        # 0xC8: disable sweep
        0xC8: MMLCommand(name="note_disable_sweep", opcode=0xC8, args=[], context="note"),
        
        # 0xC9: set gate time
        0xC9: MMLCommand(name="note_set_gate_time", opcode=0xC9, args=['u8'], context="note"),
        
        # 0xCA: set pan
        0xCA: MMLCommand(name="note_set_pan", opcode=0xCA, args=['u8'], context="note"),
        
        # 0xCB: set adsr envelope decay idx
        0xCB: MMLCommand(name="note_set_adsr_envelope_decay_idx", opcode=0xCB, args=['data_address', 'u8'], context="note"),
        
        # 0xCC: ignore drum pan
        0xCC: MMLCommand(name="note_ignore_drum_pan", opcode=0xCC, args=[], context="note"),
        
        # 0xCD: set stereo phase
        0xCD: MMLCommand(name="note_set_stereo_phase", opcode=0xCD, args=['u8'], context="note"),
        
        # 0xCE: set bend
        0xCE: MMLCommand(name="note_set_bend", opcode=0xCE, args=['u8'], context="note"),
        
        # 0xCF: set adsr decay idx
        0xCF: MMLCommand(name="note_set_adsr_decay_idx", opcode=0xCF, args=['u8'], context="note"),
        
        # 0xD0-0xDF: short note velocity sq
        **{i: MMLCommand(name=f"note_short_note_velocity_sq{i - 0xD0}",
                         opcode=i, args=[], context="note") for i in range(0xD0, 0xE0)},
        
        # 0xE0-0xEF: set short note gate time
        **{i: MMLCommand(name=f"note_set_short_note_gate_time{i - 0xE0}",
                         opcode=i, args=[], context="note") for i in range(0xE0, 0xF0)},
        
        # 0xF0: disable flags
        0xF0: MMLCommand(name="note_disable_flags", opcode=0xF0, args=['u16'], context="note"),
        
        # 0xF1: set surround effect idx
        0xF1: MMLCommand(name="note_set_surround_effect_idx", opcode=0xF1, args=['u8'], context="note"),
    },
    'common': {
        # 0xF2: branch rel not eq zero (reads u8 but treated as s8 relative)
        0xF2: MMLCommand(name="common_branch_rel_not_eq_zero", opcode=0xF2, args=['rel_address'], context="common"),
        
        # 0xF3: branch rel eq zero (reads u8 but treated as s8 relative)
        0xF3: MMLCommand(name="common_branch_rel_eq_zero", opcode=0xF3, args=['rel_address'], context="common"),
        
        # 0xF4: branch rel (reads u8 but treated as s8 relative)
        0xF4: MMLCommand(name="common_branch_rel", opcode=0xF4, args=['rel_address'], context="common"),
        
        # 0xF5: branch abs greq zero (reads s16 but treated as u16 absolute address)
        0xF5: MMLCommand(name="common_branch_abs_greq_zero", opcode=0xF5, args=['abs_address'], context="common"),
        
        # 0xF6: break
        0xF6: MMLCommand(name="common_break", opcode=0xF6, args=[], context="common"),
        
        # 0xF7: loop end
        0xF7: MMLCommand(name="common_loop_end", opcode=0xF7, args=[], context="common"),
        
        # 0xF8: loop (reads u8 loop count)
        0xF8: MMLCommand(name="common_loop", opcode=0xF8, args=['u8'], context="common"),
        
        # 0xF9: branch abs not eq zero (reads s16 but treated as u16 absolute address)
        0xF9: MMLCommand(name="common_branch_abs_not_eq_zero", opcode=0xF9, args=['abs_address'], context="common"),
        
        # 0xFA: branch abs eq zero (reads s16 but treated as u16 absolute address)
        0xFA: MMLCommand(name="common_branch_abs_eq_zero", opcode=0xFA, args=['abs_address'], context="common"),
        
        # 0xFB: branch abs (reads s16 but treated as u16 absolute address)
        0xFB: MMLCommand(name="common_branch_abs", opcode=0xFB, args=['abs_address'], context="common"),
        
        # 0xFC: call (reads s16 but treated as u16 absolute address)
        0xFC: MMLCommand(name="common_call", opcode=0xFC, args=['abs_address'], context="common"),
        
        # 0xFD: delay n frames (reads varlen)
        0xFD: MMLCommand(name="common_delay_n_frames", opcode=0xFD, args=['varlen'], context="common"),
        
        # 0xFE: delay 1 frame
        0xFE: MMLCommand(name="common_delay_1_frame", opcode=0xFE, args=[], context="common"),
        
        # 0xFF: stop script
        0xFF: MMLCommand(name="common_stop_script", opcode=0xFF, args=[], context="common"),
    }
}

def get_note_name(note_val: int) -> str:
    """Converts a MIDI note number to its string representation."""
    if note_val > 127:
        return f"0x{note_val:02X}"
    notes = ["C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"]
    note_idx = note_val % 12
    octave = (note_val // 12) - 1
    return f"{notes[note_idx]}{octave}"

class MMLDisassembler:
    """A two-pass disassembler for the Animal Crossing MML format."""

    def __init__(self, data: bytes, mode: str = "group"):
        self.data = data
        self.mode = mode  # Fallback mode for analyzing partial sections (not starting at offset 0)
        # Note: For full sequences starting at offset 0, mode is always "group" and auto-detected

        # Labels marked by type: group, subtrack, note, or data
        self.labels: Dict[int, Tuple[str, str]] = {}  # offset -> (label_name, label_type)
        self.data_labels: Dict[int, Tuple[str, str]] = {}  # offset -> (label_name, "data")
        self.reference_map: Dict[int, str] = {}
        self.visited_offsets: Set[int] = set()
        
        # Track mode contexts for subtrack and note commands
        # Maps offset -> (mode, context_info)
        # mode: "group", "subtrack", "note"
        # context_info: For subtrack: (subtrack_idx,), For note: (subtrack_idx, note_idx, subtrack_pc)
        self.mode_contexts: Dict[int, Tuple[str, Tuple]] = {}
        # Track subtrack PCs for note start calculations
        self.subtrack_pcs: Dict[int, int] = {}  # Maps (subtrack_start_offset, current_pc) -> subtrack_pc
        # Track large_notes flag per subtrack (default False)
        # Maps subtrack_idx -> large_notes (bool)
        self.subtrack_large_notes: Dict[int, bool] = {}
        # Track last dynval address loaded per subtrack for u16 data marking
        # Maps subtrack_idx -> address loaded by sub_load_dynval_from_group_seq
        self.subtrack_last_dynval_addr: Dict[int, int] = {}
        # Optional base address to add to displayed addresses/labels (useful in raw bytes mode)
        self.address_base: int = 0

    def read_u8(self, offset: int) -> int:
        return self.data[offset]

    def read_s8(self, offset: int) -> int:
        return struct.unpack_from('>b', self.data, offset)[0]

    def read_u16(self, offset: int) -> int:
        return struct.unpack_from('>H', self.data, offset)[0]

    def read_s16(self, offset: int) -> int:
        return struct.unpack_from('>h', self.data, offset)[0]

    def read_varlen(self, offset: int) -> Tuple[int, int]:
        """Read varlen value (1-2 bytes, same as Nas_ReadLengthData)."""
        val = self.read_u8(offset)
        if val & 0x80:
            return (((val & 0x7F) << 8) | self.read_u8(offset + 1)), 2
        return val, 1

    def read_length_data(self, offset: int) -> Tuple[int, int]:
        """Alias for read_varlen (Nas_ReadLengthData in track.c)."""
        return self.read_varlen(offset)

    def _get_command(self, opcode: int, mode: str = None) -> MMLCommand:
        """Get command for given opcode and mode."""
        if mode is None:
            mode = self.mode
        if opcode >= 0xF2:
            return COMMAND_MAPS.get("common", {}).get(opcode)
        command_map = COMMAND_MAPS.get(mode, {})
        return command_map.get(opcode)

    def _analyze_at_offset(self, start_offset: int, current_mode: str, context_info: Tuple = ()):
        """Recursively analyze commands starting at given offset with specified mode."""
        from collections import deque
        q = deque([(start_offset, current_mode, context_info)])
        
        while q:
            offset, mode, context = q.popleft()
            if offset >= len(self.data) or offset in self.visited_offsets:
                continue
            
            self.visited_offsets.add(offset)
            self.mode_contexts[offset] = (mode, context)
            
            addr = offset
            opcode = self.read_u8(addr)
            offset_after_opcode = addr + 1

            command = self._get_command(opcode, mode)
            if not command:
                if mode == "note" and 0x00 <= opcode <= 0xBF:  # It's a note (0x00-0xBF)
                    # Get large_notes flag for this subtrack
                    subtrack_idx = context[0] if context and len(context) > 0 else 0
                    large_notes = self.subtrack_large_notes.get(subtrack_idx, False)
                    
                    # Parse note based on large_notes flag
                    if large_notes:
                        # Large notes format
                        if (opcode & 0xC0) == 0x00:  # 0x00-0x3F
                            delay, delay_size = self.read_length_data(offset_after_opcode)
                            next_offset = offset_after_opcode + delay_size + 2  # delay, u8 vel, u8 gate
                        elif (opcode & 0xC0) == 0x40:  # 0x40-0x7F
                            delay, delay_size = self.read_length_data(offset_after_opcode)
                            next_offset = offset_after_opcode + delay_size + 1  # delay, u8 vel (gate=0)
                        else:  # 0x80-0xBF
                            next_offset = offset_after_opcode + 2  # u8 vel, u8 gate (delay=last_delay)
                    else:
                        # Small notes format
                        if (opcode & 0xC0) == 0x00:  # 0x00-0x3F
                            delay, delay_size = self.read_length_data(offset_after_opcode)
                            next_offset = offset_after_opcode + delay_size
                        else:  # 0x40-0x7F or 0x80-0xBF (no extra bytes)
                            next_offset = offset_after_opcode
                    
                    if next_offset not in self.visited_offsets and next_offset < len(self.data):
                        q.append((next_offset, mode, context))
                continue

            arg_offset = offset_after_opcode
            arg_size = 0
            subtrack_start_offset = None
            note_start_info = None
            note_set_pc_addr = None  # For sub_noteX_set_pc commands
            dynval_addr = None  # For sub_load_dynval_from_group_seq command
            
            # Check for mode transitions based on opcode ranges
            is_subtrack_start = mode == "group" and (0x90 <= opcode <= 0x9F)
            is_relative_subtrack_start = mode == "group" and (0xA0 <= opcode <= 0xAF)
            is_note_start = mode == "subtrack" and (0x78 <= opcode <= 0x7B)
            is_note_set_pc = mode == "subtrack" and (0x88 <= opcode <= 0x8B)
            is_load_dynval_from_group_seq = mode == "subtrack" and opcode == 0xB2
            is_set_dyntbl_from_group_seq = mode == "subtrack" and opcode == 0xB4
            
            # Commands that use abs_address for data (not code)
            # These commands use abs_address to point to data in seq_data:
            # - sub_set_dyntbl (0xC2): sets dynamic table pointer
            # - grp_macro_value_store (0xC7): stores macro value to data
            # - grp_dyn_tbl_call (0xCD): reads data address from table for call
            is_abs_address_data = False
            if command:
                if command.name in ["sub_set_dyntbl", "grp_macro_value_store", "grp_dyn_tbl_call"]:
                    is_abs_address_data = True
            
            arg_incomplete = False
            for arg_type in command.args:
                size = 0
                target_addr = -1
                is_data = False

                if arg_type in [ARG_U8, ARG_S8]: 
                    # Need 1 byte available
                    if arg_offset >= len(self.data):
                        arg_incomplete = True
                        size = 0
                        
                    else:
                        size = 1
                elif arg_type in [ARG_U16, ARG_S16]: 
                    # Need 2 bytes available
                    remaining = len(self.data) - arg_offset
                    if remaining < 2:
                        arg_incomplete = True
                        size = max(0, remaining)
                    else:
                        size = 2
                elif arg_type == ARG_VARLEN: 
                    # Need at least 1 byte for varlen
                    if arg_offset >= len(self.data):
                        arg_incomplete = True
                        size = 0
                    else:
                        _, size = self.read_varlen(arg_offset)
                elif arg_type == ARG_ABS_ADDRESS:
                    remaining = len(self.data) - arg_offset
                    if remaining < 2:
                        arg_incomplete = True
                        size = max(0, remaining)
                        target_addr = -1
                    else:
                        size = 2
                        target_addr = self.read_u16(arg_offset)
                    if is_subtrack_start:
                        # Switch to subtrack mode at absolute address
                        subtrack_idx = opcode - 0x90
                        subtrack_start_offset = target_addr
                    elif is_note_set_pc:
                        # Note set PC command - mark target as note
                        note_set_pc_addr = target_addr
                    elif is_abs_address_data:
                        # This abs_address refers to data, not code
                        is_data = True
                elif arg_type == ARG_REL_ADDRESS:
                    if arg_offset >= len(self.data):
                        arg_incomplete = True
                        size = 0
                    else:
                        size = 1
                    rel_offset = self.read_s8(arg_offset)
                    # Calculate target address: relative to address AFTER entire instruction
                    # Instruction size = 1 (opcode) + arg_size (previous args) + size (this arg)
                    instruction_end_addr = addr + 1 + arg_size + size
                    target_addr = instruction_end_addr + rel_offset
                elif arg_type == ARG_DATA_ADDRESS:
                    remaining = len(self.data) - arg_offset
                    if remaining < 2:
                        arg_incomplete = True
                        size = max(0, remaining)
                        target_addr = -1
                    else:
                        size = 2
                        target_addr = self.read_u16(arg_offset)
                    is_data = True
                elif arg_type == 's16':
                    remaining = len(self.data) - arg_offset
                    if remaining < 2:
                        arg_incomplete = True
                        size = max(0, remaining)
                        s16_val = 0
                    else:
                        size = 2
                        s16_val = self.read_s16(arg_offset)
                    if is_relative_subtrack_start:
                        # Switch to subtrack mode at relative address
                        subtrack_idx = opcode - 0xA0
                        subtrack_start_offset = addr + 3 + s16_val  # cmd + s16 arg + offset
                    elif is_note_start:
                        # Switch to note mode at subtrack PC + offset
                        note_idx = opcode - 0x78
                        subtrack_idx = context[0] if context else 0
                        # Calculate note start address: current PC + relative offset
                        note_start_addr = addr + 3 + s16_val  # cmd + s16 arg + offset
                        note_start_info = (subtrack_idx, note_idx, note_start_addr)
                    elif is_load_dynval_from_group_seq or is_set_dyntbl_from_group_seq:
                        # The s16 argument is actually an unsigned absolute address into the sequence script
                        # Track.c casts cmdArgs[0] to u16, so read it as u16 directly
                        dynval_addr_u16 = self.read_u16(arg_offset)
                        dynval_addr = dynval_addr_u16

                if arg_incomplete:
                    # Not enough bytes to parse this argument; advance to end of available data for this cmd
                    # and stop parsing further args for this command.
                    arg_offset += size
                    arg_size += size
                    break

                if target_addr != -1:
                    if is_data:
                        if target_addr not in self.data_labels:
                            self.data_labels[target_addr] = (f"D_{target_addr:04X}", "data")
                    else:
                        # Don't create labels here for addresses that will be handled by mode transitions
                        # (subtrack/note starts/note set PC will create labels with correct types later)
                        # Skip if this is an abs_address for subtrack start or note set PC, or s16 for relative subtrack/note start
                        skip_label_creation = (arg_type == ARG_ABS_ADDRESS and (is_subtrack_start or is_note_set_pc)) or \
                                             (arg_type == 's16' and (is_relative_subtrack_start or is_note_start))
                        if not skip_label_creation:
                            if target_addr not in self.labels:
                                    self.labels[target_addr] = (f"L_{target_addr:04X}", mode)
                            if target_addr not in self.visited_offsets and target_addr < len(self.data):
                                    # Keep same mode for regular jumps/calls
                                    q.append((target_addr, mode, context))
                
                arg_offset += size
                arg_size += size

                if arg_incomplete:
                    # Stop processing further args for this command
                    break
            
            # Calculate next offset after this command
            next_offset = addr + 1 + arg_size  # opcode + args
            
            # Handle mode transitions - add subtrack/note entry points to queue
            if subtrack_start_offset is not None and subtrack_start_offset < len(self.data):
                subtrack_idx = opcode & 0x0F if opcode >= 0x90 else (opcode - 0xA0) & 0x0F
                # Initialize large_notes flag for this subtrack (default False)
                if subtrack_idx not in self.subtrack_large_notes:
                    self.subtrack_large_notes[subtrack_idx] = False
                # Create or update label with correct type (subtrack)
                if subtrack_start_offset in self.labels:
                    # Update existing label type if it was created as "group" earlier
                    label_name, label_type = self.labels[subtrack_start_offset]
                    if label_type == "group":
                        self.labels[subtrack_start_offset] = (f"L_{subtrack_start_offset:04X}", "subtrack")
                else:
                    self.labels[subtrack_start_offset] = (f"L_{subtrack_start_offset:04X}", "subtrack")
                if subtrack_start_offset not in self.visited_offsets:
                    q.append((subtrack_start_offset, "subtrack", (subtrack_idx,)))
            
            if note_start_info is not None and note_start_info[2] < len(self.data):
                subtrack_idx, note_idx, note_addr = note_start_info
                # Create or update label with correct type (note)
                if note_addr in self.labels:
                    # Update existing label type if it was created as "subtrack" or "group" earlier
                    label_name, label_type = self.labels[note_addr]
                    if label_type in ["group", "subtrack"]:
                        self.labels[note_addr] = (f"L_{note_addr:04X}", "note")
                else:
                    self.labels[note_addr] = (f"L_{note_addr:04X}", "note")
                if note_addr not in self.visited_offsets:
                    q.append((note_addr, "note", (subtrack_idx, note_idx)))
            
            # Handle note set PC - mark target address as note and analyze it
            if note_set_pc_addr is not None and note_set_pc_addr < len(self.data):
                note_idx = opcode - 0x88
                subtrack_idx = context[0] if context else 0
                # Create or update label with correct type (note)
                if note_set_pc_addr in self.labels:
                    # Update existing label type if it was created as "subtrack" or "group" earlier
                    label_name, label_type = self.labels[note_set_pc_addr]
                    if label_type in ["group", "subtrack"]:
                        self.labels[note_set_pc_addr] = (f"L_{note_set_pc_addr:04X}", "note")
                else:
                    self.labels[note_set_pc_addr] = (f"L_{note_set_pc_addr:04X}", "note")
                # Note: note_set_pc sets the PC for the note layer, so we should analyze from that address
                if note_set_pc_addr not in self.visited_offsets:
                    q.append((note_set_pc_addr, "note", (subtrack_idx, note_idx)))
            
            # Handle dynval address from sub_load_dynval_from_group_seq - mark as data
            # Track the base address for potential u16 data marking when sub_set_dyntbl_from_group_seq follows
            if dynval_addr is not None and dynval_addr < len(self.data):
                # The s16 argument is actually an unsigned absolute address into the sequence script
                # Mark the address as data (it's an offset into the sequence script)
                if dynval_addr not in self.data_labels:
                    self.data_labels[dynval_addr] = (f"D_{dynval_addr:04X}", "data")
                
                # Track this base address for this subtrack (if we're in subtrack mode)
                # sub_load_dynval_from_group_seq reads from: base_addr + m->value * 2
                # We'll track this to mark u16 data when sub_set_dyntbl_from_group_seq follows
                if mode == "subtrack":
                    subtrack_idx = context[0] if context and len(context) > 0 else 0
                    self.subtrack_last_dynval_addr[subtrack_idx] = dynval_addr
            
            # Handle sub_set_dyntbl_from_group_seq - if it follows sub_load_dynval_from_group_seq,
            # mark the data at the address that would be loaded (assuming m->value = 0 for simplicity)
            # as u16 data. The actual address depends on m->value at runtime, but we can at least
            # mark the base case.
            if is_set_dyntbl_from_group_seq and mode == "subtrack":
                subtrack_idx = context[0] if context and len(context) > 0 else 0
                if subtrack_idx in self.subtrack_last_dynval_addr:
                    # This command uses the value loaded by sub_load_dynval_from_group_seq
                    # The address stored in dynamic_value points to u16 data (array of [u16])
                    # sub_load_dynval_from_group_seq reads from: base_addr + m->value * 2
                    # For marking purposes, we'll check the base address (m->value = 0 case)
                    base_addr = self.subtrack_last_dynval_addr[subtrack_idx]
                    if base_addr < len(self.data) - 1:  # Need at least 2 bytes for u16
                        # Read the u16 value from base_addr (assuming m->value = 0)
                        # This is the address that sub_set_dyntbl_from_group_seq would use
                        target_data_addr = self.read_u16(base_addr)
                        if target_data_addr < len(self.data):
                            # Mark as u16 data (update if it was just marked as "data")
                            if target_data_addr in self.data_labels:
                                label_name, _ = self.data_labels[target_data_addr]
                                self.data_labels[target_data_addr] = (label_name, "u16")
                            else:
                                self.data_labels[target_data_addr] = (f"D_{target_data_addr:04X}", "u16")
            
            # Handle large_notes flag changes in subtrack mode
            if mode == "subtrack" and command.name in ["sub_large_note_on", "sub_large_note_off"]:
                subtrack_idx = context[0] if context and len(context) > 0 else 0
                # Note: These command names are counterintuitive - ON sets to False, OFF sets to True
                if command.name == "sub_large_note_on":
                    self.subtrack_large_notes[subtrack_idx] = False
                elif command.name == "sub_large_note_off":
                    self.subtrack_large_notes[subtrack_idx] = True
            
            # Continue sequential execution in same mode if not a terminal command
            # Note: delay commands pause execution but don't stop sequential analysis
            # Unconditional branches stop sequential flow, but we still analyze the target
            terminal_commands = ["common_stop_script", "grp_stop_seq", "sub_stop", "common_branch_abs"]
            if command.name not in terminal_commands and next_offset not in self.visited_offsets and next_offset < len(self.data):
                q.append((next_offset, mode, context))

    def analysis_pass(self, start_offset: int = 0, start_mode: str = None):
        """First pass: find all jump/call targets and data references to create labels.
        
        Args:
            start_offset: Offset to start analysis from (default: 0)
            start_mode: Mode to start in (default: "group" for sequences, or self.mode for single-section analysis)
        """
        print("Starting analysis pass...")
        # Default to the disassembler's configured mode unless explicitly overridden
        if start_mode is None:
            start_mode = self.mode
        self._analyze_at_offset(start_offset, start_mode, ())
        
        # Mark all unreferenced bytes as data
        self._mark_unreferenced_bytes_as_data()
        
        print(f"Analysis complete. Found {len(self.labels)} code labels and {len(self.data_labels)} data labels.")

    def _mark_unreferenced_bytes_as_data(self):
        """Mark all unreferenced bytes in the script as data."""
        # Find all unreferenced byte offsets
        all_offsets = set(range(len(self.data)))
        unreferenced_all = sorted(all_offsets - self.visited_offsets)
        
        # Filter out offsets that should be treated as code in current context (e.g., notes in note mode)
        unreferenced = []
        for addr in unreferenced_all:
            mode, _ = self.mode_contexts.get(addr, (self.mode, ()))
            opcode = self.read_u8(addr)
            if mode == "note" and (0x00 <= opcode <= 0xBF or opcode == 0xC0):
                continue
            unreferenced.append(addr)
        
        # Group consecutive unreferenced bytes into data sections
        if unreferenced:
            data_start = unreferenced[0]
            for i in range(1, len(unreferenced)):
                if unreferenced[i] != unreferenced[i-1] + 1:
                    # End of current data section, create label for start
                    if data_start not in self.data_labels:
                        self.data_labels[data_start] = (f"D_{data_start:04X}", "data")
                    data_start = unreferenced[i]
            # Create label for the last data section
            if data_start not in self.data_labels:
                self.data_labels[data_start] = (f"D_{data_start:04X}", "data")

    def disassembly_pass(self) -> List[str]:
        """Second pass: generate the disassembled output text."""
        # Process all visited offsets in order, using their stored mode context
        lines = []
        processed_offsets = set()  # Track which byte offsets we've already processed
        # Track large_notes flag state per subtrack as we process addresses
        # (reset from analysis pass, will be updated as we encounter flag-changing commands)
        disasm_large_notes = {idx: False for idx in self.subtrack_large_notes.keys()}
        
        # Sort all offsets (visited code + unreferenced data) by address
        all_offsets = sorted(set(range(len(self.data))))
        
        for addr in all_offsets:
            if addr in processed_offsets:
                continue
            
            # Determine mode/context for this address
            mode, context = self.mode_contexts.get(addr, (self.mode, ()))
            opcode = self.read_u8(addr)
            disp = self.address_base + addr
            line_prefix = f"/* {disp:04X} */  "
            offset = addr + 1

            # Check if this is an unreferenced byte (not in visited_offsets)
            is_unreferenced = addr not in self.visited_offsets
            
            # Handle unreferenced bytes as data
            # BUT: if we're in note mode and this looks like a note opcode (0x00-0xBF),
            # disassemble it as a note instead of dumping as data to improve raw/note UX.
            if is_unreferenced and not (mode == "note" and 0x00 <= opcode <= 0xBF):
                # Add label if this is a labeled data address
                if addr in self.data_labels:
                    lines.append(f"\nD_{(self.address_base + addr):04X}: ; data")
                
                # Output as raw byte
                byte_val = opcode
                lines.append(f"{line_prefix}.db 0x{byte_val:02X}")
                processed_offsets.add(addr)
                continue
            
            # Helper formatters for labels/addresses using base
            def _fmt_code_label(a: int, label_type: str) -> str:
                return f"L_{(self.address_base + a):04X}"

            def _fmt_data_label(a: int) -> str:
                return f"D_{(self.address_base + a):04X}"

            def _fmt_hex(a: int) -> str:
                return f"0x{(self.address_base + a):04X}"

            # Add label if this is a labeled address
            if addr in self.labels:
                _stored_name, label_type = self.labels[addr]
                lines.append(f"\n{_fmt_code_label(addr, label_type)}: ; {label_type}")
            if addr in self.data_labels:
                lines.append(f"\n{_fmt_data_label(addr)}: ; data")

            command = self._get_command(opcode, mode)
            
            # Calculate command size
            cmd_size = 1  # opcode byte
            if not command:
                if mode == "note" and 0x00 <= opcode <= 0xBF:
                    # Get large_notes flag for this subtrack (use current state from disassembly)
                    subtrack_idx = context[0] if context and len(context) > 0 else 0
                    large_notes = disasm_large_notes.get(subtrack_idx, False)
                    
                    note_value = opcode & 0x3F  # Lower 6 bits (instrument number)
                    arg_offset = offset
                    
                    if large_notes:
                        # Large notes format
                        if (opcode & 0xC0) == 0x00:  # 0x00-0x3F
                            delay, delay_size = self.read_length_data(arg_offset)
                            arg_offset += delay_size
                            velocity = self.read_u8(arg_offset)
                            arg_offset += 1
                            gate = self.read_u8(arg_offset)
                            arg_offset += 1
                            cmd_size = arg_offset - addr
                            lines.append(f"{line_prefix}note      {get_note_name(note_value)}, {delay}, {velocity}, {gate}")
                        elif (opcode & 0xC0) == 0x40:  # 0x40-0x7F
                            delay, delay_size = self.read_length_data(arg_offset)
                            arg_offset += delay_size
                            velocity = self.read_u8(arg_offset)
                            arg_offset += 1
                            cmd_size = arg_offset - addr
                            lines.append(f"{line_prefix}note      {get_note_name(note_value)}, {delay}, {velocity}, 0")
                        else:  # 0x80-0xBF
                            velocity = self.read_u8(arg_offset)
                            arg_offset += 1
                            gate = self.read_u8(arg_offset)
                            arg_offset += 1
                            cmd_size = arg_offset - addr
                            lines.append(f"{line_prefix}note      {get_note_name(note_value)}, <last>, {velocity}, {gate}")
                    else:
                        # Small notes format
                        if (opcode & 0xC0) == 0x00:  # 0x00-0x3F
                            delay, delay_size = self.read_length_data(arg_offset)
                            arg_offset += delay_size
                            cmd_size = arg_offset - addr
                            lines.append(f"{line_prefix}note      {get_note_name(note_value)}, {delay}")
                        elif (opcode & 0xC0) == 0x40:  # 0x40-0x7F
                            cmd_size = 1
                            lines.append(f"{line_prefix}note      {get_note_name(note_value)}, <default>")
                        else:  # 0x80-0xBF
                            cmd_size = 1
                            lines.append(f"{line_prefix}note      {get_note_name(note_value)}, <last>")
                elif mode == "note" and opcode == 0xC0:
                    # Mute command
                    delay, delay_size = self.read_length_data(offset)
                    cmd_size = 1 + delay_size
                    lines.append(f"{line_prefix}note_mute                {delay}")
                else:
                    lines.append(f"{line_prefix}.db 0x{opcode:02X} ; Unknown Opcode")
                # Mark all bytes of this command as processed
                for i in range(cmd_size):
                    processed_offsets.add(addr + i)
                continue

            arg_values = []
            arg_size = 0
            arg_incomplete = False
            
            for arg_type in command.args:
                size = 0
                val = None
                if arg_type == ARG_U8: 
                    if offset + arg_size >= len(self.data):
                        arg_incomplete, val, size = True, "?", 0
                    else:
                        val, size = self.read_u8(offset + arg_size), 1
                elif arg_type == ARG_S8: 
                    if offset + arg_size >= len(self.data):
                        arg_incomplete, val, size = True, "?", 0
                    else:
                        val, size = self.read_s8(offset + arg_size), 1
                elif arg_type == ARG_U16: 
                    if offset + arg_size + 1 >= len(self.data):
                        arg_incomplete, val, size = True, "?", max(0, len(self.data) - (offset + arg_size))
                    else:
                        val, size = self.read_u16(offset + arg_size), 2
                elif arg_type == ARG_S16: 
                    if offset + arg_size + 1 >= len(self.data):
                        arg_incomplete, val, size = True, "?", max(0, len(self.data) - (offset + arg_size))
                    else:
                        val, size = self.read_s16(offset + arg_size), 2
                elif arg_type == ARG_VARLEN: 
                    if offset + arg_size >= len(self.data):
                        arg_incomplete, val, size = True, "?", 0
                    else:
                        val, size = self.read_varlen(offset + arg_size)
                elif arg_type == ARG_ABS_ADDRESS:
                    if offset + arg_size + 1 >= len(self.data):
                        arg_incomplete, val, size = True, "?", max(0, len(self.data) - (offset + arg_size))
                    else:
                        val, size = self.read_u16(offset + arg_size), 2
                    # Check if this is a data address (for commands like sub_set_dyntbl, grp_macro_value_store, grp_dyn_tbl_call)
                    is_data_addr = False
                    if command and command.name in ["sub_set_dyntbl", "grp_macro_value_store", "grp_dyn_tbl_call"]:
                        is_data_addr = True
                    
                    if is_data_addr:
                        # Look up data label name if it exists
                        if not isinstance(val, str) and val in self.data_labels:
                            val = _fmt_data_label(val)
                        else:
                            val = val if isinstance(val, str) else _fmt_data_label(val if isinstance(val, int) else 0)
                    else:
                        # Look up code label name if it exists
                        if not isinstance(val, str) and val in self.labels:
                            _lbl, _lt = self.labels[val]
                            val = _fmt_code_label(val, _lt)
                        else:
                            val = val if isinstance(val, str) else _fmt_hex(val)
                elif arg_type == ARG_REL_ADDRESS:
                    if offset + arg_size >= len(self.data):
                        arg_incomplete, rel_offset, size = True, 0, 0
                    else:
                        rel_offset, size = self.read_s8(offset + arg_size), 1
                    # Calculate target address: instruction starts at addr, total size will be 1 (opcode) + arg_size (previous args) + size (this arg)
                    # Target is relative to the address AFTER the entire instruction
                    instruction_end_addr = addr + 1 + arg_size + size
                    rel_addr = instruction_end_addr + rel_offset
                    # Look up label name if it exists
                    if rel_addr in self.labels:
                        _label_name, _ltype = self.labels[rel_addr]
                        # Show label with relative offset comment
                        val = f"{_fmt_code_label(rel_addr, _ltype)}  /* rel: {rel_offset:+d} */"
                    else:
                        # Show absolute address with relative offset comment
                        val = f"{_fmt_hex(rel_addr)}  /* rel: {rel_offset:+d} */"
                elif arg_type == ARG_DATA_ADDRESS:
                    if offset + arg_size + 1 >= len(self.data):
                        arg_incomplete, val, size = True, "?", max(0, len(self.data) - (offset + arg_size))
                    else:
                        val, size = self.read_u16(offset + arg_size), 2
                    # Look up data label if it exists
                    if not isinstance(val, str) and val in self.data_labels:
                        val = _fmt_data_label(val)
                    else:
                        val = val if isinstance(val, str) else _fmt_hex(val)
                elif arg_type == 's16':
                    if offset + arg_size + 1 >= len(self.data):
                        arg_incomplete, val, size = True, 0, max(0, len(self.data) - (offset + arg_size))
                    else:
                        val, size = self.read_s16(offset + arg_size), 2
                    # For relative subtrack start or note start, calculate target address
                    if mode == "group" and command.name.startswith("grp_start_relative_subtrack"):
                        rel_offset = val
                        target_addr = addr + 3 + rel_offset
                        if target_addr in self.labels:
                            _l, _lt = self.labels[target_addr]
                            val = _fmt_code_label(target_addr, _lt)
                        else:
                            val = _fmt_hex(target_addr)
                    elif mode == "subtrack" and command.name.startswith("sub_note") and command.name.endswith("_start"):
                        rel_offset = val
                        target_addr = addr + 3 + rel_offset
                        if target_addr in self.labels:
                            _l, _lt = self.labels[target_addr]
                            val = _fmt_code_label(target_addr, _lt)
                        else:
                            val = _fmt_hex(target_addr)
                    elif mode == "subtrack" and command.name in ["sub_load_dynval_from_group_seq", "sub_set_dyntbl_from_group_seq"]:
                        # The s16 argument is actually an unsigned absolute address into the sequence script
                        # Track.c casts cmdArgs[0] to u16, so read it as u16 directly
                        dynval_addr = self.read_u16(offset + arg_size)
                        # Mark the address as data if it's valid
                        if dynval_addr < len(self.data) and dynval_addr not in self.data_labels:
                            self.data_labels[dynval_addr] = (f"D_{dynval_addr:04X}", "data")
                        # Show as data label in output (check after marking)
                        if dynval_addr in self.data_labels:
                            val = _fmt_data_label(dynval_addr)
                        else:
                            # Fallback: show as label format even if not in dict yet
                            val = _fmt_data_label(dynval_addr)
                
                # Format numeric values > 255 as hex
                # Only format if val is still a numeric type (not already a string from label/address formatting)
                if isinstance(val, int):
                    # Negative values stay as decimal
                    if val < 0:
                        val = str(val)
                    elif val > 255:
                        # Format as hex, determining appropriate width based on value
                        if val > 0xFFFF:
                            val = f"0x{val:08X}"
                        elif val > 0xFF:
                            val = f"0x{val:04X}"
                    else:
                        # Values 0-255 stay as decimal
                        val = str(val)
                elif val is None:
                    val = "?"
                
                arg_values.append(val)
                arg_size += size

                if arg_incomplete:
                    break
            
            cmd_size += arg_size
            arg_str = ", ".join(map(str, arg_values))
            lines.append(f"{line_prefix}{command.name:<35} {arg_str}")
            
            # Handle large_notes flag changes in subtrack mode during disassembly
            if mode == "subtrack" and command.name in ["sub_large_note_on", "sub_large_note_off"]:
                subtrack_idx = context[0] if context and len(context) > 0 else 0
                # Note: These command names are counterintuitive - ON sets to False, OFF sets to True
                if command.name == "sub_large_note_on":
                    disasm_large_notes[subtrack_idx] = False
                elif command.name == "sub_large_note_off":
                    disasm_large_notes[subtrack_idx] = True
            
            # Mark all bytes of this command as processed
            for i in range(cmd_size):
                processed_offsets.add(addr + i)

        return lines

def main():
    parser = argparse.ArgumentParser(description="A two-pass disassembler for Animal Crossing MML.")
    # Either provide an input file or raw bytes
    parser.add_argument("input_file", nargs='?', help="Path to the compiled MML binary file.")
    parser.add_argument("--raw-bytes", dest="raw_bytes", default=None,
                        help="Hex byte string to disassemble (e.g. '00 12 3F' or '00123F' or '0x00,0x12,0x3F').")
    parser.add_argument("-o", "--output", help="Path to write the disassembled text file to. (Default: stdout)")
    parser.add_argument("-m", "--mode", choices=['group', 'subtrack', 'note'], default='group',
                        help="Initial disassembly mode (default: group). For full sequences starting at offset 0, "
                             "mode is auto-detected as 'group' and transitions are tracked automatically. "
                             "This parameter is only used when analyzing partial sections not starting at offset 0.")
    parser.add_argument("--addr-base", dest="addr_base", default=None,
                        help="Optional base address (hex like 0x500 or decimal) to add to output addresses.")

    args = parser.parse_args()

    # Load data from either raw bytes or file
    data = None
    if args.raw_bytes is not None:
        raw = args.raw_bytes
        bytes_out = bytearray()
        # Support a textual .db listing format like: "/* 0517 */  .db 0xEB" per line
        if '.db' in raw:
            import re as _re
            # Extract all .db byte values in order of appearance
            # Matches: .db 0xNN or .db NN
            pattern = _re.compile(r"\.db\s+0x([0-9A-Fa-f]{1,2})|\.db\s+([0-9A-Fa-f]{1,2})")
            found = pattern.findall(raw)
            if not found:
                print("Error: could not parse any .db bytes from provided text")
                return
            for a, b in found:
                hh = a or b
                try:
                    val = int(hh, 16)
                except ValueError:
                    print(f"Error: invalid .db byte '{hh}'")
                    return
                if not (0 <= val <= 0xFF):
                    print(f"Error: .db byte out of range (0-255): {val}")
                    return
                bytes_out.append(val)
            data = bytes(bytes_out)
        else:
            # Normalize incoming string: remove 0x prefixes, commas, underscores, newlines, and spaces
            tokens = (
                raw.replace(',', ' ').replace('\n', ' ').replace('\r', ' ').replace('_', ' ').split()
            )
            # If the entire string has no spaces and even length, treat as continuous hex
            if len(tokens) == 1 and all(c in '0123456789abcdefABCDEFxX' for c in tokens[0]):
                t = tokens[0]
                if t.startswith('0x') or t.startswith('0X'):
                    t = t[2:]
                if len(t) % 2 != 0:
                    print("Error: raw-bytes hex string must have even length")
                    return
                try:
                    bytes_out.extend(bytes.fromhex(t))
                except ValueError:
                    print("Error: failed to parse raw-bytes hex string")
                    return
            else:
                # Parse each token as a byte (supports '0xNN' or 'NN')
                for tok in tokens:
                    tt = tok
                    if tt.startswith('0x') or tt.startswith('0X'):
                        tt = tt[2:]
                    try:
                        val = int(tt, 16)
                    except ValueError:
                        print(f"Error: invalid byte token '{tok}' in --raw-bytes")
                        return
                    if not (0 <= val <= 0xFF):
                        print(f"Error: byte value out of range (0-255): {val}")
                        return
                    bytes_out.append(val)
            data = bytes(bytes_out)
    else:
        if not args.input_file:
            print("Error: either provide an input_file or --raw-bytes")
            return
        try:
            with open(args.input_file, "rb") as f:
                data = f.read()
        except FileNotFoundError as e:
            print(f"Error: File not found - {e.filename}")
            return

    # Run the disassembler
    # For full sequences (starting at offset 0), mode is always "group" and auto-detected
    # The mode parameter is only relevant when analyzing partial sections
    disassembler = MMLDisassembler(data, args.mode)
    # Apply address base if provided
    if args.addr_base is not None:
        try:
            if isinstance(args.addr_base, str) and args.addr_base.lower().startswith('0x'):
                disassembler.address_base = int(args.addr_base, 16)
            else:
                disassembler.address_base = int(args.addr_base, 10)
        except ValueError:
            print("Error: invalid --addr-base value; expected hex (0x...) or decimal integer")
            return
    disassembler.analysis_pass()
    output_lines = disassembler.disassembly_pass()
    
    output_str = "\n".join(output_lines)

    if args.output:
        try:
            with open(args.output, "w") as f:
                f.write(output_str)
            print(f"Disassembly complete. Output written to {args.output}")
        except IOError:
            print(f"Error: Could not write to output file {args.output}")
    else:
        print(output_str)

if __name__ == "__main__":
    main()
