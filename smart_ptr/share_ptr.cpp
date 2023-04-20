#include <thread>
#include <mutex>
#include <iostream>
using namespace std;
template <class T>
class SharedPtr{
public:
	SharedPtr(T* ptr = nullptr)
		: _ptr(ptr)
		, _pRefCount(new int(1))
		, _pMutex(new mutex)
	{}

	~SharedPtr() { Release(); }

	SharedPtr(const SharedPtr<T>& sp)
		: _ptr(sp._ptr)
		, _pRefCount(sp._pRefCount)
		, _pMutex(sp._pMutex)
	{
		AddRefCount();
	}

	// 赋值 sp1 = sp2
	SharedPtr<T>& operator=(const SharedPtr<T>& sp){
		//if (this != &sp)
		if (_ptr != sp._ptr){
			// 释放管理的旧资源
			Release();
			// 共享管理新对象的资源，并增加引用计数
			_ptr = sp._ptr;
			_pRefCount = sp._pRefCount;
			_pMutex = sp._pMutex;

			AddRefCount();
		}
		return *this;
	}

	T& operator*() { return *_ptr; }
	T* operator->() { return _ptr; }

	int UseCount() { return *_pRefCount; }
	T* Get() { return _ptr; }

	void AddRefCount(){
		// 加锁或者使用加1的原子操作
		_pMutex->lock();
		++(*_pRefCount);
		_pMutex->unlock();
	}
private:
	void Release(){
		bool deleteflag = false;

		// 引用计数减1，如果减到0，则释放资源
		_pMutex->lock();
		if (--(*_pRefCount) == 0){
			delete _ptr;
			delete _pRefCount;
			deleteflag = true;
		}
		_pMutex->unlock();

		if (deleteflag == true)
			delete _pMutex;
	}
private:
	int* _pRefCount;	// 引用计数
	T* _ptr;			// 指向管理资源的指针
	mutex* _pMutex;		 // 互斥锁
};
int main(){
	SharedPtr<int> sp1(new int(10));
	SharedPtr<int> sp2(sp1);
	*sp2 = 20;

	//sp1与sp2在管理这部分资源，引用计数为2
	cout << sp1.UseCount() << endl;		//2	
	cout << sp2.UseCount() << endl;		//2 

	SharedPtr<int> sp3(new int(10));
	sp2 = sp3;		//sp3赋值给它，释放管理的旧资源，引用计数-1，
	cout << sp1.UseCount() << endl;		//1
	cout << sp2.UseCount() << endl;		//2
	cout << sp3.UseCount() << endl;		//2

	sp1 = sp3;
	cout << sp1.UseCount() << endl;		//3
	cout << sp2.UseCount() << endl;		//3
	cout << sp3.UseCount() << endl;		//3

	system("pause");
	return 0;
}