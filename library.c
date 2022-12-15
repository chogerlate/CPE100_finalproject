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

void bookListShow(LIST_T *list) {
  // show books in booklist
  printf("[There are %d books in this library]\n\n", list->currentSize);
  for (int index = 0; index < list->currentSize; index++) {
    printf("Title: %s\n", getBookByIndex(list, index)->title);
    printf("Author Name: %s\n", getBookByIndex(list, index)->author);
    printf("Publish Year: %d\n", getBookByIndex(list, index)->year);
    if (getBookByIndex(list, index)->name != NULL) {
      // printf("Status: %s\n", );
      printf("Borrowing History:\n");

    } else {
      printf("Status: Available\n");
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
  int selectedIndex;
  int stoploop = 0;
  // วน Loop เพื่อเช็คหาชื่อหนังสือที่ต้องการแก้ไข
  while (stoploop != 1) {
    char selectedTitle[60] = "";
    printf("Enter title to edit: ");
    fgets(selectedTitle, MAX_CHAR_LENGTH, stdin);
    fflush(stdin);
    selectedTitle[strcspn(selectedTitle, "\n")] = 0;
    char book_title[60] = "";
    int cmp;
    for (int index = 0; index < list->currentSize; index++) {
      strcpy(book_title, getBookByIndex(list, index)->title);
      cmp = strcmp(selectedTitle, book_title);
      if (cmp == 0) {
        selectedIndex = index;
        stoploop = 1; // ออกจากลูปใน
        break;
      } else if (index == list->currentSize - 1) {
        printf("Title not found\n");
      }
    }
  }
  // edit detail of the book
  BOOK *editedBook = (BOOK *)calloc(1, sizeof(BOOK));
  while (1) { // title
    char temp_title[60] = "";
    printf("New title (leave blank to retain old value): ");
    fgets(temp_title, sizeof(temp_title), stdin);
    temp_title[strlen(temp_title) - 1] = 0; // remove /0 in first index
    if (strlen(temp_title) == 0) {
      strcpy(editedBook->title, getBookByIndex(list, selectedIndex)->title);
      break;
    } else if (strlen(temp_title) > 60) {
      printf("Invalid title\n");
      continue;
    } else if (strlen(temp_title) > 0 && strlen(temp_title) < 60) {
      strcpy(editedBook->title, temp_title);
      break;
    }
  }

  while (1) { // author name
    char temp_author[60] = "";
    printf("New author name (leave blank to retain old value): ");
    scanf("%s", temp_author);
    if (temp_author[0] == '\n') {
      break;
    } else if (strlen(temp_author) > 60) {
      printf("Invalid author name\n");
      continue;
    } else if (strlen(temp_author) > 0 && strlen(temp_author) < 60) {
      strcpy(editedBook->author, temp_author);
      break;
    }
  }
  while (1) { // year name
    char temp_year[60] = "";
    printf("Enter publish year: ");
    scanf("%s", temp_year);
    if (strlen(temp_year) < 1) {
      break;
    } else if (strlen(temp_year) > 4) {
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
    editedBook->year = atoi(temp_year);
    break;
  }
  // pass edited value to the book
  list->data[selectedIndex] = editedBook;
}

void bookSearch(LIST_T *list) {
  // searching with title
  char searchByTitle[60] = "";
  printf("Enter title (leave blank to include all titles):");
  fgets(searchByTitle, MAX_CHAR_LENGTH, stdin);
  fflush(stdin);
  searchByTitle[strcspn(searchByTitle, "\n")] = 0;
  // printf("Text:%s\nlen:%d\n", searchByTitle, strlen(searchByTitle));
  int length_searchByTitle = strlen(searchByTitle);

  // searching with author
  char searchByAuthor[60] = "";
  printf("Enter author name (leave blank to include all author names):");
  fgets(searchByAuthor, MAX_CHAR_LENGTH, stdin);
  fflush(stdin);
  searchByAuthor[strcspn(searchByAuthor, "\n")] = 0;
  // printf("Text:%s\nlen:%d\n", searchByAuthor, strlen(searchByAuthor));
  int length_searchByAuthor = strlen(searchByAuthor);
        
  char book_title[60] = "";
  char book_author[60] = "";
  int length_title, length_author;
  int cmp_title, cmp_author;
  for (int index = 0; index < list->currentSize; index++) {
    strcpy(book_title, getBookByIndex(list, index)->title);
    strcpy(book_author, getBookByIndex(list, index)->author);
    length_title = strlen(book_title);
    length_author = strlen(book_author);
    cmp_title = strcmp(searchByTitle, book_title);
    cmp_author = strcmp(searchByAuthor, book_author);
    // check compared value
    // printf("Cmp_title:%s value:%d\n", book_title, cmp_title);
    // printf("Cmp_author:%s value:%d\n", book_author, cmp_author);

    if ((cmp_title == 0 && length_searchByAuthor == 0) ||
        (length_searchByTitle == 0 && cmp_author) ||
        (cmp_author == 0 && cmp_title == 0)) {
      printf("Title: %s\n", getBookByIndex(list, index)->title);
      printf("Author Name: %s\n", getBookByIndex(list, index)->author);
      printf("Publish Year: %d\n", getBookByIndex(list, index)->year);
      break;
    } else {
      if (index == list->currentSize - 1) {
        printf("Not Found!");
      } else {
        continue;
      }
    }
  }
}
