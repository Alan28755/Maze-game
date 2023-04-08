#include"queue.h"
bool newQueue(queue* q, int size)
{
	//�洢�˶�����Ԫ�����ʹ�С
	q->size = size;
	//Ϊ��������ռ䣬��ʹ��βָ�����
	q->front = q->rear = (qElem*)malloc(sizeof(qElem));
	if (!q->front)
		return false;
	q->front->next = NULL;
	q->len = 0;
	return true;
}
bool q_front(queue* q, void* e)
{
	if (!q->len)
	{
		return false;
	}
	//���������ݰ��ֽڸ��Ƹ�e
	memcpy(e, q->front->next->data, q->size);
	return true;
}
bool q_back(queue* q, void* e)
{
	if (!q->len)
	{
		return false;
	}
	//����β���ݰ��ֽڸ�ֵ��e
	memcpy(e, q->rear->data, q->size);
	return true;
}
bool q_push(queue* q, void* e)
{
	//����һ����㲢����ռ�
	qElem* elem = (qElem*)malloc(sizeof(qElem));
	if (!elem)
		return false;
	//Ϊ�������ָ��������Ӧ��С�Ŀռ�
	elem->data = (void*)malloc(q->size);
	if (!elem->data)
		return false;
	//��eָ������ݰ��ֽڸ��Ƹ��������
	memcpy(elem->data, e, q->size);
	elem->next = NULL;
	//������β
	q->rear->next = elem;
	q->rear = elem;
	//���¶��г���
	q->len++;
	return true;
}
bool q_pop(queue* q)
{
	if (!q->len)
		return false;
	//������ʱ���ָ�����Ԫ��
	qElem* elem = q->front->next;
	//���¶���Ԫ��
	q->front->next = q->front->next->next;
	//���¶��г���
	q->len--;
	//���������Ѿ������һ����㣬��ʹ��βָ�����
	if (elem == q->rear)
		q->rear = q->front;
	//�ͷſռ�
	free(elem->data);
	free(elem);
	return true;
}
bool q_empty(queue* q)
{
	if (!q->len)
		return true;
	else
		return false;
}
void q_clean(queue* q)
{
	while (q->len)
	{
		q_pop(q);
	}
}