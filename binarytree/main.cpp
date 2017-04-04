#include<iostream>
#include<math.h>
#include<stack>
using namespace std;

typedef char Elemtype;
typedef struct BtNode
{
	struct BtNode *leftchild;
	struct BtNode *rightchild;
    Elemtype data;
}BtNode;
int Depth(BtNode *p);
bool is_full_binarytree(BtNode *p);
//����ڵ�
BtNode *BuyNode()
{
	BtNode *s = new BtNode;
	s->data = 0;
	s->leftchild = NULL;
	s->rightchild = NULL;
	return s;
}
//�ͷŽڵ�
void freeBtNode(BtNode *p)
{
	delete p;
}
//�������
void Pretra(BtNode *p)
{
	if(p != NULL)
	{
		cout<<p->data<<" ";
	    Pretra(p->leftchild);
	    Pretra(p->rightchild);
	}
}
//�������
void Midtra(BtNode *p)
{
	if(p != NULL)
	{
		Midtra(p->leftchild);
		cout<<p->data<<" ";
		Midtra(p->rightchild);
	}
}
//�������
void Lasttra(BtNode *p)
{
	if(p != NULL)
	{
		Lasttra(p->leftchild);
		Lasttra(p->rightchild);
		cout<<p->data<<" ";
	}
}
//����һ��������
//ֻ��һ�������NULL������һ��������
BtNode *Createtree()
{
	BtNode *p = NULL;
	Elemtype x;
	cin>>x;
	
	if(x != '#')
	{
		p = BuyNode();
		p->data = x;
		p->leftchild = Createtree();
		p->rightchild = Createtree();
	}
	return p;

}
//�����ý���
BtNode *Createtree1(char *&str)
{
     BtNode *p = NULL;
	 if( str != NULL && *str != '#')
	 {
		 p = BuyNode();
		 p->data = *str;
		 p->leftchild = Createtree1(++str);
		 p->rightchild = Createtree1(++str);
	 }
	 return p;
	 
}
//����ת���ɶ���ָ�뽨��
BtNode *Createtree2(char ** const str)
{
	BtNode *p = NULL;
	if( str != NULL  && *str != NULL && **str != '#')
	{
		p = BuyNode();
		p->data = **str;
		p->leftchild = Createtree1(++*str);
		p->rightchild = Createtree1(++*str);
	}
	return p;

}
//��һ����㽨�����Һ���
void Createtree3(BtNode *&p,char *&str)
{
	if(  str != NULL && *str != '#')
	{
		p = BuyNode();
		p->data = *str;
		Createtree3(p->leftchild,++str);
		Createtree3(p->rightchild,++str);
	}
}
//����ָ��
void Createtree4(BtNode ** const p,char *&str)
{
	if(  str != NULL && *str != '#')
	{
		(*p) = BuyNode();
		(*p)->data = *str;
		Createtree4(&(*p)->leftchild,++str);
		Createtree4(&(*p)->rightchild,++str);
	}

}
int Findvalue(char *is,Elemtype p,int n)
{
     for(int i = 0;i < n;++i)
	 {
		 if(is[i] == p)
			 return i;
	 }
	 return -1;
}
//����ǰ���������һ��������
BtNode *CreatePM(char *pr,char *is,int n)
{
	 Elemtype p = pr[0];
	 BtNode *tmp = NULL;
     if(n > 0)
	 {
		 int m = Findvalue(is,p,n);
		 if(-1 == m) exit(1);
		 tmp  = BuyNode();
		 tmp->data = p;
		 tmp->leftchild = CreatePM(pr+1,is,m);
		 tmp->rightchild = CreatePM(pr+m+1,is+m+1,n-m-1);
	
	 }
	 return tmp;
}
BtNode *CreatetreePM(char *pr,char *is,int n)
{
	  if(pr == NULL || is == NULL || n < 1) return NULL;
	  return  CreatePM(pr,is,n);
	  
}
// ��������ͺ�����һ��������
BtNode *CreateML(char *mi,char *la,int n)
{
	Elemtype p = la[n-1];
	BtNode *tmp = NULL;
	if(n > 0)
	{
		int m = Findvalue(mi,p,n);
		if(-1 == m) exit(1);
		tmp  = BuyNode();
		tmp->data = p;
		tmp->leftchild = CreateML(mi,la,m);
		tmp->rightchild = CreateML(mi+m+1,la+m,n-m-1);

	}
	return tmp;
}
BtNode *CreatetreeML(char *mi,char *la,int n)
{
	if(mi == NULL || la == NULL || n < 1) return NULL;
	return  CreateML(mi,la,n);

}
//������Ľڵ���
int size(BtNode *p)
{
	if(p == NULL ) return 0;
	else  return size(p->leftchild)+size(p->rightchild)+1;
}
//����������
int Max(BtNode *le,BtNode *ri)
{
	int m = Depth(le);
	int n = Depth(ri);
	return m> n ? m:n;
}
int Depth(BtNode *p)
{
	if(p == NULL) return 0;
	return Max(p->leftchild,p->rightchild)+1;
}
//������������ҵ�ĳ�ڵ�
BtNode *FindBtNode(BtNode *p,Elemtype x)
{
	if(p == NULL || p->data == x) return p;
	else
	{
		BtNode *m = FindBtNode(p->leftchild,x);
		if(m == NULL)
		{
			m = FindBtNode(p->rightchild,x);
		}
		return m;
	}
}
//�ж��������Ƿ����

