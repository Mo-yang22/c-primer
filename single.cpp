/*
 * @Author: skp 1123302861@qq.com
 * @Date: 2023-06-22 20:45:56
 * @LastEditors: skp 1123302861@qq.com
 * @LastEditTime: 2023-06-23 09:26:41
 * @FilePath: /c-primer/single.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <pthread.h>
using namespace std;
class single {
public:
  static single *getinstacnce();

private:
  //私有静态指针变量指向唯一实例
  static single *p;
  //静态锁,是因为静态成员函数只能操作静态变量
  static pthread_mutex_t lock;
  //私有化构造函数
  single() { pthread_mutex_init(&lock, NULL); }
  ~single();
};
//必须要声明一下吗?
pthread_mutex_t single::lock;

single *single::p = NULL;

single *single::getinstacnce() {
  if (p == NULL) {
    pthread_mutex_lock(&lock);
    if (p == NULL) {
      p = new single;
      cout << "new" << endl;
    }
    pthread_mutex_unlock(&lock);
  }
  return p;
}
int main() {
  single *s = single::getinstacnce();
  single *s1 = single::getinstacnce();
  cout << s << endl << s1 << endl;
  return 0;
}