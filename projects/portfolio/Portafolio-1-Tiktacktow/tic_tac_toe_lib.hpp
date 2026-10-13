#pragma once
#include <array>
#include <string>

using Board = std::array<char, 9>;

inline bool isWin(const Board& b, char p) {
    static const int lines[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };
    for (auto &line : lines) {
        if (b[line[0]] == p && b[line[1]] == p && b[line[2]] == p) return true;
    }
    return false;
}

inline bool isFull(const Board& b) {
    for (char c : b) if (c == ' ') return false;
    return true;
}

inline int parseIndex(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos) return -1;
    std::string t = s.substr(start, end - start + 1);
    if (t.size() == 1 && std::isdigit(static_cast<unsigned char>(t[0]))) {
        int v = t[0] - '0';
        return (v >= 1 && v <= 9) ? (v - 1) : -1;
    }
    return -1;
}
