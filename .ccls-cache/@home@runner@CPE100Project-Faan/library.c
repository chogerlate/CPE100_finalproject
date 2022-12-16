#include "library.h"
#include "arraylist.h"

#include "ctype.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_LINE_LENGTH 1000

/*        Features
1) เพิ่ม-ลบ หนังสือ
2) editing book details.
3) finding books from title or author name.
4) Borrow and return books features.
5) Storing data of the books and borrow/return records in other file
        */

BOOK *bookCreate() {
  /*This function used to manually create book struct before add it to booklist
   */
  BOOK *b1 = (BOOK *)calloc(1, sizeof(BOOK));
  while (1) { // title
    char temp_title[60] = "";
    printf("Enter title: ");
    scanf("%s", temp_title);
    if (strlen(temp_title) > 60 || strlen(temp_title) < 1) {
      printf("Invalid title");
      continue;
    }
    strcpy(b1->title, temp_title);
    break;
  }
  while (1) { // author name
    char temp_author[60] = "";
    printf("Enter author name: ");
    scanf("%s", temp_author);
    if (strlen(temp_author) > 60 || strlen(temp_author) < 1) {
      printf("Invalid author name\n");
      continue;
    }
    strcpy(b1->author, temp_author);
    break;
  }
  while (1) { // year name
    char temp_year[60] = "";
    printf("Enter publish year: ");
    scanf("%s", temp_year);
    if (strlen(temp_year) > 4 || strlen(temp_year) < 1) {
      printf("Invalid publish year\n");
      continue;
    }
    int check = 0;
    for (int i = 0; i < strlen(temp_year); i++) {
      if (!isdigit(temp_year[i])) {
        check = 1;
        continue;
      }
    }
    if (check == 1) {
      printf("Invalid publish year\n");
      continue;
    }
    b1->year = atoi(temp_year);
    break;
  }
  return b1;
}

BOOK *bookCreateAuto(char title[60], char author[60], char year[60]) {
  /* Create the BOOK structure automatically. This function must be used in
   * conjunction with the BookCreateFromText function. */
  BOOK *b1 = (BOOK *)calloc(1, sizeof(BOOK));
  char temp_title[60];
  strcpy(temp_title, title);
  if (strlen(temp_title) > 60 || strlen(temp_title) < 1) {
    printf("Invalid title\n");
  }
  strcpy(b1->title, temp_title);

  char temp_author[60];
  strcpy(temp_author, author);
  if (strlen(temp_author) > 60 || strlen(temp_author) < 1) {
    printf("Invalid author name\n");
  }
  strcpy(b1->author, temp_author);
  char temp_year[60];
  strcpy(temp_year, year);
  if (strlen(temp_year) > 4 || strlen(temp_year) < 1) {
    printf("Invalid publish year\n");
  }
  for (int i = 0; i < strlen(temp_year); i++) {
    if (!isdigit(temp_year[i])) {
      printf("Invalid publish year\n");
    }
  }
  b1->year = atoi(temp_year);

  return b1;
}

LIST_T *bookCreateFromtxt(LIST_T *list, char *filepath) {
  /*This function used to create BookList from .txt file
   */
  FILE *textfile;
  char line[MAX_LINE_LENGTH];
  char titleList[MAX_LINE_LENGTH][60];
  char authorList[MAX_LINE_LENGTH][60];
  char yearList[MAX_LINE_LENGTH][60];
  textfile = fopen(filepath, "r");
  if (textfile == NULL)
    printf("ERROR THE FILE CAN'T BE OPEN\n");

  int count = 0;
  int round = 1;
  while (fgets(line, MAX_LINE_LENGTH, textfile)) {
    line[strlen(line) - 1] = '\0'; //ลบตัว \n
    if (count == 0) {
      strcpy(titleList[round - 1], line);
    } else if (count == 1) {
      strcpy(authorList[round - 1], line);
    } else if (count == 2) {
      strcpy(yearList[round - 1], line);
    } else if (count == 3) {
      round++;
      count = 0;
      continue;
    }
    count++;
  }

  for (int i = 0; i < round; i++) {
    // append book to booklist
    // printf("%d: %s\n", i, titleList[i]);
    BOOK *temp_book = bookCreateAuto(titleList[i], authorList[i], yearList[i]);
    listAppend(list, temp_book);
  }

  fclose(textfile);

  return list;
}

BOOK *getBookByIndex(LIST_T *list, int index) {
  // using this function to get access to a book element via the index
  return (BOOK *)listGetAt(list, index);
}

