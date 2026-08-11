#ifndef DATERECMAPTEST_H
#define DATERECMAPTEST_H

#include <iostream>
#include <string>
#include "DateRecMap.h"
#include "Date.h"
#include "WeatherRecord.h"
#include "MyTime.h"

using std::cout;
using std::string;
using std::endl;

class DateRecMapTest {
private:
    int testsPassed;
    int testsFailed;

    void reportResult(const string& testName, bool passed);

    // Helper methods to create test data
    Date createTestDate(int day, int month, int year);
    WeatherRecord createTestRecord(float speed, float solar, float temp);

public:
    void runAllTests();
    void testDefaultConstructor();
    void testAddRecord();
    void testGetRecords();
    void testMultipleRecordsSameDate();
    void testMultipleDates();
    void testGetRecordsForNonExistentDate();
    void testEmptyRecordsVector();
};

#endif // DATERECMAPTEST_H

void DateRecMapTest::reportResult(const string& testName, bool passed) {
    if (passed) {
        cout << "PASS . " << testName << endl;
        testsPassed++;
    } else {
        cout << "FAIL . " << testName << endl;
        testsFailed++;
    }
}

Date DateRecMapTest::createTestDate(int day, int month, int year) {
    Date date;
    date.SetDay(day);
    date.SetMonth(month);
    date.SetYear(year);
    return date;
}

WeatherRecord DateRecMapTest::createTestRecord(float speed, float solar, float temp) {
    // Create default date and time for the record
    Date defaultDate;
    MyTime defaultTime; // Assuming MyTime has a default constructor

    WeatherRecord record(defaultDate, defaultTime, speed, temp, solar);
    return record;
}

void DateRecMapTest::runAllTests() {
    cout << "=== DATERECMAP CLASS TESTS ===" << endl;
    testsPassed = 0;
    testsFailed = 0;

    testDefaultConstructor();
    testAddRecord();
    testGetRecords();
    testMultipleRecordsSameDate();
    testMultipleDates();
    testGetRecordsForNonExistentDate();
    testEmptyRecordsVector();

    cout << "================================" << endl;
    cout << "TESTS PASSED: " << testsPassed << endl;
    cout << "TESTS FAILED: " << testsFailed << endl;

    if (testsFailed == 0) {
        cout << "ALL DATERECMAP TESTS PASSED" << endl;
    } else {
        cout << "SOME DATERECMAP TESTS FAILED" << endl;
    }
}

void DateRecMapTest::testDefaultConstructor() {
    cout << "Test 1: Default Constructor" << endl;

    DateRecMap m_dateRecMap;

    // Test getting records for any date should return empty vector
    Date testDate = createTestDate(1, 1, 2023);
    const Vector<WeatherRecord>& records = m_dateRecMap.getRecords(testDate);

    cout << "Get records for non-existent date (1/1/2023): " << endl;
    cout << "  Number of records returned: " << records.size() << " (expected: 0)" << endl;
    cout << "  Returned empty vector: " << (records.size() == 0 ? "yes" : "no") << " (expected: yes)" << endl;

    bool passed = (records.size() == 0);
    reportResult("Default constructor creates empty map", passed);
}

void DateRecMapTest::testAddRecord() {
    cout << "Test 2: Add Record" << endl;

    DateRecMap m_dateRecMap;

    // Create test date and record
    Date testDate = createTestDate(15, 3, 2023);
    WeatherRecord testRecord = createTestRecord(5.5f, 120.0f, 22.5f);

    // Add record
    m_dateRecMap.addRecord(testDate, testRecord);

    // Retrieve records for that date
    const Vector<WeatherRecord>& records = m_dateRecMap.getRecords(testDate);

    cout << "Added one record for date 15/3/2023" << endl;
    cout << "  Number of records retrieved: " << records.size() << " (expected: 1)" << endl;

    bool passed = (records.size() == 1);
    reportResult("Single record can be added and retrieved", passed);
}

