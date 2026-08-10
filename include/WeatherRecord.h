	/**
	 * @class WeatherRecord
	 * @brief  Weather data record containing date, time and sensor readings
	 *
	 * Represents a single weather observation with complete timestamp
	 * and environmental sensor data. Used as the primary data structure
	 * for storing and processing weather measurements from sensor logs.
	 *
	 * All sensor data is stored in original units from source files.\n
	 * Wind speed is stored in meters per second (m/s).\n
	 * Temperature is stored in degrees Celsius (°C).\n
	 * Solar radiation is stored in watts per square meter (W/m²).\n
	 */
#ifndef WEATHER_RECORD_H
#define WEATHER_RECORD_H

#include "Date.h"
#include "MyTime.h"

class WeatherRecord
{
public:

		/**
		 * @brief  Default constructor
		 *
		 * Initializes all sensor readings to zero and uses default
		 * date and time objects.
		 *
		 * @return void
		 * @post All numeric fields set to 0.0, date/time set to defaults
		 */
	WeatherRecord();

		/**
		 * @brief  Parameterized constructor
		 *
		 * Creates a weather record with specified date, time and sensor data.
		 *
		 * @param  d - Date of weather observation
		 * @param  t - Time of weather observation
		 * @param  s - Wind speed in meters per second
		 * @param  temp - Ambient temperature in degrees Celsius
		 * @param  sr - Solar radiation in watts per square meter
		 * @return void
		 * @post Record initialized with specified values
		 */
	WeatherRecord(const Date& d, const MyTime& t, float s, float temp, float sr);

		/**
		 * @brief  Gets the date of observation
		 *
		 * @return const Date& - Constant reference to date object
		 */
	const Date& GetDate() const;

		/**
		 * @brief  Gets the time of observation
		 *
		 * @return const MyTime& - Constant reference to time object
		 */
	const MyTime& GetTime() const;

		/**
		 * @brief  Gets the wind speed reading
		 *
		 * @return float - Wind speed in meters per second
		 */
	float GetSpeed() const;

		/**
		 * @brief  Gets the ambient temperature reading
		 *
		 * @return float - Temperature in degrees Celsius
		 */
	float GetTemp() const;

		/**
		 * @brief  Gets the solar radiation reading
		 *
		 * @return float - Solar radiation in watts per square meter
		 */
	float GetSolarRad() const;

private:

		/// Date of weather observation
	Date date;

		/// Time of weather observation
	MyTime t_time;

		/// Wind speed in meters per second
	float speed;

		/// Ambient air temperature in degrees Celsius
	float temperature;

		/// Solar radiation in watts per square meter
	float solarRadiation;
};

#endif // WEATHER_RECORD_H
