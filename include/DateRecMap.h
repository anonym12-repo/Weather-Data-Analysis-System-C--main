// DateRecordMap.h
#ifndef DATERECORDMAP_H
#define DATERECORDMAP_H

#include "Date.h"
#include "WeatherRecord.h"
#include "Map.h"
#include "Vector.h"
#include "DateUtils.h"

/**
 * @class DateRecordMap
 * @brief Maps Date objects to their corresponding WeatherRecord objects
 */
class DateRecMap {
public:
    /**
     * @brief Default constructor
     * @post Empty map is created
     */
    DateRecMap();

    /**
     * @brief Add a weather record for a specific date
     * @param date The date key
     * @param record The weather record to store
     * @pre Date must be valid
     * @post Record is added to the map for the given date
     */
    void addRecord(const Date& date, const WeatherRecord& record);

    /**
     * @brief Get all records for a specific date
     * @param date The date to search for
     * @return const Vector<WeatherRecord>& Reference to vector of records for that date
     * @pre Date must be valid
     * @post Map remains unchanged
     */
    const Vector<WeatherRecord>& getRecords(const Date& date) const;

private:

    /**
     * @brief Internal mapping of dates to corresponding weather records.
     *
     * Each Date key maps to a Vector containing all WeatherRecord entries
     * recorded on that specific date. This structure allows efficient lookup
     * and retrieval of weather data for any given day.
     */
    Map<Date, Vector<WeatherRecord>> m_dateToRecords;
    Vector<WeatherRecord> m_emptyVector;     /// Placeholder vector returned when no records exist for a date.

};


#endif // DATERECORDMAP_H
