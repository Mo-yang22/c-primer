/*
 * @Author: skp 1123302861@qq.com
 * @Date: 2023-06-22 20:45:56
 * @LastEditors: skp 1123302861@qq.com
 * @LastEditTime: 2023-06-23 10:17:20
 * @FilePath: /c-primer/RB_TREE/main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "RB_tree.cpp"
int main() {
  RBTree<int> rb;

  int arr[] = {10, 7, 8, 15, 5, 6, 11, 13, 12};
  int n = sizeof(arr) / sizeof(int);
  for (int i = 0; i < n; i++) {
    rb.Insert(arr[i]);
  }
  rb.HorizontalPrint();
  int arr2[] = {2, 4, 22, 21, 24, 23, 27, 26};
  for (auto i : arr2) {
    rb.Insert(i);
  }
  rb.HorizontalPrint();
  cout << "...................." << endl;
  rb.Remove(27);
  rb.Remove(8);
  rb.Remove(6);
  rb.HorizontalPrint();
  return 0;
}
