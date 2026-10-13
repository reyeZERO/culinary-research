#include "strextra.h"
#include <cctype>
#include <cstring>

namespace {
inline bool eqc(char a, char b, bool cs) {
    if (cs) return a == b;
    return std::tolower(static_cast<unsigned char>(a)) == std::tolower(static_cast<unsigned char>(b));
}

bool match_escaped(const char* pat, std::size_t& pi, char escape) {
    if (pat[pi] == escape && pat[pi + 1] != '\0') {
        ++pi;
        return true;
    }
    return false;
}

bool match_here(const char* s, std::size_t si, const char* p, std::size_t pi, bool cs, char escape, char any, char star) {
    while (p[pi] != '\0') {
        if (match_escaped(p, pi, escape)) {
            if (s[si] == '\0') return false;
            if (!eqc(s[si], p[pi], cs)) return false;
            ++si; ++pi;
            continue;
        }
        if (p[pi] == any) {
            if (s[si] == '\0') return false;
            ++si; ++pi;
            continue;
        }
        if (p[pi] == star) {
            while (p[pi + 1] == star) ++pi;
            if (p[pi + 1] == '\0') return true;
            std::size_t next = pi + 1;
            if (p[next] == any) {
                for (std::size_t k = si; s[k] != '\0'; ++k) {
                    if (match_here(s, k + 1, p, next + 1, cs, escape, any, star)) return true;
                }
                return false;
            }
            if (p[next] == escape && p[next + 1] != '\0') {
                char lit = p[next + 1];
                for (std::size_t k = si; s[k] != '\0'; ++k) {
                    if (eqc(s[k], lit, cs) && match_here(s, k + 1, p, next + 2, cs, escape, any, star)) return true;
                }
                return false;
            }
            for (std::size_t k = si; s[k] != '\0'; ++k) {
                if (eqc(s[k], p[next], cs) && match_here(s, k + 1, p, next + 1, cs, escape, any, star)) return true;
            }
            return false;
        }
        if (s[si] == '\0') return false;
        if (!eqc(s[si], p[pi], cs)) return false;
        ++si; ++pi;
    }
    return true;
}
}

namespace strextra {

int find(const char* haystack, char needle, std::size_t from, bool case_sensitive) {
    if (!haystack) return -1;
    std::size_t n = std::strlen(haystack);
    if (from > n) return -1;
    for (std::size_t i = from; i < n; ++i) {
        if (eqc(haystack[i], needle, case_sensitive)) return static_cast<int>(i);
    }
    return -1;
}

int find(const char* haystack, const char* needle, std::size_t from, bool case_sensitive, char escape, char any, char star) {
    if (!haystack || !needle) return -1;
    std::size_t n = std::strlen(haystack);
    if (from > n) return -1;
    if (needle[0] == '\0') return static_cast<int>(from);
    bool has_wild = false;
    for (const char* p = needle; *p; ++p) {
        if (*p == star || *p == any) { has_wild = true; break; }
        if (*p == escape && p[1] != '\0') { ++p; }
    }
    if (!has_wild) {
        std::size_t m = std::strlen(needle);
        if (m == 0) return static_cast<int>(from);
        if (m > n) return -1;
        for (std::size_t i = from; i + m <= n; ++i) {
            bool ok = true;
            for (std::size_t j = 0; j < m; ++j) {
                if (!eqc(haystack[i + j], needle[j], case_sensitive)) { ok = false; break; }
            }
            if (ok) return static_cast<int>(i);
        }
        return -1;
    } else {
        for (std::size_t i = from; i <= n; ++i) {
            if (match_here(haystack, i, needle, 0, case_sensitive, escape, any, star)) return static_cast<int>(i);
        }
        return -1;
    }
}

}
