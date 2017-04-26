#include<iostream>
using namespace std;

//C++版

template <typename KeyType>
class AVLTree
{
private:
	struct AVLNode
	{
		AVLNode *parent;
		AVLNode *leftchild;
		AVLNode *rightchild;
		int    balance;
		KeyType key;
	};
	AVLNode *root;
	static AVLNode *BuyNode()
	{
		AVLNode *p = new AVLNode;
		memset(p,0,sizeof(p));
		return p;
	}
	static void freeNode(AVLNode *p)
	{
		delete p;
	}
	static AVLNode *First(AVLNode *p)
	{
		if(p == NULL) return p;
		while(p!= NULL && p->leftchild != NULL)
			p = p->leftchild;
		return p;
	}
	static AVLNode *Next(AVLNode*p)
	{
		if(p == NULL) return p;
		AVLNode *s = p->parent;
		if(p->rightchild != NULL)
		{
			return First(p->rightchild);
		}
		else
		{
			//如果是右孩子
			while(s != NULL && s->leftchild != p)//不是左孩子，那就是右孩子
			{
				p = s;
				s = s->parent;
			}
			return s;
		}

	}
	static bool insert(AVLNode *&ptr,const KeyType kx,AVLNode *pa,int &taller)
	{
		bool res = false;
		if(ptr == NULL)
		{
			ptr = BuyNode();
			ptr->key = kx;
			ptr->parent = pa;
			ptr->balance = 0;
			ptr->leftchild = NULL;
			ptr->rightchild = NULL;
			taller = 1;//记录是否需要调节平衡的变量
			res = true;
		}
		else
		{   
			if(ptr->key >kx)
			{
				res = insert(ptr->leftchild,kx,ptr,taller);
				if(res && taller == 1)
				{
					switch(ptr->balance)
					{
					case 0:
						ptr->balance = -1;
						break;
					case 1:
						taller = 0;//已经平衡，无需调节
						ptr->balance = 0;
						break;
					case -1:
						//ptr->balance = -2;
						LeftBalance(ptr);
						taller = 0;
						break;
					}
				}
				
			}
			else if(ptr->key < kx)
			{
				res = insert(ptr->rightchild,kx,ptr,taller);
				if(res && taller == 1)
				{
					switch(ptr->balance)
					{
					case 0:
						ptr->balance = 1;
						break;
					case -1:
						ptr->balance = 0;
						taller = 0;
						break;
					case 1:
						//ptr->balance = 2;
						RightBalance(ptr);
						taller = 0;
						break;
					}
				}
			}
		}
		return res;
	}
	static void Midinder(AVLNode *p)
	{ 
		if(p == NULL) return ;
		for(AVLNode *s = First(p);s != NULL;s = Next(s))
		{
			cout<<s->key<<" ";
		}
		cout<<endl;
	}
	static bool ReMove(AVLNode *&ptr,const KeyType kx)
	{
		bool res = false;
        if(ptr == NULL)  return res;
		if(ptr->key > kx)
		{
			res = ReMove(ptr->leftchild,kx);
		}
		else if(ptr->key < kx)
		{
			res = ReMove(ptr->rightchild,kx);
		}
		else if(ptr->leftchild != NULL && ptr->rightchild != NULL) //删除双分支（狸猫换太子）
		{
			AVLNode *s = Next(ptr);
			ptr->key = s->key;
			res = ReMove(ptr->rightchild,s->key);
		}
		else//删除单分支  叶子结点   根
		{
			AVLNode *child = ptr->leftchild != NULL ? ptr->leftchild : ptr->rightchild;
			AVLNode *pa = ptr->parent;
			if(child != NULL)
				child->parent = pa;
			/*if(pa->leftchild == ptr)
			{
				pa->leftchild = child;
			}
			else if(pa->rightchild == ptr)
			{
				pa->rightchild = child;
			}*/
			if(pa->leftchild == ptr)
				pa->balance = ptr->balance+1;
			else if(pa->rightchild == ptr)
				pa->balance = ptr->balance-1;
			freeNode(ptr);
			ptr = child;
			res = true;
		}

		return res;
	} 
	//AVL树的左旋和右旋
	//右旋
	static void RotateRigth(AVLNode *&ptr)
	{

		if(ptr == NULL) return ;
		AVLNode *p = ptr->leftchild;
		p->parent = ptr->parent;
		ptr->leftchild = p->rightchild;
		if(p->rightchild != NULL)
		{
			p->rightchild->parent = ptr;
		}
		p->rightchild = ptr;
		ptr->parent = p;
		ptr = p;

	}
	//右旋
	static void RotateLeft(AVLNode *& ptr)
	{
		AVLNode *p = ptr->rightchild;
		p->parent = ptr->parent;
		ptr->rightchild = p->leftchild;
		if(p->leftchild != NULL)
		{
			p->leftchild->parent = ptr;
		}
		p->leftchild = ptr;
		ptr->parent = p;
		ptr = p;
	}
	//右边调平衡 （假设右边已经平和衡了）
	static void LeftBalance(AVLNode *&ptr)
	{
		if(ptr == NULL) return ;
		AVLNode *leftsub = ptr->leftchild,*rightsub = NULL;
		switch(leftsub->balance)
		{
		case 0:
			cout<<"left is already balance"<<endl; break;
		case -1:
			ptr->balance = 0;
			leftsub->balance = 0;
			RotateRigth(ptr);
			break;
		case 1:
			rightsub = leftsub->rightchild;
			switch(rightsub->balance)
			{
			case 0:
				ptr->balance = 0;
				leftsub->balance = 0;
				break;
			case 1://加在G的位置
			     ptr->balance = 0;
				 leftsub->balance = -1;
				 break;
				 
			case -1://加在F的位置
				ptr->balance = 1;
				leftsub->balance = 0;
				break;
			}
			rightsub->balance = 0;
			RotateLeft(ptr->leftchild);
			RotateRigth(ptr);
			break;
		}
	}
	//右边调平
	static void RightBalance(AVLNode *&ptr)
	{
		if(ptr == NULL) return ;
		AVLNode *rightsub  = ptr->rightchild,*leftsub = NULL;
		switch(rightsub->balance)
		{
		case 0:
			cout<<"right already balance"<<endl;
			break;
		case 1:
			ptr->balance = 0;
			rightsub->balance = 0;
			RotateLeft(ptr);
			break;
		case -1:
			leftsub = rightsub->leftchild;
			switch(leftsub->balance)
			{
			case 0:
				ptr->balance = 0;
                rightsub->balance = 0;
				break;
			case 1:
				ptr->balance = -1;
				rightsub->balance = 0;
				break;
			case -1:
				ptr->balance = 0;
                rightsub->balance = -1;
				break;
			}
			RotateRigth(ptr->rightchild);
			RotateLeft(ptr);
			break;
		}
	}
	
public:
	AVLTree():root(NULL){}
	~AVLTree(){}
	//C++ 插入节点
	bool insert(const KeyType kx,int &h)
	{
		return insert(root,kx,NULL,h);
	}
	void Midinder()const
	{
		return Midinder(root);
	}
	//C++删除节点
	bool  ReMove(const KeyType kx)
	{
          return ReMove(root,kx);
	}
	//删除节点
	bool ReMove1(KeyType kx)
	{
		bool res = ReMove(root,kx);
		if(!res ) return false;
		//调节平衡
		LeftBalance(root);
		RightBalance(root);
        return res;
	}
};

int main()
{
	AVLTree<int> mytree;
	//int  str[] = {53,17,78,9,45,65,87,24,81,97,89,53,87};
	int str[] = {16,3,7,11,9,26,18,14,15};//{24,17,9,10,19,36};
	int len = sizeof(str)/sizeof(str[0]);
    int h = 0;
	for(int i = 0;i < len;++i)
	{
		mytree.insert(str[i],h);
	}
	cout<<endl;
	mytree.Midinder();

	int i = 0;
	while(cin>>i,i != -1)
	{
		//s = search(root,i);
		mytree.ReMove1(i);
		mytree.Midinder();
	}
   
	return 0;
}