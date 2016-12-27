#ifndef _LIST_H_
#define _LIST_H_

typedef struct _PCB
{
	int pid;   //进程号
	int *allocation; //已分配资源数目
	int *need;     //还需资源数目
	int *available; // 系统中还剩的资源数目
	int *max;      //进程最大需要的各类资源数目
	bool finish;    //是否是分配
	struct _PCB *next;
}PCB;

void list_init(PCB **head,int MAX_RES);
void list_add(PCB *head,int pr,int pro,int MAX_RES);
void list_get(PCB *head);
void list_destroy(PCB *head);

#endif