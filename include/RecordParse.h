/**
 * RecordParse
 * @brief Parses weather data records from CSV files into WeatherRecord objects
 *
 * This handles the parsing of weather data from CSV format files,
 * extracting relevant meteorological information and converting it into
 * structured WeatherRecord objects for further processing and analysis.
 * It validates data integrity and handles various data format issues.
 */
#ifndef RecordParse_H
#define RecordParse_H

#include "WeatherRecord.h"
#include "Vector.h"
#include <string>

    /**
     * @brief Reads and parses weather data from a CSV file
     * @param filename The name/path of the CSV file to read
     * @return Vector containing all successfully parsed WeatherRecord objects
     *
     * @note The method skips malformed or invalid data rows and continues
     * processing the rest of the file. Only valid, complete records are returned.
     * Expected CSV format includes columns for date, time, wind speed,
     * temperature, and solar radiation measurements.
     *
     * @throws error message if the file cannot be opened  read
     *
     */
    Vector<WeatherRecord> ReadFile(const std::string& filename);

#endif
