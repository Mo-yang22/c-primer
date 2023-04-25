
#include "RB_tree.cpp"
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
