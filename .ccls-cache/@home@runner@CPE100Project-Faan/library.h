#ifndef LIBRARY_H
#define LIBRARY_H
#include "arraylist.h"

typedef struct {
        char title[60];
        char author[60];
        int year;
        LIST_T** name;
        LIST_T** option;
} BOOK;

BOOK* bookCreate(); //manually create book  
BOOK* booKCreateAuto(char title[60] ,char author[60],char year[60]); //Generate Book from data that receive from BookCreateFromtxt.
LIST_T* bookCreateFromtxt(LIST_T* list ,char* filepath);//Generate BookList from .txt file 
void bookListShow(LIST_T* list, LIST_T* borrowList); // Show all the book  in booklist
BOOK* getBookByIndex(LIST_T* list,int index); // get access to book 

void bookListRemoveByTitle(LIST_T* list); // remove book from booklist
void bookDestroy(BOOK* book); // clear memory of book
void bookListDestroy(LIST_T* list);  // free memory of booklist (including the books inside of it)
void saveBookList(LIST_T* list,char*filepath);// save data for the next time
void bookEdit(LIST_T *list);

typedef struct {
        char title[60];
        int status;
        char borrowHistory[100][60];
        int count;
        LIST_T** name;
        LIST_T** option;
} BORROW;
LIST_T *borrowListCreateFromtxt(LIST_T *list, char *filepath);
BORROW *borrowCreateAuto(char title[60], int status, char list[100][60], int count);
void saveBorrowList(LIST_T *list, char *filepath);
#endif