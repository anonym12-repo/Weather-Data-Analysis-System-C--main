#ifndef INTEGRATIONTESTS_H
#define INTEGRATIONTESTS_H

#include <iostream>
#include <string>
#include "MonthYearKey.h"
#include "Map.h"
#include "Bst.h"
#include "DateRecMap.h"
#include "Date.h"
#include "DateUtils.h"
#include "WeatherRecord.h"
#include "MyTime.h"
#include "Vector.h"

using std::cout;
using std::string;
using std::endl;

class IntegrationTests {
private:
    int testsPassed;
    int testsFailed;

    void reportResult(const string& testName, bool passed);

    // Helper methods
    Date createTestDate(int day, int month, int year);
    WeatherRecord createTestRecord(float speed, float solar, float temp);

    // Private helper functions for callbacks
    static Vector<Date>* s_collectedDates; // Static pointer for callback
    static void collectDateCallback(const Date& date);

public:
    void runAllTests();
    void testMonthYearMapIntegration();
    void testBSTDateRecMapPipeline();
    void testMapMonthYearKeySanity();
};

#endif // INTEGRATIONTESTS_H



// Initialize static member
Vector<Date>* IntegrationTests::s_collectedDates = nullptr;

void IntegrationTests::reportResult(const string& testName, bool passed) {
    if (passed) {
        cout << "PASS . " << testName << endl;
        testsPassed++;
    } else {
        cout << "FAIL . " << testName << endl;
        testsFailed++;
    }
}

Date IntegrationTests::createTestDate(int day, int month, int year) {
    Date date;
    date.SetDay(day);
    date.SetMonth(month);
    date.SetYear(year);
    return date;
}

WeatherRecord IntegrationTests::createTestRecord(float speed, float solar, float temp) {
    Date defaultDate;
    MyTime defaultTime;
    WeatherRecord record(defaultDate, defaultTime, speed, temp, solar);
    return record;
}

// Private helper function for BST traversal callback
void IntegrationTests::collectDateCallback(const Date& date) {
    if (s_collectedDates) {
        s_collectedDates->pushBack(date);
    }
}

void IntegrationTests::runAllTests() {
    cout << "=== INTEGRATION TESTS ===" << endl;
    testsPassed = 0;
    testsFailed = 0;

    testMonthYearMapIntegration();
    testBSTDateRecMapPipeline();
    testMapMonthYearKeySanity();

    cout << "================================" << endl;
    cout << "TESTS PASSED: " << testsPassed << endl;
    cout << "TESTS FAILED: " << testsFailed << endl;

    if (testsFailed == 0) {
        cout << "ALL INTEGRATION TESTS PASSED" << endl;
    } else {
        cout << "SOME INTEGRATION TESTS FAILED" << endl;
    }
}

