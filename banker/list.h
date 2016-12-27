#ifndef _LIST_H_
#define _LIST_H_

typedef struct _PCB
{
	int pid;   //���̺�
	int *allocation; //�ѷ�����Դ��Ŀ
	int *need;     //������Դ��Ŀ
	int *available; // ϵͳ�л�ʣ����Դ��Ŀ
	int *max;      //���������Ҫ�ĸ�����Դ��Ŀ
	bool finish;    //�Ƿ��Ƿ���
	struct _PCB *next;
}PCB;

void list_init(PCB **head,int MAX_RES);
void list_add(PCB *head,int pr,int pro,int MAX_RES);
void list_get(PCB *head);
void list_destroy(PCB *head);

#endif