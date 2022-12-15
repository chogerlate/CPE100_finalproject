#include "arraylist.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdio.h"

LIST_T* listCreate(int initialCapacity) {
    LIST_T* list = (LIST_T*) calloc(1, sizeof(LIST_T));
    list->data = (void**) calloc(initialCapacity, sizeof(void*));
    list->currentSize = 0;
    list->maxSize = initialCapacity;
    return list;
}

void listExpand(LIST_T* list) {
    void** tmp = (void**) calloc(list->maxSize * 2, sizeof(void*));
    int i;
    for (i=0; i<list->currentSize; i++) {
        tmp[i] = list->data[i];
    }
    free(list->data);
    list->data = tmp;
    list->maxSize *= 2;
}

void listAppend(LIST_T* list, void* value) {
    if (list->currentSize == list->maxSize) {
        listExpand(list);
    }
    list->data[list->currentSize] = value;
    list->currentSize += 1;
}

void listInsertAt(LIST_T* list, int index, void* value) {
    if (list->currentSize == list->maxSize) {
        listExpand(list);
    }
    int i;
    for (i=list->currentSize-1; i>=index; i--) {
        list->data[i+1] = list->data[i];
    }
    // for (i=list->currentSize; i>index; i--) {
    //     list->data[i] = list->data[i-1];
    // }
    list->data[index] = value;
    list->currentSize += 1;
}

void* listRemoveAt(LIST_T* list, int index) {
    void* toBeRemove = list->data[index];
    
    int i;
    for (i=index; i<list->currentSize-1; i++) {
        list->data[i] = list->data[i+1];
    }
    // for (i=index+1; i<list->currentSize; i++) {
    //     list->data[i-1] = list->data[i];
    // }
    list->currentSize -= 1;
    return toBeRemove;
}

void* listGetAt(LIST_T* list, int index) {
    return list->data[index];
}

int listSize(LIST_T* list) {
    return list->currentSize;
}

void listDestroy(LIST_T* list) {
    free(list->data);
    free(list);
}