void DateRecMapTest::testGetRecords() {
    cout << "Test 3: Get Records" << endl;

    DateRecMap m_dateRecMap;

    // Create test data
    Date testDate = createTestDate(10, 6, 2023);
    WeatherRecord record1 = createTestRecord(3.2f, 150.0f, 18.0f);
    WeatherRecord record2 = createTestRecord(4.1f, 180.0f, 19.5f);

    // Add records
    m_dateRecMap.addRecord(testDate, record1);
    m_dateRecMap.addRecord(testDate, record2);

    // Retrieve records
    const Vector<WeatherRecord>& records = m_dateRecMap.getRecords(testDate);

    cout << "Added 2 records for date 10/6/2023" << endl;
    cout << "  Number of records retrieved: " << records.size() << " (expected: 2)" << endl;

    // Verify we can access the records
    if (records.size() == 2) {
        cout << "  First record speed: " << records[0].GetSpeed() << " (expected: 3.2)" << endl;
        cout << "  Second record speed: " << records[1].GetSpeed() << " (expected: 4.1)" << endl;

        bool dataCorrect = (records[0].GetSpeed() == 3.2f) && (records[1].GetSpeed() == 4.1f);
        bool passed = (records.size() == 2) && dataCorrect;
        reportResult("Multiple records can be retrieved correctly", passed);
    } else {
        reportResult("Multiple records can be retrieved correctly", false);
    }
}

void DateRecMapTest::testMultipleRecordsSameDate() {
    cout << "Test 4: Multiple Records Same Date" << endl;

    DateRecMap m_dateRecMap;

    // Create test date
    Date testDate = createTestDate(20, 7, 2023);

    // Add multiple records for the same date
    WeatherRecord record1 = createTestRecord(2.5f, 100.0f, 15.0f);
    WeatherRecord record2 = createTestRecord(3.0f, 110.0f, 16.0f);
    WeatherRecord record3 = createTestRecord(3.5f, 120.0f, 17.0f);

    m_dateRecMap.addRecord(testDate, record1);
    m_dateRecMap.addRecord(testDate, record2);
    m_dateRecMap.addRecord(testDate, record3);

    const Vector<WeatherRecord>& records = m_dateRecMap.getRecords(testDate);

    cout << "Added 3 records for the same date (20/7/2023)" << endl;
    cout << "  Number of records retrieved: " << records.size() << " (expected: 3)" << endl;

    // Verify all records are present and in order (assuming insertion order)
    if (records.size() == 3) {
        cout << "  Record 1 speed: " << records[0].GetSpeed() << " (expected: 2.5)" << endl;
        cout << "  Record 2 speed: " << records[1].GetSpeed() << " (expected: 3.0)" << endl;
        cout << "  Record 3 speed: " << records[2].GetSpeed() << " (expected: 3.5)" << endl;

        bool orderCorrect = (records[0].GetSpeed() == 2.5f) &&
                           (records[1].GetSpeed() == 3.0f) &&
                           (records[2].GetSpeed() == 3.5f);
        bool passed = orderCorrect;
        reportResult("Multiple records for same date are stored and retrieved correctly", passed);
    } else {
        reportResult("Multiple records for same date are stored and retrieved correctly", false);
    }
}

