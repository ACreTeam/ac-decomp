#include "m_house.h"

#include "m_common_data.h"
#include "m_home.h"
#include "m_private.h"

#define DEFAULT_ARRANGEMENT ((mHS_HOUSE3 << 6) | (mHS_HOUSE2 << 4) | (mHS_HOUSE1 << 2) | (mHS_HOUSE0 << 0))

#define ARRANGE_GET(player_no) (((u32)Save_Get(house_arrangement) >> ((player_no) * 2)) & 3)
#define ARRANGE_MOVE(player_no, house_no) ((house_no) << ((player_no) * 2))

/**
 * @brief Initializes the `house_arrangement` variable to its default state.
 * 
 * The default state is:
 *  Player0: House0
 *  Player1: House1
 *  Player2: House2
 *  Player3: House3
 **/
extern void mHS_house_init() {
  Save_Set(house_arrangement, DEFAULT_ARRANGEMENT);
}

/**
 * @brief Retrieves the house arrangement value for a given player index.
 * 
 * @return The house index for the player.
 **/
extern int mHS_get_arrange_idx(int player_no) {
  return ARRANGE_GET(player_no);
}

/**
 * @brief Returns the index of the player who owns the house index from `house_arrangement`.
 * 
 * @return The owning player index for the house.
 **/
extern int mHS_get_pl_no(int house_no) {
  int i;
  u32 arrangement = Save_Get(house_arrangement);

  for (i = 0; i < PLAYER_NUM; i++) {
    if ((arrangement & 3) == house_no) {
      break;
    }

    arrangement >>= 2;
  }

  return i;
}

/**
 * @brief Returns the index of the player who owns a house by checking house owner IDs.
 * 
 * @return The owning player index for the house.
 **/
extern int mHS_get_pl_no_detail(int home_no) {
  mHm_hs_c* home = Save_Get(homes + (home_no & 3));

  if (mPr_NullCheckPersonalID(&home->ownerID) == FALSE) {
    int i;
    for (i = 0; i < PLAYER_NUM; i++) {
      if (mPr_CheckCmpPersonalID(&home->ownerID, Save_GetPointer(private[i].player_ID))) {
        return i;
      }
    }
  }

  return -1;
}

/* TODO: this probably had some macro.. maybe refactor? */
/**
 * @brief Sets the house arrangement value for `player_no` to `house_no`.
 * 
 * This function also swaps houses with whichever player is set in house_arrangement
 * with the house currently assigned to `player_no`.
 * 
 * @return TRUE when successfully set, FALSE otherwise.
 **/
extern int mHS_set_use(int player_no, int house_no) {
  int now_player_no;
  u32 house_arrangement;
  int mask;
  int plr_shift;
  int new_shift;
  int res = FALSE;

  if (player_no < PLAYER_NUM && house_no < PLAYER_NUM) {
    now_player_no = mHS_get_pl_no(house_no);
    if (mPr_NullCheckPersonalID(Save_GetPointer(homes[house_no].ownerID)) == TRUE) {
      if (now_player_no != player_no) {
        plr_shift = player_no * 2;
        new_shift = now_player_no * 2;
        house_arrangement = Save_Get(house_arrangement);
        
        /* create bitmask to clear previous saved indices */
        mask = 0xffffffff;
        mask ^= (3 << plr_shift) | (3 << new_shift); /* Remove the bits relating to both player indicies */

        /* Swap the player who currently owns our selected house with whatever house our player "owns" currently */ 
        Save_Set(house_arrangement, (
            ((house_arrangement & mask) | /* Clear old values */ 
            (((house_arrangement >> plr_shift) & 3)) << new_shift) | /* move current player house idx to old player house idx */ 
            (house_no << plr_shift))); /* set current player new house idx */
      }

      mHm_InitHomeInfo(Save_Get(homes + house_no), player_no);
      res = TRUE;
    }
  }

  return res;
}
