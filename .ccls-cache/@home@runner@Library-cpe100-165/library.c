#include "library.h"
#include "arraylist.h"

#include "ctype.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_LINE_LENGTH 1000
#define MAX_CHAR_LENGTH 100
/*        Features
1) เพิ่ม-ลบ หนังสือ
2) editing book details.
3) finding books from title or author name.
4) Borrow and return books features.
5) Storing data of the books and borrow/return records in other file
        */

LIST_T *getOptionListByIndex(LIST_T *list, int indexSearched) {
  return getBookByIndex(list, indexSearched)->option;
}
LIST_T *getNameListByIndex(LIST_T *list, int indexSearched) {
  return getBookByIndex(list, indexSearched)->name;
}

BOOK *bookCreate() {
  /*This function used to manually create book struct before add it to booklist
   */
  BOOK *book = (BOOK *)calloc(1, sizeof(BOOK));
  while (1) { // title
    char temp_title[100] = "";
    printf("Enter title: ");
    fgets(temp_title, MAX_CHAR_LENGTH, stdin);
    fflush(stdin);
    if (strlen(temp_title) > 60 || strlen(temp_title) < 2) {
      printf("Invalid title\n");
      continue;
    }

    temp_title[strcspn(temp_title, "\n")] =
        0; // strcspn(str,key) มันจะreturn ค่า Index ใน str ตัวแรกที่เจอเมิ่อ str
           // นั้นเหมือนกับสักตัวใน key
    strcpy(book->title, temp_title);
    break;
  }
  while (1) { // author name
    char temp_author[60] = "";
    printf("Enter author name: ");
    fgets(temp_author, MAX_CHAR_LENGTH, stdin);
    fflush(stdin);
    if (strlen(temp_author) > 60 || strlen(temp_author) < 2) {
      printf("Invalid author name\n");
      continue;
    }
    temp_author[strcspn(temp_author, "\n")] = 0;
    strcpy(book->author, temp_author);
    break;
  }
  while (1) { // year name
    char temp_year[60] = "";
    int check = 0;

    printf("Enter publish year: ");
    fgets(temp_year, MAX_CHAR_LENGTH, stdin);
    fflush(stdin);
    if (strlen(temp_year) > 100 || strlen(temp_year) < 2) {
      check++;
      printf("Invalid publish year\n");
      continue;
    }
    temp_year[strcspn(temp_year, "\n")] = 0; // ตัด "\n" เพื่อเอาค่ามาเช็ค
    for (int i = 0; i < strlen(temp_year) - 1; i++) {
      if (!isdigit(temp_year[i])) {
        check++;
        continue;
      }
    }
    if (check > 0) {
      printf("Invalid publish year\n");
      continue;
    }
    book->year = atoi(temp_year);
    break;
  }
  return book;
}

BOOK *bookCreateAuto(char title[60], char author[60], char year[60]) {
  /* Create the BOOK structure automatically. This function must be used in
   * conjunction with the BookCreateFromText function. */
  BOOK *book = (BOOK *)calloc(1, sizeof(BOOK));
  char temp_title[60];
  strcpy(temp_title, title);
  if (strlen(temp_title) > 60 || strlen(temp_title) < 1) {
    printf("Invalid title\n");
  }
  strcpy(book->title, temp_title);

  char temp_author[60];
  strcpy(temp_author, author);
  if (strlen(temp_author) > 60 || strlen(temp_author) < 1) {
    printf("Invalid author name\n");
  }
  strcpy(book->author, temp_author);
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
  book->year = atoi(temp_year);
  book->name = listCreate(1);
  book->option = listCreate(1);

  return book;
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
    line[strlen(line) - 1] = '\0'; // ลบตัว \n
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
    printf("%d: %s\n", i, titleList[i]);
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
  // show books in booklist
  printf("[There are %d books in this library]\n\n", list->currentSize);

  for (int index = 0; index < list->currentSize; index++) {
    BOOK *book = getBookByIndex(list, index);
    printf("Title: %s\n", book->title);
    printf("Author Name: %s\n", book->author);
    printf("Publish Year: %d\n", book->year);
    if (book->option) {
      if(book->option->currentSize-1 < 0 ){
              printf("[Available]\n");
      }
      else if(getOptionValueByIndex(list,index,book->option->currentSize-1)==1){
              printf("[Available]\n");
      }else {
              printf("[Borrowed]\n");
      }
      for (int index_option = 0; index_option < book->option->currentSize;
           index_option++) {
        if (*((int *)listGetAt(book->option, index_option)) == 0) {
          printf(" - Borrow: ");
        } else if (*((int *)listGetAt(book->option, index_option)) == 1) {
          printf(" - Return: ");
        }
        printf("%s\n",
               listGetAt(getBookByIndex(list, index)->name, index_option));
      }
    }
    printf("\n");
  }
}

