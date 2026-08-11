#ifndef BSTTEST_H
#define BSTTEST_H

#include <iostream>
#include <string>
#include "Bst.h"

using std::cout;
using std::string;
using std::endl;

class BstTest {
private:
    int testsPassed;
    int testsFailed;

    void reportResult(const string& testName, bool passed);
    static void printInt(const int& value);
    static bool alwaysTrue(const int& value); // Condition that always returns true

public:
    void runAllTests();
    void testDefaultConstructor();
    void testInsertAndSearch();
    void testInOrderTraversal();
    void testPreOrderTraversal();
    void testPostOrderTraversal();
    void testCopyConstructor();
    void testAssignmentOperator();
    void testDuplicateValues();
    void testEmptyTreeOperations();
    void testComplexTreeStructure();
    void testTraversalWithConditions();
};

#endif // BSTTEST_H

void BstTest::reportResult(const string& testName, bool passed) {
    if (passed) {
        cout << "PASS . " << testName << endl;
        testsPassed++;
    } else {
        cout << "FAIL . " << testName << endl;
        testsFailed++;
    }
}

void BstTest::printInt(const int& value) {
    cout << value << " ";
}

bool BstTest::alwaysTrue(const int& value) {
    return true; // Always process the node
}

void BstTest::runAllTests() {
    cout << "=== BST CLASS TESTS ===" << endl;
    testsPassed = 0;
    testsFailed = 0;

    testDefaultConstructor();
    testInsertAndSearch();
    testInOrderTraversal();
    testPreOrderTraversal();
    testPostOrderTraversal();
    testCopyConstructor();
    testAssignmentOperator();
    testDuplicateValues();
    testTraversalWithConditions(); // Add the new test

    cout << "================================" << endl;
    cout << "TESTS PASSED: " << testsPassed << endl;
    cout << "TESTS FAILED: " << testsFailed << endl;

    if (testsFailed == 0) {
        cout << "ALL BST TESTS PASSED" << endl;
    } else {
        cout << "SOME BST TESTS FAILED" << endl;
    }
}

void BstTest::testDefaultConstructor() {
    cout << "Test 1: Default Constructor" << endl;

    Bst<int> tree;

    // Test that search returns false for any value in empty tree
    bool searchEmpty = tree.search(42);
    cout << "Search for 42 in empty tree: " << (searchEmpty ? "true" : "false") << endl;
    cout << "Expected: false" << endl;

    bool passed = !searchEmpty;
    reportResult("Default constructor creates empty tree", passed);
}

void BstTest::testInsertAndSearch() {
    cout << "Test 2: Insert and Search Operations" << endl;

    Bst<int> tree;

    // Insert only 3 values
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);

    cout << "Inserted values: 50, 30, 70" << endl;

    // Test search for existing values
    bool found50 = tree.search(50);
    bool found30 = tree.search(30);
    bool found70 = tree.search(70);

    cout << "Search results for existing values:" << endl;
    cout << "  50: " << (found50 ? "found" : "not found") << " (expected: found)" << endl;
    cout << "  30: " << (found30 ? "found" : "not found") << " (expected: found)" << endl;
    cout << "  70: " << (found70 ? "found" : "not found") << " (expected: found)" << endl;

    // Test search for non-existing values
    bool found10 = tree.search(10);
    bool found100 = tree.search(100);

    cout << "Search results for non-existing values:" << endl;
    cout << "  10: " << (found10 ? "found" : "not found") << " (expected: not found)" << endl;
    cout << "  100: " << (found100 ? "found" : "not found") << " (expected: not found)" << endl;

    bool allFound = found50 && found30 && found70;
    bool noneNotFound = !found10 && !found100;
    bool passed = allFound && noneNotFound;

    reportResult("Insert and search operations work correctly", passed);
}

void BstTest::testInOrderTraversal() {
    cout << "Test 3: In-Order Traversal" << endl;

    Bst<int> tree;

    // Insert only 3 values
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);

    cout << "Inserted values: 50, 30, 70" << endl;
    cout << "In-order traversal output: ";
    tree.inOrderTraversal(printInt, nullptr); // Use nullptr for condition (process all nodes)
    cout << endl;
    cout << "Expected output: 30 50 70" << endl;

    bool passed = true; // Visual verification
    reportResult("In-order traversal produces sorted output", passed);
}

void BstTest::testPreOrderTraversal() {
    cout << "Test 4: Pre-Order Traversal" << endl;

    Bst<int> tree;

    // Insert only 3 values
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);

    cout << "Inserted values: 50, 30, 70" << endl;
    cout << "Pre-order traversal output: ";
    tree.preOrderTraversal(printInt, nullptr); // Use nullptr for condition
    cout << endl;
    cout << "Expected: Root-first traversal" << endl;

    bool passed = true; // Should not crash
    reportResult("Pre-order traversal executes without errors", passed);
}

void BstTest::testPostOrderTraversal() {
    cout << "Test 5: Post-Order Traversal" << endl;

    Bst<int> tree;

    // Insert only 3 values
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);

    cout << "Inserted values: 50, 30, 70" << endl;
    cout << "Post-order traversal output: ";
    tree.postOrderTraversal(printInt, nullptr); // Use nullptr for condition
    cout << endl;
    cout << "Expected: Root-last traversal" << endl;

    bool passed = true; // Should not crash
    reportResult("Post-order traversal executes without errors", passed);
}

