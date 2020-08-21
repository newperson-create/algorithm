//#include "test.hpp"
// ^异或，相同为0，不同为1

#include "test.hpp"

int main(int argc, char* argv[]) 
{
    MyTree::BinarySearchTree<int> my_tree;
    my_tree.push_back(5);
    my_tree.push_back(3);
    // my_tree.push_back(4);
    // my_tree.push_back(2);
    // my_tree.push_back(7);
    // my_tree.push_back(6);
    // my_tree.push_back(8);

    std::string str;
    beforePrint(my_tree.getRootNode(), str);

    std::cout << str << std::endl;
    // Timer time;
    // startGame(std::atoi(argv[0]), std::atoi(argv[1]));
    // printf("\ntime:%f\n", time.getTimerMillSecond());
}