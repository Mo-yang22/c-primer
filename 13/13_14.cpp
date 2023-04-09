#include<iostream>
#include<string>
using namespace std;
static int seq=0;
class Numbered
{
public:
    int mysn;
    Numbered(){
        mysn=(seq++);
    };
    Numbered(const Numbered& n){
        mysn=(seq++);
    };
};
void f(Numbered &n){cout<<n.mysn<<endl;}
int main()
{
    Numbered a,b=a,c=b;
    f(a);
    f(b);
    f(c);
    system("pause");
    return 0;
}