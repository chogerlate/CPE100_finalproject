// โหลด library
#include "arraylist.h"
#include "ctype.h"
#include "library.h"
#include "stdlib.h"
#include "string.h"
#include <stdio.h>

// กำหนดค่าความยาว character ที่ใช้
#define MAX_OPTION_LENGTH 10

int main(void)
{
  //----------------- Setup ---------------------------        
  // นำเอาค่าที่เซฟไว้มา เก็บเข้า booklist
  LIST_T *BookList = listCreate(1); // สร้าง list ของหนังสือใน ห้องสมุด
        
  char *bookfilepath = "bookHistory.txt"; 
  char *borrowfilepath = "borrowHistory.txt";
  char *saveBookHistoryFilePath = "bookHistory.txt";
  char *saveBorrowHistoryFilePath = "borrowHistory.txt";
  
  bookCreateFromtxt(BookList, bookfilepath); // โหลดข้อมูลจากไฟล์ที่ save ไว้
  borrowListCreateFromtxt(BookList,borrowfilepath); 
  
 //------------------ ตัวเลือก -------------------------        
  while (1)
  {
    printBookTable(BookList);    
    printf("\n");     
    char temp_option[MAX_OPTION_LENGTH]; //เก็บค่า option เป็น char ก
    int selected_choice = 0;
    printf("[ Menu ]\n");
    printf("1) Add book\n");
    printf("2) Remove book\n");
    printf("3) Edit book\n");
    printf("4) Show all book\n");
    printf("5) Search book\n");
    printf("6) Borrow book\n");
    printf("7) Return book\n");
    printf("8) Exit\n");
    fgets(temp_option, MAX_OPTION_LENGTH, stdin);
    selected_choice = atoi(temp_option);

    if (selected_choice == 1)
    {
      printf("\n-----[ You selected Add Book option ]-----\n");
      BOOK *b1 = bookCreate();
      listAppend(BookList, b1);
    }
    else if (selected_choice == 2)
    {
      printf("\n-----[ You selected Remove book option ]-----\n");
      bookListRemoveByTitle(BookList);
    }
    else if (selected_choice == 3)
    {
      printf("\n-----[ You selected Edit Book option ]-----\n");
      bookEdit(BookList);
    }
    else if (selected_choice == 4)
    {
      printf("\n-----[ You selected Show All Book option ]-----\n");
      bookListShow(BookList);
    }
    else if (selected_choice == 5)
    {
      printf("\n-----[ You selected Search option ]-----\n");
      bookSearch(BookList);
    }
    else if (selected_choice == 6)
    {
      printf("\n-----[ You selected Borrow option ]-----\n");
      borrowBook(BookList);
    }
    else if (selected_choice == 7)
    {
      printf("\n-----[ You selected Return option ]-----\n");
      returnBook(BookList);
    }
    else if (selected_choice == 8)
    {
      printf("\n-----[ You selected Exit option ]-----\n");
      saveBookList(BookList, saveBookHistoryFilePath);
      saveBorrowList(BookList, saveBorrowHistoryFilePath);
      printf("The data had been saved \nsee you later goodbye :) \n");
      break;
    }
    else
    {
      continue;
    }
    printf("---------------------------------\n");
    fflush(stdin);
  }

  return 0;
}
