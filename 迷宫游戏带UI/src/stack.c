#include"stack.h"
void newStack(stack* s, int size)
{
    s->size = size;
    s->top = NULL;
    s->len = 0;
}

bool s_push(stack* s, void* e)
{
    sElem* elem = (sElem*)malloc(sizeof(sElem));
    if (!elem)
        return false;

    elem->data = (void*)malloc(s->size);

    if (!elem->data)
        return false;

    memcpy(elem->data, e, s->size);

    elem->next = s->top;

    s->top = elem;
    s->len += 1;

    return true;
}
bool s_pop(stack* s)
{
    if (s->top == NULL)
        return false;

    sElem* p = s->top;
    s->top = s->top->next;
    s->len -= 1;

    free(p->data);
    free(p);

    return true;
}
bool s_top(stack* s, void* e)
{
    if (s->top == NULL)
        return false;
    memcpy(e, s->top->data, s->size);
    return true;
}

void s_clean(stack* s)
{
    while (s->len)
    {
        s_pop(s);
    }
}
bool s_empty(stack* s)
{
    if (!s->top)
    {
        return true;
    }
    return false;
}