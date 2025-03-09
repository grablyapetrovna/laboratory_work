#include <iostream>
#include <boost/filesystem.hpp>
#include <map>
#include <set>

namespace fs = boost::filesystem;

bool is_financial_file(const fs::path& file_path) {
    std::string filename = file_path.filename().string();
    std::cout << "Checking file: " << filename << " (length: " << filename.size() << ")" << std::endl;

    if (filename.find("balance_") != 0) {
        std::cout << "  - File does not start with 'balance_'" << std::endl;
        return false;
    }

    if (filename.substr(filename.size() - 4) != ".txt") {
        std::cout << "  - File does not end with '.txt'" << std::endl;
        return false;
    }

    if (filename.find(".old.txt") != std::string::npos) {
        std::cout << "  - File contains '.old.txt'" << std::endl;
        return false;
    }

    if (filename.size() < 26) { 
        std::cout << "  - File name is too short" << std::endl;
        return false;
    }

    std::string account = filename.substr(8, 8); 
    std::string date = filename.substr(17, 8);  

    auto is_digits = [](const std::string& str) {
        return str.find_first_not_of("0123456789") == std::string::npos;
    };

    if (!is_digits(account)) {
        std::cout << "  - Account number is not valid: " << account << std::endl;
        return false;
    }

    if (!is_digits(date)) {
        std::cout << "  - Date is not valid: " << date << std::endl;
        return false;
    }

    std::cout << "  - File is valid" << std::endl;
    return true;
}

int main(int argc, char* argv[]) {
    fs::path path_to_ftp = (argc > 1) ? argv[1] : fs::current_path();

    std::cout << "Analyzing directory: " << path_to_ftp << std::endl;

    if (!fs::exists(path_to_ftp)) {
        std::cerr << "Directory does not exist: " << path_to_ftp << std::endl;
        return 1;
    }

    std::map<std::string, std::map<std::string, std::set<std::string>>> broker_account_files;
    std::map<std::string, std::map<std::string, std::string>> broker_account_last_date;

    for (const auto& entry : fs::recursive_directory_iterator(path_to_ftp)) {
        if (fs::is_regular_file(entry)) {
            fs::path file_path = entry.path();
            std::cout << "Found file: " << file_path << std::endl;

            if (is_financial_file(file_path)) {
                std::cout << "Financial file detected: " << file_path << std::endl;

                std::string broker = file_path.parent_path().filename().string();

                std::string filename = file_path.filename().string();

                std::string account = filename.substr(8, 8); 
                std::string date = filename.substr(17, 8);  

                broker_account_files[broker][account].insert(filename);

                if (broker_account_last_date[broker][account] < date) {
                    broker_account_last_date[broker][account] = date;
                }
            }
        }
    }

    for (const auto& [broker, accounts] : broker_account_files) {
        for (const auto& [account, files] : accounts) {
            for (const auto& file : files) {
                std::cout << broker << " " << file << std::endl;
            }
        }
    }

    for (const auto& [broker, accounts] : broker_account_last_date) {
        for (const auto& [account, last_date] : accounts) {
            int file_count = broker_account_files[broker][account].size();
            std::cout << "broker:" << broker
                      << " account:" << account
                      << " files:" << file_count
                      << " lastdate:" << last_date << std::endl;
        }
    }

    return 0;
}