bool is_equal(BtNode *p,BtNode *q)
{
	return (p == NULL && q == NULL) || 
		   (p != NULL && q != NULL && 
		     p->data == q->data && is_equal(p->leftchild,p->leftchild) 
			 && is_equal(p->rightchild,q->rightchild));
}
/**********************�ǵݹ�ı��� ʹ��ջ*******************************/
//�������
void NicePreOrder(BtNode *p)
{
	 BtNode *s = NULL;
	 stack<BtNode* > st;
	 st.push(p);
	 while(!st.empty())
	 {
		 BtNode *node = st.top();st.pop();
		 cout<<node->data<<" ";
		 if( node->rightchild != NULL)
		 {
			 st.push(node->rightchild);
			 if(node->leftchild != NULL)
			 {
                 st.push(node->leftchild);
			 }
		 }
	 }
	 cout<<endl;
}
//�������
void NiceMiOrder(BtNode *p)
{
	BtNode *s = NULL;
	stack<BtNode* > st;
	while(p != NULL || !st.empty())
	{
		while(p != NULL)
		{
			st.push(p);
			p = p->leftchild;
			
		}
		BtNode *node = st.top();st.pop();
	    cout<<node->data<<" ";
	    p = node->rightchild;
	}
	cout<<endl;
}
//�������
void NiceLaOrder(BtNode *p)
{
	BtNode *s = NULL;
	stack<BtNode *> st;
	BtNode *tag = NULL;
	while(p != NULL || !st.empty())
	{
		while(p != NULL)
		{
			st.push(p);
			p = p->leftchild;
		}
		BtNode *node = st.top();st.pop();
		if(node->rightchild == NULL || node->rightchild == tag)
		{
			cout<<node->data<<" ";
			tag = node;
			node = NULL;
		}
		else
		{
			st.push(node);
			p = node->rightchild;
		}
		
	}
	cout<<endl;
}
/**********************�ǵݹ�ı��� ����*******************************/
//�ڵ�
struct SkNode
{
	BtNode *pnode;
	int popnum;
	SkNode(BtNode *p=NULL,int num=0):pnode(p),popnum(num){}
};

