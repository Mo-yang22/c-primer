#include "RB_tree.h"

/*
 功能函数
*/

//申请结点，将结点的颜色初始化为红色，初始化结点的关键字，其他初始化为空
template<class T>
RBTNode<T>*  RBTree<T>::NewNode(const T &x)
{
    RBTNode<T> *s= new RBTNode<T>();
    assert(s!=NULL);
    s->color = RED;
    s->parent = s->left = s->right = Nil;
    s->key = x;
    return s;
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
template<class T>
void RBTree<T>::LeftRotate(RBTNode<T> *z)
{
    //要左转的节点，其子节点绝不会为Nil
    RBTNode<T> *y = z->right;
    assert(y!=Nil);
    //处理y的左子节点
    z->right = y->left;
    if(y->left!= Nil)
    {
        y->left->parent = z;
    }
    //处理z的父节点
    y->parent = z->parent;
    if(z == root)
    {
        root = y;
    }
    else if(z == z->parent->left)
    {
        z->parent->left = y;
    }
    else
    {
        z->parent->right = y;
    }
    //处理两者关系
    z->parent = y;
    y->left = z;
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
template<class T>
void RBTree<T>::RightRotate(RBTNode<T> *z)
{
    RBTNode<T> *y = z->left;
    z->left = y->right;
    if(y->right != Nil)
    {
        y->right->parent = z;
    }
    y->parent = z->parent;
    if(z == root)
    {
        root = y;
    }
    else if(z == z->parent->left)
    {
        z->parent->left = y;
    }
    else
    {
        z->parent->right = y;
    }
    z->parent = y;
    y->right = z;
}

template<class T>
RBTNode<T>* RBTree<T>::Find(RBTNode<T>* node,T key) const
{
    if(node == Nil) return Nil;
    if(node->key == key)
    {
        return node;
    }
    else if(node->key > key)
    {
        return Find(node->left,key);
    }
    else
    {
        return Find(node->right,key);
    }
}

template<class T>
RBTNode<T>* RBTree<T>::FindSuccessor(RBTNode<T>* node) const
{
    RBTNode<T>* n = node->right;
    if(n == Nil)
    {
        return Nil;
    }
    while(n->left != Nil)
    {
        n = n->left;
    }
    return n;
}

/*
插入操作
*/

//插入
//1.BST方式插入
//2.调整平衡
template<class T>
bool RBTree<T>::Insert(const T &key)
{
    RBTNode<T> *pr = Nil; //存储父节点
    RBTNode<T> *s = root;
    while(s != Nil)
    {
        if(s->key == key)
            return false;
        pr = s;
        if(s->key > key)
        {
            s = s->left;
        }
        else
        {
            s = s->right;
        }
    }
    s = NewNode(key);
    if(pr == Nil)
    {
        root = s;
        root->color = BLACK;
    }
    else if (pr->key > key)
    {
        s->parent = pr;
        pr->left = s;
    }
    else
    {
        s->parent = pr;
        pr->right = s;
    }
    InsertFixup(s);
    return true;
}

template<class T>
void RBTree<T>::InsertFixup(RBTNode<T>* s)
{
    RBTNode<T> *uncle;
    //仅当父节点到的颜色是红色时，才进行调整，用while是因为有一种情况可能会回溯
    while(s != root && s->parent->color == RED)
    {
        //祖父节点一定存在，因为父节点为红，不可能为root
        if(s->parent == s->parent->parent->left)
        {
            uncle = s->parent->parent->right;
            //红父红叔
            if(uncle->color == RED)
            {
                s->parent->color = BLACK;
                uncle->color = BLACK;
                s->parent->parent->color = RED;
                //回溯的情况
                s = s->parent->parent;
            }
            else
            {
                if(s == s->parent->right)
                {
                    //完成下面两个操作后，s的层级不变
                    s = s->parent;
                    LeftRotate(s);
                }
                s->parent->color = BLACK;
                s->parent->parent->color = RED;
                RightRotate(s->parent->parent);
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
                s = s->parent->parent;
            }
            else
            {
                if(s == s->parent->left)
                {
                    //完成下面两个操作后，s的层级不变
                    s = s->parent;
                    RightRotate(s);
                }
                s->parent->color = BLACK;
                s->parent->parent->color = RED;
                LeftRotate(s->parent->parent);               
            }
        }
    }
    root->color = BLACK;
}

/*
删除操作
*/
template<class T>
bool RBTree<T>::Remove(T key)
{
    RBTNode<T> *node;
    if((node = Find(root,key)) != Nil)
    {
        Remove(node);
        return true;
    }
    else
        return false;
}

template<class T>
void RBTree<T>::Remove(RBTNode<T> *z)
{
    //表明是真正删除的地方
    RBTNode<T> *y;
    //当只有一个子节点或者没有子节点
    if(z->left == Nil || z->right == Nil)
    {
        y = z;
    }
    else{//有两个结点
        y = FindSuccessor(z);
        swap(y->key,z->key);
    }

    RBTNode<T> *yp = y->parent;
    //取孩子结点，可能为Nil
    RBTNode<T> *ychild = y->left != Nil?y->left:y->right;
    //不知道为什么没有判断ychild是不是Nil
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
        RemoveFixup(ychild);
    delete y; 
}

template<class T>
void RBTree<T>::RemoveFixup(RBTNode<T> *x)
{
    while(x != root && x->color == BLACK)
    {
        RBTNode<T>* bro;
        if(x == x->parent->left)
        {
            bro = x->parent->right;
            //红兄
            if(bro->color == RED)
            {
                bro->color = BLACK;
                x->parent->color = RED;
                LeftRotate(x->parent);
                //更新bro
                bro = x->parent->right;
            }
            //包含两种情况，黑兄黑侄
            if(bro->left->color == BLACK && bro->right->color == BLACK)
            {
                bro->color = RED;
                //回溯，在黑兄黑侄黑父情况下回溯成功
                x = x->parent;
            }
            else//黑兄红侄
            {
                if(bro->left->color == RED)
                {
                    bro->left->color = BLACK;
                    bro->color = RED;
                    RightRotate(bro);
                    bro = x->parent->right;
                }
                bro->color = x->parent->color;
                x->parent->color = BLACK;
                bro->right->color = BLACK;
                LeftRotate(x->parent);
                x = root;//结束循环
            }
        }
        else
        {
            bro = x->parent->left;
            //红兄
            if(bro->color == RED)
            {
                bro->color = BLACK;
                x->parent->color = RED;
                RightRotate(x->parent);
                //更新bro
                bro = x->parent->left;
            }
            //包含两种情况，黑兄黑侄
            if(bro->left->color == BLACK && bro->right->color == BLACK)
            {
                bro->color = RED;
                //回溯，在黑兄黑侄黑父情况下回溯成功
                x = x->parent;
            }
            else//黑兄红侄
            {
                if(bro->right->color == RED)
                {
                    bro->right->color = BLACK;
                    bro->color = RED;
                    LeftRotate(bro);
                    bro = x->parent->left;
                }
                bro->color = x->parent->color;
                x->parent->color = BLACK;
                bro->right->color = BLACK;
                RightRotate(x->parent);
                x = root;//结束循环
            }           
        }
    }
    x->color = BLACK;
}

/*
其他函数
*/
template<class T>
RBTree<T>::RBTree()
{
    Nil = NewNode();
    root = Nil;
    Nil->color = BLACK;
}
template<class T>
RBTree<T>::~RBTree()
{
    destroy(root);
    delete Nil;
    Nil = nullptr;
}
template<class T>
void RBTree<T>::destroy(RBTNode<T> *node)
{
    if(node == Nil)
        return;
    destroy(node->left);
    destroy(node->right);
    delete node;
    node = nullptr;
}
template<class T>
void RBTree<T>::InOrder(RBTNode<T> *node) const
{
    if(node == Nil)
        return;
    InOrder(node->left);
    cout<<node->key<<" ";
    InOrder(node->right);
}
template<class T>
void RBTree<T>::LevelOrderPrint(RBTNode<T> *node)
{
    if(node == Nil)
        return;
    queue<RBTNode<T>*> q;
    q.push(node);
    while(!q.empty()){
        int s = q.size();
        for(int i =0 ;i<s;++i)
        {
            RBTNode<T> *tmp=q.front();
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
template<class T>
void RBTree<T>::HorizontalPrint(RBTNode<T>*node,int depth,char prefix)
{
    if(node == Nil)
    {
        return;
    }
    HorizontalPrint(node->right,depth+1,'/');
    cout << setw(depth*4) << prefix << "(" << node->key << "," << (node->color==BLACK ? "B" : "R") << ")" << endl;
    HorizontalPrint(node->left,depth+1,'\\');
}
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
