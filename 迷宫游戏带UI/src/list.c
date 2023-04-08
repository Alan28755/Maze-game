#include"list.h"
#include <xkeycheck.h>

bool newList(list* l, unsigned int size)
{
	l->Size = size;
	l->front = l->rear = (lElem*)malloc(sizeof(lElem));
	if (!l->front)
		return false;
	l->front->next = NULL;
	l->len = 0;
	return true;
}
bool l_insert(list* l, void* e, unsigned int i)
{
	if (i >= l->len)
	{
		printf("插入下标越界\n");
		return false;
	}
	lElem* elem = (lElem*)malloc(sizeof(lElem));
	if (!elem)
	{
		return false;
	}
	elem->data = (void*)malloc(l->Size);
	if (!elem->data)
	{
		return false;
	}
	memcpy(elem->data, e, l->Size);
	lElem* a = l->front;
	for (int t = 0; t < i; t++)
	{
		a = a->next;
	}
	lElem* b = a->next;
	a->next = elem;
	elem->next = b;
	l->len++;
	return true;
}
bool l_push_back(list* l, void* e)
{
	lElem* elem= (lElem*)malloc(sizeof(lElem));
	if (!elem)
	{
		return false;
	}
	elem->data = (void*)malloc(l->Size);
	if (!elem->data)
	{
		return false;
	}
	memcpy(elem->data, e, l->Size);
	elem->next = NULL;
	l->rear->next = elem;
	l->rear = elem;
	l->len++;
	return true;
}
bool l_erase(list* l, unsigned int i)
{
	if (i >= l->len)
	{
		printf("插入下标越界\n");
		return false;
	}
	lElem* a = l->front;
	for (int t = 0; t < i; t++)
	{
		a = a->next;
	}
	lElem* elem = a->next;
	a->next = a->next->next;
	l->len--;
	if (elem == l->rear)
	{
		l->rear = a;
	}
	free(elem->data);
	free(elem);
	
	return true;
}
bool l_visit(list* l, void* e, unsigned int i)
{
	if (i >= l->Size)
	{
		printf("访问下标越界\n");
		return false;
	}
	lElem* a = l->front;
	for (int t = 0; t <= i; t++)
	{
		a = a->next;
	}
	memcpy(e, a->data, l->Size);
	return true;
}
bool l_visit_erase(list* l, void* e, unsigned int i)
{
	if (i >= l->len)
	{
		printf("插入下标越界\n");
		return false;
	}
	lElem* a = l->front;
	for (int t = 0; t < i; t++)
	{
		a = a->next;
	}
	lElem* elem = a->next;
	a->next = a->next->next;
	l->len--;
	if (elem == l->rear)
	{
		l->rear = a;
	}
	memcpy(e, elem->data, l->Size);
	free(elem->data);
	free(elem);

	return true;
}
bool l_empty(list* l)
{
	if (l->front == l->rear)
	{
		return true;
	}
	return false;
}
void l_clean(list* l)
{
	lElem* elem;
	while (l->len--)
	{
		elem = l->front->next;
		l->front->next = elem->next;
		free(elem->data);
		free(elem);
	}
}