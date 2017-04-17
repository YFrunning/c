#include<ioatream>
#include<stack>

using namespace std;

//1号栈（负责打印）
void Rotat(stack<int> *p,stack<int> *p1)
{
     int key = 0;
	 /*while(!p->empty() || !p1->empty())
	 {*/
		 //让1号栈的元素入到2号栈里面
		 while(p->size() != 1)
		 {
			 key = p->top();p->pop();
			 p1->push(key);
		 }
		 //只有一个元素的时候打印
		 key = p->top();p->pop();
		 cout<<key<<" ";
		 //将2号栈里面的元素全部放入1号栈里面
		 while(!p1->empty())
		 {
			 int key = p1->top();p1->pop();
			 p->push(key);
		 }
	 cout<<endl;
}
void choice(stack<int> *p,stack<int> *p1)
{
      int n = 0;
	  int key = 0;
	  while(1)
	  {
		  cout<<"1代表想入栈，2代表不想入栈"<<endl;
		  cin>>n;
		  switch(n)
		  {
		  case 1:
			   cout<<"请输入数据(-1结束)"<<endl;
			  while(cin>>key,key != -1)
			  {
			      p->push(key);
			  }
			  
			  break;
		  case 2:
			  if(!p->empty())
			  {
					Rotat(p,p1);
			  } 
			  break;
		  default:
			  cout<<"输入不正确"<<endl;
			  break;
		  }
	  }
	  
}

int main()
{
	int arr[] = {1,4,2,7,0,8};
	stack<int> st;
	stack<int> st1;
	choice(&st,&st1);
	cout<<endl;
	return 0;
}
