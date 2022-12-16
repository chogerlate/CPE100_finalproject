// โหลด library
#include "arraylist.h"
#include "ctype.h"
#include "library.h"
#include "stdlib.h"
#include "string.h"
#include <stdio.h>

// กำหนดค่าความยาว character ที่ใช้
#define MAX_OPTION_LENGTH 10



int main(void) {
  //----------------- Setup ---------------------------
  // นำเอาค่าที่เซฟไว้มา เก็บเข้า booklist
  LIST_T *BookList = listCreate(1);
  char *filepath = "data.txt"; //
  // bookCreateFromtxt(BookList, filepath); // แบบมี starter
  bookCreateFromtxt(BookList, "output.txt"); // โหลดข้อมูลจากไฟล์ที่ save ไว้

  //------------------ ค่าตัวเลือก -------------------------
  
  while (1) {
    char temp_option[MAX_OPTION_LENGTH];
    int selected_choice = 0;
    printf("Menu \n");
    printf("1)Add book\n");
    printf("2)Remove book\n");
    printf("3)Edit book\n");
    printf("4)Show all book\n");
    printf("5)Search book\n");
    printf("6)Borrow book\n");
    printf("7)Return book\n");
    printf("8)Exit\n");
    fgets(temp_option, MAX_OPTION_LENGTH, stdin);
    selected_choice = atoi(temp_option);

    if (selected_choice == 1) {
      printf("\n-----[ You selected Add Book option ]-----\n");
      BOOK *b1 = bookCreate();
      listAppend(BookList, b1);
    } else if (selected_choice == 2) {
      printf("\n-----[ You selected Remove book option ]-----\n");
      bookListRemoveByTitle(BookList);
      bookListShow(BookList);
    } else if (selected_choice == 3) {
      printf("\n-----[ You selected Edit Book option ]-----\n");
      bookEdit(BookList);
    } else if (selected_choice == 4) {
      printf("\n-----[ You selected Show All Book option ]-----\n");
      bookListShow(BookList);
    } else if (selected_choice == 5) {
      printf("\n-----[ You selected Search option ]-----\n");
      bookSearch(BookList);
    } else if (selected_choice == 6) {
      printf("\n-----[ You selected Borrow option ]-----\n");
    } else if (selected_choice == 7) {
      printf("\n-----[ You selected Return option ]-----\n");
    } else if (selected_choice == 8) {
      printf("\n-----[ You selected Exit option ]-----\n");
      saveBookList(BookList, "output.txt");
      printf("The data had been saved \n see you later goodbye :) \n");
      break;
    } else {
      continue;
    }
    printf("---------------------------------\n");
    fflush(stdin);
  }
  

  return 0;
}
