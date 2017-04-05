//创建一个二叉树
//只给一个先序和NULL来建立一个二叉树
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
//传引用建树
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
//引用转换成二级指针建树
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
//给一个结点建立左右孩子
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
//利用指针
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
//根据前序和中序建立一个二叉树
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
// 根据中序和后序建立一个二叉树
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