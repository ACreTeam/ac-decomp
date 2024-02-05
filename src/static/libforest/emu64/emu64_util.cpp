#include "emu64.hpp"

const char* emu64::combine_name(u32 param, u32 type) {
    switch (param) {
        case 0:
            return "COMBINED";
        case 1:
            return "TEXEL0";
        case 2:
            return "TEXEL1";
        case 3:
            return "PRIMITIVE";
        case 4:
            return "SHADE";
        case 5:
            return "ENVIRONMENT";
        case 6:
            if (type == COMBINER_PARAM_B) {
                return "CENTER";
            } else if (type == COMBINER_PARAM_C) {
                return "SCALE";
            } else {
                return "1";
            }
        case 7:
            if (type == COMBINER_PARAM_A) {
                return "NOISE";
            } else if (type == COMBINER_PARAM_B) {
                return "K4";
            } else if (type == COMBINER_PARAM_C) {
                return "COMBINED_ALPHA";
            } else {
                return "0";
            }
    }

    if (type != COMBINER_PARAM_C) {
        return "0";
    }

    switch (param) {
        case 8:
            return "TEXEL0_ALPHA";
        case 9:
            return "TEXEL1_ALPHA";
        case 10:
            return "PRIMITIVE_ALPHA";
        case 11:
            return "SHADE_ALPHA";
        case 12:
            return "ENV_ALPHA";
        case 13:
            return "LOD_FRACTION";
        case 14:
            return "PRIM_LOD_FRAC";
        case 15:
            return "K5";
        default:
            return "0";
    }
}

const char* emu64::combine_alpha(int param, int type) {
    switch (param) {
        case 0:
            return type == COMBINER_PARAM_C ? "LOD_FRACTION" : "COMBINED";
        case 1:
            return "TEXEL0";
        case 2:
            return "TEXEL1";
        case 3:
            return "PRIMITIVE";
        case 4:
            return "SHADE";
        case 5:
            return "ENVIRONMENT";
        case 6:
            return type == COMBINER_PARAM_C ? "PRIM_LOD_FRAC" : "1";
        case 7:
            return "0";
    }

/* There should be a default case here, but they forgot it. */
/* It returns a pointer to the emu64 class instead. */
#ifdef EMU64_FIX_COMBINE_NAME_RETURN_VALUES
    return "0";
#endif
}

void emu64::print_combine(u64 combine) {
    Gsetcombine_new* setcombine = (Gsetcombine_new*)&combine;
    this->Printf0(
        "gsDPSetCombineLERP(%s,%s,%s,%s, %s,%s,%s,%s, %s,%s,%s,%s, %s,%s,%s,%s),",
        this->combine_name(setcombine->a0, COMBINER_PARAM_A), this->combine_name(setcombine->b0, COMBINER_PARAM_B),
        this->combine_name(setcombine->c0, COMBINER_PARAM_C), this->combine_name(setcombine->d0, COMBINER_PARAM_D),

        this->combine_alpha(setcombine->Aa0, COMBINER_PARAM_A), this->combine_alpha(setcombine->Ab0, COMBINER_PARAM_B),
        this->combine_alpha(setcombine->Ac0, COMBINER_PARAM_C), this->combine_alpha(setcombine->Ad0, COMBINER_PARAM_D),

        this->combine_name(setcombine->a1, COMBINER_PARAM_A), this->combine_name(setcombine->b1, COMBINER_PARAM_B),
        this->combine_name(setcombine->c1, COMBINER_PARAM_C), this->combine_name(setcombine->d1, COMBINER_PARAM_D),

        this->combine_alpha(setcombine->Aa1, COMBINER_PARAM_A), this->combine_alpha(setcombine->Ab1, COMBINER_PARAM_B),
        this->combine_alpha(setcombine->Ac1, COMBINER_PARAM_C), this->combine_alpha(setcombine->Ad1, COMBINER_PARAM_D));
}
