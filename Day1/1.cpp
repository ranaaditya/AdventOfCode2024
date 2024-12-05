#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <unordered_map>

void solve_part1(const std::vector<int>& left_list, const std::vector<int>& right_list) {
    std::vector<int> sorted_left = left_list;
    std::vector<int> sorted_right = right_list;
    
    // Sort both lists
    std::sort(sorted_left.begin(), sorted_left.end());
    std::sort(sorted_right.begin(), sorted_right.end());
    
    // Calculate total distance
    long long total_distance = 0;
    for (size_t i = 0; i < sorted_left.size(); i++) {
        total_distance += std::abs(sorted_left[i] - sorted_right[i]);
    }
    
    std::cout << "Part 1 - Total distance: " << total_distance << std::endl;
}

void solve_part2(const std::vector<int>& left_list, const std::vector<int>& right_list) {
    // Count occurrences in right list
    std::unordered_map<int, int> right_counts;
    for (int num : right_list) {
        right_counts[num]++;
    }
    
    // Calculate similarity score
    long long similarity_score = 0;
    for (int num : left_list) {
        similarity_score += static_cast<long long>(num) * right_counts[num];
    }
    
    std::cout << "Part 2 - Similarity score: " << similarity_score << std::endl;
}

int main() {
    std::vector<int> left_list;
    std::vector<int> right_list;
    std::string line;
    
    // Open input file
    std::ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    
    // Read input
    while (std::getline(input_file, line)) {
        if (line.empty()) continue;
        
        std::istringstream iss(line);
        int left, right;
        iss >> left >> right;
        
        left_list.push_back(left);
        right_list.push_back(right);
    }
    
    input_file.close();
    
    // Solve both parts
    solve_part1(left_list, right_list);
    solve_part2(left_list, right_list);
    
    return 0;
}