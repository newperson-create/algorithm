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

namespace MyTree
{
    template <typename T>
    struct BinaryNode
    {
        BinaryNode(const T& value, BinaryNode* left = nullptr, BinaryNode* right = nullptr)
        {
            _element = value;
            _left = left;
            _right = right;
        }

        BinaryNode(const T&& value, BinaryNode* left = nullptr, BinaryNode* right = nullptr)
        {
            _element = std::move(value);
            _left = left;
            _right = right;
        }

        T _element;
        struct BinaryNode* _left;
        struct BinaryNode* _right;
    };

    template <typename T>
    const BinaryNode<T>* const findMin(const BinaryNode<T>* root)
    {
        if(nullptr == root)
        {
            return nullptr;
        }
        else if(nullptr == root->_left)
        {
            return root;
        }
        else 
        {
            BinaryNode<T>* node = root->_left;
            while(nullptr != node->_left)
            {
                node = node->_left;
            }

            return node;
        }
    }

    template <typename T>
    const BinaryNode<T>* const findMax(const BinaryNode<T>* root)
    {
        if(nullptr == root)
        {
            return nullptr;
        }
        else if(nullptr == root->_right)
        {
            return root;
        }
        else 
        {
            BinaryNode<T>* node = root->_right;
            while(nullptr != node->_right)
            {
                node = node->_right;
            }

            return node;
        }
    }

    template <typename T>
    class BinarySearchTree
    {
    public:
        BinarySearchTree() : _root(nullptr), _size(0){}

        int size() const { return _size; } 

        void push_back(const T& value)
        {
            bool is_succ = false;
            if(nullptr == _root)
            {
                _root = new BinaryNode<T>(value, nullptr, nullptr);
                is_succ = true;
            }
            else
            {
                BinaryNode<T>* new_element = new BinaryNode<T>(value, nullptr, nullptr);
                is_succ = this->insertElement(new_element);
            }

            if(is_succ)
            {
                ++_size;
            }
        }

        void push_back(const T&& value)
        {
            bool is_succ = false;
            if(nullptr == _root)
            {
                _root = new BinaryNode<T>(std::move(value), nullptr, nullptr);
                is_succ = true;
            }
            else
            {
                BinaryNode<T>* new_element = new BinaryNode<T>(std::move(value), nullptr, nullptr);
                is_succ = this->insertElement(new_element);
            }

            if(is_succ)
            {
                ++_size;
            }
        }

        void erase(const T& value)
        {
            this->deleteElement(value);
        }

        const BinaryNode<T>* getRootNode() const
        {
            return _root;
        }

    private:
        // 插入元素
        bool insertElement(BinaryNode<T>* new_node)
        {
            if(nullptr == new_node || new_node->_element == _root->_element)
            {
                return false;
            }

            // 寻找合适位置
            BinaryNode<T>* last_node = nullptr;
            BinaryNode<T>* cur_node = _root;
            while(nullptr != cur_node)
            {
                last_node = cur_node;
                if(cur_node->_element < new_node->_element)
                {
                    cur_node = cur_node->_right;
                }
                else if(cur_node->_element > new_node->_element)
                {
                    cur_node = cur_node->_left;
                }
            }

            // 插入元素
            if(last_node->_element < new_node->_element)
            {
                last_node->_right = new_node;
            }
            else if(cur_node->_element > new_node->_element)
            {
                 last_node->_left = new_node;
            }

            return true;
        }

        BinaryNode<T>* findElement(const T& value)
        {
            // 寻找元素所在节点
            BinaryNode<T>* tmp_node = _root;
            while(nullptr != tmp_node)
            {
                if(tmp_node->_element > value)
                {
                    tmp_node = tmp_node->_left;
                }
                else if(tmp_node->_element < value)
                {
                    tmp_node = tmp_node->_right;
                }
                else
                {
                    break;
                }
            }

            return tmp_node;
        }

        void deleteElement(const T& value)
        {
            // 寻找所删除元素的节点
            BinaryNode<T>* element_node = this->findElement(value);
            if(nullptr == element_node)
            {
                return;
            }

            BinaryNode<T>* delete_element = nullptr;
            if(nullptr != element_node->_left)
            {
                // 寻找左子树中的最大值
                delete_element = findMax(element_node->_left);
                element_node->_element = delete_element->_element;
            }
            else if(nullptr != element_node->_right)
            {
                 // 寻找右子树中的最小值
                  delete_element = findMin(element_node->_right);
                  element_node->_element = delete_element->_element;
            }
            else
            {
                // 无左右子树，为叶子节点，则直接删除
                delete_element = element_node;
            }

            if(nullptr != delete_element)
            {
                --_size;
                delete delete_element;
            }
        }

    private:
        struct BinaryNode<T>* _root;
        int _size;
    };

    // 先序输出
    template <typename T>
    void beforePrint(const BinaryNode<T>* root, std::string& str)
    {
        if(nullptr == root)
        {
            return;
        }

        str += std::to_string(root->_element) + " ";
        beforePrint(root->_left, str);
        beforePrint(root->_right, str);
    }
}

#endif