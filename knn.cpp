#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <chrono>

struct HSV {
    int h, s, v;
    std::string label;
};

// Euclidean distance function
double euclideanDistance(const HSV& x1, const HSV& x2) {
    return std::sqrt(std::pow(x2.h - x1.h, 2) + std::pow(x2.s - x1.s, 2) + std::pow(x2.v - x1.v, 2));
}

// KNN prediction function
std::string knnPredict(const std::vector<HSV>& data, const HSV& query, int k) {
    std::vector<std::pair<double, std::string>> distances;
    for (const auto& entry : data) {
        double dist = euclideanDistance(query, entry);
        distances.emplace_back(dist, entry.label);
    }

    std::sort(distances.begin(), distances.end());
    distances.resize(k);

    std::unordered_map<std::string, int> labelCounts;
    for (const auto& [dist, label] : distances) {
        labelCounts[label]++;
    }

    std::string majorityClass;
    int maxCount = 0;
    for (const auto& [label, count] : labelCounts) {
        if (count > maxCount) {
            maxCount = count;
            majorityClass = label;
        }
    }
    return majorityClass;
}

int main() {
    std::vector<HSV> data = {
        {0, 255, 200, "Red"},
        {2, 250, 195, "Red"},
        {120, 255, 200, "Green"},
        {122, 250, 195, "Green"},
        {240, 255, 200, "Blue"},
        {245, 250, 195, "Blue"}
    };

    HSV query = {120, 250, 180}; 
    int k = 3;
    int iterations = 10000;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        knnPredict(data, query, k);
    }
    auto end = std::chrono::high_resolution_clock::now();

    double avg_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / (double)iterations;
    std::cout << "Average time per prediction in C++: " << avg_time << " microseconds" << std::endl;

    return 0;
}
