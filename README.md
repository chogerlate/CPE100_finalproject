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
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras quis nisl leo. Pellentesque in ultricies lacus. Sed posuere risus eget odio imperdiet, nec lobortis sem eleifend. Integer venenatis nunc nunc, eu pretium purus pellentesque et. Nullam sapien elit, dignissim in odio eget, ornare suscipit purus. Proin porttitor tempus velit, eget porttitor erat scelerisque sit amet. Sed sodales et est sed ultrices. Integer non varius eros. Duis sit amet purus et lectus rutrum ornare vitae et felis. Nam orci nulla, imperdiet ac felis ac, volutpat ultrices sapien. Duis nec ultrices dui. Etiam non maximus magna. Ut mattis ornare elementum.



### main.c


---
### arraylist.c 


---
### arraylist.h


---
### library.c
##### function 1:

```c
LIST_T* listCreate(int initialCapacity) { 
    LIST_T* list = (LIST_T*) calloc(1, sizeof(LIST_T));
    list->data = (void**) calloc(initialCapacity, sizeof(void*));
    list->currentSize = 0;
    list->maxSize = initialCapacity;
    return list;
}        
```
คำอธิบาย

        ค่ารับเข้ามา:
        ค่าส่งออก:
        การทำงานเบื้องต้น:
        ข้อจำกัด:

---

### library.h


---
### borrow.txt



---
### output.txt



---
