#ifndef __TEST_HPP__
#define __TEST_HPP__

#include <iostream>
#include <set>
#include <vector>

#include "timer.hpp"
#include "myalgorithm.hpp"

// 取字符串不同排序abc bac cba acb
void permute(const std::string& str, int low, int high)
{
    if(low < 0 || high > static_cast<int>(str.size()) || low >= high)
    {
        return;
    }

    for(int i = low + 1;i < high; ++i)
    {
        std::string tmp = str;
        std::swap(tmp[low], tmp[i]);
        printf("%s ", tmp.c_str());
    }

    permute(str, low + 1, high);
}

void permute(const std::string& str)
{
    printf("%s ", str.c_str());
    permute(str, 0, static_cast<int>(str.size()));
}

//------------------------------------------------------

template<typename Comparable>
class OrderedCollection
{
public:
    OrderedCollection() : _min_pos(0), _max_pos(0) {}

    bool isEmpty() { return _array.empty(); } 

    void insert(const Comparable& other)
    {
        if(this->isEmpty())
        {
            // 插入第一个元素
            _min_pos = 0;
            _max_pos = 0;
            _array.push_back(other);
            return;
        }

        _array.push_back(other);
        if(_array[_min_pos] > other)
        {
            _min_pos = this->size() - 1;
        }

        if(_array[_max_pos] < other)
        {
            _max_pos = this->size() - 1;
        }   
    }

    int size()
    {
        return static_cast<int>(_array.size());
    }

    const Comparable* findMin()
    {
        if(this->isEmpty())
        {
            return nullptr;
        }

        return &_array[_min_pos];
    }

    const Comparable* findMax()
    {
        if(this->isEmpty())
        {
            return nullptr;
        }

        return &_array[_max_pos];
    }

    void remove(const Comparable& other)
    {
        if(this->isEmpty())
        {
            return;
        }

        bool is_recalc = false;
        for(auto vet_it = _array.begin(); vet_it != _array.end();)
        {
            if(other == *vet_it)
            {
                if(*vet_it == _array[_min_pos] || *vet_it == _array[_max_pos])
                {
                    is_recalc = true;
                }

                _array.erase(vet_it);
                break;
            }
            else
            {
                ++vet_it;
            }
            
        }

        if(is_recalc)
        {
            // 重新找最大值、最小值
            this->recalcMinAndMax();
        }
    }

    const std::vector<Comparable>& getArray() { return _array; } 

private:
    void recalcMinAndMax()
    {
        if(this->isEmpty())
        {
            return;
        }

        _min_pos = 0;
        _min_pos = 0;
        for(int i = 1; i < this->size(); ++i)
        {
            if(_array[_min_pos] > _array[i])
            {
                _min_pos = i;
            }

            if(_array[_max_pos] < _array[i])
            {
                _max_pos = i;
            }
        }
    }

private:
    std::vector<Comparable> _array;
    int _min_pos;
    int _max_pos;
};

class Rectangle
{
public:
    Rectangle(int width = 0, int length = 0)
    {
        _width = width;
        _length = length;
    }

    bool operator<(const Rectangle& other)
    {
        int self_area = this->getArea();
        int other_area = other._length * other._width;
        if(self_area < other_area)
        {
            return true;
        }
        else
        {
            int self_perimeter = this->getPerimeter();
            int other_perimeter = (other._width + other._length) * 2;
            return self_perimeter < other_perimeter;
        }
    }

    bool operator>(const Rectangle& other)
    {
        int self_area = this->getArea();
        int other_area = other._length * other._width;
        if(self_area > other_area)
        {
            return true;
        }
        else
        {
            int self_perimeter = this->getPerimeter();
            int other_perimeter = (other._width + other._length) * 2;
            return self_perimeter > other_perimeter;
        }
    }

    int getWidth() const { return _width; }
    int getLength() const { return _length; }

    int getArea() const
    {
        return _width * _length;
    }

    int getPerimeter() const
    {
        return (_width + _length) * 2;
    }

private:
    int _width;
    int _length;
};

//------------------------------------------------------

#endif