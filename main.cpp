#include <iostream>
#include "RecordParse.h"
#include "WindlogAggregator.h"
#include "Menu.h"
#include "FileReader.h"


int main() {
    std::cout << "=== Weather Data Analysis System ===\n";

    // Get data source filename
    std::cout << "Getting data source filenames...\n";
    Vector<std::string> dataFile = GetAllDataSourceFilenames();

    // Display the found files
    for (int i = 0; i < dataFile.size(); ++i) {
        std::cout << "File " << (i+1) << ": " << dataFile[i] << "\n";
    }

    WindlogAggregator aggregator;
    Vector<WeatherRecord> allWeatherData;
    int totalRecords = 0;

    std::cout << "\n=== Processing Data Files ===\n";

    // Process each data file
    for (int i = 0; i < dataFile.size(); ++i) {
        std::string currentFile = dataFile[i];
        std::cout << "Processing: " << currentFile << "\n";

        // Read weather data
        Vector<WeatherRecord> weatherData = ReadFile(currentFile);
        std::cout << "Read " << weatherData.size() << " records from " << currentFile << "\n";

        // Aggregate data by month and year
        if (!weatherData.isEmpty()) {
            aggregator.aggregateData(weatherData);
            totalRecords += weatherData.size();

            // Collect all records for BST testing
            for (int j = 0; j < weatherData.size(); ++j) {
                allWeatherData.pushBack(weatherData[j]);
            }
            std::cout << "Successfully aggregated data from " << currentFile << "\n";
        } else {
            std::cout << "WARNING: No data read from " << currentFile << "\n";
        }
    }

    std::cout << "\n=== Data Processing Summary ===\n";
    std::cout << "Total records processed: " << totalRecords << "\n";
    std::cout << "All weather data collected: " << allWeatherData.size() << " records\n";

    std::cout << "\n=== Starting Menu System ===\n";

    // Start menu system
    Menu menu(aggregator);
    menu.run();

    std::cout << "Menu system exited.\n";
    std::cout << "Program completed successfully.\n";

    return 0;
}


