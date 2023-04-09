#include<iostream>
#include<string>
using namespace std;
class HasPtr{
private:
    string *ps;
    int i;
    size_t *use;
public:
    HasPtr(const string &s=string());
    HasPtr(const HasPtr &p);
    HasPtr& operator=(const HasPtr&);
    ~HasPtr();
};
HasPtr::HasPtr(const string &s=string()){
    ps=new string(s);
    i=0;
    use=new size_t(1);
}
HasPtr::HasPtr(const HasPtr &p)
{
    ps=p.ps;
    i=p.i;
    *(p.use)=*(p.use)+1;//这里该怎么写
    use=p.use;
}
HasPtr& HasPtr::operator=(const HasPtr&h)
{
    *h.use=*h.use+1;
    if(--*use==0){
        delete use;
        delete ps;
    }
    use=h.use;
    ps=h.ps;
    i=h.i;
    return *this;
}
HasPtr::~HasPtr()
{
    if(--*use==0)
    {
        delete use;
        delete ps;
    }
}