//�������
void NicePreOrder1(BtNode *p)
{
	BtNode *s = NULL;
	stack<SkNode > st;
	st.push(SkNode(p));
	while(!st.empty())
	{
        SkNode node = st.top();st.pop();
		if(++node.popnum == 1)
		{
			cout<<node.pnode->data<<" ";
		   if( node.pnode->rightchild != NULL)
		   {
				st.push(node); 
		   }
		   if( node.pnode->leftchild != NULL)
		   {
			   st.push(SkNode(node.pnode->leftchild));
		   }
		}
		else if(node.popnum == 2)
		{
            st.push(SkNode(node.pnode->rightchild));
		}
	}
	cout<<endl;
}
//�������
void NiceMiOrder1(BtNode *p)
{
	BtNode *s = NULL;
	stack<SkNode> st;
	st.push(SkNode(p));
	while(!st.empty())
	{
         SkNode node = st.top();st.pop();
		 if(++ node.popnum == 2)
		 {
			 cout<<node.pnode->data<<" ";
			 if(node.pnode->rightchild != NULL)
			 {
				 st.push(SkNode(node.pnode->rightchild));
			 }
		 }
		 else if(node.popnum == 1)
		 {
			 st.push(node);
			 if(node.pnode->leftchild != NULL)
				 st.push(SkNode(node.pnode->leftchild));
		 }
	}
	cout<<endl;
}
//�������
void NiceLaOrder1(BtNode *p)
{
	BtNode *s = NULL;
	stack<SkNode> st;
	st.push(SkNode(p));
	while(!st.empty())
	{
		SkNode node = st.top();st.pop();
		if(++node.popnum == 3)
		{
			cout<<node.pnode->data<<" ";
		}
		else 
		{
			st.push(node);
			if(node.popnum == 1 && node.pnode->leftchild != NULL)
			{
				 st.push(SkNode(node.pnode->leftchild));
			}
			else if(node.popnum == 2 && node.pnode->rightchild != NULL)
			{
				st.push(SkNode(node.pnode->rightchild));
			}
			
		}
	}
	cout<<endl;
}
/***********************************************************/


//��ȫ������

int sum_size(int de)
{
	int sum = 1;
	for(int i = 1;i < de;++i)
	{
         sum = sum+(int)pow(2.0,i);
	}
	return sum;
}
bool is_full_binarytree(BtNode *p)
{
	
	if(p == NULL )return true;
	else 
	{
		int de = Depth(p);
		int siz = size(p);
		int num = sum_size(de);
		return num == siz;

	}
}
int main()
{
	
	char *pre = "ABCDEFGH";
	char *mid = "CBEDFAGH";
	char *last = "CEFDBHGA";
    
	char *pre1 = "ABC";//*/"ABDECFG";
	char *mid1 = "CBA";//*/"DBEAFCG";
	

    int n = strlen(pre);
	//BtNode *s = Createtree5(pre,mid,n);
    BtNode *s = CreatetreePM(pre,mid,n);
	BtNode *s1 = CreatetreePM(pre1,mid1,n);
	//BtNode *s1 = CreatetreeML(mid,last,n);

	NicePreOrder1(s);
	NiceMiOrder1(s);
	NiceLaOrder1(s);
	//NiceMiOrder(s);
	//NiceLaOrder(s);
	//BtNode *p = FindBtNode(s,'H');
	//cout<<p<<endl;
	//int sizenum = size(s);
	//int sizenum = Depth(s);
	//cout<<sizenum<<endl;
//	bool full = is_equal(s,s1);//is_full_binarytree(s);
	//cout<<full<<endl;
	/*
	Pretra(s);
	cout<<endl;
	Midtra(s);
	cout<<endl;
	Lasttra(s);
	cout<<endl;
    */
    

    /*
	char *str="ABC##DE##F##G#H##";
	    
	//BtNode *s = Createtree();
    // BtNode *s = Createtree1(str);
	 //BtNode *s = Createtree2(&str);
	BtNode *s = NULL;
	//Createtree3(s,str);
	Createtree4(&s,str);
    Pretra(s);
	cout<<endl;
    Midtra(s);
	cout<<endl;
	Lasttra(s);
	cout<<endl;
   */
	return 0;
}