#include "player_select.h"

#include "m_field_info.h"
#include "m_start_data_init.h"
#include "m_controller.h"
#include "m_select.h"
#include "m_font.h"
#include "m_lib.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_flashrom.h"
#include "m_common_data.h"

/* ' みとうろく' (Unregisterd) */
static u8 mitouroku_str[6] = { 0x20, 0x1F, 0x13, 0x02, 0xC0, 0x07 };

/* '<がいしゅつちゅう>' (<Away>) */
static u8 l_gaishutu_str[10] = { 0x3C, 0xE7, 0x01, 0x0B, 0xCA, 0x11, 0x10, 0xCA, 0x02, 0x3E };

/* '<ざいたくちゅう>' (<Home>) */
static u8 l_zaitaku_str[9] = { 0x3C, 0xEC, 0x01, 0x0F, 0x07, 0x10, 0xCA, 0x02, 0x3E };

/* 'よそからあそびにきた' (Came from another place) */
static u8 l_yosokara_str[10] = { 0x60, 0x0E, 0x05, 0x7B, 0x00, 0x0E, 0xF7, 0x15, 0x06, 0x0F };

static void player_select_game_data_init(GAME_PLAYER_SELECT* player_select) {
  int player_no = player_select->player_no;
  mFI_ClearFieldData();
  if (mSDI_StartInitBefore((GAME*)player_select, player_no, mSDI_INIT_MODE_NEW, mSDI_MALLOC_FLAG_GAME) == TRUE) {
    player_select->err_no = PLAYER_SELECT_INIT_ERR_SUCCESS;
  }
}

static void player_select_game_data_init_save(GAME_PLAYER_SELECT* player_select) {
  if (mSDI_StartInitBefore((GAME*)player_select, player_select->player_no, mSDI_INIT_MODE_FROM, mSDI_MALLOC_FLAG_GAME) == TRUE) {
    player_select->err_no = PLAYER_SELECT_INIT_ERR_SUCCESS;
  }
  else {
    player_select->err_no = PLAYER_SELECT_INIT_ERR_SAVE;
  }
}

static void player_select_game_data_init_new_player(GAME_PLAYER_SELECT* player_select) {
  if (mSDI_StartInitBefore((GAME*)player_select, player_select->player_no, mSDI_INIT_MODE_NEW_PLAYER, mSDI_MALLOC_FLAG_GAME) == TRUE) {
    player_select->err_no = PLAYER_SELECT_INIT_ERR_SUCCESS;
  }
  else {
    player_select->err_no = PLAYER_SELECT_INIT_ERR_SAVE;
  }
}

static void player_select_game_data_init_pak(GAME_PLAYER_SELECT* player_select) {
  if (mSDI_StartInitBefore((GAME*)player_select, player_select->player_no, mSDI_INIT_MODE_PAK, mSDI_MALLOC_FLAG_GAME) == TRUE) {
    player_select->err_no = PLAYER_SELECT_INIT_ERR_SUCCESS;
  }
  else {
    player_select->err_no = PLAYER_SELECT_INIT_ERR_PAK;
  }
}

static void player_select_game_data_init_err(GAME_PLAYER_SELECT* player_select) {
  player_select->mode = PLAYER_SELECT_MODE_SELECTION;
}

static PLAYER_SELECT_INIT_PROC l_init_proc[mSDI_INIT_MODE_NUM] = {
  &player_select_game_data_init,
  &player_select_game_data_init_new_player,
  &player_select_game_data_init_save,
  &player_select_game_data_init_pak,
  &player_select_game_data_init_err
};

static void player_select_init_after(GAME_PLAYER_SELECT* player_select) {
  mSDI_StartInitAfter((GAME*)player_select, FALSE, mSDI_MALLOC_FLAG_GAME);
}

static void player_select_next_mode(int* mode, int max) {
  (*mode)++;
  if (*mode >= max) {
    *mode = 0;
  }
}

static void player_select_back_mode(int* mode, int max) {
  (*mode)--;
  if (*mode < 0) {
    *mode = max - 1;
  }
}

