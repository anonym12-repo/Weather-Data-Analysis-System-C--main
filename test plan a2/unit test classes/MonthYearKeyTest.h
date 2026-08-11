
#ifndef MONTHYEARKEYTEST_H
#define MONTHYEARKEYTEST_H

#include <iostream>
#include <string>
#include "MonthYearKey.h"

using std::cout;
using std::string;
using std::endl;

class MonthYearKeyTest {
private:
    int testsPassed;
    int testsFailed;

    void reportResult(const string& testName, bool passed);

public:
    void runAllTests();
    void testConstructor();
    void testLessThanOperator();
    void testEqualityOperator();
    void testComparisonConsistency();
    void testBoundaryValues();
    void testMapCompatibility();
};

#endif // MONTHYEARKEYTEST_H

void MonthYearKeyTest::reportResult(const string& testName, bool passed) {
    if (passed) {
        cout << "PASS . " << testName << endl;
        testsPassed++;
    } else {
        cout << "FAIL . " << testName << endl;
        testsFailed++;
    }
}

void MonthYearKeyTest::runAllTests() {
    cout << "=== MONTHYEARKEY CLASS TESTS ===" << endl;
    testsPassed = 0;
    testsFailed = 0;

    testConstructor();
    testLessThanOperator();
    testEqualityOperator();
    testComparisonConsistency();
    testBoundaryValues();
    testMapCompatibility();

    cout << "================================" << endl;
    cout << "TESTS PASSED: " << testsPassed << endl;
    cout << "TESTS FAILED: " << testsFailed << endl;

    if (testsFailed == 0) {
        cout << "ALL MONTHYEARKEY TESTS PASSED" << endl;
    } else {
        cout << "SOME MONTHYEARKEY TESTS FAILED" << endl;
    }
}

void MonthYearKeyTest::testConstructor() {
    cout << "Test 1: Constructor" << endl;

    // Test normal construction
    MonthYearKey key1(2023, 5);
    cout << "Created MonthYearKey(2023, 5):" << endl;
    cout << "  Year: " << key1.year << " (expected: 2023)" << endl;
    cout << "  Month: " << key1.month << " (expected: 5)" << endl;

    // Test boundary values
    MonthYearKey key2(2024, 1);  // January
    MonthYearKey key3(2024, 12); // December

    cout << "Boundary month tests:" << endl;
    cout << "  MonthYearKey(2024, 1) - month: " << key2.month << " (expected: 1)" << endl;
    cout << "  MonthYearKey(2024, 12) - month: " << key3.month << " (expected: 12)" << endl;

    bool yearCorrect = (key1.year == 2023) && (key2.year == 2024) && (key3.year == 2024);
    bool monthCorrect = (key1.month == 5) && (key2.month == 1) && (key3.month == 12);
    bool passed = yearCorrect && monthCorrect;

    reportResult("Constructor correctly initializes year and month", passed);
}

void MonthYearKeyTest::testLessThanOperator() {
    cout << "Test 2: Less Than Operator" << endl;

    // Test year comparison
    MonthYearKey key1(2023, 5);
    MonthYearKey key2(2024, 1);

    cout << "Year comparison:" << endl;
    cout << "  MonthYearKey(2023, 5) < MonthYearKey(2024, 1): " << (key1 < key2 ? "true" : "false") << " (expected: true)" << endl;
    cout << "  MonthYearKey(2024, 1) < MonthYearKey(2023, 5): " << (key2 < key1 ? "true" : "false") << " (expected: false)" << endl;

    // Test month comparison (same year)
    MonthYearKey key3(2024, 3);
    MonthYearKey key4(2024, 7);

    cout << "Month comparison (same year):" << endl;
    cout << "  MonthYearKey(2024, 3) < MonthYearKey(2024, 7): " << (key3 < key4 ? "true" : "false") << " (expected: true)" << endl;
    cout << "  MonthYearKey(2024, 7) < MonthYearKey(2024, 3): " << (key4 < key3 ? "true" : "false") << " (expected: false)" << endl;

    // Test equal keys
    MonthYearKey key5(2023, 8);
    MonthYearKey key6(2023, 8);

    cout << "Equal keys comparison:" << endl;
    cout << "  MonthYearKey(2023, 8) < MonthYearKey(2023, 8): " << (key5 < key6 ? "true" : "false") << " (expected: false)" << endl;

    bool yearComparisonCorrect = (key1 < key2) && !(key2 < key1);
    bool monthComparisonCorrect = (key3 < key4) && !(key4 < key3);
    bool equalKeysCorrect = !(key5 < key6);
    bool passed = yearComparisonCorrect && monthComparisonCorrect && equalKeysCorrect;

    reportResult("Less than operator works correctly for year and month comparisons", passed);
}