void IntegrationTests::testMonthYearMapIntegration() {
    cout << "\nINT-01: MonthYearKey plus Map Integration = Sorted Iteration" << endl;

    // Create MonthYearKeys in random order
    std::vector<MonthYearKey> keys = {
        MonthYearKey(2023, 8),  // Random order insertion
        MonthYearKey(2022, 12), // Should be first
        MonthYearKey(2024, 1),  // Should be last
        MonthYearKey(2023, 3),  // Middle
        MonthYearKey(2023, 11)  // Between Aug and next year
    };

    cout << "Inserting keys in this order:" << endl;
    for (size_t i = 0; i < keys.size(); i++) {
        cout << "  [" << i << "]: (" << keys[i].year << ", " << keys[i].month << ")" << endl;
    }

    // Create map and insert in random order
    Map<MonthYearKey, string> monthMap;

    monthMap.inserts(keys[0], "August 2023 Data");
    monthMap.inserts(keys[1], "December 2022 Data");
    monthMap.inserts(keys[2], "January 2024 Data");
    monthMap.inserts(keys[3], "March 2023 Data");
    monthMap.inserts(keys[4], "November 2023 Data");

    cout << "Verifying all keys are accessible:" << endl;
    bool allAccessible = true;
    for (size_t i = 0; i < keys.size(); i++) {
        bool contains = monthMap.contains(keys[i]);
        cout << "  Contains (" << keys[i].year << ", " << keys[i].month << "): "
             << (contains ? "yes" : "no") << " (expected: yes)" << endl;
        if (!contains) allAccessible = false;
    }

    // Expected chronological order
    std::vector<MonthYearKey> expectedOrder = {
        MonthYearKey(2022, 12), // Earliest
        MonthYearKey(2023, 3),
        MonthYearKey(2023, 8),
        MonthYearKey(2023, 11),
        MonthYearKey(2024, 1)   // Latest
    };

    cout << "Expected chronological order:" << endl;
    for (size_t i = 0; i < expectedOrder.size(); i++) {
        cout << "  [" << i << "]: (" << expectedOrder[i].year << ", " << expectedOrder[i].month << ")" << endl;
    }

    // Verify we can retrieve data in correct order by querying
    cout << "Retrieving data in chronological order:" << endl;
    bool retrievalCorrect = true;
    for (size_t i = 0; i < expectedOrder.size(); i++) {
        if (monthMap.contains(expectedOrder[i])) {
            string data = monthMap.get(expectedOrder[i]);
            cout << "  Retrieved (" << expectedOrder[i].year << ", " << expectedOrder[i].month << "): " << data << endl;
        } else {
            cout << "  ERROR: Missing (" << expectedOrder[i].year << ", " << expectedOrder[i].month << ")" << endl;
            retrievalCorrect = false;
        }
    }

    // Test duplicate key prevention
    MonthYearKey duplicateKey(2023, 8); // Same as first key
    bool duplicateInsert = monthMap.inserts(duplicateKey, "Duplicate Data");
    cout << "Duplicate key insertion prevented: " << (!duplicateInsert ? "yes" : "no") << " (expected: yes)" << endl;

    // Verify original data unchanged
    string originalData = monthMap.get(keys[0]);
    bool dataPreserved = (originalData == "August 2023 Data");
    cout << "Original data preserved: " << (dataPreserved ? "yes" : "no") << " (expected: yes)" << endl;

    bool passed = allAccessible && retrievalCorrect && !duplicateInsert && dataPreserved;
    reportResult("INT-01: Map maintains MonthYearKeys in chronological order", passed);
}

