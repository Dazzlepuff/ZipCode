#include "buffer.h"
#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <iomanip>  // For formatting table output

// Function to find extreme zip codes for each state
std::map<std::string, std::vector<ZipCodeRecord>> findExtremes(const std::vector<ZipCodeRecord>& records) {
    std::map<std::string, std::vector<ZipCodeRecord>> stateExtremes;

    for (const auto& record : records) {
        std::string state = record.stateID;

        if (stateExtremes.find(state) == stateExtremes.end()) {
            // Initialize first entry
            stateExtremes[state] = {record, record, record, record};  // East, West, North, South
        } else {
            auto& extremes = stateExtremes[state];

            if (record.longitude < extremes[0].longitude) extremes[0] = record; // Easternmost
            if (record.longitude > extremes[1].longitude) extremes[1] = record; // Westernmost
            if (record.latitude > extremes[2].latitude) extremes[2] = record;   // Northernmost
            if (record.latitude < extremes[3].latitude) extremes[3] = record;   // Southernmost
        }
    }

    return stateExtremes;
}

// Function to print the formatted table
void printTable(const std::map<std::string, std::vector<ZipCodeRecord>>& stateExtremes) {
    std::cout << std::left;  // Align text to the left
    std::cout << std::setw(8) << "State" << " | "
              << std::setw(12) << "East ZIP" << " | "
              << std::setw(12) << "West ZIP" << " | "
              << std::setw(12) << "North ZIP" << " | "
              << std::setw(12) << "South ZIP" << "\n";
    std::cout << "-------------------------------------------------------------------\n";

    for (const auto& pair : stateExtremes) {
        const std::string& state = pair.first;
        const auto& extremes = pair.second;

        std::cout << std::setw(8) << state << " | "
                  << std::setw(12) << extremes[0].zipCode << " | "
                  << std::setw(12) << extremes[1].zipCode << " | "
                  << std::setw(12) << extremes[2].zipCode << " | "
                  << std::setw(12) << extremes[3].zipCode << "\n";
    }
}

int main() {
    // Load CSV file into Buffer
    Buffer buffer("C:/Users/Chils/Downloads/us_postal_codes.csv");
    buffer.loadCSV();

    // Find extreme zip codes per state
    std::map<std::string, std::vector<ZipCodeRecord>> stateExtremes = findExtremes(buffer.getRecords());

    // Print results
    printTable(stateExtremes);

    return 0;
}
