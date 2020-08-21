#ifndef __MY_ALGORITHM_HPP__
#define __MY_ALGORITHM_HPP__

#include <string>
#include <vector>

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

std::vector<std::string> SplitString(const std::string& str,const std::string& delim)
{
    std::vector<std::string> result;
    std::string::size_type pos1 = 0;
    std::string::size_type pos2 = str.find(delim);
    size_t delim_size = delim.size();

    while(pos2 != std::string::npos)
    {
        result.emplace_back(std::string(str, pos1, pos2 - pos1));
        pos1 = pos2 + delim_size;
        pos2 = str.find(delim, pos1);
    }

    if(pos1 != str.length())
    {
        result.emplace_back(std::string(str, pos1));
    }

    return result;
}

std::vector<int> SplitStringInt(const std::string& str,const std::string& delim)
{
    std::vector<int> result;
    std::string::size_type pos1 = 0;
    std::string::size_type pos2 = str.find(delim);
    size_t delim_size = delim.size();

    while(pos2 != std::string::npos)
    {
        result.emplace_back(stoi(std::string(str, pos1, pos2 - pos1)));
        pos1 = pos2 + delim_size;
        pos2 = str.find(delim, pos1);
    }

    if(pos1 != str.length())
    {
        result.emplace_back(stoi(std::string(str, pos1)));
    }

    return result;
}

#endif