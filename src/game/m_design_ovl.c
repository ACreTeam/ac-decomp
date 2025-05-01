#include "m_design_ovl.h"

#include "m_debug.h"
#include "padmgr.h"

#define mDE_POS_MIN 0
#define mDE_POS_MAX 31
#define mDE_DESIGN_TEXELS (mNW_ORIGINAL_DESIGN_WIDTH * mNW_ORIGINAL_DESIGN_HEIGHT)

#define mDE_POS2TEXEL(x, y) ((((x) & 7) + ((y) & 7) * 8 + ((((x) & 0x18) >> 3) + (((y) & 0x18) >> 3) * 4) * 0x40) >> 1)

enum {
    mDE_MOVE_DIR_UP,
    mDE_MOVE_DIR_DOWN,
    mDE_MOVE_DIR_LEFT,
    mDE_MOVE_DIR_RIGHT,

    mDE_MOVE_DIR_NUM
};

enum {
    mDE_MAIN_MODE_0,
};

static void mDE_pallet_RGB5A3_to_RGB24(mDE_Ovl_c* design_ovl) {
    int i;

    for (i = 0; i < mNW_PALETTE_COUNT; i++) {
        u16 color = design_ovl->palette_p[i];

        if (color & 0x8000) {
            // fully opaque, a1r5g5b5
            design_ovl->rgb8_pal[i].r = (((color >> 10) & 0x1F) * 255) / 31;
            design_ovl->rgb8_pal[i].g = (((color >>  5) & 0x1F) * 255) / 31;
            design_ovl->rgb8_pal[i].b = (((color >>  0) & 0x1F) * 255) / 31;
        } else {
            // transparent color, a3r4g4b4
            design_ovl->rgb8_pal[i].r = ((color >> 8) & 0xF) * 17;
            design_ovl->rgb8_pal[i].g = ((color >> 4) & 0xF) * 17;
            design_ovl->rgb8_pal[i].b = ((color >> 0) & 0xF) * 17;
        }
    }
}

static int mDE_judge_stick(mDE_Ovl_c* design_ovl) {
    design_ovl->_6B8++;
    if (design_ovl->move_pR >= 0.1f && design_ovl->_6B5 == 0) {
        design_ovl->_6B5 = 1;
        design_ovl->_6B8 = 0;
        return TRUE;
    }

    if (design_ovl->move_pR > 0.9f && design_ovl->_6C0 >= design_ovl->_6C4 && design_ovl->_6B5 && design_ovl->_6B8 > design_ovl->_6BC) {
        design_ovl->_6B8 = 0;
        return TRUE;
    }

    if (design_ovl->_6B8 > design_ovl->_6BC) {
        design_ovl->_6B8 = 0;
    }

    return FALSE;
}

static int mDE_judge_stick_full(mDE_Ovl_c* design_ovl) {
    if (design_ovl->move_pR >= 0.9f) {
        design_ovl->_6C0++;
        if (design_ovl->_6C0 > design_ovl->_6C4) {
            design_ovl->_6C0 = design_ovl->_6C4;
        }

        return TRUE;
    }

    return FALSE;
}

static int mDE_judge_stick_nuetral(mDE_Ovl_c* design_ovl) {
    if (design_ovl->move_pR < 0.1f) {
        design_ovl->_6C0 = 0;
        design_ovl->_6B4 = 0;
        design_ovl->_6B5 = 0;
        return TRUE;
    }

    design_ovl->_6B4 = 1;
    return FALSE;
}

static int mDE_cursor_move_check(mDE_Ovl_c* design_ovl, int move_dir) {
    int min = 0;

    if (design_ovl->main_mode_act == mDE_MAIN_MODE_0) {
        switch (design_ovl->_6A0) {
            case 1:
                min = 1;
                break;
            case 2:
                min = 2;
                break;
        }
    }

    switch (move_dir) {
        case mDE_MOVE_DIR_UP:
            if (gamePT->pads[PAD0].now.stick_y > 0 && design_ovl->cursor_y > min) {
                return TRUE;
            }
            break;
        case mDE_MOVE_DIR_DOWN:
            if (gamePT->pads[PAD0].now.stick_y < 0 && design_ovl->cursor_y < mDE_POS_MAX) {
                return TRUE;
            }
            break;
        case mDE_MOVE_DIR_LEFT:
            if (gamePT->pads[PAD0].now.stick_x < 0 && design_ovl->cursor_x > 0) {
                return TRUE;
            }
            break;
        case mDE_MOVE_DIR_RIGHT:
            if (gamePT->pads[PAD0].now.stick_x > 0 && design_ovl->cursor_x < (mDE_POS_MAX - min)) {
                return TRUE;
            }
            break;
    }

    return FALSE;
}

