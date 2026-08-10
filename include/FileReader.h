/**
 *  FileReader
 * @brief Handles file path operations for weather data source files
 *
 * This provides functionality to read and manage data source filenames
 * from configuration files. It encapsulates file I/O operations for retrieving
 * the path to weather data files.
 */

#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include "Vector.h"



    /**
     * @brief Gets all data source filenames from data/data_source.txt
     * @return Vector of full paths to data files
     */
    Vector<std::string> GetAllDataSourceFilenames();



#endif

