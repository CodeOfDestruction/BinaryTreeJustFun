#include "binTree.h"

int main() try
{
    using std::cout;
    binTree<int> tree;
    tree.insert(20);
    tree.insert(1);
    tree.insert(50);
    tree.insert(23);
    tree.insert(24);
    tree.insert(25);
    tree.insert(90);
    tree.insert(45);
    tree.insert(46);
    tree.insert(7);
    tree.insert(200);
    tree.insert(201);
    std::cout<<tree;
   // std::cout<< tree.size()<<std::endl;
    tree.remove(90);
   std::cout<<tree;
    for (auto& T : tree) std::cout<<T<<" ";

}
catch(nullDeref&  t){ std::cerr<< t.what();}