void bookListRemoveByTitle(LIST_T *list) {
  // remove book from booklist via title
  char temp_title[60] = "";
  while (1) {
    // title
    printf("Enter title: ");
    fgets(temp_title, MAX_CHAR_LENGTH, stdin);
    fflush(stdin);
    temp_title[strcspn(temp_title, "\n")] = 0;
    if (strlen(temp_title) > 60 || strlen(temp_title) < 1) {
      printf("Invalid title\n");
      continue;
    }
    break;
  }
  // find the index of the book that matches the received name.
  for (int index = 0; index < list->currentSize; index++) {
    if (!strcmp(temp_title, getBookByIndex(list, index)->title)) {
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
  int selectedIndex; // ตัวแปรสำหรับเก็บค่า index ที่ต้องการจะแก้ไข
  int stoploop = 0; // ตัวแปรสำหรับเงื่อนไข loop
  // Loop-1(While) รับค่าอินพุต (หากค้นหาชื่อหนังสือไม่เจอ จะวนลูปเพื่อรับค่าใหม่เรื่อยๆ)
  // Loop-2(for) ค้นหาหนังสือตามที่ชื่อที่ต้องการ และเพื่อระบุ index ที่ต้องการแก้ไข
  while (stoploop != 1) {
    char selectedTitle[60] = ""; // ตัวแปรสำหรับเก็บชื่อหนังสือที่ผู้ใช้อินพุต
    printf("Enter title to edit: ");
    fgets(selectedTitle, MAX_CHAR_LENGTH, stdin);
    fflush(stdin);
    selectedTitle[strcspn(selectedTitle, "\n")] = 0; // ตัด "\n" เพื่อเอาค่ามาเช็ค
    for (int index = 0; index < list->currentSize; index++) {
      // กรณี 1: เจอชื่อหนังสือที่ต้องการแก้ไข
      if (strcmp(selectedTitle, getBookByIndex(list, index)->title) == 0) {
        selectedIndex = index; // ระบุ index ที่ต้องการแก้ไข
        stoploop = 1;
        break;
      }
      // กรณี 2: วนลูปจนถึงรอบสุดท้ายแล้วยังไม่เจอหนังสือที่ต้องการแก้ไข
      else if (index == list->currentSize - 1) {
        printf("Title not found\n");
      }
    }
  }

  BOOK *editedBook = (BOOK *)calloc(1, sizeof(BOOK)); // สำหรับเก็บข้อมูลหลังแก้ไข
  // Loop-1(While) แก้ไข title
  // Loop-2(While) แก้ไข author name
  // Loop-3(While) แก้ไข year name
  while (1) { // title
    char temp_title[60] = "";
    printf("New title (leave blank to retain old value): ");
    fgets(temp_title, sizeof(temp_title), stdin);
    temp_title[strlen(temp_title) - 1] = 0; // ตัด "\n" เพื่อเอาค่ามาเช็ค
    // กรณี 1 : เว้นว่าง (ไม่แก้ไขใดๆ คงค่าเดิมเอาไว้)
    if (strlen(temp_title) == 0) {
      strcpy(editedBook->title, getBookByIndex(list, selectedIndex)->title);
      break;
    }
    // กรณี 2 : อินพุตเกินจำนวนที่กำหนด (วนลูปเพื่อรับค่าใหม่อีกครั้ง)
    else if (strlen(temp_title) > 60) {
      printf("Invalid title\n");
      continue;
    }
    // กรณี 3 : อินพุตตามปกติ (แก้ไขค่าตามอินพุต)
    else if (strlen(temp_title) > 0 && strlen(temp_title) < 60) {
      strcpy(editedBook->title, temp_title);
      break;
    }
  }
  while (1) { // author name
    char temp_author[60] = "";
    printf("New author name (leave blank to retain old value): ");
    fgets(temp_author, sizeof(temp_author), stdin);
    temp_author[strlen(temp_author) - 1] = 0; // ตัด "\n" เพื่อเอาค่ามาเช็ค
    // กรณี 1 : เว้นว่าง (ไม่แก้ไขใดๆ คงค่าเดิมเอาไว้)
    if (strlen(temp_author) == 0) {
      strcpy(editedBook->author, getBookByIndex(list, selectedIndex)->author);
      break;
    }
    // กรณี 2 : อินพุตเกินจำนวนที่กำหนด (วนลูปเพื่อรับค่าใหม่อีกครั้ง)
    else if (strlen(temp_author) > 60) {
      printf("Invalid author name\n");
      continue;
    }
    // กรณี 3 : อินพุตตามปกติ (แก้ไขค่าตามอินพุต)
    else if (strlen(temp_author) > 0 && strlen(temp_author) < 60) {
      strcpy(editedBook->author, temp_author);
      break;
    }
  }
  while (1) { // year name
    char temp_year[60] = "";
    printf("Enter publish year: ");
    fgets(temp_year, sizeof(temp_year), stdin);
    temp_year[strlen(temp_year) - 1] = 0; // ตัด "\n" เพื่อเอาค่ามาเช็ค
    // กรณี 1 : เว้นว่าง (ไม่แก้ไขใดๆ คงค่าเดิมเอาไว้)
    if (strlen(temp_year) == 0) {
      editedBook->year = getBookByIndex(list, selectedIndex)->year;
      break;
    }
    // กรณี 2 : อินพุตผิดปกติ (วนลูปเพื่อรับค่าใหม่อีกครั้ง)
    else if (strlen(temp_year) > 4) {
      printf("Invalid publish year\n");
      continue;
    }
    int check = 0;
    // ตรวจสอบว่าค่าที่อินพุตเป็นตัวเลขทั้งหมดหรือไม่
    for (int i = 0; i < strlen(temp_year); i++) {
      if (!isdigit(temp_year[i])) {
        check = 1;
        continue;
      }
    }
    // กรณี 3 : อินพุตผิดปกติ (วนลูปเพื่อรับค่าใหม่อีกครั้ง)
    if (check == 1) {
      printf("Invalid publish year\n");
      continue;
    }
    editedBook->year = atoi(temp_year); // แก้ไขค่าตามอินพุต
    break;
  }
  // ส่งค่าที่แก้ไขแล้วไปยัง data ตาม index นั้นๆ
  list->data[selectedIndex] = editedBook;
}

void bookShow_SpecificIndex(LIST_T *list, int indexSpec) {
       
    BOOK *book = getBookByIndex(list, indexSpec);
    printf("Title: %s\n", book->title);
    printf("Author Name: %s\n", book->author);
    printf("Publish Year: %d\n", book->year);
    if (book->option) {
      if(book->option->currentSize-1 < 0 ){
              printf("[Available]\n");
      }
      else if(getOptionValueByIndex(list,indexSpec,book->option->currentSize-1)==1){
              printf("[Available]\n");
      }else {
              printf("[Borrowed]\n");
      }
      for (int index_option = 0; index_option < book->option->currentSize;
           index_option++) {
        if (*((int *)listGetAt(book->option, index_option)) == 0) {
          printf(" - Borrow: ");
        } else if (*((int *)listGetAt(book->option, index_option)) == 1) {
          printf(" - Return: ");
        }
        printf("%s\n",
              listGetAt(getBookByIndex(list, indexSpec)->name, index_option));
      }
    }
    printf("\n");
        
        
}

void bookSearch(LIST_T *list, LIST_T *borrowList) {
  // ค้นหาด้วย title
  char searchByTitle[60] = "";
  printf("Enter title (leave blank to include all titles): ");
  fgets(searchByTitle, MAX_CHAR_LENGTH, stdin);
  fflush(stdin);
  searchByTitle[strcspn(searchByTitle, "\n")] = 0;

  // ค้นหาด้วย author
  char searchByAuthor[60] = "";
  printf("Enter author name (leave blank to include all author names): ");
  fgets(searchByAuthor, MAX_CHAR_LENGTH, stdin);
  fflush(stdin);
  searchByAuthor[strcspn(searchByAuthor, "\n")] = 0;

  printf("\n");

  char *result_title; // ตัวแปรสำหรับเก็บผลลัพธ์ที่ผ่านการใช้ฟังก์ชัน strstr 
  char *result_author; // ตัวแปรสำหรับเก็บผลลัพธ์ที่ผ่านการใช้ฟังก์ชัน strstr 
  int indexSearched = -1; // กำหนดค่าเริ่มต้นเพื่อความสะดวกต่อการเช็คเงื่อนไข

  // กรณี 1 : ทั้ง title และ author เว้นว่าง (แสดงหนังสือทุกเล่ม)
  if (strlen(searchByTitle) == 0 && strlen(searchByAuthor) == 0) {
    bookListShow(list, borrowList);
  }

  // กรณี 2 : ระบุ title แต่ author เว้นว่าง
  else if (strlen(searchByTitle) != 0 && strlen(searchByAuthor) == 0) {
    // Loop เพื่อเช็คหาชื่อหนังสือที่ตรงกับคำค้นหา
    for (int index = 0; index < list->currentSize; index++) {
      result_title = strstr(getBookByIndex(list, index)->title, searchByTitle);
      // กรณี 2.1 : เจอคำค้นหาซ้ำเหมือนชื่อหนังสือ
      if (result_title != NULL) {
        indexSearched = index;
        bookShow_SpecificIndex(list, indexSearched); // แสดงผลหนังสือที่ค้นหาเจอ
      }
      // กรณี 2.2 : ไม่เจอคำซ้ำเหมือนชื่อหนังสือ
      else if (result_title == NULL && index == list->currentSize - 1 &&
               indexSearched == -1) {
        printf("Not Found\n");
      }
    }
  }

  // กรณี 3 : title เว้นว่าง แต่ระบุ author
  else if (strlen(searchByTitle) == 0 && strlen(searchByAuthor) != 0) {
    // Loop เพื่อเช็คหาชื่อผู้แต่งที่ตรงกับคำค้นหา
    for (int index = 0; index < list->currentSize; index++) {
      result_author = strstr(getBookByIndex(list, index)->author, searchByAuthor);
      // กรณี 3.1 : เจอคำค้นหาซ้ำเหมือนชื่อผู้แต่ง
      if (result_author != NULL) {
        indexSearched = index;
        bookShow_SpecificIndex(list, indexSearched); // แสดงผลหนังสือที่ค้นหาเจอ
      }
      // กรณี 3.2 : ไม่เจอคำซ้ำเหมือนชื่อผู้แต่ง
      else if (result_author == NULL && index == list->currentSize - 1 &&
               indexSearched == -1) {
        printf("Not Found\n");
      }
    }
  }

  // กรณี 4 : ระบุทั้ง title และ author
  else if (strlen(searchByTitle) != 0 && strlen(searchByAuthor) != 0) {
    // Loop เพื่อเช็คหาชื่อผู้แต่งที่ตรงกับคำค้นหา
    for (int index = 0; index < list->currentSize; index++) {
      result_title = strstr(getBookByIndex(list, index)->title, searchByTitle);
      result_author = strstr(getBookByIndex(list, index)->author, searchByAuthor);
      // กรณี 3.1 : เจอคำค้นหาซ้ำเหมือนชื่อผู้แต่ง
      if (result_title != NULL && result_author != NULL) {
        indexSearched = index;
        bookShow_SpecificIndex(list, indexSearched); // แสดงผลหนังสือที่ค้นหาเจอ
      }
      // กรณี 3.2 : ไม่เจอคำซ้ำเหมือนชื่อผู้แต่ง
      else if ((result_title == NULL || result_author == NULL) && index == list->currentSize - 1 && indexSearched == -1) {
        printf("Not Found\n");
      }
    }
  }

  printf("\n");
}

/* fan version:
BORROW *borrowCreateAuto(char title[60], int status, char list[100][60],
                         int count) {
  //  Create the BOOK structure automatically. This function must be used in
  //   conjunction with the BookCreateFromText function. 
  BORROW *b1 = (BORROW *)calloc(count, sizeof(BORROW));
  char temp_title[60];
  strcpy(temp_title, title);
  if (strlen(temp_title) > 60 || strlen(temp_title) < 1) {
    printf("Invalid title\n");
  }
  int temp_status = status;
  strcpy(b1->title, temp_title);
  b1->status = temp_status;
  memcpy(&b1->borrowHistory, list, count * 60 * sizeof(char));
  // b1->borrowHistory = list;
  b1->count = count;
  return b1;
}

LIST_T *borrowListCreateFromtxt(LIST_T *list, char *filepath) {
  // This function used to create BookList from .txt file

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
      tempBookHistoryNumber[round - 1] = count - 1;
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
    BORROW *temp_borrow =
        borrowCreateAuto(titleList[i], tempBookStatus[i], bookHistoryList[i],
                         tempBookHistoryNumber[i]);
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
    fprintf(textfile, "%s\n",
            &getBorrowByIndex(list, book_index)->borrowHistory[0][0]);
    // fprintf(textfile, "%s\n", getBorrowByIndex(list,
    // book_index)->borrowHistory[0][0]); fprintf(textfile, "%s\n",
    // getBookByIndex(list, book_index)->author); fprintf(textfile, "%d\n",
    // getBookByIndex(list, book_index)->year);
    if (book_index == list->currentSize - 1) {
      break;
    }
    fprintf(textfile, "\n");
  }

  fclose(textfile);
}

*/

// Ger version instead of using borrow struct, let's store our information in
// one place .
LIST_T *borrowListCreateFromtxt(LIST_T *list, char *filepath) {
  // This function used to create BookList from .txt file

  FILE *textfile;
  char line[MAX_LINE_LENGTH];
  char titleList[MAX_LINE_LENGTH][60];

  textfile = fopen(filepath, "r");
  if (textfile == NULL)
    printf("ERROR THE FILE CAN'T BE OPEN\n");

  int count = 0;
  int temp_history_length = 0;
  int round = 1;
  int indexSearched = 0;
  char *result_title;
  char tempHistory[MAX_LINE_LENGTH];
  int title_length = 0;
  int history_length[100];
  char optionHistoryList[MAX_LINE_LENGTH][100]
                        [60]; // เก็บเป็น array of string แล้วค่อยมา format

  int asd = 0;
  while (fgets(line, MAX_LINE_LENGTH, textfile)) {
    // printf("\n----- %d-------", asd++);
    line[strcspn(line, "\n")] = '\0'; //ลบตัว \n
    if (strlen(line)) {
      if (count == 0) {
        strcpy(titleList[round - 1], line);
        count++;
        title_length++;
      } else if (count > 0) {
        // printf("\n        here2");
        strcpy(optionHistoryList[round - 1][temp_history_length], line);
        temp_history_length++;
        count++;
      }
    } else if (!strlen(line)) {
      // printf("\nhere1");
      history_length[round - 1] = temp_history_length;
      round++;
      count = 0;
      temp_history_length = 0;
    }
  }
  // for (int i = 0; i < title_length; i++) {
  //   printf("\n history-len of index:%d = %d ", i, history_length[i]);
  //   for (int j = 0; j < history_length[i]; j++) {
  //     printf("\n %s", optionHistoryList[i][j]);
  //   }
  // }
  char temp_list_name[100][100][60];
  for (int round_index = 0; round_index < title_length; round_index++) {
    // Loop เพื่อเช็คหาชื่อหนังสือที่ตรงกับคำค้นหา
    LIST_T *option_list;
    for (int book_index = 0; book_index < list->currentSize; book_index++) {
      // กรณี 2.1 : เจอคำซ้ำเหมือนชื่อหนังสือ
      // printf("\n Compare: %d", strcmp(getBookByIndex(list, book_index)->title,
      //                                 titleList[round_index]));
      if (!strcmp(getBookByIndex(list, book_index)->title,
                  titleList[round_index])) {
        indexSearched = book_index; // index ของหนังสือที่อยู่ใน booklist
        for (int option_index = 0; option_index < history_length[round_index];
             option_index++) {

          int temp_option = 0;
          char temp_name[60] = "";
          sscanf(optionHistoryList[round_index][option_index], "%d: %[^\n]%*c",
                 &temp_option, temp_name);
          // printf("\n option: %d, name: %s", temp_option, temp_name);

          // char *toadd_name = (char *) calloc(60,sizeof(char));
          // strcpy(toadd_name, const char *restrict __src)
          int *toadd_option = (int *)calloc(1, sizeof(int));
          *toadd_option = temp_option;

          // char *toadd_name = (char*) calloc(60,sizeof(char));
          // toadd_name = temp_name;
          strcpy(temp_list_name[round_index][option_index], temp_name);

          listAppend(getNameListByIndex(list, indexSearched),
                     temp_list_name[round_index][option_index]);
          // printf(
          //     "\n ---- %s -----",
          //     listGetAt(getNameListByIndex(list, indexSearched), option_index));
          listAppend(getOptionListByIndex(list, indexSearched), toadd_option);
          continue;
        }
      }
    }
    // BOOK* temp_book = getBookByIndex(list, indexSearched);
    // temp_book->option = listCreate(1);
    // listAppend(temp_book->option->data, option_list);
  }
  //  for (int round_index = 0; round_index < title_length; round_index++){
  // for (int option_index = 0; option_index <
  // history_length[round_index];option_index++) { printf("\n ---- %s
  // -----",listGetAt(getBookByIndex(list, round_index)->name, option_index ));
  // }
  // }
  fclose(textfile);
  return list;
}

int getOptionValueByIndex(LIST_T* list,int book_index , int index_option){
        BOOK *book = getBookByIndex(list, book_index); // เข้าถึง book ใน book_index ที่ใส่เข้ามา
        int result = 0 ; // เก็บค่าผลลัพธ์ 
        if(book->option->currentSize == 0){ // ถ้าภายใน book ยังไม่มีการเก็บค่า option
                return -1; // return ค่าที่จะเอาออกไปบอกได้ว่ามันภายใน option ยังไม่มีการเก็บค่า ในที่นี้เลือกเป็น -1
        }
        result = *((int *)listGetAt(book->option, index_option)); // รับค่าของ option เก็บไว้ใน result
        return result;
}
char* getNameValueByIndex(LIST_T* list,int book_index , int index_option){
        BOOK *book = getBookByIndex(list, book_index); // เข้าถึง book ใน book_index ที่ใส่เข้ามา
         char *name = (char *)calloc(60, sizeof(char)); // เก็บค่าผลลัพธ์ 
        if(book->option->currentSize == 0){ // ถ้าภายใน book ยังไม่มีการเก็บค่า name
                return NULL; // return ค่าที่จะเอาออกไปบอกได้ว่ามันภายใน option ยังไม่มีการเก็บค่า ในที่นี้เลือกเป็น NULL
        }
        strcpy(name,listGetAt(book->name, index_option)); // copy ค่าใส่ผลลัพธ์
        return name;
}
void saveBorrowList(LIST_T *list, char *filepath) {
  FILE *textfile;
  textfile = fopen(filepath, "w");
  if (textfile == NULL)
    printf("ERROR THE FILE CAN'T BE OPEN\n");

  for (int book_index = 0; book_index < list->currentSize; book_index++) {
    // write booklist to output file
    fprintf(textfile, "%s\n", getBookByIndex(list, book_index)->title);
    if (getOptionListByIndex(list, book_index)) {
      for (int line_index = 0;
           line_index < getOptionListByIndex(list, book_index)->currentSize;
           line_index++) {
                fprintf(textfile, "%d: %s\n",getOptionValueByIndex(list, book_index,line_index), listGetAt(getBookByIndex(list, book_index)->name, line_index));
                
      }
    }
        if (book_index == list->currentSize - 1) {
      break;
                }       
    fprintf(textfile, "\n");
  }
 fprintf(textfile, "\n");
  fclose(textfile);
}

void borrowBook(LIST_T *list){
  // เก็บข้อมูลชื่อผู้ยืม
  char user_name[60] = "";
  printf("Enter borrower name: ");
  fgets(user_name, MAX_CHAR_LENGTH, stdin);
  fflush(stdin);
  user_name[strcspn(user_name, "\n")] = 0;

  // ค้นหาด้วย title
  char searchByTitle[60] = "";
  printf("Enter title to borrow: ");
  fgets(searchByTitle, MAX_CHAR_LENGTH, stdin);
  fflush(stdin);
  searchByTitle[strcspn(searchByTitle, "\n")] = 0;

  int indexSearched = 0 ;
  int result_title;
  int status;
  for (int index = 0; index < list->currentSize; index++) {
      BOOK *book = getBookByIndex(list, index);
      result_title = strcmp(book->title, searchByTitle); // เช็คว่ามีชื่อหนังสือที่เหมือนกับที่กรอกไหม
      status = getOptionValueByIndex(list,index,book->option->currentSize-1);
      // printf("compare to %s retult =  %d \n",book->title,result_title);
          
      // กรณี 2.1 : เจอคำค้นหาซ้ำเหมือนชื่อหนังสือ และสามารถยืมได้
      if (result_title == 0 && (status == 1 || status == -1) ) {
        indexSearched = index;
        int *toadd_option = (int *)calloc(1, sizeof(int));
        *toadd_option = 0;                
          listAppend(getNameListByIndex(list, indexSearched),user_name);
          listAppend(getOptionListByIndex(list, indexSearched), toadd_option);
          break;
      }
      else if(result_title == 0 && status == 0){
              printf("{ Sorry but this book has already borrowed. }\n");
              break;
      }
      // กรณี 2.2 : ไม่เจอคำซ้ำเหมือนชื่อหนังสือ
      else  {
        continue;
      }
    }
}

void returnBook(LIST_T *list){
  // เก็บข้อมูลชื่อผู้ยืม
  // ค้นหาด้วย title
  char searchByTitle[60] = "";
  printf("Enter title to return: ");
  fgets(searchByTitle, MAX_CHAR_LENGTH, stdin);
  fflush(stdin);
  searchByTitle[strcspn(searchByTitle, "\n")] = 0;

  int indexSearched = 0 ;
  int result_title;
  int status;
  char* returner ;

        
  for (int index = 0; index < list->currentSize; index++) {
      BOOK *book = getBookByIndex(list, index);
      result_title = strcmp(book->title, searchByTitle); // เช็คว่ามีชื่อหนังสือที่เหมือนกับที่กรอกไหม
      status = getOptionValueByIndex(list,index,book->option->currentSize-1);
      returner = getNameValueByIndex(list,index,book->option->currentSize-1);
      printf("compare to %s result =  %d \n",book->title,result_title);
          
      // กรณี 2.1 : เจอคำค้นหาซ้ำเหมือนชื่อหนังสือ และสามารถยืมได้
      if (result_title == 0 && status == 0 ) {
        indexSearched = index;
        int *toadd_option = (int *)calloc(1, sizeof(int));
        *toadd_option = 1;                
          listAppend(getNameListByIndex(list, indexSearched),returner);
          listAppend(getOptionListByIndex(list, indexSearched), toadd_option);
          printf("{ Success }\n");
          break;
      }
      else if(result_title == 0 && status == 1){
              printf("{ This book had already returned. }\n");
              break;
      }
      else if(result_title == 0 && status == -1){
              printf("{ There is no history of this book being borrowed. } \n");
              break;
      }
      // กรณี 2.2 : ไม่เจอคำซ้ำเหมือนชื่อหนังสือ
      else  {
        continue;
      }
    }
}