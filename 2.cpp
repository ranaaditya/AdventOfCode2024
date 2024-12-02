#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

bool is_safe_sequence(const std::vector<int>& levels) {
    if (levels.size() < 2) return true;
    
    // Check first two numbers to determine if sequence should be increasing or decreasing
    bool should_increase = levels[1] > levels[0];
    
    // Check each adjacent pair
    for (size_t i = 1; i < levels.size(); i++) {
        int diff = levels[i] - levels[i-1];
        
        if (should_increase) {
            if (diff <= 0 || diff > 3) return false;
        } else {
            if (diff >= 0 || diff < -3) return false;
        }
    }
    
    return true;
}

bool is_safe_with_dampener(const std::vector<int>& levels) {
    // First check if it's safe without removing any level
    if (is_safe_sequence(levels)) return true;
    
    // Try removing each level one at a time
    for (size_t i = 0; i < levels.size(); i++) {
        std::vector<int> modified = levels;
        modified.erase(modified.begin() + i);
        
        if (is_safe_sequence(modified)) return true;
    }
    
    return false;
}

void solve_puzzles(const std::vector<std::vector<int>>& reports) {
    int safe_count_part1 = 0;
    int safe_count_part2 = 0;
    
    for (const auto& report : reports) {
        if (is_safe_sequence(report)) safe_count_part1++;
        if (is_safe_with_dampener(report)) safe_count_part2++;
    }
    
    std::cout << "Part 1 - Number of safe reports: " << safe_count_part1 << std::endl;
    std::cout << "Part 2 - Number of safe reports with Problem Dampener: " << safe_count_part2 << std::endl;
}

int main() {
    std::ifstream input_file("2_input.txt");
    if (!input_file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    
    std::vector<std::vector<int>> reports;
    std::string line;
    
    // Read all reports
    while (std::getline(input_file, line)) {
        if (line.empty()) continue;
        
        std::vector<int> levels;
        std::istringstream iss(line);
        int num;
        
        while (iss >> num) {
            levels.push_back(num);
        }
        
        reports.push_back(levels);
    }
    
    input_file.close();
    
    solve_puzzles(reports);
    
    return 0;
}