static void player_select_move_main(GAME_PLAYER_SELECT* player_select) {
  int mode = player_select->mode;

  if (player_select->err_no == PLAYER_SELECT_INIT_ERR_NONE) {
    if (chkTrigger(BUTTON_A)) {
      int player_no = player_select->player_no;
      if (mode == PLAYER_SELECT_MODE_SELECTION) {
        player_select->mode = PLAYER_SELECT_MODE_PLAY;
      }

      if (player_select->mode == PLAYER_SELECT_MODE_PLAY) {
        (*player_select->init_procs[player_no])(player_select);
      }
    }

    if (chkTrigger(BUTTON_DDOWN) && player_select->mode == PLAYER_SELECT_MODE_SELECTION) {
      if (player_select->land_exist == TRUE) {
        player_select_next_mode(&player_select->player_no, SELECT_PLAYER_NUM);
      }
      else {
        player_select_next_mode(&player_select->player_no, PLAYER_NUM);
      }
    }

    if (chkTrigger(BUTTON_DUP) && player_select->mode == PLAYER_SELECT_MODE_SELECTION) {
      if (player_select->land_exist == TRUE) {
        player_select_back_mode(&player_select->player_no, SELECT_PLAYER_NUM);
      }
      else {
        player_select_back_mode(&player_select->player_no, PLAYER_NUM);
      }
    }
  }
  else if (player_select->err_no == PLAYER_SELECT_INIT_ERR_SUCCESS) {
    player_select_init_after(player_select);
    GAME_GOTO_NEXT((GAME*)player_select, select, SELECT);
  }
  else {
    Common_Set(scene_from_title_demo, -1);
    player_select->err_no = PLAYER_SELECT_INIT_ERR_NONE;
    player_select->mode = PLAYER_SELECT_MODE_SELECTION;
  }
}

static void str_add_word(u8* dst, const u8* word0, const u8* word1, int word0_len, int word1_len) {
  for (word0_len; word0_len != 0; word0_len--) {
    *dst++ = *word0++;
  }

  for (word1_len; word1_len != 0; word1_len--) {
    *dst++ = *word1++;
  }
}

static int l_ps_white_color[3] = { 250, 220, 100 };
static int l_ps_select_color[3] = { 200, 55, 55 };

/* not translated, プレーヤー せんたく, player selection */
static u8 _debug_player_select[10] = { 0xE4, 0xBA, 0x90, 0xB4, 0x90, 0x20, 0x0D, 0xC3, 0x0F, 0x07 };

static void player_select_draw_title(GAME_PLAYER_SELECT* player_select) {
  mFont_SetMatrix(player_select->game.graph, mFont_MODE_FONT);
  mFont_SetLineStrings_AndSpace(
    (GAME*)player_select,
    _debug_player_select, ARRAY_SIZE(_debug_player_select, u8),
    85.0f, 15.0f,
    200, 200, 200, 255,
    FALSE, TRUE, 0,
    1.2f, 1.2f,
    mFont_MODE_FONT
  );
  mFont_UnSetMatrix(player_select->game.graph, mFont_MODE_FONT);
}

static void player_select_draw_player_no(GAME_PLAYER_SELECT* player_select) {
  u8 name_buf[8 + SELECT_NAME_LEN];
  u8 pre_str[8] = { 0xED, 0xCA, 0x02, 0x15, 0xC3, 0x20, 0x20, 0x20 };
  int player_no = player_select->player_no;
  int i;

  for (i = 0; i < PLAYER_NUM; i++)  {
    int* color;

    /* create text */
    mem_clear(name_buf, ARRAY_SIZE(name_buf, u8), CHAR_SPACE);
    str_add_word(name_buf, pre_str, player_select->player_names[i], 8, SELECT_NAME_LEN);
    
    /* set player no */
    name_buf[6] = (u8)i | CHAR_ZERO;

    color = (player_no == i) ? l_ps_select_color : l_ps_white_color;

    mFont_SetMatrix(player_select->game.graph, mFont_MODE_FONT);
    mFont_SetLineStrings_AndSpace(
      (GAME*)player_select,
      name_buf, ARRAY_SIZE(name_buf, u8),
      70.0f, 65.0f + 15.0f * i,
      color[0], color[1], color[2], 255,
      FALSE, TRUE, 0,
      0.8f, 0.8f,
      mFont_MODE_FONT
    );
    mFont_UnSetMatrix(player_select->game.graph, mFont_MODE_FONT);
  }
}

static void player_select_draw_yosokara(GAME_PLAYER_SELECT* player_select) {
  u8* name = player_select->player_names[PLAYER_NUM];
  int* color = (player_select->player_no == PLAYER_NUM) ? l_ps_select_color : l_ps_white_color;

  mFont_SetMatrix(player_select->game.graph, mFont_MODE_FONT);
  mFont_SetLineStrings_AndSpace(
    (GAME*)player_select,
    name, SELECT_NAME_LEN,
    70.0f, 65.0f + 15.0f * PLAYER_NUM,
    color[0], color[1], color[2], 255,
    FALSE, TRUE, 0,
    0.8f, 0.8f,
    mFont_MODE_FONT
  );
  mFont_UnSetMatrix(player_select->game.graph, mFont_MODE_FONT);
}

