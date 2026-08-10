// DateRecordMap.cpp
#include "DateRecMap.h"


// Constructor
DateRecMap::DateRecMap()
:m_dateToRecords(),  // Initializes the internal Map (Date to Vector<WeatherRecord>) as empty
m_emptyVector()     // Initializes the placeholder empty vector
{}

// Adds a new WeatherRecord to the map for a given date
void DateRecMap::addRecord(const Date& date, const WeatherRecord& record){
    // Check if the map already contains this date as a key
    if (!m_dateToRecords.contains(date)){
        // If the date key does not exist, create a new empty vector for this date
        Vector<WeatherRecord> newRecordList;
        m_dateToRecords.inserts(date, newRecordList);
    }

    // Retrieve the vector for this date and append the new record to it
    m_dateToRecords.get(date).pushBack(record);
}


// Retrieves all WeatherRecords for a given date
const Vector<WeatherRecord>& DateRecMap::getRecords(const Date& date) const {
    // If the date exists in the map, return a reference to its corresponding record list
    if (m_dateToRecords.contains(date)){
        return m_dateToRecords.get(date);
    }
    // If the date does not exist, return a reference to the empty placeholder vector
    // This avoids returning a dangling reference to a temporary object
    return m_emptyVector;
}

