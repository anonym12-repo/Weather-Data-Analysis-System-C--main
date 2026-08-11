

#ifndef MAPTEST_H
#define MAPTEST_H

#include <iostream>
#include <string>
#include "Map.h"

using std::cout;
using std::string;
using std::endl;

class MapTest {
private:
    int testsPassed;
    int testsFailed;

    void reportResult(const string& testName, bool passed);

public:
    void runAllTests();
    void testDefaultConstructor();
    void testInsertOperations();
    void testContainsOperations();
    void testGetOperations();
    void testDuplicateKeys();
    void testConstGetOperations();

};

#endif // MAPTEST_H

void MapTest::reportResult(const string& testName, bool passed) {
    if (passed) {
        cout << "PASS . " << testName << endl;
        testsPassed++;
    } else {
        cout << "FAIL . " << testName << endl;
        testsFailed++;
    }
}

void MapTest::runAllTests() {
    cout << "=== MAP CLASS TESTS ===" << endl;
    testsPassed = 0;
    testsFailed = 0;

    testDefaultConstructor();
    testInsertOperations();
    testContainsOperations();
    testGetOperations();
    testDuplicateKeys();
    testConstGetOperations();

    cout << "================================" << endl;
    cout << "TESTS PASSED: " << testsPassed << endl;
    cout << "TESTS FAILED: " << testsFailed << endl;

    if (testsFailed == 0) {
        cout << "ALL MAP TESTS PASSED" << endl;
    } else {
        cout << "SOME MAP TESTS FAILED" << endl;
    }
}


void MapTest::testDefaultConstructor() {
    cout << "Test 1: Default Constructor" << endl;

    Map<int, string> m_map;

    // Test that contains returns false for any key in empty map
    bool containsEmpty = m_map.contains(42);
    cout << "Contains key 42 in empty m_map: " << (containsEmpty ? "true" : "false") << endl;
    cout << "Expected: false" << endl;

    bool passed = !containsEmpty;
    reportResult("Default constructor creates empty map", passed);
}

void MapTest::testInsertOperations() {
    cout << "Test 2: Insert Operations" << endl;

    Map<int, string> m_map;

    // Insert key-value pairs
    bool insert1 = m_map.inserts(1, "one");
    bool insert2 = m_map.inserts(2, "two");
    bool insert3 = m_map.inserts(3, "three");

    cout << "Insert operations:" << endl;
    cout << "  Insert (1, 'one'): " << (insert1 ? "success" : "failed") << " (expected: success)" << endl;
    cout << "  Insert (2, 'two'): " << (insert2 ? "success" : "failed") << " (expected: success)" << endl;
    cout << "  Insert (3, 'three'): " << (insert3 ? "success" : "failed") << " (expected: success)" << endl;

    // Verify all keys exist
    bool contains1 = m_map.contains(1);
    bool contains2 = m_map.contains(2);
    bool contains3 = m_map.contains(3);

    cout << "Contains operations after insert:" << endl;
    cout << "  Contains key 1: " << (contains1 ? "yes" : "no") << " (expected: yes)" << endl;
    cout << "  Contains key 2: " << (contains2 ? "yes" : "no") << " (expected: yes)" << endl;
    cout << "  Contains key 3: " << (contains3 ? "yes" : "no") << " (expected: yes)" << endl;

    bool allInsertsSuccess = insert1 && insert2 && insert3;
    bool allContainsSuccess = contains1 && contains2 && contains3;
    bool passed = allInsertsSuccess && allContainsSuccess;

    reportResult("Insert operations work correctly", passed);
}

void MapTest::testContainsOperations() {
    cout << "Test 3: Contains Operations" << endl;

    Map<int, string> m_map;

    // Insert some values
    m_map.inserts(10, "ten");
    m_map.inserts(20, "twenty");
    m_map.inserts(30, "thirty");

    cout << "Inserted keys: 10, 20, 30" << endl;

    // Test contains for existing keys
    bool contains10 = m_map.contains(10);
    bool contains20 = m_map.contains(20);
    bool contains30 = m_map.contains(30);

    cout << "Contains existing keys:" << endl;
    cout << "  Contains 10: " << (contains10 ? "yes" : "no") << " (expected: yes)" << endl;
    cout << "  Contains 20: " << (contains20 ? "yes" : "no") << " (expected: yes)" << endl;
    cout << "  Contains 30: " << (contains30 ? "yes" : "no") << " (expected: yes)" << endl;

    // Test contains for non-existing keys
    bool contains5 = m_map.contains(5);
    bool contains25 = m_map.contains(25);
    bool contains40 = m_map.contains(40);

    cout << "Contains non-existing keys:" << endl;
    cout << "  Contains 5: " << (contains5 ? "yes" : "no") << " (expected: no)" << endl;
    cout << "  Contains 25: " << (contains25 ? "yes" : "no") << " (expected: no)" << endl;
    cout << "  Contains 40: " << (contains40 ? "yes" : "no") << " (expected: no)" << endl;

    bool allExistingFound = contains10 && contains20 && contains30;
    bool noneNonExistingFound = !contains5 && !contains25 && !contains40;
    bool passed = allExistingFound && noneNonExistingFound;

    reportResult("Contains operations work correctly", passed);
}

