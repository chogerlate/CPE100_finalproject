# Library Management Program
## รายละเอียดเกี่ยวกับโปรเจค
คำอธิบายสั้นๆ: โปรเจคนี้เป็นส่วนหนึ่งในวิชา CPE100: Computer Programming for Engineers ภาคการศึกษาที่ 1 ปีการศึกษา 2022 โดยจะเป็นโปรเจคที่ให้เราพัฒนาโปรแกรมช่วนในการบริหารจัดการห้องสมุด 
โดยจะมีฟังก์ชั่นการทำงานหลัก ดังนี้
- สามารถเพิ่ม-ลบหนังสือในห้องสมุดได้
- สามารถแก้ไขรายละเอียดของหนังสือ (ชื่อหนังสือ, ชื่อผู้แต่ง, ปีที่พิมพ์) ได้
- สามารถค้นหาหนังสือจากชื่อหนังสือและ/หรือชื่อผู้แต่งได้
- มีระบบการยืม-คืนหนังสือ โดยไม่จํากัดจํานวนครั้งในการยืม-คืนของหนังสือแต่ละเล่ม
- จัดเก็บข้อมูลลงไฟล์โดยอัตโนมัติโดยเมื่อเปิด-ปิดโปรแกรมใหม่รายละเอียดหนังสือและรายการยืมคืนทั้งหมด
  จะต้องยังคงอยู่

### สมากชิกกลุ่ม:
1. นายชยพล วงศ์ภูวรักษ์ 65070501011
2. นายรุดฟาน ไมมะหาด 65070501049
3. นายศิวราช เหลาพรม 65070501052
4. นายดนัย แสงบัวหมัด 65070501076
---

## รายละเอียดของโปรแกรม

* ## main.c

* ## library.c
  * ### Function การเข้าถึงarrayของหนังสือ
    * Function 1:
    ```c
    int getOptionValueByIndex(LIST_T* list,int book_index ,int index);
    ```
    * Function 2:
    ```c
    char* getNameValueByIndex(LIST_T* list,int book_index , int index);
    ```
    * Function 3:
    ```c
    LIST_T* getOptionListByIndex(LIST_T*, int);    
    ```
    * Function 4:
    ```c
    LIST_T* getNameListByIndex(LIST_T*,int);
    ```
  * ### Function จัดการข้อมูลของหนังสือ
    ---
    * #### manually create book: 
      
      ฟังก์ชันนี้ใช้สร้างรายละเอียดของหนังสือตามข้อมูลในstructureด้วยตนเองก่อนที่จะเพิ่มลงในรายการหนังสือ
    ```c
    BOOK *bookCreate();
    ```
    
    * #### Generate Book from data that receive:
      ฟังก์ชันนี้ใช้สร้างรายละเอียดของหนังสือตามข้อมูลใน structure อัตโนมัติและจะต้องใช้ร่วมกัน       
      **bookCreateFromtxt**
    ```c
    BOOK *booKCreateAuto(char title[60], char author[60],char year[60]);
    ```
    
    * #### Generate BookList from .txt file:
      ฟังก์ชันนี้ใช้สร้าง BookList จากไฟล์ .txt
    ```c
    LIST_T *bookCreateFromtxt(LIST_T *list,char *filepath);

    ```
    * #### Show all the book in booklist:
      ฟังก์ชันนี้ใช้แสดงหนังสือที่อยู่ใน BookList 
    ```c
    void bookListShow(LIST_T *list,LIST_T *borrowList);
    ```
    
    * #### get access to book:
      ฟังก์ชันนี้ใช้เข้าถึงข้อมูลหนังสือผ่านทาง index
    ```c
    BOOK *getBookByIndex(LIST_T *list, int index);
    ```
    
    * #### remove book from booklist:
      ฟังก์ชันนี้ใช้ลบหนังสือจากBacklist จากชื่อหนังสือ
    ```c
    void bookListRemoveByTitle(LIST_T *list);
    ```
    
    * #### clear memory of book:
      ฟังก์ชันนี้ใช้เพื่อ free memory ของหนังสือ
    ```c
    void bookDestroy(BOOK *book);
    ```
    
    * #### free memory of booklist (including the books inside of it):
      ฟังก์ชันนี้ใช้เพื่อ free memory ของ booklist รวมไปถึงภายใน booklist ด้วย
    ```c
    void bookListDestroy(LIST_T *list);
    ```
    
    * #### save data for the next time:
      ฟังก์ชันนี้ใช้เพื่อบันทึกข้อมูลใน booklist
    ```c 
    void saveBookList(LIST_T *list, char *filepath);
    ```
    
    * #### Edit book:
      ฟังก์ชันนี้ใช้เพื่อแก้ไขข้อมูลหนังสือ
    ```c
    void bookEdit(LIST_T *list);
    ```
  * ### Function จัดการการยืมหนังสือ
    * Create borrow list from file txt:
      ฟังก์ชันนี้ใช้เพื่อ list การยืมหนังสือจากไฟล์ txt
    ```c
    LIST_T *borrowListCreateFromtxt(LIST_T *list, char *filepath);
    ```
    
    * create borrow list auto:
    ฟังก์ชันนี้ใช้เพื่อ list 
    ```c
    BORROW *borrowCreateAuto(char title[60], int status, char list[100][60]int count);
    ```
    
    * Save borrow list:
      ฟังก์ชันนี้ใช้เพื่อบันทึก list การยืมหนังสือ
    ```c
    void saveBorrowList(LIST_T *list, char *filepath);
    ```
    
    * Searching book:
      ฟังก์ชันนี้ใช้เพื่อค้นหาหนังสือ
    ```c
    void bookSearch(LIST_T *list, LIST_T *borrowList);
    ```
* ## library.h
  * Structure ข้อมูลของหนังสือ :
    ```c
    typedef struct {
      char title[60];
      char author[60];
      int year;
      int status; 
      LIST_T *name;
      LIST_T *option;
    }BOOK;
    ```
  * Structure ข้อมูลการยืมหนังสือ :
    ```c
    typedef struct {
      char title[60];
      int status;
      char borrowHistory[100][60];
      int count;
      LIST_T **name;
      LIST_T **option;
    } BORROW;
    ```
* ## ประเภทไฟล์ที่ใช้
  * Text File
    
* ## รูปแบบการจัดเก็บข้อมูลลงในไฟล์
  
  * ### borrow.txt

  * ### output.txt
    * ชื่อหนังสือ
    * ชื่อผู้เเต่ง
    * ปีที่ตีพิมพ์

* ## ข้อจํากัดของโปรแกรม
  * รองรับตัวอักษรได้สูงสุด 100 ตัวอักษร
  * รองรับข้อมูลภายในไฟล์ .txt ได้ 1000 บรรทัด

---