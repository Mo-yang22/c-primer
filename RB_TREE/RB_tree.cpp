#include <iostream>
#include <assert.h>

using namespace std;

typedef enum{
    RED = 0,
    BLACK
}Color;

//红黑树结点类型
template<typename Type>
struct RBTNode
{
    Color color;
    Type key;
    RBTNode *left;
    RBTNode *right;
    RBTNode *parent;
};

//红黑树类型
template<typename Type>
class RBTree
{
public:
    //插入
    //1.BST方式插入
    //2.调整平衡
    bool Insert(const Type &value)
    {
        RBTNode<Type> *pr = Nil;//pr用来记住父节点
        RBTNode<Type> *s = root;
        while(s!=Nil)
        {
            if(value == s->key)
            {
                return false;
            }
            pr = s//每次记住s的父节点
            if(value>s->key)
            {
                s = s->right;
            }
            else
            {
                s = s->left;
            }
        }
        //循环结束后s==Nil
        s = BuyNode(value);
        if(pr==Nil) //第一次root指向Nil，所以pr==Nil
        {
            root = s;
            root->parent = pr;
        }
        else{
            if(value < pr->key)
            {
                pr->left = s;
            }
            else{
                pr->right =s;
            }
            s->parent = pr;
        }
        //调整平衡
        Insert_Fixup(s);
        return true;
    }
protected:
    //申请结点，将结点的颜色初始化为红色，初始化结点的关键字，其他初始化为空，各指针在上层调用
    RBTNode<Type> *BuyNode(const Type &x=Type())
    {
        RBTNode<Type> *s = new RBTNode<Type>();
        assert(s!=NULL);
        s->color = RED;
        s->left = s->right = s->parent = Nil;
        s->key = x;
        return s;
    }

    //中序遍历
    void InOrder(RBTNode<Type>* root)
    {
        if(root!=Nil)
        {
            InOrder(root->left);
            cout<<root->key<<" ";
            InOrder(root->right);
        }
    }

    /* 左转，对z结点左转
     *       zp                 zp
     *       /                  /
     *     z                   y
     *    / \      ===>       / \
     *   lz  y               z   ry
     *      / \             / \
     *     ly  ry          lz  ly  
     */
    void LeftRotate(RBTNode<Type> *z)
    {
        //假如要左转，y绝对不会是Nil
        RBTNode<Type> *y = z->right;//用y指向要转动的z结点
        //处理y的子节点的parent指针
        z->right=y->left;
        if(y->left!=Nil)
        {
            y->left->parent=z;
        }
        //处理z的parent的孩子指针
        y->parent=z->parent;
        if (root == z) //z就是根节点
        {
            root = y;
        }
        else if (z == z->parent->left) //z在左结点
        {
            z->parent->left = y;
        }
        else //z在右结点
        {
            z->parent->right = y;
        }
        //处理y与z的关系
        y->left=z;
        z->parent=y;
    }
    /* 右转，对z结点进行右转
    *         zp               zp
    *        /                 /
    *       z                 y
    *      / \    ===>       / \
    *     y   rz           ly   z   
    *    / \                   / \
    *   ly  ry                ry  rz
    */
    void RightRotate(RBTNode<Type> *z)
    {
        RBTNode<Type> *y=z->left;
        z->left=y->right;
        if(y->right!=Nil)
        {
            y->right->parent=z;
        }
        y->parent=z->parent;
        if(root==z)
        {
            root=y;
        }
        else if(z==z->parent->left)
        {
            z->parent->left=y;
        }
        else{
            z->parent->right=y;
        }
        y->right=z;
        z->parent=y;
    }
    //插入后的调整函数
    void Insert_Fixup(RBTNode<Type> *s)
    {
        RBTNode<Type> *uncle;
        //当父结点是黑结点时，直接插就行
        while(s->parent->color == RED)
        {
            if(s->parent == s->parent->parent->left)//肯定有祖父存在
            {
                uncle = s->parent->parent->right;

                //可以尝试把情况重构
                if(uncle->color == RED)//红父红叔情况
                {
                    s->parent->color = BLACK;
                    uncle->color =BLACK;
                    s->parent->parent->color =RED;
                    s = s->parent->parent;
                }
                else//没有叔结点，或者叔结点为黑色
                {
                    if(s==s->parent->right)//如果调整的结点在右边
                    {
                        //以s的父节点为基点进行左转
                        //注意左转后s层级不变
                        //下面一句话把s升层
                        s=s->parent;
                        //下面这句话把s降层
                        LeftRotate(s);
                    }
                    //现在，调整的结点都位于左边
                    s->parent->color = BLACK;
                    s->parent->parent->color= RED;
                    RightRotate(s->parent->parent);
                    //这种情况下其实已经不会循环了
                }
            }
            else
            {
                uncle = s->parent->parent->left;

                if(uncle->color == RED)
                {
                    s->parent->color = BLACK;
                    uncle->color = BLACK;
                    s->parent->parent = RED;
                    s=s->parent->parent;
                }
                else
                {
                    if(s=s->parent->left)
                    {
                        s=s->parent;
                        RightRotate(s);
                    }
                    s->parent->color=BLACK;
                    s->parent->parent->color = RED;
                    LeftRotate(s->parent->parent);
                }
            }
        }
        root->color =BLACK;
    }

    //查找key结点
    RBTNode<Type> *Search(RBTNode<Type> *root,Type key) const
    {
        if(root == Nil)
        {
            return Nil;
        }

        if(root->key == key)
        {
            return root;
        }
        if(key<root->key)
        {
            return Search(root->left,key);
        }
        else
        {
            return Search(root->right,key);
        }
    }
    
private:
    RBTNode<Type> *root;//根指针
    RBTNode<Type> *Nil;//外部结点，表示为空结点，黑色
};