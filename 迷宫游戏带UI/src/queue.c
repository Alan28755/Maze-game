#include"queue.h"
bool newQueue(queue* q, int size)
{
	//存储此队列中元素类型大小
	q->size = size;
	//为队首申请空间，并使队尾指向队首
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
	//将队首数据按字节复制给e
	memcpy(e, q->front->next->data, q->size);
	return true;
}
bool q_back(queue* q, void* e)
{
	if (!q->len)
	{
		return false;
	}
	//将队尾数据按字节赋值给e
	memcpy(e, q->rear->data, q->size);
	return true;
}
bool q_push(queue* q, void* e)
{
	//声明一个结点并申请空间
	qElem* elem = (qElem*)malloc(sizeof(qElem));
	if (!elem)
		return false;
	//为结点数据指针申请相应大小的空间
	elem->data = (void*)malloc(q->size);
	if (!elem->data)
		return false;
	//将e指向的数据按字节复制给结点数据
	memcpy(elem->data, e, q->size);
	elem->next = NULL;
	//更换队尾
	q->rear->next = elem;
	q->rear = elem;
	//更新队列长度
	q->len++;
	return true;
}
bool q_pop(queue* q)
{
	if (!q->len)
		return false;
	//声明临时结点指向队首元素
	qElem* elem = q->front->next;
	//更新队首元素
	q->front->next = q->front->next->next;
	//更新队列长度
	q->len--;
	//若弹出的已经是最后一个结点，则使队尾指向队首
	if (elem == q->rear)
		q->rear = q->front;
	//释放空间
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