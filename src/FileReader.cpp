#include "FileReader.h"
#include <fstream>
#include <iostream>

// Local helper - not exposed to header
bool containsFilename(const Vector<std::string>& filenames, const std::string& target) {
    // Iterate through all filenames in the vector
    for (int i = 0; i < filenames.size(); ++i) {
        // Check if current filename matches the target filename
        if (filenames[i] == target) {
            // Found a match - target filename exists in the vector
            return true;
        }
    }
    // No match found after checking all filenames
    return false;
}

Vector<std::string> GetAllDataSourceFilenames(){
    Vector<std::string> dataFilenames;
    // Open the data file
    std::ifstream sourceFile("data/data_source.txt");

    if (!sourceFile) {
        std::cerr << "Error: Could not open data/data_source.txt\n";
        return dataFilenames; // Return empty vector on error
    }

    std::string dataFilename;
    int fileCount = 0;

    // Read each line (each line is a CSV filename)
    while (getline(sourceFile, dataFilename)) {
        // Remove carriage returns if present
        std::string cleanFilename;
        for (size_t i = 0; i < dataFilename.length(); ++i) {
            if (dataFilename[i] != '\r') {
                cleanFilename += dataFilename[i];
            }
        }
        dataFilename = cleanFilename;

        // Skip empty lines
        if (!dataFilename.empty()) {
            // Construct full path by prepending data directory
            std::string fullPath = "data/" + dataFilename;

            if (!containsFilename(dataFilenames, fullPath)) {
                dataFilenames.pushBack(fullPath);
                fileCount++;
                std::cout << "Found data file: " << fullPath << "\n";
            } else {
                std::cout << "Duplicate skipped: " << fullPath << "\n";
            }
        }
    }

    if (fileCount == 0) {
        std::cerr << "Error: No data files found in data_source.txt\n";
    } else {
        std::cout << "Total data files to process: " << fileCount << "\n";
    }

    return dataFilenames;
}


