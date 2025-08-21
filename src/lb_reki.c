/*
 * lb_reki.c
 *
 * This source file contains a set of functions used to convert dates
 * between the Gregorian calendar (seiyo reki, 西洋暦) and the old Japanese
 * lunisolar calendar (kyuu reki, 旧暦). The functions also handle special
 * date calculations related to the Japanese calendar, such as Vernal Equinox Day,
 * Autumnal Equinox Day, and Harvest Moon Day.
 *
 * Functions in this file include:
 *
 * - lbRk_SeirekiDays: Calculate the number of days in a given month of a given year in the Gregorian calendar.
 * - lbRk_ToSeiyoMonthAndDay: Convert a kyuureki year and month to the corresponding Gregorian month and day.
 * - lbRk_KyuurekiLeapDays: Calculate the number of leap days in a given kyuureki year.
 * - lbRk_IsKyuurekiLeapYear: Check if a kyuureki year is a leap year.
 * - lbRk_IsLeapMonth: Check if a kyuureki month is a leap month.
 * - lbRk_IsLeapOnNextMonth: Check if a leap month occurs after the given kyuureki month.
 * - lbRk_KyuurekiDays: Calculate the number of days in a given kyuureki month of a given year.
 * - lbRk_ToSeiyouReki: Convert a kyuureki date to the corresponding Gregorian date.
 * - lbRk_ToKyuuReki: Convert a Gregorian date to the corresponding kyuureki date.
 * - lbRk_VernalEquinoxDay: Calculate the Vernal Equinox Day for a given year.
 * - lbRk_AutumnalEquinoxDay: Calculate the Autumnal Equinox Day for a given year.
 * - lbRk_HarvestMoonDay: Calculate the Harvest Moon Day for a given year.
 */

#include "lb_reki.h"

#include "types.h"

typedef struct lbRk_date_s {
  lbRTC_month_t month;
  lbRTC_day_t day;
} lbRk_date_t;

/**
 * @brief Gets the number of days in a given month of the Seiyo Reki (Gregorian calendar).
 *
 * @param year Year value.
 * @param month Month value.
 * @return The number of days in the specified month of the given year.
 */
