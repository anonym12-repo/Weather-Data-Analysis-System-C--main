/**
	 * @class WindlogAggregator
	 * @brief  Aggregates weather data by month and year for statistical analysis
	 *
	 * Processes raw weather records and organizes them into monthly datasets
	 * stored in MonthlyData objects. Provides efficient access to weather data
	 * organized by month and year for statistical calculations and reporting.
	 *
	 * Solar radiation values below 100 W/m² are filtered out during aggregation.\n
	 * Data is organized chronologically for efficient month/year lookup.\n
	 * Supports retrieval of individual sensor data types for analysis.\n
	 */
#ifndef WINDLOGAGGREGATOR_H
#define WINDLOGAGGREGATOR_H

#include "MonthlyData.h"
#include "Bst.h"
#include "MonthYearKey.h"
#include "DateRecMap.h"

class WindlogAggregator{
public:

    /// Collection of monthly data organized by year and month
    WindlogAggregator();

    /**
     * @brief Aggregates weather records into monthly data
     * @param data Vector of weather records to aggregate
     */
    void aggregateData(const Vector<WeatherRecord>& data);

    /**
     * @brief Checks if data exists for a specific month and year
     * @param year Year to check
     * @param month Month to check
     * @return True if data exists, false otherwise
     */
    bool hasDataForMonth(int year, int month) const;

    /**
     * @brief Gets wind speeds for a specific month and year
     * @param year Year
     * @param month Month
     * @return Vector of wind speeds
     */
    const Vector<float> getSpeeds(int year, int month) const;

    /**
     * @brief Gets temperatures for a specific month and year
     * @param year Year
     * @param month Month
     * @return Vector of temperatures
     */
    const Vector<float> getTemps(int year, int month) const;

    /**
     * @brief Gets solar radiation values for a specific month and year
     * @param year Year
     * @param month Month
     * @return Vector of solar radiation values
     */
    const Vector<float> getSolar(int year, int month) const;

    /**
     * @brief Retrieves the internal BST containing all recorded dates
     *
     * Provides read-only access to the Binary Search Tree (BST) used
     * to maintain chronological ordering of all unique dates in the dataset.
     *
     * @return const reference to the BST of Date objects
     * @pre Aggregation must have been performed before calling
     * @post No modification to internal data structures
     */
     const Bst<Date>& getDateTree() const;

     /**
     * @brief Retrieves the internal map of monthly aggregated data
     *
     * Provides read-only access to the mapping between MonthYearKey and
     * MonthlyData objects used for efficient month/year lookups.
     *
     * @return const reference to the Map containing all monthly datasets
     * @pre Aggregation must have been performed before calling
     * @post No modification to internal data structures
     */
     const Map<MonthYearKey, MonthlyData>& getMonthlyMap() const;

     /**
     * @brief Retrieves all weather records for a specified month across all years
     *
     * Combines records from multiple years that belong to the same month number.
     * Useful for cross-year comparisons (e.g., all July data across years).
     *
     * @param month Month number (1–12)
     * @return Vector containing all WeatherRecord entries for that month
     * @pre Month number must be in range [1, 12]
     * @post Returns empty vector if no records exist for that month
     */
     Vector<WeatherRecord> getAllRecordsForMonth(int month) const;

private:
    Map<MonthYearKey, MonthlyData> m_monthlyMap;  /// Fast monthly lookup
    Bst<Date> m_dateTree;           /// Chronological ordering of all dates
    DateRecMap m_dateRecordMap; /// Links dates to actual records

    // private static members used during traversal
    static int s_targetMonth;          ///< holds current month filter
    static Vector<Date>* s_collected;  ///< pointer to collector vector

    // private static callbacks for traversal
    static void collectMonthDates(const Date& d);
    static bool isTargetMonth(const Date& d);

};

#endif