void IntegrationTests::testBSTDateRecMapPipeline() {
    cout << "\nINT-02: BST -> DateRecMap Pipeline" << endl;

    // Create test dates
    Date date1 = createTestDate(15, 3, 2023);  // March 15, 2023
    Date date2 = createTestDate(20, 6, 2023);  // June 20, 2023
    Date date3 = createTestDate(5, 9, 2023);   // September 5, 2023

    cout << "Test dates:" << endl;
    cout << "  Date1: " << date1.GetDay() << "/" << date1.GetMonth() << "/" << date1.GetYear() << endl;
    cout << "  Date2: " << date2.GetDay() << "/" << date2.GetMonth() << "/" << date2.GetYear() << endl;
    cout << "  Date3: " << date3.GetDay() << "/" << date3.GetMonth() << "/" << date3.GetYear() << endl;

    // Create BST and insert dates in non-sorted order
    Bst<Date> dateBST;
    dateBST.insert(date2);  // June
    dateBST.insert(date1);  // March (should come first)
    dateBST.insert(date3);  // September

    cout << "Dates inserted in BST in order: June, March, September" << endl;

    // Create DateRecMap and add records
    DateRecMap dateRecMap;

    // Add multiple records for each date
    dateRecMap.addRecord(date1, createTestRecord(3.5f, 120.0f, 18.0f));
    dateRecMap.addRecord(date1, createTestRecord(4.2f, 150.0f, 19.5f));

    dateRecMap.addRecord(date2, createTestRecord(5.1f, 180.0f, 22.0f));

    dateRecMap.addRecord(date3, createTestRecord(2.8f, 90.0f, 16.5f));
    dateRecMap.addRecord(date3, createTestRecord(3.1f, 110.0f, 17.0f));
    dateRecMap.addRecord(date3, createTestRecord(2.5f, 85.0f, 15.5f));

    cout << "Records added to DateRecMap:" << endl;
    cout << "  Date1: 2 records" << endl;
    cout << "  Date2: 1 record" << endl;
    cout << "  Date3: 3 records" << endl;

    // Simulate traversal and record counting
    int totalRecords = 0;
    Vector<Date> collectedDates;

    // Set up the static pointer for the callback
    s_collectedDates = &collectedDates;

    // Perform in-order traversal to collect dates in sorted order
    cout << "Performing BST in-order traversal..." << endl;
    dateBST.inOrderTraversal(collectDateCallback);

    cout << "Dates collected in BST order:" << endl;
    for (int i = 0; i < collectedDates.size(); i++) {
        const Date& date = collectedDates[i];
        cout << "  [" << i << "]: " << date.GetDay() << "/" << date.GetMonth() << "/" << date.GetYear() << endl;
    }

    // Verify deterministic order (should be March, June, September)
    bool orderCorrect = true;
    if (collectedDates.size() == 3) {
        bool firstIsMarch = (collectedDates[0].GetMonth() == 3);
        bool secondIsJune = (collectedDates[1].GetMonth() == 6);
        bool thirdIsSeptember = (collectedDates[2].GetMonth() == 9);

        cout << "Order verification:" << endl;
        cout << "  First date is March: " << (firstIsMarch ? "yes" : "no") << " (expected: yes)" << endl;
        cout << "  Second date is June: " << (secondIsJune ? "yes" : "no") << " (expected: yes)" << endl;
        cout << "  Third date is September: " << (thirdIsSeptember ? "yes" : "no") << " (expected: yes)" << endl;

        orderCorrect = firstIsMarch && secondIsJune && thirdIsSeptember;
    }

    // Fetch records for each date and count totals
    cout << "Fetching records for each date:" << endl;
    Vector<int> recordCounts;

    for (int i = 0; i < collectedDates.size(); i++) {
        const Date& date = collectedDates[i];
        const Vector<WeatherRecord>& records = dateRecMap.getRecords(date);
        recordCounts.pushBack(records.size());
        totalRecords += records.size();

        cout << "  Date " << date.GetDay() << "/" << date.GetMonth() << "/" << date.GetYear()
             << ": " << records.size() << " records" << endl;
    }

    // Verify record counts
    bool countsCorrect = (recordCounts.size() == 3) &&
                        (recordCounts[0] == 2) &&  // March: 2 records
                        (recordCounts[1] == 1) &&  // June: 1 record
                        (recordCounts[2] == 3) &&  // September: 3 records
                        (totalRecords == 6);       // Total: 6 records

    cout << "Total records counted: " << totalRecords << " (expected: 6)" << endl;
    cout << "Record counts match expected: " << (countsCorrect ? "yes" : "no") << " (expected: yes)" << endl;

    // Clean up static pointer
    s_collectedDates = nullptr;

    bool passed = orderCorrect && countsCorrect && (collectedDates.size() == 3);
    reportResult("INT-02: BST->DateRecMap pipeline preserves deterministic order and correct counts", passed);
}

