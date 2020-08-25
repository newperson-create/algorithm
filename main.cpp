//#include "test.hpp"
// ^异或，相同为0，不同为1

#include "test.hpp"

int main(int argc, char* argv[]) 
{
    MyTree::BinarySearchTree<int> my_tree;
    my_tree.insert(5);
    my_tree.insert(3);
    my_tree.insert(4);
    my_tree.insert(2);
    my_tree.insert(7);
    my_tree.insert(6);
    my_tree.insert(8);

    std::string str;
    beforePrint(my_tree.getRootNode(), str);
    std::cout << str << std::endl;
    std::cout << my_tree.size() << std::endl; 

    Timer time;
    my_tree.erase(3);
    printf("\ntime:%f\n", time.getTimerMillSecond());

    std::string str2;
    beforePrint(my_tree.getRootNode(), str2);
    std::cout << str2 << std::endl;
    std::cout << my_tree.size() << std::endl; 
}