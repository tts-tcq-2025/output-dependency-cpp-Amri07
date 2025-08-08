#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <cassert>

// Generate the color map as a vector of tuples
std::vector<std::tuple<int, std::string, std::string>> generate_color_map() {
    std::vector<std::string> major_colors = {"White", "Red", "Black", "Yellow", "Violet"};
    std::vector<std::string> minor_colors = {"Blue", "Orange", "Green", "Brown", "Slate"};
    std::vector<std::tuple<int, std::string, std::string>> color_map;

    for (size_t i = 0; i < major_colors.size(); ++i) {
        for (size_t j = 0; j < minor_colors.size(); ++j) {
            int pair_number = static_cast<int>(i * minor_colors.size() + j);
            color_map.emplace_back(pair_number, major_colors[i], minor_colors[j]);
        }
    }
    return color_map;
}

// Format a color map entry as a string
std::string format_color_map_entry(int pair_number, const std::string& major, const std::string& minor) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%d | %-6s | %s", pair_number, major.c_str(), minor.c_str());
    return std::string(buffer);
}

// Print function abstraction
void printOnConsole(const std::string& lineItem) {
    std::cout << lineItem << std::endl;
}

// Print color map using an output function
int print_color_map(const std::function<void(const std::string&)>& output_func = printOnConsole) {
    auto color_map = generate_color_map();
    for (const auto& entry : color_map) {
        int pair_number;
        std::string major, minor;
        std::tie(pair_number, major, minor) = entry;
        std::string line = format_color_map_entry(pair_number, major, minor);
        output_func(line);
    }
    return static_cast<int>(color_map.size());
}

// Test function designed to fail
void test_print_color_map_fail() {
    // Intentionally incorrect expected output to fail the test
    std::vector<std::string> expected_lines = {
        "1 | White  | Blue",  // Should be "0 | White  | Blue"
        "2 | White  | Orange",
        "3 | White  | Green",
        "4 | White  | Brown",
        "5 | White  | Slate",
        "6 | Red    | Blue",
        "7 | Red    | Orange",
        "8 | Red    | Green",
        "9 | Red    | Brown",
        "10 | Red    | Slate",
        "11 | Black  | Blue",
        "12 | Black  | Orange",
        "13 | Black  | Green",
        "14 | Black  | Brown",
        "15 | Black  | Slate",
        "16 | Yellow | Blue",
        "17 | Yellow | Orange",
        "18 | Yellow | Green",
        "19 | Yellow | Brown",
        "20 | Yellow | Slate",
        "21 | Violet | Blue",
        "22 | Violet | Orange",
        "23 | Violet | Green",
        "24 | Violet | Brown",
        "25 | Violet | Slate"
    };

    // Mock print function to record calls
    std::vector<std::string> calls;
    auto mock_print = [&calls](const std::string& line) {
        calls.push_back(line);
    };

    int count = print_color_map(mock_print);

    // assertions
    assert(static_cast<int>(calls.size()) == 25); // value based testing
    assert(calls[0] == "0 | White  | Blue");      // interaction or Behavior Testing
    assert(calls.back() == "24 | Violet | Slate");
    // The following will fail because expected_lines[0] != calls[0]
    assert(calls[0] == expected_lines[0]);
}

int main() {
    test_print_color_map_fail();
    return 0;
}
