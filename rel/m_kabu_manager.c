#include "m_kabu_manager.h"

#include "lb_rtc.h"
#include "m_common_data.h"
#include "libc64/qrand.h"

#define TRADE_MARKET_ODDS_NUM (Kabu_TRADE_MARKET_TYPE_NUM - 1)

/**
 * @brief Set Stalk Market update time to current day at 00:00.
 **/
static void Kabu_set_schedule_day() {
  lbRTC_time_c* kabu_update_time = Save_GetPointer(kabu_price_schedule.update_time);

  /* copy current date-time */
  lbRTC_TimeCopy(kabu_update_time, Common_GetPointer(time.rtc_time));
  
  /* set time to beginning of day */
  kabu_update_time->hour = 0;
  kabu_update_time->min = 0;
  kabu_update_time->sec = 0;

  /* back-track to the last Sunday */
  lbRTC_Sub_DD(kabu_update_time, kabu_update_time->weekday);
  kabu_update_time->weekday = lbRTC_SUNDAY;
}

/**
 * @brief Decide a new Stalk Market trend using the last trend for % odds.
 **/
static void Kabu_decide_trade_market() {
  static f32 next_trade_market_typeA[TRADE_MARKET_ODDS_NUM] = {
    0.5f, /* Type A (50%) */
    0.3f  /* Type B (30%) */
  //0.2f  /* Type C (20%) */
  };

  static f32 next_trade_market_typeB[TRADE_MARKET_ODDS_NUM] = {
    0.6f, /* Type A (60%) */
    0.2f  /* Type B (20%) */
  //0.1f  /* Type C (20%) */
  };

  static f32 next_trade_market_typeC[TRADE_MARKET_ODDS_NUM] = {
    0.6f, /* Type A (60%) */
    0.3f  /* Type B (30%) */
  //0.1f  /* Type C (10%) */
  };

  static f32* next_trade_market[Kabu_TRADE_MARKET_TYPE_NUM] = {
    next_trade_market_typeA, next_trade_market_typeB, next_trade_market_typeC
  };

  f32* next_type_market = next_trade_market[Save_Get(kabu_price_schedule.trade_market)];
  f32 chosen = fqrand(); /* [0.0f, 1.0f) */
  int i;

  /* Subtract odds from chosen until we're below the current odds, or reach the last market type */
  for (i = 0; i < TRADE_MARKET_ODDS_NUM; i++) {
    if (chosen < *next_type_market) {
      break;
    }

    chosen -= *next_type_market;
    next_type_market++;
  }

  if (i < Kabu_TRADE_MARKET_TYPE_START || i >= Kabu_TRADE_MARKET_TYPE_NUM) {
    i = 0;
  }

  Save_Set(kabu_price_schedule.trade_market, i);
}

/* Predeclare schedule function defs */
static void Kabu_decide_price_schedule_typeA();
static void Kabu_decide_price_schedule_typeB();
static void Kabu_decide_price_schedule_typeC();

#define TRADE_MARKET_A_SPIKE_DAYS 5
#define TRADE_MARKET_A_SPIKE_DAY_BEGIN lbRTC_MONDAY
#define TRADE_MARKET_A_SPIKE_MULTIPLIER 8.0f

/**
 * @brief Generate weekly Stalk Market prices in a 'random' trend. With one huge spike.
 * 
 * The spike day will be [Monday, Friday], and will always be 8 times the Sunday buy price.
 **/
static void Kabu_decide_price_schedule_typeA() {
  f32 spike_price;
  int spike_day;

  Kabu_decide_price_schedule_typeB(); /* start with a 'random' trend */

  /* determine spike price & spike day */
  spike_price = Save_Get(kabu_price_schedule.daily_price[lbRTC_SUNDAY]) * TRADE_MARKET_A_SPIKE_MULTIPLIER;
  spike_day = fqrand() * TRADE_MARKET_A_SPIKE_DAYS;
  spike_day += lbRTC_MONDAY;
  Save_Set(kabu_price_schedule.daily_price[spike_day], spike_price);
}

#define TRADE_MARKET_B_SUNDAY_PRICE_MULT 0.8f /* 0.8x (80%) minimum possible price */
#define TRADE_MARKET_B_PRICE_INCREASE_START 1.05f /* 1.05x (105%) initial increase rate */
#define TRADE_MARKET_B_PRICE_DECREASE_RATE 0.7f /* 0.7x (70%) static decrease rate */
#define TRADE_MARKET_B_PRICE_INCREASE_RATE 0.01f /* 1% linear increase percent rate */
#define TRADE_MARKET_B_PRICE_DECREASE_ODDS_START 0.1f /* 10% initial decrease chance  */
#define TRADE_MARKET_B_PRICE_DECREASE_ODDS_RATE 0.14f /* 14% decrease percentage increase rate */
#define TRADE_MARKET_B_PRICE_DECREASE_LOWER_RATE 0.3f /* 30% decrease percentage decrease rate */

/**
 * @brief Generate weekly Stalk Market prices in a 'random' trend.
 **/
