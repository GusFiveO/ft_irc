#include "Utils.hpp"

int
isBNFSpecial(char c)
{
    if (c == ';' || c == '[' || c == ']' || c == '\\' || c == '`' ||
        c == '_' || c == '^' || c == '{' || c == '|' || c == '}')
    {
        return 1;
    }
    return 0;
}