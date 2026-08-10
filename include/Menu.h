/**
 * @class Menu
 * @brief Handles user interaction and menu operations for weather data analysis.
 *
 * Provides a text-based interface that allows users to access and analyze
 * aggregated weather information such as wind speed, temperature, and solar radiation.
 *
 * Each menu option corresponds to a specific analytical task, such as computing averages,
 * standard deviations, correlations, or exporting data to files.
 */

#ifndef MENU_H
#define MENU_H

#include "WindlogAggregator.h"
#include "Stats.h"
#include "UnitConvert.h"


class Menu {

public:

    /**
     * @brief Constructs a Menu object bound to a WindlogAggregator instance.
     *
     * Initializes the menu with access to aggregated weather data and
     * prepares helper objects for unit conversion and statistical analysis.
     *
     * @param agg Reference to a WindlogAggregator instance containing weather data.
     * @post Menu is ready to handle user input and perform calculations.
     */
     Menu(const WindlogAggregator& agg);

    /**
     * @brief Runs the main menu loop for user interaction.
     *
     * Continuously displays options to the user and executes corresponding
     * analytical functions until the user chooses to exit.
     *
     * @post Executes menu options based on user input.
     */
     void run() const;

    /**
     * @brief Menu Option 1 — Calculates average wind speed and standard deviation for a specific month and year.
     *
     * Prompts the user for month and year, retrieves the relevant wind speed data,
     * performs statistical analysis, and displays the results.
     *
     * @pre The aggregator must contain valid weather data for the requested month and year.
     * @post Displays computed wind speed statistics to the console.
     */
     void option1() const;

    /**
     * @brief Menu Option 2 — Calculates average temperature and standard deviation for each month of a specific year.
     *
     * Iterates through all months, retrieves temperature data from the aggregator,
     * computes statistical measures, and prints the results month-by-month.
     *
     * @pre The aggregator must contain valid weather data for the requested year.
     * @post Displays monthly temperature statistics for the year.
     */
     void option2() const;

    /**
     * @brief Menu Option 3 — Calculates correlation coefficients for a specific month across all years.
     *
     * Computes Pearson correlation coefficients between wind speed, temperature,
     * and solar radiation for all records corresponding to the selected month.
     *
     * @pre The aggregator must contain records for the selected month.
     * @post Displays computed correlation coefficients (S_T, S_R, T_R) to the console.
     */
     void option3() const;

   /**
     * @brief Menu Option 4  Exports comprehensive monthly weather data to a CSV file.
     *
     * Writes averaged and statistical data (wind speed, temperature, solar radiation)
     * for each month of a specified year into "WindTempSolar.csv".
     *
     * @pre Aggregated data must exist for the specified year.
     * @post Creates or overwrites "WindTempSolar.csv" with formatted results.
     */
     void option4() const;

private:

    const WindlogAggregator &aggregator;  /// Reference to the WindlogAggregator that provides all weather data.

};

#endif
