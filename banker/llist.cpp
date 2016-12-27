#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "list.h"


void list_init(PCB **head,int MAX_RES )
{
	if(head == NULL)
	{
		return;
	}
	*head = (PCB *)malloc(sizeof(PCB));
	(*head)->allocation = (int *)malloc(sizeof(int) * MAX_RES);
	(*head)->available =(int *)malloc(sizeof(int) * MAX_RES);
	(*head)->max = (int *)malloc(sizeof(int) * MAX_RES);
	(*head)->need = (int *)malloc(sizeof(int) * MAX_RES);
	(*head)->next = NULL;
}
void list_add(PCB *head,int pr,int pro,int MAX_RES )
{
	if(head == NULL)
	{
		return;
	}
	int i = 0;
	PCB *q = (PCB *)malloc(sizeof(PCB));
	q->allocation = (int *)malloc(sizeof(int) * MAX_RES);
	q->available =(int *)malloc(sizeof(int) * MAX_RES);
	q->max = (int *)malloc(sizeof(int) * MAX_RES);
	q->need = (int *)malloc(sizeof(int) * MAX_RES);
	q->next = NULL;
	q->pid = pr; 

	printf("\t -<<请输入 p%d 的Max>>-:",pr);  
	for(i=0;i<MAX_RES;i++)    
		scanf("%d",&q->max[i]);

	printf("\t请输入 p%d 的Allocation:",pr);  
	for(i=0;i<MAX_RES;i++)       
		scanf("%d",&q->allocation[i]);   

	for(i=0;i<MAX_RES;i++)   
	   q->need[i]= q->max[i] - q->allocation[i];
	if(pr == pro-1)
	{
		printf("\t -<<请输入Available>>-:"); 
		for(i=0;i<MAX_RES;i++)    
			scanf("%d",&head->available[i]);    
	}
	q->finish = false;
	q->next = NULL;
	while(head->next != NULL)
	{
		head = head->next;
	}
	head->next = q;
}
void list_get(PCB *head)
{
	if(head == NULL)
	{
		return;
	}
	PCB *q = head->next;
	if(q != NULL)
	{
        head->next = q->next;
		free(q->allocation);
		free(q->available);
		free(q->max);
		free(q->need);
		free(q);
	}
	
	
}
void list_destroy(PCB *head)
{
	if(head == NULL)
	{
		return;
	}
	PCB *q = head->next;
	while(q!= NULL)
	{
		list_get(head);
		q = head->next;
	}
	free(head->allocation);
	free(head->available);
	free(head->max);
	free(head->need);
	free(head);
}
