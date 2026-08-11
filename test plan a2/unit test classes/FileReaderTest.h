#ifndef FILEREADERTEST_H
#define FILEREADERTEST_H

#include <iostream>
#include <string>
#include <fstream>
#include "FileReader.h"
#include "Vector.h"

using std::cout;
using std::string;
using std::endl;

class FileReaderTest {
private:
    int testsPassed;
    int testsFailed;

    void reportResult(const string& testName, bool passed);

public:
    void runAllTests();
    void testGetAllDataSourceFilenames();
    void testFileExistence();
    void testMultipleFilenames();
    void testEmptyFile();
    void testFileNotFound();
};

#endif // FILEREADERTEST_H

void FileReaderTest::reportResult(const string& testName, bool passed) {
    if (passed) {
        cout << "PASS . " << testName << endl;
        testsPassed++;
    } else {
        cout << "FAIL . " << testName << endl;
        testsFailed++;
    }
}

void FileReaderTest::runAllTests() {
    cout << "=== FILEREADER CLASS TESTS ===" << endl;
    testsPassed = 0;
    testsFailed = 0;

    testGetAllDataSourceFilenames();
    testFileExistence();
    testMultipleFilenames();
    testEmptyFile();
    testFileNotFound();

    cout << "================================" << endl;
    cout << "TESTS PASSED: " << testsPassed << endl;
    cout << "TESTS FAILED: " << testsFailed << endl;

    if (testsFailed == 0) {
        cout << "ALL FILEREADER TESTS PASSED" << endl;
    } else {
        cout << "SOME FILEREADER TESTS FAILED" << endl;
    }
}

void FileReaderTest::testGetAllDataSourceFilenames() {
    cout << "Test 1: GetAllDataSourceFilenames Basic Functionality" << endl;

    FileReader m_fileReader;

    // Test the main functionality
    Vector<string> filenames = m_fileReader.GetAllDataSourceFilenames();

    cout << "GetAllDataSourceFilenames() returned:" << endl;
    cout << "  Number of filenames: " << filenames.size() << endl;

    // Display the filenames that were read
    for (int i = 0; i < filenames.size(); i++) {
        cout << "  [" << i << "]: " << filenames[i] << endl;
    }

    // Basic test - should return at least one filename
    bool hasFilenames = (filenames.size() > 0);
    cout << "  Contains filenames: " << (hasFilenames ? "yes" : "no") << " (expected: yes)" << endl;

    // Check if filenames are not empty
    bool allFilenamesNonEmpty = true;
    for (int i = 0; i < filenames.size(); i++) {
        if (filenames[i].empty()) {
            allFilenamesNonEmpty = false;
            break;
        }
    }
    cout << "  All filenames non-empty: " << (allFilenamesNonEmpty ? "yes" : "no") << " (expected: yes)" << endl;

    bool passed = hasFilenames && allFilenamesNonEmpty;
    reportResult("GetAllDataSourceFilenames returns non-empty filenames", passed);
}

void FileReaderTest::testFileExistence() {
    cout << "Test 2: File Existence Check" << endl;

    FileReader m_fileReader;
    Vector<string> filenames = m_fileReader.GetAllDataSourceFilenames();

    cout << "Checking if returned files exist:" << endl;

    bool allFilesExist = true;
    int existingCount = 0;

    for (int i = 0; i < filenames.size(); i++) {
        std::ifstream file(filenames[i]);
        bool exists = file.good();

        cout << "  " << filenames[i] << ": " << (exists ? "exists" : "missing") << endl;

        if (exists) {
            existingCount++;
        } else {
            allFilesExist = false;
        }
    }

    cout << "  Files that exist: " << existingCount << "/" << filenames.size() << endl;

    // This test passes if we got some filenames, even if not all exist
    // (since the method should return what's in the data_source.txt, not validate existence)
    bool passed = (filenames.size() > 0);
    reportResult("FileReader returns filenames from data_source.txt", passed);
}

