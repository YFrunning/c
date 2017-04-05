
//先序遍历
void Pretra(BtNode *p)
{
	if(p != NULL)
	{
		cout<<p->data<<" ";
	    Pretra(p->leftchild);
	    Pretra(p->rightchild);
	}
}
//中序遍历
void Midtra(BtNode *p)
{
	if(p != NULL)
	{
		Midtra(p->leftchild);
		cout<<p->data<<" ";
		Midtra(p->rightchild);
	}
}
//后序遍历
void Lasttra(BtNode *p)
{
	if(p != NULL)
	{
		Lasttra(p->leftchild);
		Lasttra(p->rightchild);
		cout<<p->data<<" ";
	}
}

/**********************非递归的遍历 使用栈*******************************/
//先序遍历
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
//中序遍历
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
//后序遍历
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
/**********************非递归的遍历 计数*******************************/
//节点
struct SkNode
{
	BtNode *pnode;
	int popnum;
	SkNode(BtNode *p=NULL,int num=0):pnode(p),popnum(num){}
};

//先序遍历
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
//中序遍历
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
//后序遍历
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


