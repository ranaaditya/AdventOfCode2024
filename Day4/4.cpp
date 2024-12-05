#include <iostream>
#include <fstream>
#include <vector>
#include <string>

bool check_xmas_pattern(const std::vector<std::string>& grid, int x, int y) {
    int rows = grid.size();
    int cols = grid[0].size();
    
    // Check bounds for the entire X pattern
    if (x < 1 || x >= rows - 1 || y < 1 || y >= cols - 1) {
        return false;
    }
    
    // Check if center is 'A'
    if (grid[x][y] != 'A') {
        return false;
    }
    
    // Check all possible combinations of MAS in X shape
    bool valid = false;
    
    // Helper lambda to check if a character is M or S
    auto isM = [](char c) { return c == 'M'; };
    auto isS = [](char c) { return c == 'S'; };
    
    // Check all possible combinations:
    // Top-left to bottom-right: MAS or SAM
    // Top-right to bottom-left: MAS or SAM
    
    // Case 1: M-A-S and M-A-S
    if (isM(grid[x-1][y-1]) && isS(grid[x+1][y+1]) &&
        isM(grid[x-1][y+1]) && isS(grid[x+1][y-1])) {
        valid = true;
    }
    // Case 2: M-A-S and S-A-M
    if (isM(grid[x-1][y-1]) && isS(grid[x+1][y+1]) &&
        isS(grid[x-1][y+1]) && isM(grid[x+1][y-1])) {
        valid = true;
    }
    // Case 3: S-A-M and M-A-S
    if (isS(grid[x-1][y-1]) && isM(grid[x+1][y+1]) &&
        isM(grid[x-1][y+1]) && isS(grid[x+1][y-1])) {
        valid = true;
    }
    // Case 4: S-A-M and S-A-M
    if (isS(grid[x-1][y-1]) && isM(grid[x+1][y+1]) &&
        isS(grid[x-1][y+1]) && isM(grid[x+1][y-1])) {
        valid = true;
    }
    
    return valid;
}

int count_xmas_patterns(const std::vector<std::string>& grid) {
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();
    
    // Check each position as a potential center of X
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            if (check_xmas_pattern(grid, i, j)) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    std::ifstream input("input.txt");
    if (!input.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    
    std::vector<std::string> grid;
    std::string line;
    
    // Read the grid
    while (std::getline(input, line)) {
        grid.push_back(line);
    }
    
    int result = count_xmas_patterns(grid);
    std::cout << "X-MAS pattern appears " << result << " times." << std::endl;
    
    return 0;
}