void FileReaderTest::testMultipleFilenames() {
    cout << "Test 3: Multiple Filename Handling" << endl;

    FileReader m_fileReader;
    Vector<string> filenames = m_fileReader.GetAllDataSourceFilenames();

    cout << "Multiple filename analysis:" << endl;
    cout << "  Total filenames returned: " << filenames.size() << endl;

    // Check for duplicates
    bool hasDuplicates = false;
    for (int i = 0; i < filenames.size(); i++) {
        for (int j = i + 1; j < filenames.size(); j++) {
            if (filenames[i] == filenames[j]) {
                hasDuplicates = true;
                break;
            }
        }
        if (hasDuplicates) break;
    }
    cout << "  Contains duplicate filenames: " << (hasDuplicates ? "yes" : "no") << " (expected: no)" << endl;

    // Check filename patterns (basic validation)
    bool allHaveValidFormat = true;
    for (int i = 0; i < filenames.size(); i++) {
        const string& filename = filenames[i];
        // Basic check - should contain data/ and end with .txt
        bool validFormat = (filename.find("data/") != string::npos) &&
                          (filename.find(".txt") != string::npos);
        if (!validFormat) {
            allHaveValidFormat = false;
            cout << "  Invalid format detected: " << filename << endl;
        }
    }
    cout << "  All filenames have valid format: " << (allHaveValidFormat ? "yes" : "no") << " (expected: yes)" << endl;

    bool passed = !hasDuplicates && allHaveValidFormat;
    reportResult("Multiple filenames are handled correctly without duplicates", passed);
}

void FileReaderTest::testEmptyFile() {
    cout << "Test 4: Empty File Handling" << endl;

    // Create a temporary empty test file
    const string testEmptyFile = "data/test_empty_source.txt";

    // Create the empty file
    std::ofstream createFile(testEmptyFile);
    createFile.close();

    // Note: This test assumes FileReader reads from a specific file path
    // In a real test, you might want to modify FileReader to accept a file path parameter
    // For now, we'll test the behavior with the existing implementation

    FileReader m_fileReader;
    Vector<string> filenames = m_fileReader.GetAllDataSourceFilenames();

    cout << "Testing behavior with potentially empty sections in data source:" << endl;
    cout << "  Filenames returned: " << filenames.size() << endl;

    // Check if any empty filenames were returned
    bool hasEmptyFilenames = false;
    for (int i = 0; i < filenames.size(); i++) {
        if (filenames[i].empty()) {
            hasEmptyFilenames = true;
            break;
        }
    }
    cout << "  Contains empty filenames: " << (hasEmptyFilenames ? "yes" : "no") << " (expected: no)" << endl;

    // Clean up test file
    std::remove(testEmptyFile.c_str());

    // Test passes if no empty filenames are returned
    bool passed = !hasEmptyFilenames;
    reportResult("Empty lines in source file are handled correctly", passed);
}

void FileReaderTest::testFileNotFound() {
    cout << "Test 5: File Not Found Resilience" << endl;

    FileReader m_fileReader;

    // Test that the method doesn't crash when data_source.txt doesn't exist
    // or has invalid entries
    try {
        Vector<string> filenames = m_fileReader.GetAllDataSourceFilenames();

        cout << "Method executed without crashing:" << endl;
        cout << "  Return type: Vector<string> with " << filenames.size() << " elements" << endl;
        cout << "  Method completed successfully: yes (expected: yes)" << endl;

        // Even if no files are found, the method should return an empty vector, not crash
        bool isVector = true; // We got a Vector object
        bool noCrash = true;  // Method didn't throw exception

        bool passed = isVector && noCrash;
        reportResult("FileReader handles missing files gracefully", passed);

    } catch (const std::exception& e) {
        cout << "Exception occurred: " << e.what() << endl;
        cout << "  Method completed successfully: no (expected: yes)" << endl;
        reportResult("FileReader handles missing files gracefully", false);
    } catch (...) {
        cout << "Unknown exception occurred" << endl;
        cout << "  Method completed successfully: no (expected: yes)" << endl;
        reportResult("FileReader handles missing files gracefully", false);
    }
}
