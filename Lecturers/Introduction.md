# Hands on Arduino!
hi and welcome to tihs course.


| Type           | Byte length | Range of values                                              |
|----------------|-------------|--------------------------------------------------------------|
| boolean        | 1           | Limited to logic true and false                              |
| char           | 1           | Range: -128 to +127                                          |
| unsigned char  | 1           | Range: 0 to 255                                              |
| byte           | 1           | Range: 0 to 255                                              |
| int            | 2           | Range: -32,768 to 32,767                                     |
| unsigned int   | 2           | Range: 0 to 65,535                                           |
| word           | 2           | Range: 0 to 65,535                                           |
| long           | 4           | Range: -2,147,483,648 to 2,147,483,647                       |
| unsigned long  | 4           | Range: 0 to 4,294,967,295                                    |
| float          | 4           | Range: -3.4028235E+38 to 3.4028235E+38                       |
| double         | 4           | Range: -3.4028235E+38 to 4.0000000E+38                       |
| string         | ?           | A null ('\0') terminated reference type data build from a character array |
| String         | ?           | A reference data type object                                 |
| array          | ?           | A sequence of a value type that is referenced by a single variable name |



```cpp
void setup() {
  Serial.begin(9600);
}
```




همان‌طور که در <a href="#tabla-datos">جدول ۳-۱</a> نشان داده شده است...

<figure id="fig-architecture">
  <img src="diagram.png" alt="Diagrama">
  <figcaption><strong>شکل ۱:</strong> نمودار بلوکی سیستم</figcaption>
</figure>

واقعیت در [شکل ۱](#fig-architecture) قابل مشاهده است.
