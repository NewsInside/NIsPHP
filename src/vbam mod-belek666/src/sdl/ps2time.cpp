// PS2Time
// This library require CDVDLib

/* Author: Krystian 'KarasQ' Karas
 * Contact: k4rasq@gmail.com
 */

#include <libcdvd.h>
#include "ps2time.h"

const int MonthsTable[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int MonthsTableDays[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

PS2Time::PS2Time() :
   m_LeapYearsNum(0),
   m_GMTOffset(0),
   m_DaylightSaving(-1)
{
   if ( UpdatePS2Clock() ) {
      // Set GMT and Daylight Saving
      m_GMTOffset = configGetTimezone() / 60;
      m_DaylightSaving = configIsDaylightSavingEnabled();
      
      // It's necessary to init valid value to get valid time
      m_PS2Clock.is_leap_year = isLeapYear(m_PS2Clock.year);
      
      // It's necessary to set leap years value to get valid time
      setLeapYearsNum(UNIX_START_YEAR, m_PS2Clock.year);
   }
}

PS2Time::~PS2Time() {
}
 
bool PS2Time::setLeapYearsNum(int startYear, int endYear) {
   int i = 0;
   if ( startYear > endYear ) {
      return false;
   }
   
   for (i = startYear; i < endYear; i++) {
      if ( isLeapYear(i) ) {
         m_LeapYearsNum++;
      }
   }
   return true;
}

int PS2Time::getSecFromData(PS2TimeData *date) {
   int seconds = 0;
   
   if ( date->month > 1 && date->is_leap_year ) {
      seconds += 86400;
   }
   
   seconds += MonthsTableDays[date->month] * 24 * 60 * 60;
   seconds += (date->day - 1) * 24 * 60 * 60;
   seconds += date->hour * 60 * 60;
   seconds += date->minute * 60;
   seconds += date->second;
   
   return seconds;
}

int PS2Time::getTime(int *timer) {
   if ( timer ) {
      *timer = UpdatePS2Clock() ? ((m_PS2Clock.year * 365 - UNIX_START_YEAR * 365) +
         getLeapYearsNum()) * 24 * 60 * 60 + getSecFromData(&m_PS2Clock) : -1;
      return *timer;
   } else {
      return UpdatePS2Clock() ? ((m_PS2Clock.year * 365 - UNIX_START_YEAR * 365) +
         getLeapYearsNum()) * 24 * 60 * 60 + getSecFromData(&m_PS2Clock) : -1;
   }
}


struct tm *PS2Time::getLocaltime(const int *timer) {
   static struct tm PS2_Date;
   
   if ( UpdatePS2Clock() && !timer )
   {
      PS2_Date.tm_sec   = m_PS2Clock.second;
      PS2_Date.tm_min   = m_PS2Clock.minute;
      PS2_Date.tm_hour  = m_PS2Clock.hour;
      PS2_Date.tm_mday  = m_PS2Clock.day;
      PS2_Date.tm_mon   = m_PS2Clock.month;
      PS2_Date.tm_year  = m_PS2Clock.year; // !: years since 1900 required
      PS2_Date.tm_wday  = getWeekDay(PS2_Date.tm_mday, PS2_Date.tm_mon, PS2_Date.tm_year);
      PS2_Date.tm_yday  = MonthsTableDays[PS2_Date.tm_mon] + PS2_Date.tm_mday;
      PS2_Date.tm_isdst = m_DaylightSaving;
   
      // Fixing values
      PS2_Date.tm_year -= 1900;
   
      if ( PS2_Date.tm_mon > 1 && m_PS2Clock.is_leap_year )
         PS2_Date.tm_yday++;
   } else if ( timer ) {
      int i;
      register int work = *timer % (24 * 60 * 60);
      
      PS2_Date.tm_sec   = work % 60; work /= 60;
      PS2_Date.tm_min   = work % 60;
      PS2_Date.tm_hour  = work / 60;
      
      work = *timer / (24 * 60 * 60);
      
      PS2_Date.tm_wday = (work + 4) % 7;
      
      for ( i = UNIX_START_YEAR; ; ++i ) {
         register time_t k = isLeapYear(i) ? 366 : 365;
         
         if ( work >= k )
            work -= k;
         else
            break;
      }

      PS2_Date.tm_year = i - 1900;
      PS2_Date.tm_yday = work;
      PS2_Date.tm_mday = 1;
      
      if ( isLeapYear(i) && (work > 58) ) {
         if ( work == 59 )
            PS2_Date.tm_mday = 2;
            
         work -= 1;
      }
      
      for ( i = 11; i && (MonthsTableDays[i] > work); --i );

      PS2_Date.tm_mon = i;
      PS2_Date.tm_mday += work - MonthsTableDays[i];
   }
   
   return &PS2_Date;
}

bool PS2Time::UpdatePS2Clock() {
   CdvdClock_t Clock;
   
   if ( !cdReadClock(&Clock) ) {
      return false;
   }
   
   m_PS2Clock.year   = BCD2DEC(Clock.year);         // Warning!: RTC returns year less 2000
   m_PS2Clock.month  = BCD2DEC(Clock.month) & 0x0F; // Warning!: RTC return month values 1 - 12
   m_PS2Clock.day    = BCD2DEC(Clock.day) & 0x1F;
   m_PS2Clock.hour   = BCD2DEC(Clock.hour);         // Warning!: Hour in Japan (GMT + 9)
   m_PS2Clock.minute = BCD2DEC(Clock.minute);
   m_PS2Clock.second = BCD2DEC(Clock.second);
   
   // Fixing warnings
   m_PS2Clock.hour = (m_PS2Clock.hour - 9) + m_GMTOffset + m_DaylightSaving;
   m_PS2Clock.year += 2000;
   m_PS2Clock.month--;
   
   if ( m_PS2Clock.hour < 0 ) // is day changed?
   {
      m_PS2Clock.hour += 24;
      
      if ( --m_PS2Clock.day == 0 ) // is month changed?
      {
         if ( --m_PS2Clock.month < 0 ) // is year changed?
         {
            m_PS2Clock.month = 11;
            
            // So, now we have to fix leap years number and year... 
            if ( m_PS2Clock.is_leap_year || !isLeapYear(m_PS2Clock.year - 1) ) {
               m_PS2Clock.year--;
               m_PS2Clock.is_leap_year = false;
            } else {
               m_LeapYearsNum--;
               m_PS2Clock.year--;
               m_PS2Clock.is_leap_year = true;
            }
         }
         
         // Change day to last day of previous month
         m_PS2Clock.day = MonthsTable[m_PS2Clock.month];
         
         // Check if the changed month is not February and it haven't extra day
         if ( m_PS2Clock.month == 1 && m_PS2Clock.is_leap_year )
            m_PS2Clock.day++;
      }
   }
   
   return true;
}

int PS2Time::getWeekDay(int day, int month, int year) {
   int w;
   if (month > 2) {
      month -= 2;
   } else {
      month += 10;
      year--;
   }
   
   w = year / 100;
   year %= 100;
   
   return (day + (13 * month - 1) / 5 + year + year / 4 + w / 4 + 5 * w) % 7;
}
