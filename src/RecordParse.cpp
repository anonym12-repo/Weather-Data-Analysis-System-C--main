#include "RecordParse.h"
#include "Date.h"
#include "MyTime.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Read and parse weather data from CSV file
Vector<WeatherRecord> ReadFile(const std::string& filename) {
    std::ifstream inFile(filename);  // Open input file
    Vector<WeatherRecord> weather_data;  // Vector to store parsed records

    // Check if file opened successfully
    if (!inFile) {
        std::cerr << "Error: cannot open file " << filename << "\n";
        return weather_data;  // Return empty vector on error
    }

    std::string headerL;  // Variable to store header line
    getline(inFile, headerL);  // Read first line (col headers)

    // Clean the header line
    //remove carriage returns because this was happening Looking for col "SR" but finding "SR\r"
    std::string cleanHeader;
    for (size_t i = 0; i < headerL.length(); ++i) {
        if (headerL[i] != '\r') {  // Skip carriage return characters
            cleanHeader += headerL[i];  // Build clean string
        }
    }
    headerL = cleanHeader;  // Replace with cleaned header

    std::stringstream ss(headerL);  // Create string stream for parsing
    std::string col;  // Variable to store each col name
    Vector<std::string> headers;  // Vector to store all col headers

    // Parse header line by splitting on commas
    while (getline(ss, col, ',')) {
        headers.pushBack(col);  // Add each col name to headers vector
    }

    // Initialize col indices to -1 (not found)
    int wastIdx = -1, speedIdx = -1, tempIdx = -1, solarRadIdx = -1;
    // Find indices of required columns by name
    for (int i = 0; i < headers.size(); ++i) {
        if (headers[i] == "WAST"){
            wastIdx = i;
        }else if (headers[i] == "S"){
            speedIdx = i;
        }else if (headers[i] == "T"){
            tempIdx = i;
        }else if (headers[i] == "SR"){
            solarRadIdx = i;
        }
    }

    // Validate that all required columns were found
    if (wastIdx == -1 || speedIdx == -1 || tempIdx == -1 || solarRadIdx == -1) {
        std::cerr << "Error: required columns not present.\n";
        std::cerr << "Found columns are: ";
        // Display all found columns
        for (int i = 0; i < headers.size(); ++i) {
            std::cerr << headers[i] << " ";
        }
        std::cerr << "\n";
        return weather_data; // Return empty vector on error
    }

    // Find maximum col index
    int maxIndex = wastIdx;
    if (speedIdx > maxIndex){
            maxIndex = speedIdx;
    }
    if (tempIdx > maxIndex){
        maxIndex = tempIdx;

    }
    if (solarRadIdx > maxIndex){
        maxIndex = solarRadIdx;
    }

    std::string line;  // Variable to store each data line
    int lineCount = 0;  //for debugging
    // Process each data line in the file
    while (getline(inFile, line)){
        lineCount++;

        // Clean the data line (remove carriage returns)
        std::string cleanLine;
        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] != '\r') {
                cleanLine += line[i];
            }
        }
        line = cleanLine;

        std::stringstream row(line);  // Create string stream for parsing data line
        std::string field;  // Variable to store each field
        Vector<std::string> fields;  // Vector to store all fields in the row
        // Parse data line by splitting on commas
        while (getline(row, field, ',')){
            fields.pushBack(field);  // Add each field to fields vector
        }

        // Check if row has enough columns for all required data
        if (fields.size() > maxIndex) {
            std::string wastField = fields[wastIdx];
            std::stringstream wastss(wastField);
            std::string dateStr, timeStr;
            wastss >> dateStr >> timeStr;

            // Parse date (format: DD/MM/YYYY)
            int dd, mm, yyyy;
            char slash;
            std::stringstream ds(dateStr);  // Create stream for parsing date
            if (ds >> dd >> slash >> mm >> slash >> yyyy){  // Parse date components
                Date d(dd, mm, yyyy);  // Create Date object

                // Parse time (format: HH:MM)
                int hrs, mins;
                char colon;
                std::stringstream ts(timeStr);  // Create stream for parsing time
                if (ts >> hrs >> colon >> mins){  //Parse time components
                    MyTime t(hrs, mins);

                    // Extract data fields from CSV columns
                    std::string speedStr = fields[speedIdx];
                    std::string tempStr = fields[tempIdx];
                    std::string solarRadStr = fields[solarRadIdx];

                    // Check for valid data (not empty and not "NA")
                    if (!speedStr.empty() && speedStr != "N/A" &&
                        !tempStr.empty() && tempStr != "N/A" &&
                        !solarRadStr.empty() && solarRadStr != "N/A") {

                        try{
                            // Convert string data to numeric values
                            float speed = std::stof(speedStr);
                            float temp = std::stof(tempStr);
                            float sr = std::stof(solarRadStr);
                            // Create WeatherRecord with parsed data
                            //if (sr >= 100.0f) {
                                WeatherRecord rec(d, t, speed, temp, sr);
                                weather_data.pushBack(rec);
                            //}
                        } catch (const std::exception& e) {
                            std::cerr << "error parsing data!" << "\n";
                        }
                    }
                }
            }
        }
    }
    // Report success and return parsed data
    std::cout << "Successfully read " << weather_data.size() << " records from " << filename << "\n";
    return weather_data; // Return vector of parsed weather records
}