void MonthYearKeyTest::testEqualityOperator() {
    cout << "Test 3: Equality Operator" << endl;

    // Test equal keys
    MonthYearKey key1(2023, 5);
    MonthYearKey key2(2023, 5);

    cout << "Equal keys:" << endl;
    cout << "  MonthYearKey(2023, 5) == MonthYearKey(2023, 5): " << (key1 == key2 ? "true" : "false") << " (expected: true)" << endl;

    // Test different years
    MonthYearKey key3(2023, 5);
    MonthYearKey key4(2024, 5);

    cout << "Different years:" << endl;
    cout << "  MonthYearKey(2023, 5) == MonthYearKey(2024, 5): " << (key3 == key4 ? "true" : "false") << " (expected: false)" << endl;

    // Test different months
    MonthYearKey key5(2023, 5);
    MonthYearKey key6(2023, 6);

    cout << "Different months:" << endl;
    cout << "  MonthYearKey(2023, 5) == MonthYearKey(2023, 6): " << (key5 == key6 ? "true" : "false") << " (expected: false)" << endl;

    // Test both different
    MonthYearKey key7(2023, 5);
    MonthYearKey key8(2024, 6);

    cout << "Both different:" << endl;
    cout << "  MonthYearKey(2023, 5) == MonthYearKey(2024, 6): " << (key7 == key8 ? "true" : "false") << " (expected: false)" << endl;

    bool equalCorrect = (key1 == key2);
    bool differentYearCorrect = !(key3 == key4);
    bool differentMonthCorrect = !(key5 == key6);
    bool bothDifferentCorrect = !(key7 == key8);
    bool passed = equalCorrect && differentYearCorrect && differentMonthCorrect && bothDifferentCorrect;

    reportResult("Equality operator correctly compares year and month", passed);
}

void MonthYearKeyTest::testComparisonConsistency() {
    cout << "Test 4: Comparison Consistency" << endl;

    // Test that comparisons are consistent
    MonthYearKey key1(2023, 3);
    MonthYearKey key2(2023, 7);
    MonthYearKey key3(2024, 2);

    cout << "Consistency checks:" << endl;

    // key1 < key2 should be true
    bool lt1 = key1 < key2;
    cout << "  MonthYearKey(2023, 3) < MonthYearKey(2023, 7): " << (lt1 ? "true" : "false") << " (expected: true)" << endl;

    // key2 < key1 should be false
    bool lt2 = key2 < key1;
    cout << "  MonthYearKey(2023, 7) < MonthYearKey(2023, 3): " << (lt2 ? "true" : "false") << " (expected: false)" << endl;

    // key1 == key2 should be false
    bool eq1 = key1 == key2;
    cout << "  MonthYearKey(2023, 3) == MonthYearKey(2023, 7): " << (eq1 ? "true" : "false") << " (expected: false)" << endl;

    // key1 < key3 should be true
    bool lt3 = key1 < key3;
    cout << "  MonthYearKey(2023, 3) < MonthYearKey(2024, 2): " << (lt3 ? "true" : "false") << " (expected: true)" << endl;

    // Test transitive property
    MonthYearKey key4(2022, 12);
    MonthYearKey key5(2023, 1);
    MonthYearKey key6(2023, 6);

    bool transitive1 = key4 < key5;
    bool transitive2 = key5 < key6;
    bool transitive3 = key4 < key6; // Should be true if transitive

    cout << "Transitive property:" << endl;
    cout << "  (2022,12) < (2023,1): " << (transitive1 ? "true" : "false") << " (expected: true)" << endl;
    cout << "  (2023,1) < (2023,6): " << (transitive2 ? "true" : "false") << " (expected: true)" << endl;
    cout << "  (2022,12) < (2023,6): " << (transitive3 ? "true" : "false") << " (expected: true)" << endl;

    bool basicConsistency = lt1 && !lt2 && !eq1 && lt3;
    bool transitiveConsistency = transitive1 && transitive2 && transitive3;
    bool passed = basicConsistency && transitiveConsistency;

    reportResult("Comparison operators maintain consistency and transitive property", passed);
}

