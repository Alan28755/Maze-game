#pragma once
#include<malloc.h>
#include <stdbool.h>
#include<string.h>
#include<stdio.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
	typedef struct lElem
	{
		void* data;
		struct lElem* next;
	}lElem;
	typedef struct list
	{
		unsigned int Size;
		lElem* front;
		lElem* rear;
		unsigned int len;
	}list;
	bool newList(list* l, unsigned int size);
	bool l_insert(list* l, void* e,unsigned int i);
	bool l_push_back(list* l, void* e);

	bool l_erase(list* l, unsigned int i);
	bool l_visit(list* l, void* e, unsigned int i);
	bool l_visit_erase(list* l, void* e, unsigned int i);
	bool l_empty(list* l);
	void l_clean(list* l);

#ifdef __cplusplus
}
#endif // __cplusplus