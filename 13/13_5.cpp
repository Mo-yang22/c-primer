#include<iostream>
#include<string>
using namespace std;
class HasPtr{
public:
    HasPtr(const string &s=string()):
        ps(new string(s)),i(0){};
    HasPtr(const HasPtr &h):ps(new string(*h.ps)),i(h.i){};
    HasPtr& operator=(const HasPtr &h);
    ~HasPtr();
    string *Getps(){return ps;};
private:
    string *ps;
    int i;
};
HasPtr& HasPtr::operator=(const HasPtr &h)
{
    this->ps=new string(*h.ps);
    this->i=h.i;
    return *this;
}
HasPtr::~HasPtr()
{
    delete this->ps;
}
int main()
{
    string s="hello";
    HasPtr h1(s);
    cout<<(*h1.Getps())<<endl;
    HasPtr h2=h1;
    cout<<(*h2.Getps())<<endl;
    cout<<(h1.Getps())<<endl;
    cout<<(h2.Getps())<<endl;
    HasPtr h3;
    h3=h1;
    cout<<(*h3.Getps())<<endl;
    cout<<(h3.Getps())<<endl;
    system("pause");
    return 0;
    
}