void MonthYearKeyTest::testBoundaryValues() {
    cout << "Test 5: Boundary Values" << endl;

    // Test minimum and maximum months
    MonthYearKey janKey(2023, 1);
    MonthYearKey decKey(2023, 12);

    cout << "Month boundaries:" << endl;
    cout << "  January (1) created successfully: " << (janKey.month == 1 ? "yes" : "no") << " (expected: yes)" << endl;
    cout << "  December (12) created successfully: " << (decKey.month == 12 ? "yes" : "no") << " (expected: yes)" << endl;
    cout << "  January < December: " << (janKey < decKey ? "true" : "false") << " (expected: true)" << endl;

    // Test year boundaries
    MonthYearKey earlyYear(2000, 6);
    MonthYearKey lateYear(2030, 6);

    cout << "Year boundaries:" << endl;
    cout << "  Year 2000 created successfully: " << (earlyYear.year == 2000 ? "yes" : "no") << " (expected: yes)" << endl;
    cout << "  Year 2030 created successfully: " << (lateYear.year == 2030 ? "yes" : "no") << " (expected: yes)" << endl;
    cout << "  2000 < 2030: " << (earlyYear < lateYear ? "true" : "false") << " (expected: true)" << endl;

    // Test December to January transition
    MonthYearKey dec2023(2023, 12);
    MonthYearKey jan2024(2024, 1);

    cout << "Year transition:" << endl;
    cout << "  (2023,12) < (2024,1): " << (dec2023 < jan2024 ? "true" : "false") << " (expected: true)" << endl;
    cout << "  (2024,1) < (2023,12): " << (jan2024 < dec2023 ? "true" : "false") << " (expected: false)" << endl;

    bool monthBoundariesCorrect = (janKey.month == 1) && (decKey.month == 12) && (janKey < decKey);
    bool yearBoundariesCorrect = (earlyYear.year == 2000) && (lateYear.year == 2030) && (earlyYear < lateYear);
    bool yearTransitionCorrect = (dec2023 < jan2024) && !(jan2024 < dec2023);
    bool passed = monthBoundariesCorrect && yearBoundariesCorrect && yearTransitionCorrect;

    reportResult("Boundary values are handled correctly", passed);
}

void MonthYearKeyTest::testMapCompatibility() {
    cout << "Test 6: Map Compatibility" << endl;

    // Test that MonthYearKey can be used as a Map key
    // This tests that the comparison operators work correctly for sorting

    // Create keys in unsorted order
    MonthYearKey key1(2023, 8);
    MonthYearKey key2(2022, 12);
    MonthYearKey key3(2023, 3);
    MonthYearKey key4(2024, 1);
    MonthYearKey key5(2023, 8); // Duplicate of key1

    cout << "Map key compatibility tests:" << endl;

    // Test ordering
    cout << "  Expected order: (2022,12) < (2023,3) < (2023,8) == (2023,8) < (2024,1)" << endl;

    bool order1 = key2 < key3; // 2022,12 < 2023,3
    bool order2 = key3 < key1; // 2023,3 < 2023,8
    bool order3 = key1 < key4; // 2023,8 < 2024,1
    bool equality = key1 == key5; // 2023,8 == 2023,8

    cout << "  (2022,12) < (2023,3): " << (order1 ? "true" : "false") << " (expected: true)" << endl;
    cout << "  (2023,3) < (2023,8): " << (order2 ? "true" : "false") << " (expected: true)" << endl;
    cout << "  (2023,8) < (2024,1): " << (order3 ? "true" : "false") << " (expected: true)" << endl;
    cout << "  (2023,8) == (2023,8): " << (equality ? "true" : "false") << " (expected: true)" << endl;

    // Test that equal keys are not less than each other
    bool notLess1 = !(key1 < key5);
    bool notLess2 = !(key5 < key1);

    cout << "  Equal keys symmetry:" << endl;
    cout << "    !(key1 < key5): " << (notLess1 ? "true" : "false") << " (expected: true)" << endl;
    cout << "    !(key5 < key1): " << (notLess2 ? "true" : "false") << " (expected: true)" << endl;

    bool orderingCorrect = order1 && order2 && order3;
    bool equalityCorrect = equality && notLess1 && notLess2;
    bool passed = orderingCorrect && equalityCorrect;

    reportResult("MonthYearKey is suitable for use as Map key with proper ordering", passed);
}
