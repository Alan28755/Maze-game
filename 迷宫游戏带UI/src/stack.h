#pragma once
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
	typedef struct sElem
	{
		void* data;
		struct qElem* next;
	}sElem;
	typedef struct stack
	{
		unsigned int size;
		sElem* top;
		unsigned int len;
	}stack;

	void newStack(stack* s, int size);

	bool s_push(stack* s, void* e);

	bool s_pop(stack* s);

	bool s_top(stack* s, void* e);

	void s_clean(stack* s);

	bool s_empty(stack* s);

#ifdef __cplusplus
}
#endif // __cplusplus