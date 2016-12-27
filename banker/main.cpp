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
		printf("ϵͳ���ڲ���ȫ״̬��");   
		return false; 
	}  
	else  
	{    
		printf("\nϵͳ��ǰΪ��ȫ״̬,��ȫ����Ϊ:");
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
	printf("----------------------------���м��㷨չʾ--------------------------------\n");
	printf("****************************T0ʱ����Դ�������****************************\n");  
	printf("������         Max        Allocation          Need         Available \n"); 

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
	printf("----------------------------���м��㷨չʾ---------------------------------\n");
	printf("****************************T0ʱ����Դ�������*****************************\n");  
	printf("������        Work            Need        Allocation      Work+Allocation    Finish\n"); 

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
	printf("������Դ�����õ���Դ��Ϊ:");   
	for (i = 0; i < MAX_RES; i++)         
	{
		printf(" %d",head->available[i]);
	}   
	printf("\n");
}
void  changdata(int i)//��i���̽�����Դ���� 
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
void alloc()//�������м��㷨��������Դ�Խ����ж� 
{  
	int i=0,j=0; 
	bool flag = 1;
	
	PCB * pcur = head->next;
	
	printf("������Ҫ��������Դ���̺ţ�0-%d)\n",pro-1);
	while(1)
	{
		scanf("%d",&i); 
		if(i >=  pro)
		{
			printf("������̲����ڣ����������룺\n");
			continue;
		}
		break;
	}
	while(1)
	{
		flag = 1;
		printf("���������%d�������Դ��\n",i);
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
					if(Request[j]>pcur->need[j])//�ж������Ƿ������������������� 
					{  
						printf("����%d ������Դ����������Ҫ����Դ\n",i);
						printf("���䲻���������䣡\n");
						flag = 0; 
						break; 
					} 
					else if(Request[j]>head->available[j])
					{    
						printf("����%d������Դ����ϵͳ���ڿ����õ�;\n");
						printf("������������䣡\n");
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
	 printf("\t       **  1.���м��㷨   **        \n");
	 printf("\t************************************\n");
	 printf("\t--<<�������������>>--:"); 
	 scanf("%d",&pro);
	 printf("\t<<��������Դ�������>>:");  
	 scanf("%d",&MAX_RES);
	 
}
int main() 
{   
	iput();
	int i;
	list_init(&head,MAX_RES);
	for(i=0;i<pro;i++)
	{  
		list_add(head,i,pro,MAX_RES);   //������֪���������Դ������  
	}
	showdata();    
	if(safecheck())
	{
		alloc_show();
		alloc();
	}
	else
	{
		printf("����ȫ���˳��ˣ�\n");
        return 0 ;
	}
	printf("\n�Ƿ������һ������(y,Y)/(n,N)��\n");
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