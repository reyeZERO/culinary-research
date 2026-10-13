#ifndef STREXTRA_H
#define STREXTRA_H

#include <cstddef>

namespace strextra {
int find(const char* haystack, char needle, std::size_t from = 0, bool case_sensitive = true);
int find(const char* haystack, const char* needle, std::size_t from = 0, bool case_sensitive = true, char escape = '/', char any = '?', char star = '*');
}

#endif
