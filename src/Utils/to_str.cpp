#include "to_str.h"

std::string to_str(int a)
{
    std::string res;
    if (a > 99) {
        res += '0' + (a / 100);
        a %= 100;
    }
    if (a > 9) {
        res += '0' + (a / 10);
        a %= 10;
    }
    res += '0' + a;
    return res;
}