void MapTest::testGetOperations() {
    cout << "Test 4: Get Operations" << endl;

    Map<int, string> m_map;

    // Insert key-value pairs
    m_map.inserts(100, "hundred");
    m_map.inserts(200, "two hundred");
    m_map.inserts(300, "three hundred");

    cout << "Inserted: (100, 'hundred'), (200, 'two hundred'), (300, 'three hundred')" << endl;

    // Test get for existing keys
    try {
        string value1 = m_map.get(100);
        string value2 = m_map.get(200);
        string value3 = m_map.get(300);

        cout << "Get operations:" << endl;
        cout << "  Get(100): '" << value1 << "' (expected: 'hundred')" << endl;
        cout << "  Get(200): '" << value2 << "' (expected: 'two hundred')" << endl;
        cout << "  Get(300): '" << value3 << "' (expected: 'three hundred')" << endl;

        bool valuesCorrect = (value1 == "hundred") && (value2 == "two hundred") && (value3 == "three hundred");

        // Test modification through reference
        m_map.get(100) = "modified hundred";
        string modifiedValue = m_map.get(100);
        cout << "After modification - Get(100): '" << modifiedValue << "' (expected: 'modified hundred')" << endl;

        bool modificationWorks = (modifiedValue == "modified hundred");
        bool passed = valuesCorrect && modificationWorks;

        reportResult("Get operations work correctly", passed);

    } catch (const std::exception& e) {
        cout << "Exception during get operations: " << e.what() << endl;
        reportResult("Get operations work correctly", false);
    }
}

void MapTest::testDuplicateKeys() {
    cout << "Test 5: Duplicate Key Handling" << endl;

    Map<int, string> m_map;

    // Insert first key-value pair
    bool firstInsert = m_map.inserts(5, "first");
    cout << "First insert (5, 'first'): " << (firstInsert ? "success" : "failed") << " (expected: success)" << endl;

    // Try to insert duplicate key
    bool duplicateInsert = m_map.inserts(5, "duplicate");
    cout << "Duplicate insert (5, 'duplicate'): " << (duplicateInsert ? "success" : "failed") << " (expected: failed)" << endl;

    // Verify original value is unchanged
    string value = m_map.get(5);
    cout << "Value for key 5 after duplicate attempt: '" << value << "' (expected: 'first')" << endl;

    bool firstInsertSuccess = firstInsert;
    bool duplicateInsertFailed = !duplicateInsert;
    bool valueUnchanged = (value == "first");
    bool passed = firstInsertSuccess && duplicateInsertFailed && valueUnchanged;

    reportResult("Duplicate keys are rejected and original values preserved", passed);
}

void MapTest::testConstGetOperations() {
    cout << "Test 6: Const Get Operations" << endl;

    Map<int, string> m_map;

    // Insert key-value pairs
    m_map.inserts(1, "const one");
    m_map.inserts(2, "const two");

    // Test const version of get
    const Map<int, string>& constMap = m_map;

    try {
        const string& value1 = constMap.get(1);
        const string& value2 = constMap.get(2);

        cout << "Const get operations:" << endl;
        cout << "  Const get(1): '" << value1 << "' (expected: 'const one')" << endl;
        cout << "  Const get(2): '" << value2 << "' (expected: 'const two')" << endl;

        bool valuesCorrect = (value1 == "const one") && (value2 == "const two");

        // Verify we can't modify through const reference (this would cause compile error if uncommented)
        //value1 = "modified"; // This should not compile

        bool passed = valuesCorrect;
        reportResult("Const get operations work correctly", passed);

    } catch (const std::exception& e) {
        cout << "Exception during const get operations: " << e.what() << endl;
        reportResult("Const get operations work correctly", false);
    }
}
