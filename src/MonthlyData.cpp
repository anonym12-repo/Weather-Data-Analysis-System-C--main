#include "MonthlyData.h"
#include <iostream> //required for std::cerr
#include "DateUtils.h"

// Default constructor
MonthlyData::MonthlyData()
:m_year(0), m_month(0), m_windSpeeds(), m_temperatures(), m_solarRadiation(),records()
{}

// Parameterized constructor
MonthlyData::MonthlyData(int year, int month)
:m_year(0), m_month(0), m_windSpeeds(), m_temperatures(), m_solarRadiation(),records()
{

    // Only set if valid, otherwise leave as 0 (invalid)
    if (isValidYear(year)){
        m_year = year;
    }
    if (isValidMonth(month)){
        m_month = month;
    }

}

// Validate if month is within 1-12 range
bool MonthlyData::isValidMonth(int month)  const{
    return (month >= 1 && month <= 12);
}

// Validate if year is positive (basic validation)
bool MonthlyData::isValidYear(int year) const{
    return (year > 0);
}

int MonthlyData::getYear() const{
    return m_year;
}

int MonthlyData::getMonth() const{
    return m_month;
}

// Get reference to wind speeds vector (const to prevent modification)
const Vector<float>& MonthlyData::getWindSpeeds() const{
    return m_windSpeeds;
}

// Get reference to temperatures vector
const Vector<float>& MonthlyData::getTemperatures() const{
    return m_temperatures;
}

// Get reference to solar radiation vector
const Vector<float>& MonthlyData::getSolarRadiation() const{
    return m_solarRadiation;
}

// Check if any data exists in this monthly record
bool MonthlyData::hasData() const{
    // Return true if any of the data vectors has entries
    return (m_windSpeeds.size() > 0 || m_temperatures.size() > 0 || m_solarRadiation.size() > 0);
}


// Validate if current object state is valid
bool MonthlyData::isValid() const{
    return isValidYear(m_year) && isValidMonth(m_month);
}

void MonthlyData::addRecord(const WeatherRecord& record) {
    // Skip duplicates with same date & time
    for (int i = 0; i < records.size(); ++i) {
        if (records[i].GetDate() == record.GetDate() &&
            records[i].GetTime() == record.GetTime()) {
            // Duplicate found — skip insertion
            return;
        }
    }

    // Only reached if no duplicate found
    records.pushBack(record);

    m_windSpeeds.pushBack(record.GetSpeed());
    m_temperatures.pushBack(record.GetTemp());
    m_solarRadiation.pushBack(record.GetSolarRad());
}