static void player_select_draw_main(GAME_PLAYER_SELECT* player_select) {
  GRAPH* g = player_select->game.graph;

  OPEN_DISP(g);

  gSPSegment(NOW_POLY_OPA_DISP++, G_MWO_SEGMENT_0, 0);
  gSPSegment(NOW_FONT_DISP++, G_MWO_SEGMENT_0, 0);

  DisplayList_initialize(g, 0, 0, 0, NULL);

  gDPPipeSync(NOW_POLY_OPA_DISP++);
  
  CLOSE_DISP(g);

  showView(&player_select->view, VIEW_UPDATE_ALL);
  player_select_draw_title(player_select);
  player_select_draw_player_no(player_select);
  player_select_draw_yosokara(player_select);
}

static void player_select_main(GAME* game) {
  GAME_PLAYER_SELECT* player_select = (GAME_PLAYER_SELECT*)game;

  player_select_move_main(player_select);
  player_select_draw_main(player_select);

  {
    GRAPH* g = game->graph;
    game_debug_draw_last(game, g);
    game_draw_last(g);
  }
}

extern void player_select_cleanup(GAME* game) { }

extern void player_select_init(GAME* game) {
  GAME_PLAYER_SELECT* player_select = (GAME_PLAYER_SELECT*)game;
  GRAPH* g = game->graph;
  int i;
  
  game->exec = &player_select_main;
  game->cleanup = &player_select_cleanup;

  {
    View* view = &player_select->view;
    initView(view, g);
    view->flag = VIEW_UPDATE_ORTHOGRAPHIC;
  }

  new_Matrix(game);
  SetGameFrame(1);
  
  player_select->player_no = 0;
  player_select->err_no = PLAYER_SELECT_INIT_ERR_NONE;
  player_select->mode = PLAYER_SELECT_MODE_SELECTION;

  for (i = 0; i < SELECT_PLAYER_NUM; i++) {
    int j;

    for (j = 0; j < 6; j++) {
      player_select->player_names[i][j] = mitouroku_str[j];
    }

    for (j = 6; j < SELECT_NAME_LEN; j++) {
      player_select->player_names[i][j] = CHAR_SPACE;
    }

    player_select->player_types[i] = PLAYER_SELECT_PLAYER_MODE_NO_SAVE;
  }

  for (i = 0; i < LAND_NAME_SIZE; i++) {
    player_select->land_name[i] = CHAR_SPACE;
  }
  player_select->land_exist = FALSE;

  if (mFRm_CheckSaveData() == TRUE) {
    Private_c* private_p = Save_Get(private);
    for (i = 0; i < PLAYER_NUM; i++) {
      u8* name = player_select->player_names[i];

      if (mPr_CheckPrivate(private_p) == TRUE) {
        mPr_CopyPlayerName(name, private_p->player_ID.player_name);

        if (private_p->exists == FALSE) {
          mem_copy(name + PLAYER_NAME_LEN, l_gaishutu_str, 10);
          player_select->player_types[i] = PLAYER_SELECT_PLAYER_MODE_OUT;
        }
        else {
          mem_copy(name + PLAYER_NAME_LEN, l_zaitaku_str, 9);
          player_select->player_types[i] = PLAYER_SELECT_PLAYER_MODE_HOME;
        }
      }
      else {
        player_select->player_types[i] = PLAYER_SELECT_PLAYER_MODE_UNREGISTERED;
      }

      private_p++;
    }

    mLd_CopyLandName(player_select->land_name, Save_Get(land_info.name));
    player_select->land_exist = TRUE;
  }

  for (i = 0; i < SELECT_PLAYER_NAME_EXTRA; i++) {
    player_select->player_names[PLAYER_NUM][i] = l_yosokara_str[i];
  }

  for (i = SELECT_PLAYER_NAME_EXTRA; i < SELECT_NAME_LEN; i++) {
    player_select->player_names[PLAYER_NUM][i] = CHAR_SPACE;
  }

  player_select->player_types[PLAYER_NUM] = PLAYER_SELECT_PLAYER_MODE_OUT;

  for (i = 0; i < SELECT_PLAYER_NUM; i++) {
    player_select->init_procs[i] = l_init_proc[player_select->player_types[i]];
  }

  Common_Set(player_no, 0);
  Common_Set(player_data_mode, 0);
  Common_Set(scene_from_title_demo, -1);
}