static void mDE_cursor_move(mDE_Ovl_c* design_ovl, int move_dir) {
    switch (move_dir) {
        case mDE_MOVE_DIR_UP:
            design_ovl->cursor_y--;
            design_ovl->_654 += 5;
            break;
        case mDE_MOVE_DIR_DOWN:
            design_ovl->cursor_y++;
            design_ovl->_654 -= 5;
            break;
        case mDE_MOVE_DIR_LEFT:
            design_ovl->cursor_x--;
            design_ovl->_650 -= 5;
            break;
        case mDE_MOVE_DIR_RIGHT:
            design_ovl->cursor_x++;
            design_ovl->_650 += 5;
            break;
    }
}

static void mDE_cursor_analog_move_hosei(f32* move_x, f32* move_y, f32 corrected_val, f32 min, f32 max) {
    if (*move_y > min && *move_y < max) {
        *move_y = corrected_val;
    }

    if (*move_y > -max && *move_y < -min) {
        *move_y = -corrected_val;
    }

    if (*move_x > min && *move_x < max) {
        *move_x = corrected_val;
    }

    if (*move_x > -max && *move_x < -min) {
        *move_x = -corrected_val;
    }
}

static void mDE_cursor_analog_move(mDE_Ovl_c* design_ovl) {
    int bounds = 0;
    f32 move_x;
    f32 move_y;
    int _660;
    int _664;
    int x;
    int y;

    if (design_ovl->main_mode_act == mDE_MAIN_MODE_0) {
        switch (design_ovl->_6A0) {
            case 1:
                bounds = 1;
                break;
            case 2:
                bounds = 2;
                break;
        }
    }
    
    _660 = (int)(design_ovl->_660 / 5.0f);
    _664 = -(int)(design_ovl->_664 / 5.0f);
    move_x = gamePT->pads[PAD0].now.stick_x / 72.0f;
    move_y = gamePT->pads[PAD0].now.stick_y / 72.0f;
    // _664 = -_664;

    if (!GETREG(NMREG, 16)) {
        mDE_cursor_analog_move_hosei(&move_x, &move_y, 0.5f, 0.44f, 0.56f);
        mDE_cursor_analog_move_hosei(&move_x, &move_y, 0.75f, 0.725f, 0.775f);
        mDE_cursor_analog_move_hosei(&move_x, &move_y, 0.25f, 0.225f, 0.275f);
        mDE_cursor_analog_move_hosei(&move_x, &move_y, 0.8f, 0.775f, 0.825f);
        mDE_cursor_analog_move_hosei(&move_x, &move_y, 0.2f, 0.175f, 0.225f);
    }

    if (gamePT->pads[PAD0].now.stick_y != 0) {
        move_x *= 10.0f;
    } else {
        move_x *= 5.0f;
    }

    if (gamePT->pads[PAD0].now.stick_x != 0) {
        move_y *= 10.0f;
    } else {
        move_y *= 5.0f;
    }

    if (_664 < bounds) {
        design_ovl->cursor_y = bounds;
        design_ovl->_654 = -design_ovl->cursor_y * 5;
    } else if (_664 > mDE_POS_MAX) {
        design_ovl->cursor_y = mDE_POS_MAX;
        design_ovl->_654 = -design_ovl->cursor_y * 5;
    }

    if (_660 < 0) {
        design_ovl->cursor_x = 0;
        design_ovl->_650 = design_ovl->cursor_x * 5;
    } else if (_660 > (mDE_POS_MAX - bounds)) {
        design_ovl->cursor_x = mDE_POS_MAX - bounds;
        design_ovl->_650 = design_ovl->cursor_x * 5;
    }

    y = gamePT->pads[PAD0].now.stick_y;
    if ((y > 0 && design_ovl->cursor_y > bounds) ||
        (y < 0 && design_ovl->cursor_y < mDE_POS_MAX)) {
        if (GETREG(NMREG, 19)) {
            if (GETREG(NMREG, 18)) {
                design_ovl->_664 += gamePT->pads[PAD0].now.stick_y * (10.0f / 72.0f);
            } else if (GETREG(NMREG, 17)) {
                design_ovl->_664 += gamePT->pads[PAD0].now.stick_y * (5.0f / 72.0f);
            } else {
                design_ovl->_664 += gamePT->pads[PAD0].now.stick_y * ((1.0f + GETREG(NMREG, 20) * 0.1f) / 72.0f);
            }
        } else {
            design_ovl->_664 += move_y;
        }
    }

    x = gamePT->pads[PAD0].now.stick_x;
    if ((x < 0 && design_ovl->cursor_x > 0) ||
        (x > 0 && design_ovl->cursor_x < (mDE_POS_MAX - bounds))) {
        if (GETREG(NMREG, 19)) {
            if (GETREG(NMREG, 18)) {
                design_ovl->_660 += gamePT->pads[PAD0].now.stick_x * (10.0f / 72.0f);
            } else if (GETREG(NMREG, 17)) {
                design_ovl->_660 += gamePT->pads[PAD0].now.stick_x * (5.0f / 72.0f);
            } else {
                design_ovl->_660 += gamePT->pads[PAD0].now.stick_x * ((1.0f + GETREG(NMREG, 20) * 0.1f) / 72.0f);
            }
        } else {
            design_ovl->_660 += move_x;
        }
    }
}

