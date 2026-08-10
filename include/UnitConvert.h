/**
 * UnitConvert
 * for unit conversions that works with any float type
 *
 * Provides unit conversion functions for weather data
 */
#ifndef UNITCONVERT_H
#define UNITCONVERT_H

#include "Vector.h"


    /**
     * @brief Converts meters per second to kilometers per hour
     * @param ms Speed in m/s
     * @return Speed in km/h
     */
float metersPerSecondToKmh(float ms);

    /**
     * @brief Converts solar radiation from W/m² to kWh/m²
     * @param solarRadW Solar radiation in W/m²
     * @return Solar radiation in kWh/m²
     */
float solarWToKWh(float solarRadW);

    /**
     * @brief Converts vector of speeds from m/s to km/h
     * @param speedsMs Speeds in m/s
     * @return Speeds in km/h
     */
Vector<float> convertSpeedsToKmh(const Vector<float>& speedsMs);

     /**
     * @brief Calculates total solar radiation in kWh/m² from vector of readings
     * @param solarRadiation Vector of solar radiation values in W/m²
     * @return Total solar radiation in kWh/m²
     */
float calculateTotalSolarKWh(const Vector<float>& solarRadiation);

#endif
