	/**
	 * @class MyTime
	 * @brief  Represents a time of day with hours and minutes
	 *
	 * This class provides storage for time values and includes functionality
	 * for time manipulation, validation, and stream input/output operations.
	 * Time values are validated to ensure they represent valid times of day.
	 *
	 * Time format is 24-hour with hours (0-23) and minutes (0-59).\n
	 * Stream operators support input/output in "HH:MM" format.\n
	 * Leading zeros are used for single-digit hours and minutes.\n
	 *
	 */

#ifndef MYTIME_H
#define MYTIME_H

#include <iostream>
#include <string>

class MyTime
{
public:

		/**
		 * @brief  Default constructor
		 *
		 * Initializes time to 00:00 (midnight)
		 *
		 * @return void
		 */
	MyTime();

		/**
		 * @brief  Parameterized constructor
		 *
		 * Creates a MyTime object with specified hours and minutes.
		 * No validation is performed in constructor - use setters for validation.
		 *
		 * @param  hr - Hours component (0-23)
		 * @param  min - Minutes component (0-59)
		 * @return void
		 */
	MyTime(int hr, int min);

		/**
		 * @brief  Gets the hours component
		 *
		 * @return int - Hours as integer (0-23)
		 */
	int GetHours() const;

		/**
		 * @brief  Gets the minutes component
		 *
		 * @return int - Minutes as integer (0-59)
		 */
	int GetMins() const;

		/**
		 * @brief  Sets the hours component
		 *
		 * Sets the hours component of the time. Caller should ensure
		 * the value is within valid range (0-23).
		 *
		 * @param  hr - Hours value to set (0-23)
		 * @return void
		 */
	bool SetHours(const int hr);

		/**
		 * @brief  Sets the minutes component
		 *
		 * Sets the minutes component of the time. Caller should ensure
		 * the value is within valid range (0-59).
		 *
		 * @param  min - Minutes value to set (0-59)
		 * @return void
		 */
	bool SetMins(const int min);

private:


	int hours; /// Hours component (0-23)


	int minutes; /// Minutes component (0-59)
};

#endif // MYTIME_H