static int lbRk_SeirekiDays(int year, int month) {
  // Table containing the number of days for each month in standard and leap years in the Seiyo Reki (Gregorian calendar)
  static lbRTC_day_t t_seiyo_days_tbl[][lbRTC_MONTHS_MAX + 1] = {
      {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, /* Standard days for each month */
      {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} /* Days for each month during leap year */
  };

  int idx = 0;
  if ((year % 4) == 0) {
    idx = 1;
  }

  return t_seiyo_days_tbl[idx][month];
}

/* Convesion table which gets the beginning of a Kyuu Reki (Japanese lunisolar)
   date in Seiyo Reki (Gregoran calendar) date. */
static lbRk_date_t l_lbRk_ConvertTable[lbRk_YEAR_NUM][lbRk_KYUU_LEAP_MONTH] = {
  /* 2000 */ {{2,  5}, {3,  6}, {4,  5}, {5,  4}, {6,  2}, {7,  2}, {7, 31}, {8, 29}, { 9, 28}, {10, 27}, {11, 26}, {12, 26}, { 0,  0}},
  /* 2001 */ {{1, 24}, {2, 23}, {3, 25}, {4, 24}, {6, 21}, {7, 21}, {8, 19}, {9, 17}, {10, 17}, {11, 15}, {12, 15}, { 1, 13}, { 5, 23}},
  /* 2002 */ {{2, 12}, {3, 14}, {4, 13}, {5, 12}, {6, 11}, {7, 10}, {8,  9}, {9,  7}, {10,  6}, {11,  5}, {12,  4}, { 1,  3}, { 0,  0}},
  /* 2003 */ {{2,  1}, {3,  3}, {4,  2}, {5,  1}, {5, 31}, {6, 30}, {7, 29}, {8, 28}, { 9, 26}, {10, 25}, {11, 24}, {12, 23}, { 0,  0}},
  /* 2004 */ {{1, 22}, {2, 20}, {4, 19}, {5, 19}, {6, 18}, {7, 17}, {8, 16}, {9, 14}, {10, 14}, {11, 12}, {12, 12}, { 1, 10}, { 3, 21}},
  /* 2005 */ {{2,  9}, {3, 10}, {4,  9}, {5,  8}, {6,  7}, {7,  6}, {8,  5}, {9,  4}, {10,  3}, {11,  2}, {12,  2}, {12, 31}, { 0,  0}},
  /* 2006 */ {{1, 29}, {2, 28}, {3, 29}, {4, 28}, {5, 27}, {6, 26}, {7, 25}, {9, 22}, {10, 22}, {11, 21}, {12, 20}, { 1, 19}, { 8, 24}},
  /* 2007 */ {{2, 18}, {3, 19}, {4, 17}, {5, 17}, {6, 15}, {7, 14}, {8, 13}, {9, 11}, {10, 11}, {11, 10}, {12, 10}, { 1,  8}, { 0,  0}},
  /* 2008 */ {{2,  7}, {3,  8}, {4,  6}, {5,  5}, {6,  4}, {7,  3}, {8,  1}, {8, 31}, { 9, 29}, {10, 29}, {11, 28}, {12, 27}, { 0,  0}},
  /* 2009 */ {{1, 26}, {2, 25}, {3, 27}, {4, 25}, {5, 24}, {7, 22}, {8, 20}, {9, 19}, {10, 18}, {11, 17}, {12, 16}, { 1, 15}, { 6, 23}},
  /* 2010 */ {{2, 14}, {3, 16}, {4, 14}, {5, 14}, {6, 12}, {7, 12}, {8, 10}, {9,  8}, {10,  8}, {11,  6}, {12,  6}, { 1,  4}, { 0,  0}},
  /* 2011 */ {{2,  3}, {3,  5}, {4,  3}, {5,  3}, {6,  2}, {7,  1}, {7, 31}, {8, 29}, { 9, 27}, {10, 27}, {11, 25}, {12, 25}, { 0,  0}},
  /* 2012 */ {{1, 23}, {2, 22}, {3, 22}, {5, 21}, {6, 20}, {7, 19}, {8, 18}, {9, 16}, {10, 15}, {11, 14}, {12, 13}, { 1, 12}, { 4, 21}},
  /* 2013 */ {{2, 10}, {3, 12}, {4, 10}, {5, 10}, {6,  9}, {7,  8}, {8,  7}, {9,  5}, {10,  5}, {11,  3}, {12,  3}, { 1,  1}, { 0,  0}},
  /* 2014 */ {{1, 31}, {3,  1}, {3, 31}, {4, 29}, {5, 29}, {6, 27}, {7, 27}, {8, 25}, { 9, 24}, {11, 22}, {12, 22}, { 1, 20}, {10, 24}},
  /* 2015 */ {{2, 19}, {3, 20}, {4, 19}, {5, 18}, {6, 16}, {7, 16}, {8, 14}, {9, 13}, {10, 13}, {11, 12}, {12, 11}, { 1, 10}, { 0,  0}},
  /* 2016 */ {{2,  8}, {3,  9}, {4,  7}, {5,  7}, {6,  5}, {7,  4}, {8,  3}, {9,  1}, {10,  1}, {10, 31}, {11, 29}, {12, 29}, { 0,  0}},
  /* 2017 */ {{1, 28}, {2, 26}, {3, 28}, {4, 26}, {5, 26}, {7, 23}, {8, 22}, {9, 20}, {10, 20}, {11, 18}, {12, 18}, { 1, 17}, { 6, 24}},
  /* 2018 */ {{2, 16}, {3, 17}, {4, 16}, {5, 15}, {6, 14}, {7, 13}, {8, 11}, {9, 10}, {10,  9}, {11,  8}, {12, 27}, { 1,  6}, { 0,  0}},
  /* 2019 */ {{2,  5}, {3,  7}, {4,  5}, {5,  5}, {6,  3}, {7,  3}, {8,  1}, {8, 30}, { 9, 29}, {10, 28}, {11, 27}, {12, 26}, { 0,  0}},
  /* 2020 */ {{1, 25}, {2, 24}, {3, 24}, {4, 23}, {6, 21}, {7, 21}, {8, 19}, {9, 17}, {10, 17}, {11, 15}, {12, 15}, { 1, 13}, { 5, 23}},
  /* 2021 */ {{2, 12}, {3, 13}, {4, 12}, {5, 12}, {6, 10}, {7, 10}, {8,  8}, {9,  7}, {10,  6}, {11,  5}, {12,  4}, { 1,  3}, { 0,  0}},
  /* 2022 */ {{2,  1}, {3,  3}, {4,  1}, {5,  1}, {5, 30}, {6, 29}, {7, 29}, {8, 27}, { 9, 26}, {10, 25}, {11, 24}, {12, 23}, { 0,  0}},
  /* 2023 */ {{1, 22}, {2, 20}, {3, 22}, {5, 20}, {6, 18}, {7, 18}, {8, 16}, {9, 15}, {10, 15}, {11, 13}, {12, 13}, { 1, 11}, { 4, 20}},
  /* 2024 */ {{2, 10}, {3, 10}, {4,  9}, {5,  8}, {6,  6}, {7,  6}, {8,  4}, {9,  3}, {10,  3}, {11,  1}, {12,  1}, {12, 31}, { 0,  0}},
  /* 2025 */ {{1, 29}, {2, 28}, {3, 29}, {4, 28}, {5, 27}, {6, 25}, {8, 23}, {9, 22}, {10, 21}, {11, 20}, {12, 20}, { 1, 19}, { 7, 25}},
  /* 2026 */ {{2, 17}, {3, 19}, {4, 17}, {5, 17}, {6, 15}, {7, 14}, {8, 13}, {9, 11}, {10, 11}, {11,  9}, {12,  9}, { 1,  8}, { 0,  0}},
  /* 2027 */ {{2,  7}, {3,  8}, {4,  7}, {5,  6}, {6,  5}, {7,  4}, {8,  2}, {9,  1}, { 9, 30}, {10, 29}, {11, 28}, {12, 28}, { 0,  0}},
  /* 2028 */ {{1, 27}, {2, 25}, {3, 26}, {4, 25}, {5, 24}, {7, 22}, {8, 20}, {9, 19}, {10, 18}, {11, 16}, {12, 16}, { 1, 15}, { 6, 23}},
  /* 2029 */ {{2, 13}, {3, 15}, {4, 14}, {5, 13}, {6, 12}, {7, 12}, {8, 10}, {9,  8}, {10,  8}, {11,  6}, {12,  5}, { 1,  4}, { 0,  0}},
  /* 2030 */ {{2,  3}, {3,  4}, {4,  3}, {5,  2}, {6,  1}, {7,  1}, {7, 30}, {8, 29}, { 9, 27}, {10, 27}, {11, 25}, {12, 25}, { 0,  0}},
  /* 2031 */ {{1, 23}, {2, 22}, {3, 23}, {4, 22}, {6, 20}, {7, 19}, {8, 18}, {9, 17}, {10, 16}, {11, 15}, {12, 14}, { 1, 13}, { 5, 21}},
  /* 2032 */ {{2, 11}, {3, 12}, {4, 10}, {5,  9}, {6,  8}, {7,  7}, {8,  6}, {9,  5}, {10,  4}, {11,  3}, {12,  3}, { 1,  1}, { 0,  0}},
};

// The number of Japanese lunisolar leap days for a given lunisolar year.
static int l_lbRk_leapdays[lbRk_YEAR_NUM] = {
  0, 29, 0, 0,
  29, 0, 29, 0,
  0, 29, 0, 0,
  30, 0, 29, 0,
  0, 29, 0, 0,
  29, 0, 0, 30,
  0, 29, 0, 0,
  29, 0, 0, 30,
  0
};

/**
 * @brief Get a pointer to the lbRk_date_t structure for the Seiyo Reki (Gregorian calendar) month and day.
 *
 * @param year Year value.
 * @param month Month value.
 * @return Pointer to the lbRk_date_t structure representing the Seiyo Reki (Gregorian calendar) month and day.
 */
static lbRk_date_t* lbRk_ToSeiyoMonthAndDay(int year, int month) {
  return &l_lbRk_ConvertTable[year - lbRk_YEAR_MIN][month - 1];
}

/**
 * @brief Get the number of leap days for a given Kyuu Reki (Japanese lunisolar) year.
 *
 * @param year Year value.
 * @return The number of leap days for the specified Kyuu Reki (Japanese lunisolar) year.
 */
static int lbRk_KyuurekiLeapDays(int year) {
  return l_lbRk_leapdays[year - lbRk_YEAR_MIN];
}

/**
 * @brief Check if a given Kyuu Reki (Japanese lunisolar) year is a leap year.
 *
 * @param year Year value.
 * @return Non-zero (TRUE) if the given Kyuu Reki (Japanese lunisolar) year is a leap year, zero (FALSE) otherwise.
 */
static int lbRk_IsKyuurekiLeapYear(int year) {
  return l_lbRk_leapdays[year - lbRk_YEAR_MIN] != 0;
}

/**
 * @brief Check if a given month is a leap month in the Kyuu Reki (Japanese lunisolar) calendar.
 *
 * @param month Month value.
 * @return Non-zero (TRUE) if the given month is a leap month, zero (FALSE) otherwise.
 */
static int lbRk_IsLeapMonth(int month) {
  return month == lbRk_KYUU_LEAP_MONTH;
}

/**
 * @brief Check if the leap month occurs next month in the Kyuu Reki (Japanese lunisolar) calendar.
 *
 * @param year Year value.
 * @param month Month value.
 * @return Non-zero (TRUE) if the leap month occurs next month, zero (FALSE) otherwise.
 */
static int lbRk_IsLeapOnNextMonth(int year, int month) {
  lbRk_date_t* seiyo_monthday = lbRk_ToSeiyoMonthAndDay(year, month);
  lbRk_date_t* convert_monthday = &l_lbRk_ConvertTable[year - lbRk_YEAR_MIN][lbRTC_MONTHS_MAX];

  // Check if the leap month occurs next month by comparing the month values
  // in the Seiyo Reki (Gregorian calendar)
  return !(convert_monthday->month != seiyo_monthday->month + 1);
}

/**
 * Calculates the number of days in a given month of the Japanese lunisolar calendar (kyuureki)
 * for a given year and month.
 *
 * @param year The year in the kyuureki calendar.
 * @param month The month in the kyuureki calendar.
 * @return The number of days in the specified month of the Japanese lunisolar calendar.
 */
static int lbRk_KyuurekiDays(int year, int month) {
  int days;
  lbRk_date_t* next_seiyo_month_day;

  // Get the corresponding Seiyo (Gregorian) month and day for the given kyuureki year and month
  lbRk_date_t* seiyo_monthday = lbRk_ToSeiyoMonthAndDay(year, month);

  // If the month is a leap month, return the number of leap days for the year
  if (lbRk_IsLeapMonth(month) == TRUE) {
    return lbRk_KyuurekiLeapDays(year);
  }

  // Determine the Seiyo (Gregorian) month and day for the next month in the kyuureki calendar
  if (month != lbRTC_MONTHS_MAX) {
    if (lbRk_IsLeapOnNextMonth(year, month) == TRUE) {
      next_seiyo_month_day = lbRk_ToSeiyoMonthAndDay(year, lbRk_KYUU_LEAP_MONTH);
    } else {
      next_seiyo_month_day = lbRk_ToSeiyoMonthAndDay(year, month + 1);
    }
  } else {
    next_seiyo_month_day = lbRk_ToSeiyoMonthAndDay(year + 1, 1);
  }

  // Calculate the number of days in the Kyuu (Japanese lunisolar) month
  if (seiyo_monthday->month == next_seiyo_month_day->month) {
    days = next_seiyo_month_day->day - seiyo_monthday->day;
  } else {
    if (seiyo_monthday->month < month) {
      year += 1;
    }

    days = lbRk_SeirekiDays(year, seiyo_monthday->month) - seiyo_monthday->day;
    if ((next_seiyo_month_day->month - seiyo_monthday->month) >= 2) {
      days += lbRk_SeirekiDays(year, seiyo_monthday->month + 1);
    }
    days += next_seiyo_month_day->day;
  }
  return days;
}


/**
 * Converts a date from the Japanese lunisolar calendar (kyuureki) to the Gregorian calendar (seiyo reki).
 *
 * @param seiyo_ymd The output date in the Gregorian calendar.
 * @param kyuu_ymd The input date in the kyuureki calendar.
 * @return TRUE if the conversion is successful, FALSE if the input date is invalid.
 */
extern int lbRk_ToSeiyouReki(lbRTC_ymd_c* seiyo_ymd, lbRTC_ymd_c* kyuu_ymd) {
  int seireki_days;
  int year;
  int month;
  int day;
  lbRk_date_t* seiyo_monthday;

  // Validate the input kyuureki date
  if ((kyuu_ymd->year < 1) || (kyuu_ymd->year > lbRk_YEAR_MAX)) {
    return FALSE;
  }
  if (kyuu_ymd->month > lbRk_KYUU_LEAP_MONTH) {
    return FALSE;
  }
  if (lbRk_IsKyuurekiLeapYear(kyuu_ymd->year) == FALSE && kyuu_ymd->month >= lbRk_KYUU_LEAP_MONTH) {
    return FALSE;
  }
  if (lbRk_KyuurekiDays(kyuu_ymd->year, kyuu_ymd->month) < kyuu_ymd->day) {
    return FALSE;
  }

  // Get the corresponding Seiyo (Gregorian) month and day for the given kyuureki year and month
  seiyo_monthday = lbRk_ToSeiyoMonthAndDay(kyuu_ymd->year, kyuu_ymd->month);
  month = seiyo_monthday->month;
  year = kyuu_ymd->year;
  day = seiyo_monthday->day + kyuu_ymd->day - 1;

  // Adjust the Gregorian date based on the number of days in the Seiyo (Gregorian) month
  seireki_days = lbRk_SeirekiDays(year, month);
  if (day > seireki_days) {
    month++;
    day -= seireki_days;
    if (month > lbRTC_MONTHS_MAX) {
      month = 1;
    }
  }

  // Adjust the Gregorian year if necessary
  if (month < kyuu_ymd->month && kyuu_ymd->month != lbRk_KYUU_LEAP_MONTH) {
    year++;
  }

  // Set the output Gregorian date
  seiyo_ymd->year = year;
  seiyo_ymd->month = month;
  seiyo_ymd->day = day;

  return TRUE;
}

/**
 * Converts a date from the Gregorian calendar (seiyo reki) to the Japanese lunisolar calendar (kyuureki).
 *
 * @param kyuu_ymd The output date in the kyuureki calendar.
 * @param seiyo_ymd The input date in the Gregorian calendar.
 * @return TRUE if the conversion is successful, FALSE if the input date is invalid.
 */
extern int lbRk_ToKyuuReki(lbRTC_ymd_c* kyuu_ymd, lbRTC_ymd_c* seiyo_ymd) {
  lbRTC_ymd_c kyuu_date = (lbRTC_ymd_c){lbRk_YEAR_MIN, lbRk_KYUU_MONTH_START, lbRk_KYUU_DAY_START};
  lbRTC_ymd_c seyio_date;

  while (TRUE) {
    // Attempt to convert the current kyuureki date to Gregorian date
    if (lbRk_ToSeiyouReki(&seyio_date, &kyuu_date) == FALSE) {
      return FALSE;
    }

    // Check if the converted Gregorian date matches the input seiyo_ymd
    if (seyio_date.day == seiyo_ymd->day && seyio_date.month == seiyo_ymd->month && seyio_date.year == seiyo_ymd->year) {
      kyuu_ymd->day = kyuu_date.day;
      kyuu_ymd->month = kyuu_date.month;
      kyuu_ymd->year = kyuu_date.year;
      return TRUE;
    }

    // Increment the kyuureki day
    kyuu_date.day++;

    // If the kyuureki day exceeds the number of days in the current kyuureki month, reset the day and increment the month
    if (lbRk_KyuurekiDays(kyuu_date.year, kyuu_date.month) < kyuu_date.day) {
      kyuu_date.day = 1;
      kyuu_date.month++;

      // Handle leap years and month transitions
      if (lbRk_IsKyuurekiLeapYear(kyuu_date.year) == FALSE) {
        if (kyuu_date.month > lbRk_KYUU_MONTH_END) {
          kyuu_date.month = 1;
          kyuu_date.year++;
          if (kyuu_date.year > lbRk_YEAR_MAX) {
            return FALSE;
          }
        }
      } else if (kyuu_date.month > lbRk_KYUU_LEAP_MONTH) {
        kyuu_date.month = 1;
        kyuu_date.year++;
        if (kyuu_date.year > lbRk_YEAR_MAX) {
          return FALSE;
        }
      }
    }
  }
}

/**
 * Calculates the Vernal Equinox Day for the given year.
 *
 * @param year The input year.
 * @return The Vernal Equinox Day for the given year.
 * @remarks This function calculates the Vernal Equinox Day from 1980 thru 2099.
 *          It was sourced from '新こよみ便利帳 天文現象・暦計算のすべて'
 *          by Kouseisha Kouseikaku (ISBN4-7699-0700-1).
 */
extern int lbRk_VernalEquinoxDay(int year) {
  year -= 1980;
  return (int)(20.8431f + (0.242194f * (f32)year)) - (year / 4);
}

/**
 * Calculates the Autumnal Equinox Day for the given year.
 *
 * @param year The input year.
 * @return The Autumnal Equinox Day for the given year.
 * @remarks This function calculates the Autmnal Equinox Day from 1980 thru 2099.
 *          It was sourced from '新こよみ便利帳 天文現象・暦計算のすべて'
 *          by Kouseisha Kouseikaku (ISBN4-7699-0700-1).
 */
extern int lbRk_AutumnalEquinoxDay(int year) {
  year -= 1980;
  return (int)(23.2488f + (0.242194f * (f32)year)) - (year / 4);
}

/**
 * Calculates the Harvest Moon Day for the given year.
 *
 * @param harvest_moon_day The output Harvest Moon Day in the Gregorian calendar.
 * @param year The input year.
 */
extern void lbRk_HarvestMoonDay(lbRTC_ymd_c* harvest_moon_day, int year) {
  /* Array of precomputed Seiyo Reki (Gregorian calendar)
     Havest Moon Day dates. */
  static lbRk_date_t ev_day[lbRk_HARVEST_MOON_YEAR_NUM] = {
    /* 2002 */ {9, 21},
    /* 2003 */ {9, 10},
    /* 2004 */ {9, 28},
    /* 2005 */ {9, 18},
    /* 2006 */ {10, 7},
    /* 2007 */ {9, 26},
    /* 2008 */ {9, 15},
    /* 2009 */ {10, 4},
    /* 2010 */ {9, 23},
    /* 2011 */ {9, 12},
    /* 2012 */ {9, 30},
    /* 2013 */ {9, 19},
    /* 2014 */ {9, 9},
    /* 2015 */ {9, 28},
    /* 2016 */ {9, 16},
    /* 2017 */ {10, 5},
    /* 2018 */ {9, 25},
    /* 2019 */ {9, 14},
    /* 2020 */ {10, 1},
    /* 2021 */ {9, 20},
    /* 2022 */ {9, 10},
    /* 2023 */ {9, 29},
    /* 2024 */ {9, 18},
    /* 2025 */ {10, 7},
    /* 2026 */ {9, 26},
    /* 2027 */ {9, 15},
    /* 2028 */ {10, 3},
    /* 2029 */ {9, 22},
    /* 2030 */ {9, 11}
  };

  lbRTC_ymd_c kyuu_ymd;

  // If the year is within the pre-calculated range, use the stored values
  if ((year >= lbRk_HARVEST_MOON_YEAR_MIN) && (year < lbRk_HARVEST_MOON_YEAR_MAX + 1)) {
    year -= lbRk_HARVEST_MOON_YEAR_MIN;
    harvest_moon_day->month = ev_day[year].month;
    harvest_moon_day->day = ev_day[year].day;
    return;
  }

  // If the year is outside the pre-calculated range, calculate the Harvest Moon Day
  // using the Japanese lunisolar date of 8th month 15th day.
  kyuu_ymd.year = year;
  kyuu_ymd.month = 8;
  kyuu_ymd.day = 15;
  lbRk_ToSeiyouReki(harvest_moon_day, &kyuu_ymd);
}