void DateRecMapTest::testMultipleDates() {
    cout << "Test 5: Multiple Dates" << endl;

    DateRecMap m_dateRecMap;

    // Create different dates
    Date date1 = createTestDate(1, 1, 2023);
    Date date2 = createTestDate(2, 1, 2023);
    Date date3 = createTestDate(3, 1, 2023);

    // Add records for different dates
    WeatherRecord record1 = createTestRecord(1.0f, 50.0f, 10.0f);
    WeatherRecord record2 = createTestRecord(2.0f, 60.0f, 11.0f);
    WeatherRecord record3 = createTestRecord(3.0f, 70.0f, 12.0f);

    m_dateRecMap.addRecord(date1, record1);
    m_dateRecMap.addRecord(date2, record2);
    m_dateRecMap.addRecord(date3, record3);

    // Retrieve records for each date
    const Vector<WeatherRecord>& records1 = m_dateRecMap.getRecords(date1);
    const Vector<WeatherRecord>& records2 = m_dateRecMap.getRecords(date2);
    const Vector<WeatherRecord>& records3 = m_dateRecMap.getRecords(date3);

    cout << "Added one record each for 3 different dates (1/1/2023, 2/1/2023, 3/1/2023)" << endl;
    cout << "  Records for date1: " << records1.size() << " (expected: 1)" << endl;
    cout << "  Records for date2: " << records2.size() << " (expected: 1)" << endl;
    cout << "  Records for date3: " << records3.size() << " (expected: 1)" << endl;

    // Verify each date has correct record
    bool allDatesCorrect = (records1.size() == 1) && (records2.size() == 1) && (records3.size() == 1);

    if (allDatesCorrect) {
        cout << "  Date1 record speed: " << records1[0].GetSpeed() << " (expected: 1.0)" << endl;
        cout << "  Date2 record speed: " << records2[0].GetSpeed() << " (expected: 2.0)" << endl;
        cout << "  Date3 record speed: " << records3[0].GetSpeed() << " (expected: 3.0)" << endl;

        bool dataCorrect = (records1[0].GetSpeed() == 1.0f) &&
                          (records2[0].GetSpeed() == 2.0f) &&
                          (records3[0].GetSpeed() == 3.0f);
        bool passed = allDatesCorrect && dataCorrect;
        reportResult("Multiple dates are handled correctly with separate record vectors", passed);
    } else {
        reportResult("Multiple dates are handled correctly with separate record vectors", false);
    }
}

void DateRecMapTest::testGetRecordsForNonExistentDate() {
    cout << "Test 6: Get Records For Non-Existent Date" << endl;

    DateRecMap m_dateRecMap;

    // Add records for one date
    Date existingDate = createTestDate(5, 5, 2023);
    WeatherRecord record = createTestRecord(4.5f, 200.0f, 25.0f);
    m_dateRecMap.addRecord(existingDate, record);

    // Try to get records for a date that doesn't exist
    Date nonExistentDate = createTestDate(6, 6, 2023);
    const Vector<WeatherRecord>& records = m_dateRecMap.getRecords(nonExistentDate);

    cout << "Added record for date 5/5/2023" << endl;
    cout << "  Getting records for non-existent date 6/6/2023:" << endl;
    cout << "    Number of records returned: " << records.size() << " (expected: 0)" << endl;
    cout << "    Returned empty vector: " << (records.size() == 0 ? "yes" : "no") << " (expected: yes)" << endl;

    // Verify existing date still works
    const Vector<WeatherRecord>& existingRecords = m_dateRecMap.getRecords(existingDate);

    bool nonExistentEmpty = (records.size() == 0);
    bool existingStillWorks = (existingRecords.size() == 1);
    bool passed = nonExistentEmpty && existingStillWorks;

    reportResult("Non-existent dates return empty vector without affecting existing data", passed);
}

void DateRecMapTest::testEmptyRecordsVector() {
    cout << "Test 7: Empty Records Vector Consistency" << endl;

    DateRecMap m_dateRecMap;

    // Get records for multiple non-existent dates
    Date date1 = createTestDate(10, 10, 2023);
    Date date2 = createTestDate(11, 10, 2023);
    Date date3 = createTestDate(12, 10, 2023);

    const Vector<WeatherRecord>& records1 = m_dateRecMap.getRecords(date1);
    const Vector<WeatherRecord>& records2 = m_dateRecMap.getRecords(date2);
    const Vector<WeatherRecord>& records3 = m_dateRecMap.getRecords(date3);

    cout << "Getting records for 3 different non-existent dates:" << endl;
    cout << "  Records for date1 size: " << records1.size() << " (expected: 0)" << endl;
    cout << "  Records for date2 size: " << records2.size() << " (expected: 0)" << endl;
    cout << "  Records for date3 size: " << records3.size() << " (expected: 0)" << endl;

    // All should return empty vectors
    bool allEmpty = (records1.size() == 0) && (records2.size() == 0) && (records3.size() == 0);

    // Verify they all return the same empty vector (by reference)
    bool sameEmptyVector = (&records1 == &records2) && (&records2 == &records3);

    cout << "  All return same empty vector instance: " << (sameEmptyVector ? "yes" : "no") << " (expected: yes)" << endl;

    bool passed = allEmpty && sameEmptyVector;
    reportResult("All non-existent dates return the same empty vector instance", passed);
}
