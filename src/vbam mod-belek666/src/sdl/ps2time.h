// PS2Time
// This library require CDVDLib

/* Author: Krystian 'KarasQ' Karas
 * Contact: k4rasq@gmail.com
 */
 
#ifndef _LIB_TIME_H_
#define _LIB_TIME_H_

#include <time.h>
#include <libcdvd.h>
#include <osd_config.h>

#define UNIX_START_YEAR  1970

#define BCD2DEC(bcd)     ( ((((bcd) >> 4) & 0x0F) * 10) + ((bcd) & 0x0F) ) 

extern const int MonthsTable[];
extern const int MonthsTableDays[];

typedef struct _ps2time_data {
   int year;
   int month;
   int day;
   int hour;
   int minute;
   int second;
   bool is_leap_year;
} PS2TimeData;

class PS2Time {
   public:
      /* Function isLeapYear(); checks if year is leap */
      
      bool isLeapYear(int Year) {
         return ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0) ? true : false;
      }
      
      /* Function setLeapYearsNum() sets numbers of leap years since
       * startYear to endYear and return false if startYear > endYear
       * otherwise returns true
       */
       
      bool setLeapYearsNum(int startYear, int endYear);
      
      /* Function getSecFromData() returns number of seconds
       * since new year to current data. 
       * date need to be set before you call this function!
       */
       
      int getSecFromData(PS2TimeData *date);
      
      /* Function getLeapYearsNum() returns current value of
       * leap years.
       */
       
      int getLeapYearsNum() { 
         return m_LeapYearsNum; 
      }
      
      /* Function getTime() returns UNIX time (number of seconds
       * since 1 January of 1970 or other defined in UNIX_START_YEAR)
       */
       
      int getTime(int *t = 0);
      
      /* Function getLocaltime() fill tm struct with
       * date values and return address to this structure
       */
       
      struct tm *getLocaltime(const int *t = 0);
      
      PS2Time();
     ~PS2Time();
     
   private:
      int m_LeapYearsNum;
      int m_GMTOffset;
      int m_DaylightSaving;
      
      PS2TimeData m_PS2Clock;
   
      bool UpdatePS2Clock();
      int getWeekDay(int day, int month, int year);
};

#endif