BORROW *getBorrowByIndex(LIST_T *list, int index) {
  // using this function to get access to a book element via the index
  return (BORROW *)listGetAt(list, index);
}

void bookListShow(LIST_T *list, LIST_T *borrowList) {
  // show books in booklist
  for (int index = 0; index < list->currentSize; index++) {
    printf("Title: %s\n", getBookByIndex(list, index)->title);
    printf("Author Name: %s\n", getBookByIndex(list, index)->author);
    printf("Publish Year: %d\n", getBookByIndex(list, index)->year);
    if (strcmp(getBorrowByIndex(borrowList, index)->title,
               getBookByIndex(list, index)->title) == 0) {
      if ((getBorrowByIndex(borrowList, index)->status) == 0) {
        printf("Status: Available\n");
      } else {
        printf("Status: Borrowed\n");
      }
    } else {
      printf("Invalid Order Book\n");
    }
    printf("Borrowing History: \n");
    for(int i=0;i<getBorrowByIndex(borrowList, index)->count;i++){
      //&(getBorrowByIndex(borrowList, index)->borrowHistory[i][0]))
      //printf("%s\n", &(getBorrowByIndex(borrowList, index)->borrowHistory[i][0]));
      int j=0;
      while((getBorrowByIndex(borrowList, index)->borrowHistory[i][j]) != '\0')
      {
        if((getBorrowByIndex(borrowList, index)->borrowHistory[i][j])=='0'){
          //printf("found 0\n");
          printf("%s%s\n", "Borrow",&(getBorrowByIndex(borrowList, index)->borrowHistory[i][1]));
          //getBorrowByIndex(borrowList, index)->borrowHistory[i][j]="Borrow";
        }
        else if((getBorrowByIndex(borrowList, index)->borrowHistory[i][j])=='1'){
          //printf("found 1\n");
          printf("%s%s\n","Return", &(getBorrowByIndex(borrowList, index)->borrowHistory[i][1]));
        }
        else{
          //printf("other\n");
        }
        j++;
      }
    }
    printf("\n");
  }
}

void bookListRemoveByTitle(LIST_T *list) {
  // remove book from booklist via title
  char temp_title[60] = "";
  while (1) { // title
    printf("Enter title: ");
    scanf("%s", temp_title);
    if (strlen(temp_title) > 60 || strlen(temp_title) < 1) {
      printf("Invalid title");
      continue;
    }
    break;
  }
  
  // find index of corresponded name
  for (int index = 0; index < list->currentSize; index++) {
    if (!strcmp(temp_title, getBookByIndex(list, index)->title)) {
      //printf("FOUND\n");
      bookDestroy(listRemoveAt(list, index));
    }
  }
}

void bookDestroy(BOOK *book) {
  // free memory of book
  free(book->name);
  free(book->option);
  free(book);
}
void bookListDestroy(LIST_T *list) {
  // free memory of booklist (including the books inside of it)
  for (int index = 0; index < list->currentSize; index++) {
    bookDestroy(getBookByIndex(list, index));
  }
  free(list);
}

void saveBookList(LIST_T *list, char *filepath) {
  FILE *textfile;
  char line[MAX_LINE_LENGTH];
  char titleList[MAX_LINE_LENGTH][60];
  char authorList[MAX_LINE_LENGTH][60];
  char yearList[MAX_LINE_LENGTH][60];
  textfile = fopen(filepath, "w");
  if (textfile == NULL)
    printf("ERROR THE FILE CAN'T BE OPEN\n");

  for (int book_index = 0; book_index < list->currentSize; book_index++) {
    // write booklist to output file
    fprintf(textfile, "%s\n", getBookByIndex(list, book_index)->title);
    fprintf(textfile, "%s\n", getBookByIndex(list, book_index)->author);
    fprintf(textfile, "%d\n", getBookByIndex(list, book_index)->year);
    if (book_index == list->currentSize - 1) {
      break;
    }
    fprintf(textfile, "\n");
  }

  fclose(textfile);
}

void bookEdit(LIST_T *list) {
  int selectedBook;
  // show name of all book
  for (int index = 0; index < list->currentSize; index++) {
    printf("%d : ", index + 1);
    printf("Title: %s\n", getBookByIndex(list, index)->title);
  }
  // select the book
  printf("Select number of book to edit\n");
  scanf("%d", &selectedBook);
  // show current detail
  printf("Current detail of this book (%d)\n", selectedBook);
  printf("Title: %s\n", getBookByIndex(list, selectedBook - 1)->title);
  printf("Author Name: %s\n", getBookByIndex(list, selectedBook - 1)->author);
  printf("Publish Year: %d\n", getBookByIndex(list, selectedBook - 1)->year);
  // edit detail of book
  printf("-> Edit detail\n");
  BOOK *newbook = bookCreate();
  list->data[selectedBook - 1] = newbook;
}

