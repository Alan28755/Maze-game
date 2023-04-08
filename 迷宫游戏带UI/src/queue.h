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
	//定义泛型队列结构体
	typedef struct queue
	{
		unsigned int size;//存储此队列元素大小
		qElem* front;
		qElem* rear;
		unsigned int len;//存储当前队列长度
	}queue;
	bool newQueue(queue* q, int size);//初始化队列
	bool q_front(queue* q, void* e);//访问队首元素，存储到e中
	bool q_back(queue* q, void* e);//访问队尾元素，存储到e中
	bool q_push(queue* q, void* e);//e入队
	bool q_pop(queue* q);//弹出队首元素
	bool q_empty(queue* q);//判断队列是否为空，空则返回真
	void q_clean(queue* q);//清除队内元素

#ifdef __cplusplus
}
#endif // __cplusplus