static void Kabu_decide_price_schedule_typeB() {
  u16* prices = Save_GetPointer(kabu_price_schedule.daily_price[lbRTC_MONDAY]);
  f32 current_price_mult = TRADE_MARKET_B_PRICE_INCREASE_START;
  f32 price_decrease_percent = TRADE_MARKET_B_PRICE_DECREASE_ODDS_START;
  f32 current_price = (f32)Save_Get(kabu_price_schedule.daily_price[lbRTC_SUNDAY]);
  f32 min_price = (f32)Save_Get(kabu_price_schedule.daily_price[lbRTC_SUNDAY]) * TRADE_MARKET_B_SUNDAY_PRICE_MULT;
  int day;

  for (day = lbRTC_MONDAY; day <= lbRTC_SATURDAY; day++) {
    /* check if rng roll is less than our decrease chance */
    if (fqrand() < price_decrease_percent) {
      current_price *= TRADE_MARKET_B_PRICE_DECREASE_RATE; /* decrease price */
      if (current_price > min_price) {
          /* if decreased price is greater than the minimum decrease price, clamp it */
          current_price = min_price;
      }

      /* lower decrease chance, and clamp it to <= initial decrease odds */
      price_decrease_percent *= TRADE_MARKET_B_PRICE_DECREASE_LOWER_RATE;
      if (price_decrease_percent > TRADE_MARKET_B_PRICE_DECREASE_ODDS_START) {
        price_decrease_percent = TRADE_MARKET_B_PRICE_DECREASE_ODDS_START;
      }
    }
    else {
      /* increase increase multiplier & price, but also increase decrease chance */
      current_price *= current_price_mult;
      current_price_mult += TRADE_MARKET_B_PRICE_INCREASE_RATE;
      price_decrease_percent += TRADE_MARKET_B_PRICE_DECREASE_ODDS_RATE;
    }

    *prices++ = current_price; /* move to next day save slot */
  }
}

#define TRADE_MARKET_C_ADJUST_MULT_SPREAD 0.14999998f /* mwcc doesn't generate the same */ //0.15f
#define TRADE_MARKET_C_ADJUST_MULT_BASE 0.8f

/**
 * @brief Generate weekly Stalk Market prices in a 'falling' trend.
 **/
static void Kabu_decide_price_schedule_typeC() {
  u16* price = Save_GetPointer(kabu_price_schedule.daily_price[lbRTC_MONDAY]);
  f32 current_price = Save_Get(kabu_price_schedule.daily_price[lbRTC_SUNDAY]);
  int day;

  for (day = lbRTC_MONDAY; day <= lbRTC_SATURDAY; day++) {
    current_price *= (TRADE_MARKET_C_ADJUST_MULT_BASE + TRADE_MARKET_C_ADJUST_MULT_SPREAD * fqrand()); /* [80%, 95%) */
    *price++ = current_price;
  }
}

#define TRADE_MARKET_SUNDAY_BASE_PRICE 100.0f

/**
 * @brief Generate Sunday Stalk Market buy price.
 * 
 * Prices will always been in the range of [70, 129] bells.
 **/
static void Kabu_decide_price_sunday() {
  f32 price = 1.0f + (fqrand() - 0.5f) * 0.6f;
  Save_Set(kabu_price_schedule.daily_price[lbRTC_SUNDAY], price * TRADE_MARKET_SUNDAY_BASE_PRICE); /* [0.7, 1.3) * 100.0f = [70, 130) bells */
}

/**
 * @brief Run the set Stalk Market trend algorithm.
 **/
static void Kabu_decide_price_without_sunday() {
  static void (*process[])(void) = { Kabu_decide_price_schedule_typeA, Kabu_decide_price_schedule_typeB, Kabu_decide_price_schedule_typeC };
  (*process[Save_Get(kabu_price_schedule.trade_market)])();
}

/**
 * @brief Picks a new Stalk Market trend, generates new sell prices, & sets the update time.
 **/
static void Kabu_decide_price_schedule_without_sunday() {
  Kabu_decide_trade_market();
  Kabu_decide_price_without_sunday();
  Kabu_set_schedule_day();
}

/**
 * @brief Generates a new Stalk Market Sunday buy price, Stalk Market trend, sell prices, & sets the update time.
 **/
extern void Kabu_decide_price_schedule() {
  Kabu_decide_price_sunday();
  Kabu_decide_price_schedule_without_sunday();
}

/**
 * @brief Retrieves the current day's Stalk Market price.
 **/
extern u16 Kabu_get_price() {
  return Save_Get(kabu_price_schedule.daily_price[Common_Get(time.rtc_time.weekday)]);
}

/**
 * @brief Checks if the Stalk Market should be re-rolled based on the current date
 * 
 * It will re-roll the Stalk Market Trend & sell prices if called on Sunday
 * after the Stalk Market has already been set for the week.
 * 
 * It will completely re-roll Stalk Market if the date is greater than one week
 * from the last Stalk Market update.
 **/
extern void Kabu_manager() {
  lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
  lbRTC_time_c* kabu_update_time = Save_GetPointer(kabu_price_schedule.update_time);
  
  /* Check if being called on the Sunday where the Stalk Market has already been set */
  if (lbRTC_IsEqualDate(
      rtc_time->year, rtc_time->month, rtc_time->day,
      kabu_update_time->year, kabu_update_time->month, kabu_update_time->day
    ) == lbRTC_EQUAL
  ) {
    Kabu_decide_price_schedule_without_sunday(); /* reset non-sunday prices & the trend type */
  }
  else {
    lbRTC_time_c week_ahead;
    lbRTC_time_c week_behind;

    lbRTC_TimeCopy(&week_ahead, kabu_update_time);
    lbRTC_Add_DD(&week_ahead, lbRTC_WEEK);
    
    lbRTC_TimeCopy(&week_behind, kabu_update_time);
    lbRTC_Sub_DD(&week_behind, lbRTC_WEEK);

    if (lbRTC_IsOverTime(&week_ahead, Common_GetPointer(time.rtc_time)) == lbRTC_OVER ||
        lbRTC_IsOverTime(&week_behind, Common_GetPointer(time.rtc_time)) == lbRTC_LESS
    ) {
      Kabu_decide_price_schedule(); /* greater than one week has passed, reset entire schedule */
    }
  }
}
