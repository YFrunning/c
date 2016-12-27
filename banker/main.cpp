#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include<string.h>
#include "list.h"

int MAX_RES = 3;
PCB *head = NULL;  
int pro = 0;      
int flag = 0;
int *work = (int *)malloc(sizeof(int)*MAX_RES);
int *a = (int *)malloc(sizeof(int)*pro);

int *Request= (int *)malloc(sizeof(int)*MAX_RES);
void showdata();
void alloc_show();
bool safecheck();
void alloc();


bool safecheck()   
{   
	int flag = 1;
	int i,v=0;
	int pnum; 
	PCB *q = head->next;

	while(q != NULL)
	{
		q->finish = false;  
		q = q->next;
	}

	for(i=0;i<MAX_RES;i++) 
	{
		work[i] = head->available[i];  
	}

	pnum = pro;
	while(pnum > 0)
	{
		q = head->next;
		while(q != NULL)
		{
			if(q->finish == false)    
			{      
				flag =1;     
				for(i=0;i<MAX_RES;i++) 
				{
					if(q->need[i]>work[i])
					{
						flag =0;
						break;
					}
				}
				if(flag == 1)          
				{        
					q->finish = true;       
				     a[v++] = q->pid;
					for(i=0;i<MAX_RES;i++) 
					{
						work[i]+=q->allocation[i]; 
					}
				}
			} 
			q = q->next;  
		} 
		pnum--; 
	}

	flag =1;
	q=head->next;
	while(q!=NULL) 
	{
		if(q->finish == false)   
		{     
			flag=0;    
			break;   
		} 
		q = q->next;
	}   
	if(flag == 0)     
	{    
		printf("系统处在不安全状态！");   
		return false; 
	}  
	else  
	{    
		printf("\n系统当前为安全状态,安全序列为:");
		for(int i = 0;i < pro;++i)
		{
			printf("p%d",a[i]);
			if(i < pro-1) printf("->");
			
		}
		printf("\n");
		return true;
	} 
} 

