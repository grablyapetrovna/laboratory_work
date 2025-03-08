#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm> 

const int NUM_ITERATIONS = 1000;

void warmUpCache(int* buffer, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        [[maybe_unused]] int temp = buffer[i]; 
    }
}

void directTraversal(int* buffer, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        [[maybe_unused]] int temp = buffer[i];
    }
}

void reverseTraversal(int* buffer, size_t size) {
    for (size_t i = size; i-- > 0;) {
        [[maybe_unused]] int temp = buffer[i];
    }
}

void randomTraversal(int* buffer, size_t size) {
    std::vector<int> indices(size);
    for (size_t i = 0; i < size; ++i) {
        indices[i] = i;
    }
    std::shuffle(indices.begin(), indices.end(), std::mt19937{std::random_device{}()}); 
    
    for (size_t i = 0; i < size; ++i) {
        [[maybe_unused]] int temp = buffer[indices[i]];
    }
}

void runExperiment(size_t bufferSize, const std::string& travelVariant) {
    int* buffer = new int[bufferSize];
    std::generate(buffer, buffer + bufferSize, std::rand); 

    warmUpCache(buffer, bufferSize);

    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        if (travelVariant == "direct") {
            directTraversal(buffer, bufferSize);
        } else if (travelVariant == "reverse") {
            reverseTraversal(buffer, bufferSize);
        } else if (travelVariant == "random") {
            randomTraversal(buffer, bufferSize);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> duration = end - start;

    std::cout << "Travel variant: " << travelVariant << ", Buffer size: " << bufferSize << " bytes, Duration: " 
              << duration.count() << " ns" << std::endl;

    delete[] buffer;
}

int main() {
    const size_t cacheSizes[] = {80 * 1024, 1280 * 1024, 24 * 1024 * 1024};
    const int numExperiments = 5;

    for (size_t cacheSize : cacheSizes) {
        for (int i = 0; i < numExperiments; ++i) {
            size_t bufferSize = (1 << (i + 20)); 
            if (bufferSize < 3 * cacheSize / 2) {
                runExperiment(bufferSize, "direct");
                runExperiment(bufferSize, "reverse");
                runExperiment(bufferSize, "random");
            }
        }
    }

    return 0;
}
