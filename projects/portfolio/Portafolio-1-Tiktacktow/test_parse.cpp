#include <cassert>
#include <string>
#include "tic_tac_toe_lib.hpp"

int main() {
    assert(parseIndex("1")==0);
    assert(parseIndex("9")==8);
    assert(parseIndex("  5  ")==4);
    assert(parseIndex("\t3\n")==2);
    assert(parseIndex("0")==-1);
    assert(parseIndex("10")==-1);
    assert(parseIndex("a")==-1);
    assert(parseIndex("  ")==-1);
    return 0;
}
