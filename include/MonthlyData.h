/**
 * @class MonthlyData
 * @brief Stores and manages aggregated weather data for a specific month and year.
 *
 * Encapsulates monthly weather statistics including wind speeds, temperatures,
 * and solar radiation readings. Provides controlled access to the data and
 * ensures data integrity through validation. Designed to support summary and
 * statistical calculations on monthly datasets.
 */

#ifndef MONTHLYDATA_H
#define MONTHLYDATA_H

#include "Vector.h"
#include "WeatherRecord.h"

class MonthlyData {

public:

    /**
     * @brief Default constructor.
     *
     * Initializes the object with year and month values (set to 0)
     * and empty data vectors for wind speed, temperature, and solar radiation.
     *
     * @post Creates an empty MonthlyData instance with no records.
     */
     MonthlyData();

    /**
     * @brief Constructs a MonthlyData object for a given year and month.
     *
     * Performs validation on input parameters to ensure that the
     * month is within range (1 to 12) and year is positive.
     *
     * @param year The year in record.
     * @param month The month (1–12)
     * @post Creates an empty MonthlyData container with validated month and year.
     */
     MonthlyData(int year, int month);

    /**
     * @brief Retrieves the year associated
     * @return Integer year value.
     * @post Object remains unchanged.
     */
     int getYear() const;

     /**
     * @brief Retrieves the month associated
     * @return Integer month value (1–12).
     * @post Object remains unchanged.
     */
     int getMonth() const;

     /**
     * @brief Provides read-only access to wind speed readings.
     * @return Constant reference to vector of wind speeds (in m/s).
     * @post Vector contents remain unchanged.
     */
     const Vector<float>& getWindSpeeds() const;

     /**
     * @brief Provides read-only access to temperature readings.
     * @return Constant reference to vector of temperatures (°C).
     * @post Vector contents remain unchanged.
     */
     const Vector<float>& getTemperatures() const;

     /**
     * @brief Provides read-only access to solar radiation readings.
     * @return Constant reference to vector of solar radiation values (W/m²).
     * @post Vector contents remain unchanged.
     */
     const Vector<float>& getSolarRadiation() const;

    /**
     * @brief Adds a WeatherRecord to the monthlydata.
     *
     * Appends data extracted from a WeatherRecord into the relevant
     * measurement vectors (wind speed, temperature, solar radiation),
     * ensuring that duplicate date-time entries are not added.
     *
     * @param record The WeatherRecord object to add.
     * @post Record is added only if it is not a duplicate entry.
     */
     void addRecord(const WeatherRecord& record);

    /**
     * @brief Checks whether the monthly data contains anything.
     *
     * Returns true if at least one of the internal vectors
     * (wind speed, temperature, or solar radiation) contains data.
     *
     * @return True if any measurements exist, false otherwise.
     * @post Object remains unchanged.
     */
     bool hasData() const;

    /**
     * @brief Validates the month and year associated
     *
     * Returns true if both month and year hold valid values.
     *
     * @return True if valid, false otherwise.
     * @post Object remains unchanged.
     */
     bool isValid() const;

private:

    int m_year;                           ///< Year (must be positive)

    int m_month;                          ///< Month (1-12)

    Vector<float> m_windSpeeds;           ///< Wind speed readings in m/s

    Vector<float> m_temperatures;         ///< Temperature readings in °C

    Vector<float> m_solarRadiation;       ///< Solar radiation readings in W/m²

    Vector<WeatherRecord> records;  ///< Stores all raw records for the month

    /**
     * @brief Validates if a month number is within valid range
     * @param month Month number to validate
     * @return True if month is valid (1-12), false otherwise
     */
    bool isValidMonth(int month) const;

    /**
     * @brief Validates if a year number is reasonable
     * @param year Year number to validate
     * @return True if year is valid (positive), false otherwise
     */
    bool isValidYear(int year) const;
};

#endif
