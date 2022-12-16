#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct
{
    void **data;
    int currentSize;
    int maxSize;
} LIST_T;

LIST_T *listCreate(int initialCapacity);
void listAppend(LIST_T *list, void *value);
void listInsertAt(LIST_T *list, int index, void *value);
void *listRemoveAt(LIST_T *list, int index);
void *listGetAt(LIST_T *list, int index);
int listSize(LIST_T *list);
void listDestroy(LIST_T *list);

#endif