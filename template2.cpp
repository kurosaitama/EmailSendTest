#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

// very simple FNV-1a 32-bit hash function
uint32_t calculateFileHash(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    
    if (!file) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return 0;
    }

    uint32_t hash = 0x811c9dc5; // FNV offset basis
    const uint32_t prime = 0x01000193; // FNV prime

    char buffer;
    while (file.get(buffer)) {
        // XOR the hash with the current byte
        hash ^= static_cast<uint8_t>(buffer);
        // Multiply by the FNV prime
        hash *= prime;
    }

    return hash;
}

int main() {
    std::string filename = "example.txt"; // make sure the file exists
    
    uint32_t result = calculateFileHash(filename);
    
    if (result != 0) {
        std::cout << "File: " << filename << std::endl;
        std::cout << "Checksum (Hex): " << std::hex << result << std::dec << std::endl;
    }

    return 0;
}