void bookSearch(LIST_T *list) {
  // input searching word
  char searchword[60] = "";
  printf("Enter title or author: ");
  scanf("%s", searchword);
  for (int index = 0; index < list->currentSize; index++) {
    if (searchword == getBookByIndex(list, index)->title ||
        getBookByIndex(list, index)->author) {
    }
    printf("Title: %s\n", getBookByIndex(list, index)->title);
    printf("Author Name: %s\n", getBookByIndex(list, index)->author);
    printf("Publish Year: %d\n", getBookByIndex(list, index)->year);
  }
}

BORROW *borrowCreateAuto(char title[60], int status, char list[100][60], int count) {
  /* Create the BOOK structure automatically. This function must be used in
   * conjunction with the BookCreateFromText function. */
  BORROW *b1 = (BORROW *)calloc(count, sizeof(BORROW));
  char temp_title[60];
  strcpy(temp_title, title);
  if (strlen(temp_title) > 60 || strlen(temp_title) < 1) {
    printf("Invalid title\n");
  }
  int temp_status = status;
  strcpy(b1->title, temp_title);
  b1->status = temp_status;
  memcpy(&b1->borrowHistory,list,count*60*sizeof(char));
  //b1->borrowHistory = list;
  b1->count = count;
  return b1;
}

LIST_T *borrowListCreateFromtxt(LIST_T *list, char *filepath) {
  /*This function used to create BookList from .txt file
   */
  FILE *textfile;
  char line[MAX_LINE_LENGTH];
  char titleList[MAX_LINE_LENGTH][60];
  textfile = fopen(filepath, "r");
  if (textfile == NULL)
    printf("ERROR THE FILE CAN'T BE OPEN\n");

  int count = 0;
  int round = 1;
  char tempHistory[MAX_LINE_LENGTH];
  int tempStatusList[MAX_LINE_LENGTH];
  int tempBookStatus[MAX_LINE_LENGTH];
  int tempBookHistoryNumber[MAX_LINE_LENGTH];
  char bookHistoryList[MAX_LINE_LENGTH][100][60];
  while (fgets(line, MAX_LINE_LENGTH, textfile)) {
    
    line[strlen(line) - 1] = '\0'; //ลบตัว \n
    if (strcmp(line, "\0") == 0) {
      char tempStatus = tempHistory[0];
      if (tempStatus == '0') {
        tempBookStatus[round - 1] = 0;
      }
      if (tempStatus == '1') {
        tempBookStatus[round - 1] = 1;
      }
      strcpy(tempHistory, "");
      tempBookHistoryNumber[round - 1] = count-1;
      round++;
      count = 0;
    } else {
      if (count == 0) {
        strcpy(titleList[round - 1], line);
      }
      if (count >= 1) {
        strcpy(tempHistory, line);
        strcpy(bookHistoryList[round - 1][count - 1], line);
      }
      count++;
    }
  }
  for (int i = 0; i < round - 1; i++) {
    BORROW *temp_borrow = borrowCreateAuto(titleList[i], tempBookStatus[i],bookHistoryList[i], tempBookHistoryNumber[i]);
    listAppend(list, temp_borrow);
  }
  fclose(textfile);
  return list;
}

void saveBorrowList(LIST_T *list, char *filepath) {
  FILE *textfile;
  textfile = fopen("borrow_test.txt", "w");
  if (textfile == NULL)
    printf("ERROR THE FILE CAN'T BE OPEN\n");
    
  for (int book_index = 0; book_index < list->currentSize; book_index++) {
    // write booklist to output file
    fprintf(textfile, "%s\n", getBorrowByIndex(list, book_index)->title);
    fprintf(textfile,"%s\n", &getBorrowByIndex(list, book_index)->borrowHistory[0][0]);
    //fprintf(textfile, "%s\n", getBorrowByIndex(list, book_index)->borrowHistory[0][0]);
    //fprintf(textfile, "%s\n", getBookByIndex(list, book_index)->author);
    //fprintf(textfile, "%d\n", getBookByIndex(list, book_index)->year);
    if (book_index == list->currentSize - 1) {
      break;
    }
    fprintf(textfile, "\n");
  }

  fclose(textfile);
}
