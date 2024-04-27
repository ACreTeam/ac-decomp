#include "m_submenu_ovl.h"

#include "m_font.h"
#include "m_play.h"
#include "m_trademark.h"
#include "m_rcp.h"
#include "libultra/libultra.h"
#include "sys_matrix.h"

static void mSM_setup_view(Submenu* submenu, GRAPH* graph, int init_flag) {
    Gfx* gfx;
    Mtx* mtx;
    View* view;

    if (init_flag) {
        mtx = GRAPH_ALLOC_TYPE(graph, Mtx, 1);
        mFont_CulcOrthoMatrix(mtx);
        submenu->overlay->projection_matrix = mtx;
    } else {
        mtx = submenu->overlay->projection_matrix;
    }

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    if (init_flag == FALSE) {
        if (submenu->mode != 4) {
            view = &((GAME_PLAY*)gamePT)->view;
        } else {
            view = &((GAME_TRADEMARK*)gamePT)->view; // I'm not sure this is the correct game subclass
        }

        gDPPipeSync(gfx++);
        gDPSetScissor(gfx++, G_SC_NON_INTERLACE, view->screen.l, view->screen.top, view->screen.r, view->screen.bottom);
        gSPViewport(gfx++, &view->viewport);
        gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    }

    gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mSM_change_view(GRAPH* graph, s16 angle, int width, int height, f32 eye_dist, f32 y_lookAt, f32 vp_x,
                            f32 vp_y) {
    static Vp viewport_data = { { 0, 0, 511, 0 }, { 0, 0, 511, 0 } };

    static Lights0 light_data = {
        { { 105, 90, 90 }, 0, { 105, 90, 90 }, 0 },                          // Ambient
        { { { 255, 255, 245 }, 0, { 255, 255, 245 }, 0, { 0, 60, 60 }, 0 } } // Light
    };

    Vp* viewport = GRAPH_ALLOC_TYPE(graph, Vp, 1);
    Mtx* mtx = GRAPH_ALLOC_TYPE(graph, mtx, 1);
    u16 persp_norm;
    f32 y_eye;
    f32 z_eye;

    if (viewport == NULL) {
        viewport = &viewport_data;
    } else {
        viewport->vp.vscale[0] = width << 1;
        viewport->vp.vtrans[0] = (width << 1) + (s16)vp_x;

        viewport->vp.vscale[1] = height << 1;
        viewport->vp.vtrans[1] = (height << 1) + (s16)vp_y;

        viewport->vp.vscale[2] = 511;
        viewport->vp.vtrans[2] = 511;

        viewport->vp.vscale[3] = 0;
        viewport->vp.vtrans[3] = 0;
    }

    OPEN_DISP(graph);

    gSPViewport(NOW_POLY_OPA_DISP++, viewport);

    CLOSE_DISP(graph);

    if (width != 256) {
        guPerspective(mtx, &persp_norm, 35.0f, (f32)width / (f32)height, 1.0f, 2000.0f, 1.0f);
    } else {
        guPerspective(mtx, &persp_norm, 20.0f, (f32)width / (f32)height, 100.0f, 800.0f, 1.0f);
    }

    OPEN_DISP(graph);

    gSPPerspNormalize(NOW_POLY_OPA_DISP++, persp_norm);
    gSPMatrix(NOW_POLY_OPA_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    CLOSE_DISP(graph);

    if (angle == DEG2SHORT_ANGLE(90.0f)) {
        angle = 0x4100;
    } else if (angle == DEG2SHORT_ANGLE(-90.0f)) {
        angle = -0x3F00;
    }

    y_eye = y_lookAt + eye_dist * sin_s(angle);
    z_eye = eye_dist * cos_s(angle);

    if (angle < DEG2SHORT_ANGLE(-90.0f) || angle > DEG2SHORT_ANGLE(90.0f)) {
        guLookAt(mtx, 0.0f, y_eye, z_eye, 0.0f, y_lookAt, 0.0f, 0.0f, -1.0f, 0.0f);
    } else {
        guLookAt(mtx, 0.0f, y_eye, z_eye, 0.0f, y_lookAt, 0.0f, 0.0f, 1.0f, 0.0f);
    }

    OPEN_DISP(graph);

    gSPMatrix(NOW_POLY_OPA_DISP++, mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    gSPSetLights0(NOW_POLY_OPA_DISP++, light_data);
    SET_POLY_OPA_DISP(gfx_set_fog_nosync(NOW_POLY_OPA_DISP++, 255, 255, 255, 255, 1000, 1000));

    CLOSE_DISP(graph);
}

static void mSM_set_char_matrix(GRAPH* graph) {
    OPEN_DISP(graph);
    gSPMatrix(NOW_POLY_OPA_DISP++, &Mtx_clear, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    CLOSE_DISP(graph);
}

static void mSM_cbuf_copy(GRAPH* graph, PreRender* prerender, int x, int y, int mode) {
    if (x < (640 - 1)) {
        u32 width = prerender->width_bak;

        if (x > -width) {
            int height = prerender->height_bak;

            if (y > -height && y < (480 - 1)) {
                int x_max;
                int x_min;
                int y_max;
                int y_min;
                u8* color_img_buf;
                u8* texture_img_buf;
                u32 w;
                u32 h;
                u32 tmem_line;
                u32 uls;
                u32 ult;
                u32 lrs;
                u32 lrt;
                u32 width2;
                u32 height2;
                u32 lrt2;

                if (x < 0) {
                    x_max = width + x;
                    x_min = -x;
                    x = 0;
                } else {
                    x_min = 0;

                    if (x + width >= 640) {
                        x_max = 640 - x;
                    } else {
                        x_max = width;
                    }
                }

                if (y < 0) {
                    y_max = height + y;
                    y_min = -y;
                    y = 0;
                } else {
                    y_min = 0;

                    if (y + height >= 480) {
                        y_max = (480 - 1) - y;
                    } else {
                        y_max = height;
                    }
                }

                if (mode == 0) {
                    color_img_buf = prerender->framebuffer_bak;
                    w = width;
                    height = height;
                    uls = x;
                    ult = y;
                    lrt = y_min;
                    lrs = x_min;
                    width2 = 640;
                    height2 = 480;
                } else {
                    texture_img_buf = prerender->framebuffer_bak;
                    w = 640;
                    h = 480;
                    uls = x_min;
                    ult = y_min;
                    lrs = x;
                    lrt = y;
                    width2 = width;
                    height2 = height;
                }

                // TODO: finish
                tmem_line = (1 << 12) / (u32)((x_max + 3) << 1);
                lrt2 = (x_max + uls) - 1;
                if (mode) {
                    Gfx* gfx;

                    OPEN_DISP(graph);

                    gfx = NOW_POLY_OPA_DISP;
                    prerender->width = 640;
                    prerender->height = 480;
                    PreRender_CopyRGBC(prerender, &gfx, x - x_min, y - y_min);
                    SET_POLY_OPA_DISP(gfx);

                    CLOSE_DISP(graph);
                } else {
                    OPEN_DISP(graph);

                    gDPPipeSync(NOW_POLY_OPA_DISP++);
                    gSPClearGeometryMode(NOW_POLY_OPA_DISP++, 0xFFFFFF);
                    gDPSetOtherMode(NOW_POLY_OPA_DISP++,
                                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE |
                                        G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_COPY | G_PM_NPRIMITIVE,
                                    G_AC_NONE | G_ZS_PRIM | G_RM_NOOP | G_RM_NOOP2);
                    gDPSetColorImage(NOW_POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, color_img_buf);
                    gDPSetScissor(NOW_POLY_OPA_DISP++, G_SC_NON_INTERLACE, 0, 0, width, height);

                    while (y_max > 0) {
                        if (tmem_line > y_max) {
                            tmem_line = y_max;
                        }

                        gDPLoadTextureTile(NEXT_POLY_OPA_DISP, texture_img_buf, G_IM_FMT_RGBA, G_IM_SIZ_16b, width2,
                                           height2, uls, ult, lrt2, (ult + tmem_line - 1), 0, G_TX_NOMIRROR | G_TX_WRAP,
                                           G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);

                        gSPTextureRectangle(NEXT_POLY_OPA_DISP, (lrs) * 4, (lrt) << G_TEXTURE_IMAGE_FRAC,
                                            (lrs + (x_max - 1)) << G_TEXTURE_IMAGE_FRAC,
                                            (lrt + (tmem_line - 1)) << G_TEXTURE_IMAGE_FRAC, G_TX_RENDERTILE, uls << 5,
                                            ult << 5, (1 << 1) << 10, 1 << 10);

                        y_max -= tmem_line;
                        ult += tmem_line;
                        lrt += tmem_line;
                    }

                    CLOSE_DISP(graph);
                }
            }
        }
    }

    // gDPPipeSync(NOW_POLY_OPA_DISP++)
    // gSPClearGeometryMode(NOW_POLY_OPA_DISP++, 0xFFFFFF)
    // gDPSetOtherMode(NOW_POLY_OPA_DISP++, G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP |
    // G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_COPY | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PRIM | G_RM_NOOP
    // | G_RM_NOOP2) gDPSetColorImage(NOW_POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, color_image_buf);
    // gDPSetScissor(NOW_POLY_OPA_DISP++, G_SC_NON_INTERLACE, 0, 0, width, height);

    // LOOP
    // [gDPLoadTextureTile]
    // gDPSetTextureImage(NOW_POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, some_width, texture_img_buf);
    // gDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
    // G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD) gDPLoadSync() gDPLoadTile(G_TX_LOADTILE, ...)
    // gDPPipeSync()
    // gDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
    // G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD) gDPSetTileSize(G_TX_RENDERTILE, ...)
    //
    // [gSPTextureRectangle]
    // gTexRect(..., G_TX_RENDERTILE)
    // gDPHalf1(...)
    // gDPHalf2(...)
}

static void mSM_set_drawMode(GRAPH* graph, PreRender* prerender, f32 dist, f32 height, s16 angle) {
    // TODO
}

static int mSM_get_groupNo(mActor_name_t item) {
    return ITEM_NAME_GET_INDEX(item);
}

typedef struct inventory_icon_info_s {
    u16* pal;
    u8* tex;
} mSM_inventory_icon_info_c;

static void mSM_set_dl_item(GRAPH* graph, f32 x, f32 y, f32 scale, mSM_inventory_icon_info_c* icon_info, u16* palette,
                            u8 l, rgba_t* color, int draw_shadow, int draw_mark) {
    // TODO
}
