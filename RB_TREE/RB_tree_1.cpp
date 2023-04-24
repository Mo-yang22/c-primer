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
    //构造函数
    RBTree()
    {
        Nil = BuyNode();
        root = Nil;
        Nil->color = BLACK;
    }
    //析构函数
    ~RBTree()
    {
        destroy(root); //销毁创建的非Nil结点
        delete Nil;    //最后删除Nil结点
        Nil = NULL;
    }
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
            pr = s;//每次记住s的父节点
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
    //删除key节点(先查找,再调用内部删除)
    void Remove(Type key)
    {
        RBTNode<Type> *t;
        if((t = Search(root,key)) != Nil)
        {
            Remove(t);
        }
        else{
            cout<< "key is not exist."<<endl;
        }
    }
    void InOrder(){ InOrder(root); }
    void LevelOrderPrint(){ LevelOrderPrint(root); }
    void HorizontalPrint() {HorizontalPrint(root,0,'|');}
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
        assert(y != Nil);
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
                    s->parent->parent->color = RED;
                    s=s->parent->parent;
                }
                else
                {
                    if(s==s->parent->left)
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
    // void Transplant(RBTNode<Type> *u,RBTNode<Type> *v)
    // {
    //     if(u->parent == Nil)
    //     {
    //         root = v;
    //     }
    //     else if(u==u->parent->left)
    //     {
    //         u->parent->left = v;
    //     }
    //     else{
    //         u->parent->right = v;
    //     }
    //     v->parent = u->parent;
    // }
    /* 找到最左结点(最小)
     *      xp
     *        \
     *         x
     *        / \
     *      xl   xr
     *     / \
     *   xll  xlr
     */
    RBTNode<Type> *Minimum(RBTNode<Type> *x)
    {
        if(x->left == Nil)
        {
            return x;
        }
        return Minimum(x->left);
    }
    //删除节点z
    void Remove(RBTNode<Type> *z)
    {
        RBTNode<Type> *y = Nil;
        if(z->left == Nil || z->right == Nil)
        {
            y = z;
        }
        else{
            y = Minimum(z->right);
            std::swap(y->key,z->key);
        }
        RBTNode<Type> *yp = y->parent;
        //?
        RBTNode<Type> *ychild = y->left != Nil?y->left:y->right;
        ychild->parent=yp;
        if(yp == Nil){
            root = ychild;
        }
        else if(yp->left==y){
            yp->left=ychild;
        }
        else{
            yp->right=ychild;
        }
        if(y->color == BLACK)
            Remove_Fixup(ychild);
        delete y; 
    }  
    //红黑树删除调整
    void Remove_Fixup(RBTNode<Type> *x)
    {
        while(x != root && x->color ==BLACK)
        {
            if(x == x->parent->left)
            {
                RBTNode<Type> *w = x->parent->right;

                if(w->color == RED)//红兄的情况,先行进行处理,可以转化为其他情况
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    LeftRotate(x->parent);
                    w= x->parent->right;
                }
                
                if(w->left->color == BLACK && w->right->color ==BLACK)
                {
                    w->color = RED;
                    x= x->parent;
                }
                else//黑兄红父
                {
                    //一种情况,转换为第二种
                    if(w->right->color == BLACK)
                    {
                        w->color =RED;
                        w->left->color = BLACK;
                        RightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = w->parent->color;
                    w->parent->color = BLACK;
                    w->right->color =BLACK;
                    LeftRotate(x->parent);
                    x = root;//结束循环
                }
            }
            else//x在右子树
            {
                RBTNode<Type> *w=x->parent->left;
                if(w->color == RED)
                {
                    w->parent->color = RED;
                    w->color = BLACK;
                    RightRotate(x->parent);
                    w = x->parent->left;
                }
                if(w->right->color == BLACK && w->right->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if(w->left->color == BLACK)
                    {
                        w->right->color = BLACK;
                        w->color = RED;
                        LeftRotate(w);
                        w= x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color =BLACK;
                    w->left->color =BLACK;
                    RightRotate(x->parent);
                    x = root; 
                }
            }
        }
        x->color = BLACK;
    }
    //销毁红黑树
    void destroy(RBTNode<Type> *root)
    {
        if(root == Nil)
        {
            return; 
        }
        destroy(root->left);
        destroy(root->right);
        delete root;
        root = NULL;
    }
    void LevelOrderPrint(RBTNode<Type> *node)
    {
        if(node == Nil)
            return;
        queue<RBTNode<Type>*> q;
        q.push(node);
        while(!q.empty()){
            int s = q.size();
            for(int i =0 ;i<s;++i)
            {
                RBTNode<Type> *tmp=q.front();
                q.pop();
                cout << tmp->key << "(" << ((tmp->color == BLACK) ? "BLACK" : "RED") << ")"
                    << " ";
                if(tmp->left!=Nil)
                {
                    q.push(tmp->left);
                }
                if(tmp->right!=Nil)
                {
                    q.push(tmp->right);
                }
            }
            cout<<endl;
        }
    }
    void HorizontalPrint(RBTNode<Type>*node,int depth,char prefix)
    {
        if(node == Nil)
        {
            return;
        }
        HorizontalPrint(node->right,depth+1,'/');
        cout << setw(depth*4) << prefix << "(" << node->key << "," << (node->color==BLACK ? "B" : "R") << ")" << endl;
        HorizontalPrint(node->left,depth+1,'\\');
    }
private:
    RBTNode<Type> *root;//根指针
    RBTNode<Type> *Nil;//外部结点，表示为空结点，黑色
};
int main()
{
    RBTree<int> rb;

    int arr[] = {10, 7, 8, 15, 5, 6, 11, 13, 12};
    int n = sizeof(arr) / sizeof(int);
    for (int i = 0; i < n; i++)
    {
        rb.Insert(arr[i]);
    }
    rb.HorizontalPrint();
    int arr2[] = {2,4,22,21,24,23,27,26};
    for(auto i :arr2)
    {
        rb.Insert(i);
    }
    rb.HorizontalPrint();
    cout<<"...................."<<endl;
    rb.Remove(27);
    rb.Remove(8);
    rb.Remove(6);
    rb.HorizontalPrint();
    return 0;
}
