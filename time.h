/**
 * @file time.h
 * @brief This file contains the definitions and function declarations for
 * managing time information, including time creation, comparison, and various 
 * utility functions.
 * 
 * This file is part of the parking lots manager application, which is a simple
 * application for managing parking lots and cars parked in them.
 */
#ifndef __TIME_H__
#define __TIME_H__

/**
 * @brief Structure representing the hours of a day.
 * 
 * This structure holds information about the hours and minutes of a day.
 */
typedef struct hours {
    int hours;
    int minutes;
} Hours;

/**
 * @brief Structure representing a date.
 * 
 * This structure holds information about the day, month, and year of a date.
 */
typedef struct date {
    int day;
    int month;
    int year;
} Date;

/**
 * @brief Structure representing a time.
 * 
 * This structure holds information about a date and the hours of a time.
 */
typedef struct time {
    Date date;
    Hours hours;
} Time;

/**
 * @brief Inicializes the first time.
 * 
 * @return The first time.
 */
Time time0();

/**
 * @brief Changes the time of a date.
 * 
 * @param dateToChange The date to change.
 * @param newDate The new date.
 */
void changeTime(Time *dateToChange, Time newDate);

/**
 * @brief Creates a new time.
 * 
 * @param day The day of the time.
 * @param month The month of the time.
 * @param year The year of the time.
 * @param hours The hours of the time.
 * @param minutes The minutes of the time.
 * @return The newly created time.
 */
Time newTime(int day, int month, int year, int hours, int minutes);

/**
 * @brief Checks if the time is invalid.
 * 
 * @param date The time to check.
 * @return 1 if the time is invalid, 0 otherwise.
 */
short invalidTime(Time date);

/**
 * @brief Checks if the time is posterior to another time.
 * 
 * @param time0 The first time.
 * @param time1 The second time.
 * @return 1 if the first time is posterior to the second time, 0 otherwise.
 */
short mostRecent(Time time0, Time time1);

/**
 * @brief Calculates the difference between two times in minutes.
 * 
 * @param recent The most recent time.
 * @param old The oldest time.
 * @return The difference between the two times.
 */
int timeDifference(Time recent, Time old);

/**
 * @brief Creates a new date.
 * 
 * @param day The day of the date.
 * @param month The month of the date.
 * @param year The year of the date.
 * @return The newly created date.
 */
Date newDate(int day, int month, int year);

/**
 * @brief Checks if the date is invalid.
 * 
 * @param date The date to check.
 * @return 1 if the date is invalid, 0 otherwise.
 */
short equalDate(Date d0, Date d1);

/**
 * @brief Checks if the date is posterior to another date.
 * 
 * @param d0 The first date.
 * @param d1 The second date.
 * @return 1 if the first date is posterior to the second date, 0 otherwise.
 */
short mostRecentDate(Date d0, Date d1);

/**
 * @brief Checks if the date is invalid.
 * 
 * @param date The date to check.
 * @return 1 if the date is invalid, 0 otherwise.
 */
short invalidDate(Date date);

#endif
