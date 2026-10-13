#include "source_code.h"
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <cctype>

std::string toLowerCase(const std::string &str) {
    std::string lower_str = str;
    for (char &ch : lower_str) {
        ch = std::tolower(ch);
    }
    return lower_str;
}

std::string replaceWords(const std::string &sentence) {
    std::unordered_map<std::string, std::string> word_map = {
        {"cat", "/ᐠ｡ꞈ｡ᐟ\\"},
        {"kitty", "(•ㅅ•)"},
        {"kitten", "(•ㅅ•)"},
        {"yarn", "o~"},
        {"angry", "(=ಠᆽಠ=)"},
        {"dance", "~( ˘▾˘ ~)"},
        {"love", "(₌♥ᆽ♥₌)"},
        {"happy", "(=^ ◡ ^=)"},
        {"painful", "(˃ᆺ˂)"},
        {"surprised", "／(=๏ x ๏=)＼"},
        {"mouse", "…ᘛ⁐̤ᕐᐷ"}
    };

    std::istringstream iss(sentence);
    std::string word, result;
    bool first_occurrence[256] = {false};  // Track first occurrences of words

    while (iss >> word) {
        std::string lower_word = toLowerCase(word);
        if (word_map.find(lower_word) != word_map.end() && !first_occurrence[lower_word[0]]) {
            result += word_map[lower_word] + " ";
            first_occurrence[lower_word[0]] = true;
        } else {
            result += word + " ";
        }
    }

    if (!result.empty()) {
        result.pop_back();  // Remove the trailing space
    }

    return result;
}
