#ifndef __MY_ALGORITHM_HPP__
#define __MY_ALGORITHM_HPP__

#include <string>

std::string IntToBinaryStr(int tmp)
{
    int a = tmp / 2;
    int b = tmp % 2;
    std::string ret = std::to_string(b);
   
    while(a != 0)
    {
        b = a;
        a = a / 2;
        b = b % 2;
        ret = std::to_string(b) + ret;
    }

    return ret;
}

#endif