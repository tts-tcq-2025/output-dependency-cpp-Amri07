#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

std::string formatColorMapEntry(int pair, const char* major, const char* minor) {
    char buf[64];
    snprintf(buf, sizeof(buf), "%2d | %-6s | %s", pair, major, minor);
    return std::string(buf);
}

std::vector<std::string> getColorMapLines() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    std::vector<std::string> lines;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            lines.push_back(formatColorMapEntry(i * 5 + j, majorColor[i], minorColor[j]));
        }
    }
    return lines;
}

void testPrintColorMap() {
    std::cout << "\nPrint color map test\n"; 
    auto lines = getColorMapLines();
    assert(lines.size() == 25);
    // Strengthen: check alignment and content
    assert(lines[0] == " 0 | White  | Blue"); // Should fail due to original misalignment
    assert(lines[24] == "24 | Violet | Slate");
    // Check separator alignment
    size_t sep = lines[0].find('|');
    for(const auto& line : lines) {
        assert(line.find('|') == sep); // Should fail if not aligned
    }
    std::cout << "All is well (maybe!)\n";
}
