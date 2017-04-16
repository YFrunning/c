#include<iostream>
using namespace std;
//逆序打印单链表
//1.不修改原来的链表
struct ListNode 
{
	int data;
	ListNode *next;
};
ListNode *BuyNode()
{
	ListNode *tmp = new ListNode;
	memset(tmp,0,sizeof(tmp));
	return tmp;
}
void Destroy(ListNode *p)
{
	delete p;
}
ListNode *CreateHead()
{
	ListNode *tmp = BuyNode();
	tmp->data = 0;
	tmp->next = NULL;
	return tmp;
}
bool insert(ListNode *p,int kx)//尾插
{
	if(p == NULL ) return false;
	ListNode *s = p;//标记头
	ListNode *tmp = BuyNode();
	tmp->data = kx;
	tmp->next = NULL;
	while(p->next != NULL)
	{
		p = p->next;
	}
	p->next = tmp;
	return true;

}
//递归的逆序打印
void resprint(ListNode *p)
{
	if(p != NULL)
	{
		resprint(p->next);
		cout<<p->data<<" ";
	}

}
//打印
void sprin(ListNode *p)
{
	if(p == NULL) return ;
	ListNode *s = p->next;
	while(s != NULL)
	{
		cout<<s->data<<" ";
		p = p->next;
	}
}
//改变表结构的打印
void Resprint1(ListNode *p)
{
	if(p == NULL) return ;
	ListNode *s = p->next;
	ListNode *tmp = NULL;
	p->next = NULL;//断开头
	while(s != NULL)
	{
		tmp = s;
		s = s->next;
		tmp->next = p->next;
		p->next = tmp;
	}
	sprin(p);
}

int main()
{
	int str[] = {1,4,2,8,5,9,3};
	int len = sizeof(str)/sizeof(str[0]);
	ListNode *root = CreateHead();
	for(int i = 0;i < len ;++i)
	{
		insert(root,str[i]);
	}
	resprint(root);
	cout<<endl;
	resprint(root);
	return 0;
}
