#ifndef LIBRARY_H
#define LIBRARY_H
#include "arraylist.h"

typedef struct { // เก็บข้อมูลทุกอย่างของ Book
  char title[60]; // ชื่อหนังสือ
  char author[60]; // ชื่อผู้แต่ง
  int year; // ปีที่ผลิต
  int status;  // สถานะการยืม-คืน
  LIST_T *name; // List รายชื่อผู้ยืม-คืน
  LIST_T *option; // List รายการยืม-คืน แทนค่า 0 = ได้ทำการยืม, 1 = ได้ทำการคืน
}BOOK;

//function สำหรับเพื่อให้ง่ายในการปริ้น 
void printline(); // ปริ้นตัวคั้นบรรทัด
void printBookTable(LIST_T* list); // ปริ้นตารางหนังสือภายในห้องสมุด
void bookListShow(LIST_T *list); // ปริ้นข้อมูลรายละเอียดของหนังสือทุกเล่มในห้อมสมุด

// function ช่วยในการดึงค่าจาก booklist
int getOptionValueByIndex(LIST_T* list,int book_index ,int index); //ดึงค่าภายในอาเรย์ตำแหน่งที่index จาก Option ที่อยู๋ในหนังสือที่ book_index 
char* getNameValueByIndex(LIST_T* list,int book_index , int index);//ดึงค่าภายในอาเรย์ตำแหน่งที่index จาก Name ที่อยู๋ในหนังสือที่ book_index 
LIST_T* getOptionListByIndex(LIST_T* list, int index); // ดึง List of Option จาก List ของหนังสือลำดับที่ index จาก list
LIST_T* getNameListByIndex(LIST_T* list,int index); // ดึง List of Name ของหนังสือลำดับที่ index จาก list
BOOK *getBookByIndex(LIST_T *list, int index); // ดึง BOOK Struct จาก List ตำแหน่งที่ index

// function ใช่ในการอ่านค่าจากไฟล์เซฟ
BOOK *booKCreateAuto(char title[60], char author[60],
                     char year[60]); // สร้าง BOOK struct จากค่าที่ส่งมาจาก function bookCreateFromtxt
LIST_T *bookCreateFromtxt(LIST_T *list,
                          char *filepath); // อ่านค่าและสร้าง list ของหนังสือจากไฟล์ 

// function ในการเซฟข้อมูลไฟล์
void saveBookList(LIST_T *list, char *filepath); // เขียนข้อมูลหนังสือ เซฟไว้ใน filepath ที่กำหนด
void saveBorrowList(LIST_T *list, char *filepath); // เขียนข้อมูลการยืม-คืน เซฟไว้ใน filepath ที่กำหนด


// function การทำงานหลักภายในโปรแกรม
BOOK *bookCreate(); // สร้างหนังสือจากข้อมูที่ผู้ใช้กรอก
void bookListRemoveByTitle(LIST_T *list);  // ลบหนังสือจากชื่อหนังสือที่ผู้ใช้กรอก
void bookEdit(LIST_T *list); // แก้ไขข้อมูลหนังสือ 
void bookSearch(LIST_T *list); // ค้นหาข้อมูลหนังสือ 
void borrowBook(LIST_T* list); // ยืมหนังสือ
void returnBook(LIST_T* list); // คืนหนังสือ

// function ตัวช่วยเหลือของ function หลัก
void bookDestroy(BOOK *book);    // ล้างข้อมูลของ book จาก memory
void bookListDestroy( 
    LIST_T *list); //ล้างข้อมูลของ list จาก memory






// สิ่งต่างๆที่ไม่ได้ใช้แล้ว
/*

typedef struct { // ไม่ได้ใช้
  char title[60];
  int status;
  char borrowHistory[100][60];
  int count;
  LIST_T **name;
  LIST_T **option;
} BORROW; 

LIST_T *borrowListCreateFromtxt(LIST_T *list, char *filepath);
BORROW *borrowCreateAuto(char title[60], int status, char list[100][60],
                         int count);
*/
#endif