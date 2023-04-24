#include <iostream>
#include <assert.h>
#include <queue>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;
typedef enum{
    RED = 0,
    BLACK
}Color;

//红黑树结点类型
template<typename T>
struct RBTNode
{
    Color color;
    T key;
    RBTNode *left;
    RBTNode *right;
    RBTNode *parent;
};

template<class T>
class RBTree
{
public:
    RBTree();
    
    ~RBTree();

    //按照从小到大地顺序打印所有数据
    void InOrder()const{ InOrder(root); }

    //插入数据
    bool Insert(const T &key);

    //移除数据
    bool Remove(T key);

    //以层序遍历的形式打印
    void LevelOrderPrint() const{ LevelOrderPrint(root); }
    
    //以横向的形式打印
    void HorizontalPrint() const { HorizontalPrint(root,0,'|'); }
private:
    //新建一个节点
    RBTNode<T> *NewNode(const T &x=T());

    void InOrder(RBTNode<T>* node) const;

    //左转
    void LeftRotate(RBTNode<T> *z);

    //右转
    void RightRotate(RBTNode<T> *z);

    //插入后的调整函数
    void InsertFixup(RBTNode<T> *s);
    
    //寻找某个节点
    RBTNode<T> *Find(RBTNode<T> *node,T key) const;

    //寻找后继节点
    RBTNode<T> *FindSuccessor(RBTNode<T> *node) const;

    //移除函数,被公共函数调用
    void Remove(RBTNode<T> *z);

    //移除后的调整函数
    void RemoveFixup(RBTNode<T> *x);

    //摧毁
    void destroy(RBTNode<T> *node);
    
    void LevelOrderPrint(RBTNode<T> *node);

    void HorizontalPrint(RBTNode<T>*node,int depth,char prefix);

private:
    RBTNode<T> *root;//根指针
    RBTNode<T> *Nil;//外部结点，表示为空结点，黑色
};