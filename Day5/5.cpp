#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

struct Rule {
    int before;
    int after;
};

std::vector<int> topological_sort(const std::vector<int>& pages, 
                                const std::vector<Rule>& rules) {
    std::unordered_map<int, std::vector<int>> graph;
    std::unordered_map<int, int> in_degree;
    std::unordered_set<int> page_set(pages.begin(), pages.end());
    
    // Initialize in-degree
    for (int page : pages) {
        in_degree[page] = 0;
    }
    
    // Build graph
    for (const Rule& rule : rules) {
        if (page_set.count(rule.before) && page_set.count(rule.after)) {
            graph[rule.before].push_back(rule.after);
            in_degree[rule.after]++;
        }
    }
    
    // Topological sort
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    std::vector<int> result;
    
    for (const auto& pair : in_degree) {
        if (pair.second == 0) {
            q.push(pair.first);
        }
    }
    
    while (!q.empty()) {
        int current = q.top();
        q.pop();
        result.push_back(current);
        
        for (int neighbor : graph[current]) {
            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
    
    return result;
}

bool verify_order(const std::vector<int>& update, 
                 const std::vector<Rule>& rules) {
    std::unordered_set<int> update_pages(update.begin(), update.end());
    
    for (const Rule& rule : rules) {
        if (update_pages.count(rule.before) && update_pages.count(rule.after)) {
            auto pos_before = std::find(update.begin(), update.end(), rule.before);
            auto pos_after = std::find(update.begin(), update.end(), rule.after);
            if (pos_before > pos_after) {
                return false;
            }
        }
    }
    return true;
}

std::vector<Rule> parse_rules(std::ifstream& input) {
    std::vector<Rule> rules;
    std::string line;
    
    while (std::getline(input, line) && !line.empty()) {
        size_t pos = line.find('|');
        if (pos != std::string::npos) {
            int before = std::stoi(line.substr(0, pos));
            int after = std::stoi(line.substr(pos + 1));
            rules.push_back({before, after});
        }
    }
    
    return rules;
}

std::vector<std::vector<int>> parse_updates(std::ifstream& input) {
    std::vector<std::vector<int>> updates;
    std::string line;
    
    while (std::getline(input, line)) {
        std::vector<int> update;
        std::stringstream ss(line);
        std::string number;
        
        while (std::getline(ss, number, ',')) {
            update.push_back(std::stoi(number));
        }
        
        updates.push_back(update);
    }
    
    return updates;
}

int main() {
    std::ifstream input("input.txt");
    if (!input.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    
    auto rules = parse_rules(input);
    auto updates = parse_updates(input);
    
    int sum_middle_pages = 0;
    
    for (const auto& update : updates) {
        if (!verify_order(update, rules)) {
            // Fix incorrectly ordered update
            auto sorted_update = topological_sort(update, rules);
            // Get middle page number from corrected order
            int middle_idx = sorted_update.size() / 2;
            sum_middle_pages += sorted_update[middle_idx];
        }
    }
    
    std::cout << "Sum of middle page numbers from corrected invalid updates: " 
              << sum_middle_pages << std::endl;
    
    return 0;
}