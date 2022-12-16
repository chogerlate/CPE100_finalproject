#include "arraylist.h"
#include "ctype.h"
#include "library.h"
#include "stdlib.h"
#include "string.h"
#include <stdio.h>
// BOOK *allocateHeapBOOK(BOOK value) {
//   BOOK *book = (BOOK *) calloc(1, sizeof(BOOK));
//   *book = value;
//   return book;
// }

// void printBook(BOOK *book) {
//   printf("%s \n", book->title);
//   printf("%s \n", book->author);
//   printf("%d \n", book->year);
//   printf("%s \n",( (char*)listGetAt(book->name, 0)) );
//   printf("%s \n", ( (char*)listGetAt(book->option, 0)) );
//    printf("%s \n",( (char*)listGetAt(book->name, 1)) );
//   printf("%s \n", ( (char*)listGetAt(book->option, 1)) );
// }

int main(void) {

  // Create Starter-BookList List
  LIST_T *BookList = listCreate(1);
  char *filepath = "data.txt"; // 
  // bookCreateFromtxt(BookList, filepath); // แบบมี starter 
  bookCreateFromtxt(BookList, "output.txt"); // โหลด memory from saved file
  
  // Create Borrow Book History List
  LIST_T *BorrowList = listCreate(1);
  char *filepath_borrow = "borrow.txt";
  borrowListCreateFromtxt(BorrowList, filepath_borrow);
  
  // BOOK *b1 = bookCreate();
  // listAppend(BookList, b1);
  // printf("Test from main: %s\n", getBookByIndex(BookList, 0)->title);

// ค่าตัวเลือก

  do {
    int selected_choice;
    printf("Menu \n");
    printf("1)Add book\n");
    printf("2)Remove book\n");
    printf("3)Edit book\n");
    printf("4)Show all book\n");
    printf("5)Search book\n");
    printf("6)Borrow book\n");
    printf("7)Return book\n");
    printf("8)Exit\n");
    scanf("%d", &selected_choice);
    printf("\n");
    // printf("selected:%d \n",selected_choice);
    if (selected_choice == 1) {
      BOOK *b1 = bookCreate();
      listAppend(BookList, b1);
    } else if (selected_choice == 2) {
      bookListRemoveByTitle(BookList);
      bookListShow(BookList,BorrowList);
    }

    else if (selected_choice == 3){
      bookEdit(BookList);
    }
    else if (selected_choice == 4) {
      bookListShow(BookList,BorrowList);
    } else if (selected_choice == 5)
      ;
    else if (selected_choice == 6)
      ;
    else if (selected_choice == 7)
      ;
    else if (selected_choice == 8){
            saveBookList(BookList, "output.txt");
            saveBorrowList(BorrowList, filepath_borrow);
            break;
    }
   else {
           continue;
   }
    printf("\n");
  } while (1);

  return 0;
}
