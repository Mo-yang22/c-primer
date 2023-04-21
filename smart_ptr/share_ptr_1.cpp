#include <iostream>
#include <memory>
using namespace std;
struct ListNode{
	int _data;
	shared_ptr<ListNode> _prev;
	shared_ptr<ListNode> _next;

	~ListNode() { cout << "~ListNode()" << endl; }
};
int main(){
    ListNode *l1=new ListNode;
    ListNode *l2=new ListNode;
    l1->_next = make_shared<ListNode>(*l2);
    l2->_prev = make_shared<ListNode>(*l1);
	return 0;
}
