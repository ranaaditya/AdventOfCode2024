#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

struct Instruction {
    long position;  // Changed from size_t to long
    std::string type;  // "mul", "do", or "don't"
    int x;
    int y;
};

std::vector<Instruction> parse_instructions(const std::string& input) {
    std::vector<Instruction> instructions;
    
    // Regex patterns for all instruction types
    std::regex mul_pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    std::regex do_pattern(R"(do\(\))");
    std::regex dont_pattern(R"(don't\(\))");
    
    // Find all mul instructions
    auto mul_begin = std::sregex_iterator(input.begin(), input.end(), mul_pattern);
    auto mul_end = std::sregex_iterator();
    for (auto i = mul_begin; i != mul_end; ++i) {
        std::smatch match = *i;
        instructions.push_back({
            static_cast<long>(match.position()),
            "mul",
            std::stoi(match[1]),
            std::stoi(match[2])
        });
    }
    
    // Find all do() instructions
    auto do_begin = std::sregex_iterator(input.begin(), input.end(), do_pattern);
    auto do_end = std::sregex_iterator();
    for (auto i = do_begin; i != do_end; ++i) {
        std::smatch match = *i;
        instructions.push_back({
            static_cast<long>(match.position()),
            "do",
            0,
            0
        });
    }
    
    // Find all don't() instructions
    auto dont_begin = std::sregex_iterator(input.begin(), input.end(), dont_pattern);
    auto dont_end = std::sregex_iterator();
    for (auto i = dont_begin; i != dont_end; ++i) {  // Fixed loop condition
        std::smatch match = *i;
        instructions.push_back({
            static_cast<long>(match.position()),
            "dont",
            0,
            0
        });
    }
    
    // Sort instructions by position
    std::sort(instructions.begin(), instructions.end(),
        [](const Instruction& a, const Instruction& b) {
            return a.position < b.position;
        });
    
    return instructions;
}

int process_instructions(const std::vector<Instruction>& instructions) {
    int total = 0;
    bool enabled = true;  // mul instructions are enabled by default
    
    for (const auto& inst : instructions) {
        if (inst.type == "do") {
            enabled = true;
        }
        else if (inst.type == "dont") {
            enabled = false;
        }
        else if (inst.type == "mul" && enabled) {
            total += inst.x * inst.y;
        }
    }
    
    return total;
}

int main() {
    std::ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    
    std::string input;
    std::string line;
    
    // Read entire input into a single string
    while (std::getline(input_file, line)) {
        input += line;
    }
    
    input_file.close();
    
    auto instructions = parse_instructions(input);
    int result = process_instructions(instructions);
    
    std::cout << "Sum of enabled multiplication results: " << result << std::endl;
    
    return 0;
}