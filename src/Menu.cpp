#include "Menu.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Stats.h"
#include "UnitConvert.h"
#include "MonthlyData.h"



// Constructor - initialize with reference to aggregator
Menu::Menu(const WindlogAggregator& agg)
:aggregator(agg) {
}

// Main menu loop
void Menu::run() const{
    int choice; // Variable to store user's menu choice

    // Main menu loop - continues until user chooses to exit
    do {
        // Display menu options
        std::cout << "\n=== Weather Data Analysis Menu ===\n";
        std::cout << "1. Average wind speed and standard deviation for a specific month and year\n";
        std::cout << "2. Average ambient air temperature and standard deviation for each month of a specified year\n";
        std::cout << "3. Sample Pearson Correlation Coefficient for a specific month across all years\n";
        std::cout << "4. Export comprehensive data to file (WindTempSolar.csv)\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice (1-5): ";

        //get user choice
        std::cin >> choice;
        //process users choice using switch
        switch (choice) {
            case 1:
                option1(); // avg and std dev of wind speed function
                break;
            case 2:
                option2(); //avg and std dev of temperature for a year
                break;
            case 3:
                option3(); //total sr for each month in kwh/m2
                break;
            case 4:
                option4(); //write records to file
                break;
            case 5:
                std::cout << "Goodbye!\n"; //exit
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5); //continue until user exits
}

void Menu::option1() const{
    int year, month;  // Variables to store user input for year and month
    std::cout << "Enter year: ";
    std::cin >> year;
    std::cout << "Enter month (1-12): ";
    std::cin >> month;

    MonthlyData tempData(year, month); // Create with user input

    if (!tempData.isValid()) {
        // Determine which field is invalid
        if (month < 1 || month > 12) {
            std::cout << "Invalid month! Please enter a value between 1 and 12.\n";
        }
        if (year <= 0) {
            std::cout << "Invalid year! Please enter a positive year.\n";
        }
        return;
    }

    // Check if data exists for the specified month and year
    if (!aggregator.hasDataForMonth(year, month)){
        std::cout << getMonthName(month) << " " << year << ": No Data\n";
        return; // Exit if no data available
    }

    // Get wind speeds for the specified month and year
    Vector<float> speeds = aggregator.getSpeeds(year, month);

    if (speeds.size() == 0){  // Check if speed data is actually available
        std::cout << getMonthName(month) << " " << year << ": No Data\n";
        return; // Exit if no speed data found
    }

    // Convert speeds from m/s to km/h for display
    Vector<float> speedsKmh = convertSpeedsToKmh(speeds);

    // Calculate statistics for wind speeds
    double avgSpeed = calculateMean(speedsKmh); //avg speed
    double stdDevSpeed = calculateStdDev(speedsKmh); //std dev speed

    // display results
    std::cout << std::fixed << std::setprecision(1);
    std::cout << getMonthName(month) << " " << year << ":\n";
    std::cout << "Average speed: " << avgSpeed << " km/h\n";
    std::cout << "Sample stdev: " << stdDevSpeed << "\n";
}

void Menu::option2() const{
    int year;
    std::cout << "Enter year: ";
    std::cin >> year; // Get year from use

    std::cout << year << "\n";  // Display the year being analyzed
    bool hasAnyData = false;    // Flag to track if any data was found

    // Loop through all 12 months of the year
    for (int month = 1; month <= 12; ++month){
        // Check if data exists for this specific month
        if (aggregator.hasDataForMonth(year, month)){
            Vector<float> temps = aggregator.getTemps(year, month);  // Get temperature data
            if (temps.size()> 0) {  // Check if temperature data is available

                // Calculate temperature statistics
                double avgTemp = calculateMean(temps);      // Calculate average temperature
                double stdDevTemp = calculateStdDev(temps); // Calculate standard deviation

                //display result
                std::cout << std::fixed << std::setprecision(1);
                std::cout << getMonthName(month) << ": average: " << avgTemp
                         << " degrees C, stdev: " << stdDevTemp << "\n";
                hasAnyData = true; // Mark that we found some data
            }else{
                // otherwise Display no data message for this month
                std::cout << getMonthName(month) << ": No Data\n";
            }
        }else{
            // Display no data message if month has no data at all
            std::cout << getMonthName(month) << ": No Data\n";
        }
    }
    // Display message if no data was found for the entire year
    if (!hasAnyData){
        std::cout << "No data available for " << year << "\n";
    }
}

void Menu::option3() const {
    int month;
    std::cout << "Enter month (1-12): ";
    std::cin >> month;

    // Input validation
    if (month < 1 || month > 12) {
        std::cout << "Invalid month! Please enter a value between 1 and 12.\n";
        return;
    }

    // Get all records across all years for this month
    Vector<WeatherRecord> monthRecords = aggregator.getAllRecordsForMonth(month);

    if (monthRecords.isEmpty()) {
        std::cout << getMonthName(month) << ": No Data\n";
        return;
    }

    // --- Separate data for different correlation types ---
    Vector<float> allSpeeds;      // for S_T
    Vector<float> allTemps;       // for S_T
    Vector<float> validSpeeds;    // for S_R
    Vector<float> validTemps;     // for T_R
    Vector<float> validSolar;     // for both S_R & T_R

    for (int i = 0; i < monthRecords.size(); ++i) {
        const WeatherRecord& rec = monthRecords[i];

        // Always include for Speed–Temp correlation
        allSpeeds.pushBack(rec.GetSpeed());
        allTemps.pushBack(rec.GetTemp());

        // Only include for solar-based correlations if SR ≥ 100 W/m²
        if (rec.GetSolarRad() >= 100.0f) {
            validSpeeds.pushBack(rec.GetSpeed());
            validTemps.pushBack(rec.GetTemp());
            validSolar.pushBack(rec.GetSolarRad());
        }
    }


    // --- Check minimum data requirements ---
    if (allSpeeds.size() < 2 || validSolar.size() < 2) {
        std::cout << getMonthName(month)
                  << " Insufficient data for meaningful correlation.\n";
        return;
    }


    // --- Calculate correlations ---
    double s_t = calculateSpcc(allSpeeds, allTemps); // wind–temp
    double s_r = calculateSpcc(validSpeeds, validSolar); // wind–solar
    double t_r = calculateSpcc(validTemps, validSolar); // temp–solar

    // --- Display results ---
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Sample Pearson Correlation Coefficient for "
              << getMonthName(month) << "\n";
    std::cout << "S_T: " << s_t << "  (Wind Speed vs Temperature)\n";
    std::cout << "S_R: " << s_r << "  (Wind Speed vs Solar Radiation)\n";
    std::cout << "T_R: " << t_r << "  (Temperature vs Solar Radiation)\n";
}


void Menu::option4() const{
    int year;
    std::cout << "Enter year: ";
    std::cin >> year;

    // Open output file for writing
    std::ofstream outFile("WindTempSolar.csv");
    if (!outFile) {  // Check if file opened successfully
        std::cerr << "Error: Cannot create WindTempSolar.csv\n";
        return;  // Exit if file creation failed
    }
    // Write CSV header lines
    outFile << year << "\n";
    outFile << "Month,Average Wind Speed(stdev, mad),Average Ambient Temperature(stdev, mad),Solar Radiation\n";

    bool hasAnyData = false;  // Flag to track if any data was written
    // Loop through all 12 months of the year
    for (int month = 1; month <= 12; ++month){

        // Check if data exists for this specific month
        if (aggregator.hasDataForMonth(year, month)){

            // Get all data types for this month
            Vector<float> speeds = aggregator.getSpeeds(year, month);
            Vector<float> temps = aggregator.getTemps(year, month);
            Vector<float> solar = aggregator.getSolar(year, month);

            // Check which data types are actually available
            bool hasSpeed = (speeds.size() > 0);
            bool hasTemp = (temps.size() > 0);
            bool hasSolar = (solar.size() > 0);

            // Only write row if at least one data type is available
            if (hasSpeed || hasTemp || hasSolar){
                outFile << getMonthName(month) << ",";

            // DEBUG line — show how many records are being used per month
                    std::cout << getMonthName(month) << ": "
                              << "Speed=" << speeds.size()
                              << ", Temp=" << temps.size()
                              << ", Solar=" << solar.size() << "\n";

                // Process and write wind speed data if available
                if (hasSpeed){

                    // Convert all speeds from m/s to km/h
                    Vector<float> speedsKmh = convertSpeedsToKmh(speeds);

                    // Calculate wind speed statistics
                    double avgSpeed = calculateMean(speedsKmh);
                    double stdDevSpeed = calculateStdDev(speedsKmh);
                    double mad = madValue(speedsKmh);
                    outFile << std::fixed << std::setprecision(1) << avgSpeed
                           << "(" << stdDevSpeed << "," << mad << ")";
                }
                outFile << ",";

                // Process and write temperature data if available
                if (hasTemp){

                    // Calculate temperature statistics
                    double avgTemp = calculateMean(temps);
                    double stdDevTemp = calculateStdDev(temps);
                    double mad = madValue(temps);

                    outFile << std::fixed << std::setprecision(1) << avgTemp
                           << "(" << stdDevTemp << "," << mad << ")";
                }
                outFile << ",";

                // Process and write solar radiation data if available
                if (hasSolar){
                    // Calculate total solar radiation in kWh/m²
                    double totalSolar = calculateTotalSolarKWh(solar);

                    outFile << std::fixed << std::setprecision(1) << totalSolar;
                }

                outFile << "\n";
                hasAnyData = true; // Mark that we wrote some data
            }
        }
    }
    // Write message if no data was found for the entire year
    if (!hasAnyData){
        outFile << "No Data\n";
    }else{}
        // Inform user export was successful
        std::cout << "Data successfully written to WindTempSolar.csv\n";
}