static int mDE_cursor_waku_genten_rotate(mDE_Ovl_c* design_ovl, int move_dir) {
    if (design_ovl->cursor_y == design_ovl->_67C && design_ovl->cursor_x == design_ovl->_678) {
        switch (move_dir) {
            case 4:
                if (design_ovl->_6D9 == 2) {
                    design_ovl->_6D8 = 1;
                    return TRUE;
                }
                break;
            case 5:
                if (design_ovl->_6D9 == 3) {
                    design_ovl->_6D8 = 0;
                    return TRUE;
                }
                break;
            case 6:
                if (design_ovl->_6D9 == 0) {
                    design_ovl->_6D8 = 3;
                    return TRUE;
                }
                break;
            case 7:
                if (design_ovl->_6D9 == 1) {
                    design_ovl->_6D8 = 2;
                    return TRUE;
                }
                break;
        }
    }

    return FALSE;
}

static int mDE_cursor_waku_rotate(mDE_Ovl_c* design_ovl, int move_dir) {
    switch (move_dir) {
        case mDE_MOVE_DIR_UP:
            if (design_ovl->cursor_y == design_ovl->_67C && (design_ovl->_6D8 == 0 || design_ovl->_6D8 == 2)) {
                switch (design_ovl->_6D9) {
                    case 0:
                        design_ovl->_6D8 = 1;
                        break;
                    case 2:
                        design_ovl->_6D8 = 3;
                        break;
                }

                return TRUE;
            }
            break;
        case mDE_MOVE_DIR_DOWN:
            if (design_ovl->cursor_y == design_ovl->_67C && (design_ovl->_6D8 == 1 || design_ovl->_6D8 == 3)) {
                switch (design_ovl->_6D9) {
                    case 1:
                        design_ovl->_6D8 = 0;
                        break;
                    case 3:
                        design_ovl->_6D8 = 2;
                        break;
                }

                return TRUE;
            }
            break;
        case mDE_MOVE_DIR_LEFT:
            if (design_ovl->cursor_x == design_ovl->_678 && (design_ovl->_6D8 == 1 || design_ovl->_6D8 == 0)) {
                switch (design_ovl->_6D9) {
                    case 1:
                        design_ovl->_6D8 = 3;
                        break;
                    case 0:
                        design_ovl->_6D8 = 2;
                        break;
                }

                return TRUE;
            }
            break;
        case mDE_MOVE_DIR_RIGHT:
            if (design_ovl->cursor_x == design_ovl->_678 && (design_ovl->_6D8 == 3 || design_ovl->_6D8 == 2)) {
                switch (design_ovl->_6D9) {
                    case 3:
                        design_ovl->_6D8 = 1;
                        break;
                    case 2:
                        design_ovl->_6D8 = 0;
                        break;
                }

                return TRUE;
            }
            break;
    }

    return FALSE;
}

static int mDE_get_pal_on_cursor(mDE_Ovl_c* design_ovl, int x, int y) {
    int idx;

    if (x < mDE_POS_MIN || x > mDE_POS_MAX || y < mDE_POS_MIN || y > mDE_POS_MAX) {
        return 0;
    }

    idx = mDE_POS2TEXEL(x, y);
    if (x & 1) {
        return (design_ovl->work_texture.data[idx] >> 0) & 0x0F;
    } else {
        return (design_ovl->work_texture.data[idx] >> 4) & 0x0F;
    }
}

