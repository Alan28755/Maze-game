#pragma once
#include<malloc.h>
#include <stdbool.h>
#include<string.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct qElem
	{
		void* data;
		struct qElem* next;
	}qElem;
	//���巺�Ͷ��нṹ��
	typedef struct queue
	{
		unsigned int size;//�洢�˶���Ԫ�ش�С
		qElem* front;
		qElem* rear;
		unsigned int len;//�洢��ǰ���г���
	}queue;
	bool newQueue(queue* q, int size);//��ʼ������
	bool q_front(queue* q, void* e);//���ʶ���Ԫ�أ��洢��e��
	bool q_back(queue* q, void* e);//���ʶ�βԪ�أ��洢��e��
	bool q_push(queue* q, void* e);//e���
	bool q_pop(queue* q);//��������Ԫ��
	bool q_empty(queue* q);//�ж϶����Ƿ�Ϊ�գ����򷵻���
	void q_clean(queue* q);//�������Ԫ��

#ifdef __cplusplus
}
#endif // __cplusplus