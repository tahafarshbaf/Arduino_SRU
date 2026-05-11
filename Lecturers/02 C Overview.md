# What’s left in your head from C?
The C programming language began its march to become formally defined by the American National 
Standard Institute (ANSI) with the formation of the X3J11 committee in 1983. The committee’s work was 
completed and the standard passed in 1989. Since then, the language is often referred to an “ANSI C”. The 
standard is also recognized by the International Organization for Standardization (ISO), too, so sometimes 
you will hear it referred to as “ISO C”. For all practical purposes, ANSI C and ISO C are the same. In a world 
that is overly hung up on political correctness, you will also hear both versions called “standard C.” 
The C you are about to learn is not standard C. Rather, you will be learning a robust subset of standard 
C. A few standard C features are missing. But the absence of those features is not a crippling blow by any 
means. You will soon discover that the subset version of standard C, which we will call Arduino C, is more 
than able to perform just about any task you can throw at it. The missing features can easily be worked 
around, albeit sometimes in a less elegant manner.

All programming languages, from Ada to ZPL, are built from four basic elements:

- [What’s left in your head from C?](#whats-left-in-your-head-from-c)
  - [Expressions](#expressions)
  - [Statements](#statements)
    - [Operator Precedence in C (Highest to Lowest)](#operator-precedence-in-c-highest-to-lowest)
  - [Statement Blocks](#statement-blocks)
  - [Function Blocks](#function-blocks)


The last element, function blocks, may be called different names in different languages, such as 
“methods” in C++, C#, and Java; “procedures” in Pascal; “subroutines” in Basic or Fortran; or perhaps 
some more exotic name in lesser-known languages. Regardless of their name, function blocks tend to be 
blocks of code designed to address some narrowly-defined task. Programs are little more than 
arrangements of these elements in a way that solves a problem.

## Expressions
An expression is created by combining *operands* and *operators*. Simply stated, an operand is typically a 
piece of data that is acted on by an operator. An operator is often a mathematical or logical action that is 
performed on one or more operands.

```
a + b
m - 300
a > j
```

In each of these expressions, there are two operands and one operator. That’s why you will often hear 
such expressions referred to as expressions that use a *binary operator*. Binary operators (e.g., +, –, and <) 
always use two operands. Another important thing to keep in mind is that any expression will ultimately 
resolve to a value. (There are also unary operators that have only one operand and ternary operators that 
require three operands.) However, the binary operators are the most common in C.

```
g < d
5 < 4
false
```

> [!NOTE]
> In programming languages, logic true and logic false expressions do resolve 
to a value. In most languages, logic true resolves to a non-zero value (e.g., –1), and logic false is zero. 
Relational expressions are designed to resolve to a logic true or false state, so they ultimately do resolve to 
a value that can be used in a program.

## Statements
A statement is a complete C instruction for the computer. All C statements end with a semicolon (;). The 
following are examples of C statements:
```
i = 50;
a = b + c;
m = d / 2;
```

In the first example, the equal sign `(=)` *is called the assignment operator* and is used to “assign” the 
value on the right side of the equal sign to the operand on the left side of the assignment operator.

> Whats is a variable?

### Operator Precedence in C (Highest to Lowest)

| Precedence | Operators                               | Description                                                                   | Associativity |
|------------|-----------------------------------------|-------------------------------------------------------------------------------|---------------|
| 1          | `()` `[]` `.` `->` `++` `--` (postfix) | Function call, array subscript, member access, post-increment/decrement       | Left to right |
| 2          | `++` `--` (prefix) `+` `-` `!` `~` `*` `&` `sizeof` `(type)` | Prefix inc/dec, unary plus/minus, logical NOT, bitwise NOT, dereference, address-of, sizeof, type cast | Right to left |
| 3          | `*` `/` `%`                             | Multiplication, division, modulo (remainder)                                  | Left to right |
| 4          | `+` `-`                                 | Addition, subtraction                                                         | Left to right |
| 5          | `<<` `>>`                               | Bitwise left shift, bitwise right shift                                       | Left to right |
| 6          | `<` `<=` `>` `>=`                       | Relational operators (less than, less than or equal, greater than, greater than or equal) | Left to right |
| 7          | `==` `!=`                               | Equality (equal to, not equal to)                                             | Left to right |
| 8          | `&`                                     | Bitwise AND                                                                   | Left to right |
| 9          | `^`                                     | Bitwise XOR (exclusive OR)                                                    | Left to right |
| 10         | `\|`                                    | Bitwise OR (inclusive OR)                                                     | Left to right |
| 11         | `&&`                                    | Logical AND                                                                   | Left to right |
| 12         | `\|\|`                                  | Logical OR                                                                    | Left to right |
| 13         | `?:`                                    | Ternary conditional operator                                                  | Right to left |
| 14         | `=` `+=` `-=` `*=` `/=` `%=` `&=` `^=` `\|=` `<<=` `>>=` | Assignment and compound assignment operators                                   | Right to left |
| 15         | `,`                                     | Comma operator                                                                | Left to right |



## Statement Blocks
A *statement block* consists of one or more statements grouped together so they are viewed by the compiler 
as though they are a single statement. For example, suppose you are an apartment manager, and if there is 
4 or more inches of snow on the ground, then you need to shovel the sidewalk. You might express this as 
(the >= operator is read as “greater than or equal to”):
```
if (snow >= 4) {
    PutOnSnowRemovalStuff();
    GetSnowShovel();
    ShovelSidewalk();
}
else {
    GoBackToBed();
}
```
Statement blocks start with an opening brace character { and end with a closing brace character }. All 
statements between the opening and closing braces form the *statement block body*. In our example, it 
appears that when 4 or more inches of snow exist, we will put on our coat, grab a snow shovel, and shovel 
the sidewalks. If there is less than 4 inches of snow, a different statement block is executed (i.e., we go back 
to bed).

## Function Blocks

A function block is a block of code that is designed to accomplish a single task. Although you may not be 
aware of it, you actually used a function block in the previous section. That is, PutOnSnowRemovalStuff() is 
a function that is designed to have you put on your coat. The actual code might look like:
```
void PutOnSnowRemovalStuff(void) {
    if (NotDressed) {
    PutOnClothes();
    PutOnShoes();
    }
    GoToCloset();
    PutOnBoots();
    PutOnCoat();
    PutOnGloves();
    PutOnHat();
}
```


In this example, the function block also starts with an opening brace { and ends with a closing braces 
}. However, function blocks are usually written to create “**black boxes**” in which the details of how we are 
doing something are buried in the function. You might be thinking of writing the code to control a robot 
that will require sensors to sense whatever lies ahead. You might write a `TurnRight()` function that turns 
your robot 90 degrees to the right. This probably involves turning one of the wheels, perhaps applying a 
greater voltage to a stepper motor to cause the front two wheels to turn to the right. However, perhaps at a 
later time you decide to change your robot from four wheels to three wheels. Now you don’t need to turn 
two wheels; only one needs to turn. By hiding the details of what has to be done to turn your robot to the 
right in the `TurnRight()` black box, you only need to change the program code in that one place, rather 
than in a whole bunch of places where a right turn might be needed. By writing a `TurnRight()`function, 
you can avoid duplicating all of the statements that are in the `TurnRight()` function each time a right turn 
is called for in the program.

