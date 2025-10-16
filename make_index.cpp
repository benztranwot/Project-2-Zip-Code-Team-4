#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>
#include <filesystem>

const std::string DATA_FILE = "us_postal_codes_length_indicated_header_record.txt";
const std::string INDEX_FILE = "indexfile.bin";

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> result;
    size_t start = 0, end;
    while ((end = s.find(delimiter, start)) != std::string::npos) {
        result.push_back(s.substr(start, end - start));
        start = end + 1;
    }
    result.push_back(s.substr(start));
    return result;
}

void printRecord(const std::string &line) {
    auto fields = split(line, ',');
    const char *labels[] = {"Zip Code", "Place Name", "State", "County", "Lat", "Long"};

    for (size_t i = 0; i < fields.size() && i < 6; ++i) {
        std::cout << labels[i] << ": " << fields[i] << "\n";
    }
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    std::unordered_map<std::string, std::streampos> index;

    if (std::filesystem::exists(INDEX_FILE)) {
        std::ifstream idx(INDEX_FILE, std::ios::binary);
        if (!idx.is_open()) {
            std::cerr << "Error: unable to open " << INDEX_FILE << "\n";
            return 1;
        }

        while (true) {
            uint8_t len;
            if (!idx.read(reinterpret_cast<char*>(&len), sizeof(len))) break;
            std::string zip(len, '\0');
            idx.read(zip.data(), len);
            uint64_t offset;
            idx.read(reinterpret_cast<char*>(&offset), sizeof(offset));
            index[zip] = static_cast<std::streampos>(offset);
        }

        idx.close();
        std::cout << "Loaded existing index file: " << INDEX_FILE
                  << " (" << index.size() << " entries)\n";
    } else {
        std::cout << "Index not found, building new one...\n";

        std::ifstream data(DATA_FILE, std::ios::binary);
        if (!data.is_open()) {
            std::cerr << "Error: unable to open " << DATA_FILE << "\n";
            return 1;
        }

        std::string header;
        std::getline(data, header);
        std::string line;
        while (true) {
            std::streampos pos = data.tellg();
            if (!std::getline(data, line)) break;
            if (line.empty()) continue;
            if (!line.empty() && line.back() == '\r')
                line.pop_back();

            std::string zip = line.substr(0, line.find(','));
            index[zip] = pos;
        }
        data.close();

        std::ofstream idx(INDEX_FILE, std::ios::binary);
        for (const auto &[zip, offset] : index) {
            uint8_t len = static_cast<uint8_t>(zip.size());
            uint64_t off = static_cast<uint64_t>(offset);
            idx.write(reinterpret_cast<const char*>(&len), sizeof(len));
            idx.write(zip.data(), len);
            idx.write(reinterpret_cast<const char*>(&off), sizeof(off));
        }
        idx.close();

        std::cout << "Index built and written to " << INDEX_FILE
                  << " (" << index.size() << " entries)\n";
    }

    std::vector<std::string> zips;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.rfind("-Z", 0) == 0)
            zips.push_back(arg.substr(2));
    }

    std::ifstream data(DATA_FILE, std::ios::binary);
    if (!data.is_open()) {
        std::cerr << "Error: unable to open " << DATA_FILE << "\n";
        return 1;
    }

    for (const auto &zip : zips) {
        if (index.find(zip) == index.end()) {
            std::cout << zip << " not found.\n\n";
            continue;
        }

        data.clear();
        data.seekg(index[zip]);
        std::string line;
        std::getline(data, line);
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        printRecord(line);
    }

    return 0;
}