void IntegrationTests::testMapMonthYearKeySanity() {
    cout << "\nINT-03: Map<MonthYearKey, MonthlyData> Sanity" << endl;

    // Create MonthlyData structure for testing
    struct MonthlyData {
        float avgSpeed;
        float totalSolar;
        int recordCount;

        MonthlyData(float speed = 0, float solar = 0, int count = 0)
            : avgSpeed(speed), totalSolar(solar), recordCount(count) {}
    };

    // Insert months across multiple years
    Map<MonthYearKey, MonthlyData> monthlyStats;

    // Insert data in mixed year/month order
    monthlyStats.inserts(MonthYearKey(2023, 5), MonthlyData(4.5f, 1250.5f, 30));
    monthlyStats.inserts(MonthYearKey(2022, 12), MonthlyData(5.2f, 980.3f, 28));
    monthlyStats.inserts(MonthYearKey(2024, 1), MonthlyData(3.8f, 1100.7f, 31));
    monthlyStats.inserts(MonthYearKey(2023, 5), MonthlyData(6.7f, 1500.0f, 35)); // Duplicate - should fail
    monthlyStats.inserts(MonthYearKey(2022, 5), MonthlyData(4.8f, 1350.2f, 29)); // Same month, different year

    cout << "Inserted monthly data across multiple years:" << endl;
    cout << "  (2023,5): 30 records" << endl;
    cout << "  (2022,12): 28 records" << endl;
    cout << "  (2024,1): 31 records" << endl;
    cout << "  (2023,5): DUPLICATE (should be rejected)" << endl;
    cout << "  (2022,5): 29 records" << endl;

    // Test lookups - verify correct objects returned
    cout << "Testing lookups for each month-year combination:" << endl;
    bool lookupsCorrect = true;

    // Test 2023, May
    if (monthlyStats.contains(MonthYearKey(2023, 5))) {
        MonthlyData data2023May = monthlyStats.get(MonthYearKey(2023, 5));
        bool correct2023May = (data2023May.recordCount == 30) &&
                             (data2023May.avgSpeed == 4.5f) &&
                             (data2023May.totalSolar == 1250.5f);
        cout << "  (2023,5): recordCount=" << data2023May.recordCount
             << " avgSpeed=" << data2023May.avgSpeed
             << " totalSolar=" << data2023May.totalSolar
             << " (expected: 30, 4.5, 1250.5) - "
             << (correct2023May ? "CORRECT" : "WRONG") << endl;
        if (!correct2023May) lookupsCorrect = false;
    } else {
        cout << "  ERROR: Missing (2023,5)" << endl;
        lookupsCorrect = false;
    }

    // Test 2022, December
    if (monthlyStats.contains(MonthYearKey(2022, 12))) {
        MonthlyData data2022Dec = monthlyStats.get(MonthYearKey(2022, 12));
        bool correct2022Dec = (data2022Dec.recordCount == 28);
        cout << "  (2022,12): recordCount=" << data2022Dec.recordCount
             << " (expected: 28) - "
             << (correct2022Dec ? "CORRECT" : "WRONG") << endl;
        if (!correct2022Dec) lookupsCorrect = false;
    } else {
        cout << "  ERROR: Missing (2022,12)" << endl;
        lookupsCorrect = false;
    }

    // Test 2024, January
    if (monthlyStats.contains(MonthYearKey(2024, 1))) {
        MonthlyData data2024Jan = monthlyStats.get(MonthYearKey(2024, 1));
        bool correct2024Jan = (data2024Jan.recordCount == 31);
        cout << "  (2024,1): recordCount=" << data2024Jan.recordCount
             << " (expected: 31) - "
             << (correct2024Jan ? "CORRECT" : "WRONG") << endl;
        if (!correct2024Jan) lookupsCorrect = false;
    } else {
        cout << "  ERROR: Missing (2024,1)" << endl;
        lookupsCorrect = false;
    }

    // Test 2022, May (same month as 2023 but different year)
    if (monthlyStats.contains(MonthYearKey(2022, 5))) {
        MonthlyData data2022May = monthlyStats.get(MonthYearKey(2022, 5));
        bool correct2022May = (data2022May.recordCount == 29);
        cout << "  (2022,5): recordCount=" << data2022May.recordCount
             << " (expected: 29) - "
             << (correct2022May ? "CORRECT" : "WRONG") << endl;
        if (!correct2022May) lookupsCorrect = false;
    } else {
        cout << "  ERROR: Missing (2022,5)" << endl;
        lookupsCorrect = false;
    }

    // Test for cross-year collisions
    cout << "Testing for cross-year collisions:" << endl;
    bool noCollisions = true;

    // Verify that same month in different years are distinct
    if (monthlyStats.contains(MonthYearKey(2023, 5)) && monthlyStats.contains(MonthYearKey(2022, 5))) {
        MonthlyData data2023May = monthlyStats.get(MonthYearKey(2023, 5));
        MonthlyData data2022May = monthlyStats.get(MonthYearKey(2022, 5));

        bool differentData = (data2023May.recordCount != data2022May.recordCount);
        cout << "  (2023,5) vs (2022,5): different record counts? "
             << (differentData ? "yes" : "no") << " (expected: yes)" << endl;

        if (!differentData) {
            noCollisions = false;
            cout << "  ERROR: Cross-year collision detected!" << endl;
        }
    }

    // Test non-existent key
    bool nonExistentNotFound = !monthlyStats.contains(MonthYearKey(2021, 1));
    cout << "Non-existent key (2021,1) found: " << (monthlyStats.contains(MonthYearKey(2021, 1)) ? "yes" : "no")
         << " (expected: no)" << endl;

    bool passed = lookupsCorrect && noCollisions && nonExistentNotFound;
    reportResult("INT-03: Map<MonthYearKey,MonthlyData> handles multiple years without collisions", passed);
}
