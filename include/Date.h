/**
 * @class Date
 * @brief Declares the Date class representing a calendar date.
 *
 * Stores day, month, and year, and provides getters and setters.
 */

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

class Date
{
public:
    /** @brief Default constructor sets date to 0/0/0. */
    Date();

    /** @brief Constructor with day, month, year. */
    Date(int day, int month, int year);

    /** @brief Sets the day. */
    void SetDay(int day);

    /** @brief Sets the month. */
    void SetMonth(int month);

    /** @brief Sets the year. */
    void SetYear(int year);

    /** @brief Returns the day. */
    int GetDay() const;

    /** @brief Returns the month. */
    int GetMonth() const;

    /** @brief Returns the year. */
    int GetYear() const;

private:
    int day;   ///< Day of the month
    int month; ///< Month of the year
    int year;  ///< Year
};


#endif // DATE_H
