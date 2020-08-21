#ifndef __TEST_HPP__
#define __TEST_HPP__

#include <iostream>
#include <set>
#include <list>
#include <algorithm>

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

/*
    实现简易vector
 */
template <typename Object>
class Vector
{
public:
    Vector(int size = 0) : _size{size}, _capacity{_size + SPACE_CAPACITY}
    {
        _objects = new Object[_capacity];
    }

    ~Vector()
    {
        if(nullptr != _objects)
        {
            delete[] _objects;
        }
    }

    Vector(const Vector& rhs) : _size{rhs._size}, _capacity{rhs._capacity}, _objects{nullptr}
    {
        _objects = new Object[rhs._capacity];
        for(int i = 0; i < _size; ++i)
        {
            _objects[i] = rhs._objects[i];
        }
    }

    Vector& operator=(const Vector& rhs)
    {   
        if(this == &rhs)
        {
            return *this;
        }

        _size = rhs._size;
        _capacity = rhs._capacity;
        for(int i = 0; i < _size; ++i)
        {
            _objects[i] = rhs._objects[i];
        }

        return *this;
    }

    Vector(const Vector&& rhs) : _size{rhs._size}, _capacity{rhs._capacity}, _objects{rhs._objects}
    {
        rhs._size = 0;
        rhs._capacity = 0;
        rhs._objects = nullptr;
    }

    Vector& operator=(const Vector&& rhs)
    {
        if(this == &rhs)
        {
            return *this;
        }

        _size = std::move(rhs._size);
        _capacity = std::move(rhs._capacity);
        _objects = std::move(rhs._objects);

        rhs._size = 0;
        rhs._capacity = 0;
        rhs._objects = nullptr;

        return *this;
    }

    Object& operator[](int index) { return _objects[index]; }
    const Object& operator[](int index) const { return _objects[index]; }

    int size() const { return _size; }
    int capacity() const { return _capacity; }
    bool isEmpty() { return 0 == this->size(); }

    void resize(int new_size)
    {
        if(new_size > _capacity)
        {
            this->reserve(new_size * 2);
        }
        _size = new_size;
    }

    void reserve(int new_capacity)
    {
        if(new_capacity < _size)
        {
            return;
        }

        Object* tmp = new Object[new_capacity];
        for(int i = 0; i < _size; ++i)
        {
            tmp[i] = std::move(_objects[i]);
        }

        _capacity = new_capacity;
        std::swap(_objects, tmp);
        delete[] tmp;
    }

    void push_back(const Object& lhs)
    {
        if(_size >= _capacity)
        {
            this->reserve(_capacity * 2 + 1);
        }

        _objects[_size++] = lhs;
    }

    void push_back(Object&& rhs)
    {
        if(_size >= _capacity)
        {
            this->reserve(_capacity * 2 + 1);
        }

        _objects[_size++] = std::move(rhs);
    }

    void pop_back() { --_size; }
    const Object& back() const { return _objects[_size - 1]; }
public:
    typedef Object*         iterator;
    typedef const Object*   const_iterator;

    iterator begin() { return &_objects[0]; } 
    const_iterator begin() const { return &_objects[0]; }
    iterator end() { return &_objects[_size]; }
    const_iterator end() const { return &_objects[_size]; }
private:
    static const int SPACE_CAPACITY = 16;
    int _size;
    int _capacity;
    Object* _objects;
};
//------------------------------------------------------
void printLots(const std::vector<int>& tmp1, const std::vector<int>& tmp2)
{
    for(int t : tmp2)
    {
        if(t >= 0 && t < static_cast<int>(tmp1.size()))
        {
            printf("%d ", tmp1[t]);
        }
        else
        {
            printf("error_index:%d\n", t);
        }
    }
}

void test3_1()
{
    std::vector<int> tmp{1,2,3,4,5,6,7,8,9,10};
    std::vector<int> tmp2{1,4,6,8};
    printLots(tmp, tmp2);
}

//------------------------------------------------------
template <class InputIterator, class T>
InputIterator myFind(InputIterator first, InputIterator last, const T& value)
{
    while( first != last && *first != value)
    {
        ++first;
    }

    return first;
}
//------------------------------------------------------
template <typename Object>
bool binaryFindVec(const std::vector<Object>& vec,const Object& value)
{
    int begin = 0, end = static_cast<int>(vec.size() - 1);
    int mid = (begin + end) / 2;
    while(begin <= end)
    {
        if(vec[mid] > value)
        {
            end = mid - 1;
        }
        else if(vec[mid] < value)
        {
            begin = mid + 1;
        }
        else 
        {
            return true;
        }
        mid = (begin + end) / 2;
    }

    return false;
}

template <typename Object>
std::vector<Object> Merge(const std::vector<Object>& vec1, const std::vector<Object>& vec2)
{
    std::vector<Object> result;
    for(const Object& tmp : vec1)
    {
        if(binaryFindVec(vec2, tmp))
        {
            result.push_back(tmp);
        }
    }

    return result;
}
//------------------------------------------------------
struct tmp
{
    tmp(int t = 0) : v(t){}

    int v = 0;
};

int mysort(const void* a1, const void* a2)
{
    tmp *tmp1 = (tmp*)a1;
    tmp *tmp2 = (tmp*)a2;
    return tmp2->v > tmp1->v ? 1 : -1;
}

void test()
{
    tmp vec1[] = {tmp(3),tmp(2),tmp(4),tmp(57),tmp(5),tmp(4),tmp(1)};
    int vec_size = 0;
    for(const tmp& t : vec1)
    {
        printf("%d ", t.v);
        ++vec_size;
    }
    printf("\n");
    qsort(&vec1, vec_size, sizeof(tmp), mysort);
    for(const tmp& t : vec1)
    {
        printf("%d ", t.v);
    }
    printf("\n");
}
//------------------------------------------------------
std::vector<int> MergeArray(const std::vector<int>& tmp1, const std::vector<int>& tmp2)
{
    std::vector<int> result;
    auto vec1_it = tmp1.begin();
    auto vec2_it = tmp2.begin();

    while(vec1_it != tmp1.end() && vec2_it != tmp2.end())
    {
        if(*vec1_it > *vec2_it)
        {
            result.push_back(*vec2_it);
            ++vec2_it;
        }
        else
        {
            result.push_back(*vec1_it);
            ++vec1_it;
        }
    }

    if(vec1_it != tmp1.end())
    {
        result.insert(result.end(), vec1_it, tmp1.end());
    }
    else if(vec2_it != tmp2.end())
    {
        result.insert(result.end(), vec2_it, tmp2.end());
    }

    return result;
}
//------------------------------------------------------
// Josephus问题
void josephusProblem(int m,std::vector<int>& vec)
{
    auto vec_it = vec.begin();
    while(vec.size() > 1)
    {
        for(int i = 0; i < m; ++i)
        {
            ++vec_it;
            if(vec_it == vec.end())
            {
                vec_it = vec.begin();
            }
        }

        // 删除成员
        vec_it = vec.erase(vec_it);
    }
}

void startGame(int m, int n)
{
    std::vector<int> role_vec;
    for(int i = 0;i < n; ++i)
    {
        role_vec.push_back(i+1);
    }

    josephusProblem(m, role_vec);
    if(!role_vec.empty())
    {
        printf("%d", role_vec[0]);
    }
}
//------------------------------------------------------


//------------------------------------------------------
#endif