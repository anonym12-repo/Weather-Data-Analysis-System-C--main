#include "UnitConvert.h"
//==================
//implementation
//===================

float metersPerSecondToKmh(float ms) {
    // Convert speed from meters per second to kilometers per hour
    // Formula: km/h = m/s × 3.6
    return ms * 3.6f;  // Multiply input by conversion factor 3.6
                         // T(3.6) ensures the literal is treated as type T (float, double, etc.)
}

float solarWToKWh(float solarRadW) {
    // Convert solar radiation from watts per square meter to kilowatt-hours per square meter
    // This conversion assumes 10-minute interval data (1/6 hour)
    // Formula: kWh/m² = (W/m² × (1/6 hour)) / 1000
    //return (solarRadW / T(6.0)) / T(1000.0);
    return solarRadW * ((1.0f)/(6.0f) )/ (1000.0);  // Divide by 6 for 10-minute interval,
                                              // then divide by 1000 to convert watts to kilowatts
}

Vector<float> convertSpeedsToKmh(const Vector<float>& speedsMs) {
    // Convert an entire vector of speed values from m/s to km/h
    Vector<float> speedsKmh;  // Create empty vector to store converted speeds

    // Iterate through each speed value in the input vector
    for (int i = 0; i < speedsMs.size(); ++i) {
        // Convert individual speed and add to result vector
        speedsKmh.pushBack(metersPerSecondToKmh(speedsMs[i]));
    }

    return speedsKmh;  // Return the vector containing all converted speeds
}

float calculateTotalSolarKWh(const Vector<float>& solarRadiation){
    // Calculate total solar radiation in kWh/m² from a series of measurements
    float totalKWh = (0.0f);  // Initialize accumulator to zero with proper type T

    // Iterate through all solar radiation readings in the vector
    for (int i = 0; i < solarRadiation.size(); ++i) {
        // Convert each reading to kWh and add to running total
        totalKWh += solarWToKWh(solarRadiation[i]);
    }

    return totalKWh;  // Return the cumulative solar radiation total
}

