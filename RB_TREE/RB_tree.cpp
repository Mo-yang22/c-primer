#include "RB_tree.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

static int Init(RBtree* T);
static int FindMin(Node* ptr,RBtree NullNode);
static void RightRotate(RBtree* T);
static void LeftRotate(RBtree* T);
 
static void RightPreOrderTra(RBtree ptr,RBtree NullNode);
static void RightInOrderTra(RBtree ptr,RBtree NullNode);
static void RightPostOrderTra(RBtree ptr,RBtree NullNode);

int Find(RBtree T,int argD)
{
    if(T){
        Node* root = T->right;
        Node* NullNode = T->left;
        while(root!=NullNode){
            if(root->data==argD)
                return 0;
            else if(argD > root->data){
                root=root->right;
            }
            else{
                root=root->left;
            }
        }
    }
    return -1;
}
static int FindMin(Node* ptr,Node* NullNode);