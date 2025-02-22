#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp" 

using json = nlohmann::json;

void printTable(const json& students) {
        std::cout << "| name            | group  | avg      | debt          |\n";

    std::cout << "|-----------------|--------|----------|---------------|\n";
    
    for (const auto& student : students) {
        std::string name = student["name"];
        std::string group = student["group"].is_string() ? student["group"].get<std::string>() : std::to_string(student["group"].get<int64_t>());
        std::string avg = student["avg"].is_string() ? student["avg"].get<std::string>() : std::to_string(student["avg"].get<double>());
        std::string debt;

        if (student["debt"].is_null()) {
            debt = "null";
        } else if (student["debt"].is_string()) {
            debt = student["debt"];
        } else {
            debt = std::to_string(student["debt"].size()) + " items";
        }

        std::cout << "| " << std::setw(15) << name << " | " << std::setw(6) << group << " | " << std::setw(6) << avg << " | " << std::setw(13) << debt << " |\n";
        std::cout << "|-----------------|--------|----------|---------------|\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_json_file>\n";
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Could not open the file: " << argv[1] << "\n";
        return 1;
    }

    json data;
    inputFile >> data;
    inputFile.close();

    printTable(data["items"]);
    return 0;
}
