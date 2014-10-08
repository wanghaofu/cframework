// Fig. 10.1: Time.h
// Definition of class Time.
// Member functions defined in Time.cpp.
#ifndef TIME_H
#define TIME_H

class Time
{
  public:
    Time( int = 0, int = 0, int = 0 ); //default constructor

    // set functions
    void setTime( int, int, int );
    void setHour( int ); // set hour
    void setMinute( int ); // set minute
    void setSecond( int ); // set second

    // get functions ( normally declared const)
    int getHour() const;
    int getMinute() const; // return minute
    int getSecond() const; // return second

    // print functions (normall declared const)
    void printUniversal() const; // print univeraal time
    void printStandard(); // print standard time (should be const)
  private:
    int hour; // 0 - 23 (24-hour clock format)
    int minute; // 0-59
    int second; // 0-59
}; // end class Time

#endif
