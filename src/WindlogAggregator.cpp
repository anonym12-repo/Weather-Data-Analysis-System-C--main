#include "WindlogAggregator.h"

// Define private static members
int WindlogAggregator::s_targetMonth = 0;
Vector<Date>* WindlogAggregator::s_collected = nullptr;

// --------------------------------------------------
// Condition callback: checks if date matches month
// --------------------------------------------------
bool WindlogAggregator::isTargetMonth(const Date& d) {
    return d.GetMonth() == s_targetMonth;
}

// ----------------------------------------------
// Visit callback: adds matching date to vector
// ----------------------------------------------
void WindlogAggregator::collectMonthDates(const Date& d) {
    if (s_collected){
        s_collected->pushBack(d);
    }
}

// Default constructor
WindlogAggregator::WindlogAggregator()
    : m_monthlyMap(), m_dateTree(), m_dateRecordMap() {}

// Aggregate weather records into monthly data
void WindlogAggregator::aggregateData(const Vector<WeatherRecord>& data) {
    for (int i = 0; i < data.size(); ++i) {
        const WeatherRecord& record = data[i];
        const Date& date = record.GetDate();

        // Only insert unique dates into BST
        if(!m_dateTree.search(date)){
           m_dateTree.insert(date);
        }

        m_dateRecordMap.addRecord(date, record);


        // Aggregate into monthly data using Map
        int year = date.GetYear();
        int month = date.GetMonth();
        MonthYearKey key(year, month);

        if (!m_monthlyMap.contains(key)) {
            MonthlyData newData(year, month);
            m_monthlyMap.inserts(key, newData);
        }

        MonthlyData& monthlyData = m_monthlyMap.get(key);
        monthlyData.addRecord(record);  // handles duplicates internally


    }
}

// Check if data exists for specific month and year
bool WindlogAggregator::hasDataForMonth(int year, int month) const {
    MonthYearKey key(year, month);
    return m_monthlyMap.contains(key) && m_monthlyMap.get(key).hasData();
}

// Get wind speeds for specific month and year
const Vector<float> WindlogAggregator::getSpeeds(int year, int month) const {
    MonthYearKey key(year, month);
    if (m_monthlyMap.contains(key)) {
        return m_monthlyMap.get(key).getWindSpeeds();
    }
    return Vector<float>();
}

// Get temperatures for specific month and year
const Vector<float> WindlogAggregator::getTemps(int year, int month) const {
    MonthYearKey key(year, month);
    if (m_monthlyMap.contains(key)) {
        return m_monthlyMap.get(key).getTemperatures();
    }
    return Vector<float>();
}

// Get solar radiation for specific month and year
const Vector<float> WindlogAggregator::getSolar(int year, int month) const {
    MonthYearKey key(year, month);
    if (m_monthlyMap.contains(key)) {
        return m_monthlyMap.get(key).getSolarRadiation();
    }
    return Vector<float>();
}

const Bst<Date>& WindlogAggregator::getDateTree() const {
    return m_dateTree;
}

const Map<MonthYearKey, MonthlyData>& WindlogAggregator::getMonthlyMap() const {
    return m_monthlyMap;
}

Vector<WeatherRecord> WindlogAggregator::getAllRecordsForMonth(int month) const {
    Vector<WeatherRecord> allRecords;
    Vector<Date> collectedDates;      // local temporary

    // Step 1: Collect all dates from BST
    s_targetMonth = month;
    s_collected   = &collectedDates;
    m_dateTree.inOrderTraversal(collectMonthDates, isTargetMonth);

    //Reset static pointers (safety)
    s_targetMonth = 0;
    s_collected   = nullptr;

    // Step 2: For each collected date, filter by month and collect records
    for (int i = 0; i < collectedDates.size(); ++i) {
        const Date& d = collectedDates[i];
       // if (d.GetMonth() == month){//single pass through BST instead of traversal+filtering
            const Vector<WeatherRecord>& recs = m_dateRecordMap.getRecords(d);
            for (int j = 0; j < recs.size(); ++j) {
                allRecords.pushBack(recs[j]);
            }
       //}
    }

    return allRecords;
}






