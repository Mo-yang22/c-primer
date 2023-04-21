// 利用vector存储实现堆，且从下标0位置开始存储元素
// parent(i) =  (i-1)/2
// leftChild(i) =  2 * i + 1
// rightChild(i) =  2 * i  +  2
// 最后一个非叶子节点索引为 (count-1) / 2， 其中 count 为当前堆中元素个数
#include <iostream>
#include <string>
#include <vector>
using namespace std;
template<typename T>
class MaxHeap_vector {
    using uint = unsigned int;
public:
    MaxHeap_vector(){
    }
    MaxHeap_vector(const T arr[],int n)
    {
        data.assign(arr,arr+n);
        count = n;
        //?
        for(int i = (count-1)/2;i>=0;i--){
            shift_down(i);
        }
    }
    ~MaxHeap_vector(){
        data.clear();
        data.shrink_to_fit();
    }
    void insert(T d){
        data.push_back(d);
        ++count;
        shift_up(count-1);
    }
    T pop_max(){
        if(count > 0){
            swap(data[0],data[count-1]);
            count--;
            shift_down(0);
            return data[count];
        }
        cerr<<"try to pop from empty heap"<<endl;
        return T();
    }

    T peek_max(){
        if(!count)
        {
            cerr<<"try to peek from empty heap"<<endl;
            return T();
        }
        else return data[0];

    }


    void debug_print() {
        for (uint i = 0; i < count; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
private:
    void shift_down(uint i){
        uint k = i;
        while(2*k+1<count ){
            uint j = 2*k+1;
            if((j+1<count)&& (data[j]<data[j+1]))
                j++;
            if(data[k]<data[j]){
                std::swap(data[k],data[j]);
                k=j;
                continue;
            }
            break;
        }
    }
    void shift_up(uint i){
        uint k = i;
        while(k>0){
            uint j=(k-1)/2;
            if(j>0&&data[j]<data[k]){
                swap(data[j],data[k]);
                k=j;
                continue;
            }
            break;
        }
    }
private:
    uint count = 0;
    vector<T> data;
};
void HeapSort_WithMaxHeapVector(int arr[], int n) {
    MaxHeap_vector<int> maxHeap_vector(arr, n);  // 用待排序数组构造最大堆
    for (int i = 0; i < n; ++i) {
        arr[n - i - 1] = maxHeap_vector.pop_max();  // 依次取出堆得最大元素用于排序
    }
}
int main()
{
    int arr[]{4,3,9,7,13,23,18,16,14,8};
    int arr1[]{1,2,3,4,12,23,18,19,5,6,9,19,8,13,16};
    MaxHeap_vector<int> mvi(arr1,10);
    mvi.debug_print();
    mvi.insert(17);
    mvi.debug_print();
    mvi.insert(99);
    cout<<mvi.peek_max()<<endl;;
    cout<<mvi.pop_max()<<endl;
    mvi.debug_print();
    return 0;
}