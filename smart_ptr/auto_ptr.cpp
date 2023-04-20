#include <iostream>
#include <string>
using namespace std;
template<typename T>
class auto_ptr
{
public:
    explicit auto_ptr(T *ptr) noexcept
        :ptr_(ptr){}
    ~auto_ptr() noexcept
    { delete ptr_;}

    T& operator*() const noexcept
    { return *ptr_;}

    //?
    T *operator->() const noexcept
    { return ptr_;}
    operator bool() const noexcept
    { return ptr_;}
    T* get() const noexcept
    { return ptr_;}

    T *release() noexcept{
        T* ptr = ptr_;
        //?
        ptr_=nullptr;
        return ptr; 
    }
    void swap(auto_ptr& rhs) noexcept{
        using std::swap;
        swap(ptr_,rhs.ptr_);
    }
    auto_ptr(auto_ptr &other) noexcept{
        ptr_=other.release();
    }
    //赋值运算符重载要用copy and swap
    //一般赋值运算都会涉及析构和拷贝
    auto_ptr &operator=(auto_ptr &rhs) noexcept{
        auto_ptr tmp(rhs.release());
        tmp.swap(*this);
        return *this;
    }
private:
    T *ptr_;
};
template<typename T>
void swap(auto_ptr<T> &lhs, auto_ptr<T> &rhs) noexcept
{
    lhs.swap(&rhs);
}
int main()
{
    string s="hello world";
    auto_ptr<string> ptr1(&s);
    auto_ptr<string> ptr2(ptr1);
    if(ptr1.get() == nullptr && *ptr2==s )
        cout<<"good"<<endl;
    else
        cout<<"bad"<<endl;
    
    string s1="mother fuck";
    auto_ptr<string> ptr3(&s1);
    ptr1 = ptr3;
    if(ptr3.get() == nullptr && ptr1.get())
        cout<<"good";
    return 0;
}