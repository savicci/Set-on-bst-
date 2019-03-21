#include"set.hpp"


int main()
{
    Set<int> set;

    set.insert(1);
    set.insert(0);
    set.insert(2);
    set.insert(3);
    set.insert(5);
    set.insert(9);
    set.insert(34);
    set.insert(7);

    for(auto it=set.begin(); it != set.end(); ++it)
    {
        std::cout<<*it<<", "<<std::endl;
    }

    std::cout<<"SIEMANO"<<std::endl;
    for(auto it : set)
    {
        std::cout<<it<<std::endl;
    }

}