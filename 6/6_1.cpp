#include <iostream>
using namespace std;
int my_sum(int i,initializer_list<int>il)
{
    cout<<il.size()<<endl;
    cout<<il.begin()<<il.end()<<endl;
    int res =i;
    for(auto &beg:il)
    {
        res+=beg;
    }
    return res;
}
int main()
{
    cout<<my_sum(5,{0,1,2,3,4,5,6,7,8,9})<<endl;
    return 0;
}