static void mDE_set_pal_on_cursor(mDE_Ovl_c* design_ovl, int x, int y, int pal) {
    int idx;
    
    if (x < mDE_POS_MIN || x > mDE_POS_MAX || y < mDE_POS_MIN || y > mDE_POS_MAX) {
        return;
    }

    idx = mDE_POS2TEXEL(x, y);
    if (x & 1) {
        design_ovl->work_texture.data[idx] &= 0xF0;
        design_ovl->work_texture.data[idx] |= (pal << 0);
    } else {
        design_ovl->work_texture.data[idx] &= 0x0F;
        design_ovl->work_texture.data[idx] |= (pal << 4);
    }
}

typedef struct design_bounds_s {
    int x0;
    int x1;
    int y0;
    int y1;
} mDE_bounds_c;

static void mDE_farbado(mDE_Ovl_c* design_ovl, int x, int y, int pal) {
    mDE_bounds_c pos_tbl[mDE_DESIGN_TEXELS];
    int i = 1;
    int j = 0;
    int k;
    int cur_pal;
    int chk_pal;

    pos_tbl[0].x0 = x;
    pos_tbl[0].x1 = x;
    pos_tbl[0].y0 = y;
    pos_tbl[0].y1 = y;
    cur_pal = mDE_get_pal_on_cursor(design_ovl, x, y);

    while (TRUE) {
        mDE_bounds_c* bounds = &pos_tbl[j++];
        int x0 = bounds->x0;
        int x1 = bounds->x1;
        int y0 = bounds->y0;
        int y1 = bounds->y1;
        int left = x0 - 1;
        int right = x1 + 1;
        int up;
        int down;
        
        if (j == mDE_DESIGN_TEXELS) {
            j = 0;
        }

        chk_pal = mDE_get_pal_on_cursor(design_ovl, x0, y0);
        if (chk_pal != pal) {
            while (x1 <= mDE_POS_MAX) {
                x1++;
                chk_pal = mDE_get_pal_on_cursor(design_ovl, x1, y0);
                if (chk_pal != cur_pal) {
                    break;
                }
            }

            while (x0 > 0) {
                x0--;
                chk_pal = mDE_get_pal_on_cursor(design_ovl, x0, y0);
                if (chk_pal != cur_pal) {
                    break;
                }
            }

            for (k = x0; k <= x1; k++) {
                mDE_set_pal_on_cursor(design_ovl, k, y0, pal);
            }

            y0--;
            if (y0 >= mDE_POS_MIN) {
                if (y0 == y1) {
                    while (x0 <= left) {
                        while (x0 < left) {
                            if (cur_pal == mDE_get_pal_on_cursor(design_ovl, x0, y0)) {
                                break;
                            }

                            x0++;
                        }

                        if (cur_pal != mDE_get_pal_on_cursor(design_ovl, x0, y0)) {
                            break;
                        }

                        bounds = &pos_tbl[i];
                        bounds->x0 = x0;
                        while (x0 <= left) {
                            if (cur_pal != mDE_get_pal_on_cursor(design_ovl, x0, y0)) {
                                break;
                            }

                            x0++;
                        }
                        i++;
                        bounds->x1 = x0 - 1;
                        bounds->y0 = y0;
                        bounds->y1 = y1;

                        if (i == mDE_DESIGN_TEXELS) {
                            i = 0;
                        }
                    }
                }
            }

            down = y0 + 1;
            k = right;
            while (k <= x1) {
                while (k < x1) {
                    if (cur_pal != mDE_get_pal_on_cursor(design_ovl, k, y0)) {
                        break;
                    }

                    k++;
                }

                if (cur_pal != mDE_get_pal_on_cursor(design_ovl, k, y0)) {
                    break;
                }

                bounds = &pos_tbl[i];
                bounds->x0 = k;
                while (k <= x1) {
                    if (cur_pal != mDE_get_pal_on_cursor(design_ovl, k, y0)) {
                        break;
                    }

                    k++;
                }
                i++;
                bounds->x1 = k - 1;
                bounds->y0 = y0;
                bounds->y1 = y1;

                if (i == mDE_DESIGN_TEXELS) {
                    i = 0;
                }
            }

            down = y0 + 1;
        }
        
        if (j == i) {
            break;
        }
    }

    // TODO: finish
}
