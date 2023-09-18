#include "readers/csv_reader.hpp"
#include <fstream>
#include <sstream>

CSVReader::CSVReader(const std::string& filename) : filename(filename) {}

bool CSVReader::readCSV(std::vector<std::vector<std::string>>& data) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string cell;
        std::vector<std::string> row;
        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }

    file.close();
    return true;
}