void showdata()  
{   
	printf("\n");   
	printf("----------------------------银行家算法展示--------------------------------\n");
	printf("****************************T0时刻资源分配情况****************************\n");  
	printf("进程名         Max        Allocation          Need         Available \n"); 

	int i;
	PCB *q = head->next;

	while(q!=NULL)
	{    
		printf("   p%d    ",q->pid); 
		for (i = 0; i < MAX_RES; i++)                
		{
			printf("  %2d",q->max[i]);
		} 
		printf("\t");
		for (i = 0; i < MAX_RES; i++)          
		{
			printf("  %2d",q->allocation[i]);
		} 
		printf("\t");
		for (i = 0; i < MAX_RES; i++)        
		{
			printf("  %2d",q->need[i]);
		}
		printf("\t");
		if(q->pid == 0)
		{
			for (i = 0; i < MAX_RES; i++)         
			{
				printf("  %2d",head->available[i]);
			}
		}
		printf("\n");  
		q = q->next;
	}       
	
}
void alloc_show()  
{   
	printf("\n"); 
	printf("----------------------------银行家算法展示---------------------------------\n");
	printf("****************************T0时刻资源分配情况*****************************\n");  
	printf("进程名        Work            Need        Allocation      Work+Allocation    Finish\n"); 

	int i,j=0;

	PCB *q = head->next;
	for(i=0;i<MAX_RES;i++)
	{
		work[i] = head->available[i] ;
	}
	
	for(int k=0;k<pro;) 
	{
		while(q!=NULL)
		{  
			if(q->pid == a[j])
			{
				printf("   p%d",a[j]); 
				printf("\t");
				for (i = 0; i < MAX_RES; i++)                
				{
					printf("  %2d",work[i]);
				} 
				printf("\t");
				for (i = 0; i < MAX_RES; i++)        
				{
					printf("  %2d",q->need[i]);
				} 
				printf("\t");
				for (i = 0; i < MAX_RES; i++)          
				{
					printf("  %2d",q->allocation[i]);
				} 
				printf("\t");
				for (i = 0; i < MAX_RES; i++)          
				{
					printf("  %2d",q->allocation[i]+work[i]);
				}
				printf("\t");
				if(q->finish)
				   printf("     true   ");
				else
				   printf("     false  ");
				for(i=0;i<MAX_RES;i++)
				{
					work[i] = q->allocation[i]+work[i];
				}
				printf("\n"); 
				k++;
				break;
			}
			q = q->next;	
		}
		j++;
		q = head->next;
	}       
	printf("\n");    
	printf("各类资源可利用的资源数为:");   
	for (i = 0; i < MAX_RES; i++)         
	{
		printf(" %d",head->available[i]);
	}   
	printf("\n");
}
void  changdata(int i)//对i进程进行资源分配 
{   
	PCB *p = head->next;
	for(int j = 0;j < MAX_RES; ++j)
	{
		while(p != NULL)
		{
			if(p->pid == i)
			{  
				p->available[j] = p->allocation[j] - Request[j];
				p->allocation[j] = p->allocation[j] + Request[j];
				p->need[j] = p->need[j] - Request[j];
				head->available[j] -= Request[j];
				break;
			}
			p = p->next;
		}
	}
	
} 
void alloc()//利用银行家算法对申请资源对进行判定 
{  
	int i=0,j=0; 
	bool flag = 1;
	
	PCB * pcur = head->next;
	
	printf("请输入要求分配的资源进程号（0-%d)\n",pro-1);
	while(1)
	{
		scanf("%d",&i); 
		if(i >=  pro)
		{
			printf("输入进程不存在，请重新输入：\n");
			continue;
		}
		break;
	}
	while(1)
	{
		flag = 1;
		printf("请输入进程%d申请的资源：\n",i);
		for(j=0;j<MAX_RES;j++) 
		{ 
			scanf("%d",&Request[j]);
		}
		while(pcur != NULL)
		{
			if(pcur->pid == i)
			{
				for (j=0;j< MAX_RES;j++)
				{ 
					if(Request[j]>pcur->need[j])//判断申请是否大于需求若大于则出错 
					{  
						printf("进程%d 申请资源大于它的需要的资源\n",i);
						printf("分配不合理，不分配！\n");
						flag = 0; 
						break; 
					} 
					else if(Request[j]>head->available[j])
					{    
						printf("进程%d申请资源大于系统现在可利用的;\n");
						printf("分配出错，不分配！\n");
						flag = 0; 
						break; 
					} 
					
				}
				break;
			}

			pcur = pcur->next;
		}
		if(flag)
		{
			break;
		}
	}
	if(flag) 
	{ 
		changdata(i);
		if(safecheck())
		alloc_show();
	} 
} 
void iput()
{
	 printf("\t************************************\n");
	 printf("\t       **  1.银行家算法   **        \n");
	 printf("\t************************************\n");
	 printf("\t--<<请输入进程总数>>--:"); 
	 scanf("%d",&pro);
	 printf("\t<<请输入资源种类个数>>:");  
	 scanf("%d",&MAX_RES);
	 
}
int main() 
{   
	iput();
	int i;
	list_init(&head,MAX_RES);
	for(i=0;i<pro;i++)
	{  
		list_add(head,i,pro,MAX_RES);   //输入已知进程最大资源需求量  
	}
	showdata();    
	if(safecheck())
	{
		alloc_show();
		alloc();
	}
	else
	{
		printf("不安全先退出了！\n");
        return 0 ;
	}
	printf("\n是否再添加一个进程(y,Y)/(n,N)：\n");
	getchar();
	char c = getchar();
	if(c == 'Y'||c == 'y')
	{
		pro += 1;
		list_add(head,pro-1,pro, MAX_RES);
		if(safecheck())
			alloc_show();
	}
	list_destroy(head);
	return 0;
}   