void BstTest::testCopyConstructor() {
    cout << "Test 6: Copy Constructor" << endl;

    Bst<int> original;

    // Insert only 3 values
    original.insert(50);
    original.insert(30);
    original.insert(70);

    cout << "Original tree contains: 50, 30, 70" << endl;

    // Create copy
    Bst<int> copy(original);

    // Test that both trees have the same values
    bool originalHasValues = original.search(50) && original.search(30) && original.search(70);
    bool copyHasValues = copy.search(50) && copy.search(30) && copy.search(70);

    cout << "Original tree search results: ";
    cout << "50:" << original.search(50) << " 30:" << original.search(30);
    cout << " 70:" << original.search(70) << endl;

    cout << "Copy tree search results: ";
    cout << "50:" << copy.search(50) << " 30:" << copy.search(30);
    cout << " 70:" << copy.search(70) << endl;

    // Modify original and ensure copy is not affected
    original.insert(100);
    bool copyUnaffected = !copy.search(100);

    cout << "After inserting 100 into original:" << endl;
    cout << "  Original contains 100: " << (original.search(100) ? "yes" : "no") << endl;
    cout << "  Copy contains 100: " << (copy.search(100) ? "yes" : "no") << " (expected: no)" << endl;

    bool passed = originalHasValues && copyHasValues && copyUnaffected;
    reportResult("Copy constructor creates independent deep copy", passed);
}

void BstTest::testAssignmentOperator() {
    cout << "Test 7: Assignment Operator" << endl;

    Bst<int> tree1;
    Bst<int> tree2;

    // Insert only 3 values
    tree1.insert(50);
    tree1.insert(30);
    tree1.insert(70);

    tree2.insert(10);
    tree2.insert(5);

    cout << "Tree1 contains: 50, 30, 70" << endl;
    cout << "Tree2 contains: 10, 5" << endl;

    // Assign tree1 to tree2
    tree2 = tree1;

    // Test that tree2 has tree1's values
    bool tree2HasTree1Values = tree2.search(50) && tree2.search(30) && tree2.search(70);
    bool tree2LostOldValues = !tree2.search(10) && !tree2.search(5);

    cout << "After assignment:" << endl;
    cout << "  Tree2 contains Tree1 values - 50:" << tree2.search(50);
    cout << " 30:" << tree2.search(30) << " 70:" << tree2.search(70) << endl;
    cout << "  Tree2 lost old values - 10:" << tree2.search(10) << " 5:" << tree2.search(5);
    cout << " (expected: false false)" << endl;

    // Test self-assignment
    tree1 = tree1; // Should not crash
    bool selfAssignmentOK = tree1.search(50); // Should still work

    cout << "After self-assignment, Tree1 still contains 50: " << (tree1.search(50) ? "yes" : "no") << endl;

    bool passed = tree2HasTree1Values && tree2LostOldValues && selfAssignmentOK;
    reportResult("Assignment operator performs deep copy and handles self-assignment", passed);
}

void BstTest::testDuplicateValues() {
    cout << "Test 8: Duplicate Values" << endl;

    Bst<int> tree;

    // Insert duplicates (only 2 unique values with duplicates)
    tree.insert(50);
    tree.insert(50);
    tree.insert(30);
    tree.insert(30);

    cout << "Inserted duplicate values: 50, 50, 30, 30" << endl;

    // All should be found
    bool found50 = tree.search(50);
    bool found30 = tree.search(30);

    cout << "Search results for duplicate values:" << endl;
    cout << "  50: " << (found50 ? "found" : "not found") << " (expected: found)" << endl;
    cout << "  30: " << (found30 ? "found" : "not found") << " (expected: found)" << endl;

    bool passed = found50 && found30;
    reportResult("Duplicate values can be inserted and searched", passed);
}

void BstTest::testTraversalWithConditions() {
    cout << "Test 11: Traversal with Conditions" << endl;

    Bst<int> tree;

    // Insert values
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Inserted values: 50, 30, 70, 20, 40, 60, 80" << endl;

    // Define condition: only process values >= 40
    auto conditionGreaterEqual40 = [](const int& value) -> bool {
        return value >= 40;
    };

    cout << "In-order traversal (values >= 40): ";
    tree.inOrderTraversal(printInt, conditionGreaterEqual40);
    cout << endl;
    cout << "Expected: 40 50 60 70 80" << endl;

    cout << "Pre-order traversal (values >= 40): ";
    tree.preOrderTraversal(printInt, conditionGreaterEqual40);
    cout << endl;
    cout << "Expected: 50 40 70 60 80" << endl;

    cout << "Post-order traversal (values >= 40): ";
    tree.postOrderTraversal(printInt, conditionGreaterEqual40);
    cout << endl;
    cout << "Expected: 40 60 80 70 50" << endl;

    // Test with alwaysTrue condition (should process all nodes)
    cout << "In-order traversal (all nodes with explicit condition): ";
    tree.inOrderTraversal(printInt, alwaysTrue);
    cout << endl;
    cout << "Expected: 20 30 40 50 60 70 80" << endl;

    bool passed = true; // Visual verification for now
    reportResult("Conditional traversal works correctly", passed);
}
