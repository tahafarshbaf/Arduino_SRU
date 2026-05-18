
**Table of Content**
1. [[#Variable Names in C]]
2. [[#Decision Making]]
3. 
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





## Variable Names in C
There are three general
rules for naming variables or functions in C: Valid variable names may contain:
1. Characters a through z and A through Z
2. The underscore character (_)
3. Digit characters 0 through 9, provided they are not used as the first character in
the name.
Just about everything else is not acceptable, including C keywords. That also means that punctuation,
and other special non-printing characters are not allowed either. Valid variable names might include:
```
jane Jane ohm ampere volt
money day1 Week50 _system XfXf
```
Using the same rules, the following would not be valid names:
```
^carat 4July -negative @URL
%percent not-Good This&That what?
```

Given these limits, how does one create a “good” variable name? As a general rule, I like variable
names that are long enough to give me a clue as to what they do in a program but short enough that I don’t
get tired of typing their name. Another convention a lot of programmers used is a variant of what’s called
camel notation. Using this notation, variable names begin with a lowercase letter with each subword
capitalized. Examples using this style might be:
```
myFriend togglePrinter reloadEmptyPaperTray closeDriveDoor
```

> [!warning]
> Keep in mind that C is case sensitive, which means that `myData` and `MyData` are two different
variables.



## Decision Making 
As you might guess, a decision is often based on comparing the state of two or more pieces of data. You 
make such decisions all the time, probably without thinking much about the process that is involved in 
making the decision. The phone rings and you get up to answer it. Implicitly, you make a decision whether 
to answer the call or not. Further, that decision involved comparing the expected benefits from answering 
the call (e.g., it might be someone you want to talk with) versus the expected costs of not answering the 
call (i.e., I may miss out on talking to someone important). Some decisions are better than others. Indeed, 
the definition of a dilemma is when you have two or more choices and they are all bad.

All of the operators in the 
table are binary operators and require two operands. 


| Operator | Interpretation           |
| -------- | ------------------------ |
| >        | Greater than             |
| >=       | Greater than or equal to |
| <        | Less than                |
| <=       | Less than or equal to    |
| ==       | Equal to                 |
| !=       | Not equal to             |


>[!NOTE]
> The result of all relational operations is either logic true (non-zero) or logic false (zero).
> ```
>5 > 4 // Logic true
>5 < 4 // logic false
>5 == 4 // logic false
>5 != 4 // logic true
>```

### The if Statement
In a computer program, unless the central processing unit (CPU) is told to do otherwise, the CPU 
processes the source code program instructions in a linear, top-to-bottom manner. That is, program 
execution starts at whatever is designated as the starting point for the program and plows through the 
source code from that point to the next statement until all of the statements have been processed.

he syntax for an if statement is:
``` C
if (expression1 is logic true) {
  // execute this if statement block if true
}
// statements following the if statement block
```
Example:
```C
int b = 10;
// some more program statement...
if (b < 20) {
  b = doSomethingNeat();
}
doSomethingElse(b);
```

![if Statement](<Images/if-statement.jpg>)

If the if statement block consists of a single program statement, then the braces defining the 
statement block may be omitted.

> [!CAUTION]
> We used a single equal sign for the relational expression rather than the proper "is equal to" operator (`==`). This means the code performs an assignment statement, not a relational test.

### The if-else Statement
 provides another form of the simple if statement called the if-else statement. The syntax for the if-else statement is:
```C
if (expression evaluates to logic true) {
  // perform this statement block if logic true
} else {
  // perform this statement block otherwise
}
```

> Just because you have a program working doesn’t mean it is the most efficient way to 
write the code.


> [!TIP]
> There are two flavors for the increment/decrement operator:
> - **Pre-increment** (`++counter`): The value of the variable is fetched, incremented, and then used in the expression.
> - **Post-increment** (`counter++`): The value of the variable is fetched and used in the expression, and then incremented afterward.
>
> Notice that `++` appears **before** the variable name for pre-increment, and **after** the variable name for post-increment.


### The switch Statement

```C
switch (expression1) { // opening brace for switch statement block
	case 1:
		 // statements to execute when expression1 is 1
		break;
	case 2:
		 // statements to execute when expression1 is 2
		break;
	case 3:
		 // statements to execute when expression1 is 3
		break;
	// more case statements as needed
	default:
		// statements to execute if expression1 doesn't have a "case value"
	break;
} // close brace for switch statement block
// This is the next statement after the switch
```

The expression1 must evaluate to an integral data type. That is, expression1 could be a byte, char, int, or long (including their unsigned counterparts)—it cannot be a floating point type (float or double) nor can it be a reference data type (e.g., string or String). Although Arduino C also accepts a Boolean data type for expression1, that seems suspect to me, and I wouldn’t suggest using it. After all, a Boolean is either true or false, so an if-else statement block would work.


> [!NOTE]
> If you forget the break statement for a given case, then program execution falls through to the next case statement. This can be a potential source of errors in your programs. However, there are also times when two case values may need to execute the same program statements.





All programming languages, from Ada to ZPL, are built from four basic elements:











The last element, function blocks, may be called different names in different languages, such as 
“methods” in C++, C#, and Java; “procedures” in Pascal; “subroutines” in Basic or Fortran; or perhaps 
some more exotic name in lesser-known languages. Regardless of their name, function blocks tend to be 
blocks of code designed to address some narrowly-defined task. Programs are little more than 
arrangements of these elements in a way that solves a problem.

## Expressions
An expression is created by combining *operands* and *operators*. Simply stated, an operand is typically a 
piece of data that is acted on by an operator. An operator is often a mathematical or logical action that is 
performed on one or more operands.

``` C
a + b
m - 300
a > j
```

In each of these expressions, there are two operands and one operator. That’s why you will often hear 
such expressions referred to as expressions that use a *binary operator*. Binary operators (e.g., +, –, and <) 
always use two operands. Another important thing to keep in mind is that any expression will ultimately 
resolve to a value. (There are also unary operators that have only one operand and ternary operators that 
require three operands.) However, the binary operators are the most common in C.

``` C
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
``` C
i = 50;
a = b + c;
m = d / 2;
```

In the first example, the equal sign `(=)` *is called the assignment operator* and is used to “assign” the 
value on the right side of the equal sign to the operand on the left side of the assignment operator.

> Whats is a variable?

### Operator Precedence in C (Highest to Lowest)

| Precedence | Operators                                                    | Description                                                                                            | Associativity |
| ---------- | ------------------------------------------------------------ | ------------------------------------------------------------------------------------------------------ | ------------- |
| 1          | `()` `[]` `.` `->` `++` `--` (postfix)                       | Function call, array subscript, member access, post-increment/decrement                                | Left to right |
| 2          | `++` `--` (prefix) `+` `-` `!` `~` `*` `&` `sizeof` `(type)` | Prefix inc/dec, unary plus/minus, logical NOT, bitwise NOT, dereference, address-of, sizeof, type cast | Right to left |
| 3          | `*` `/` `%`                                                  | Multiplication, division, modulo (remainder)                                                           | Left to right |
| 4          | `+` `-`                                                      | Addition, subtraction                                                                                  | Left to right |
| 5          | `<<` `>>`                                                    | Bitwise left shift, bitwise right shift                                                                | Left to right |
| 6          | `<` `<=` `>` `>=`                                            | Relational operators (less than, less than or equal, greater than, greater than or equal)              | Left to right |
| 7          | `==` `!=`                                                    | Equality (equal to, not equal to)                                                                      | Left to right |
| 8          | `&`                                                          | Bitwise AND                                                                                            | Left to right |
| 9          | `^`                                                          | Bitwise XOR (exclusive OR)                                                                             | Left to right |
| 10         | `\|`                                                         | Bitwise OR (inclusive OR)                                                                              | Left to right |
| 11         | `&&`                                                         | Logical AND                                                                                            | Left to right |
| 12         | `\|\|`                                                       | Logical OR                                                                                             | Left to right |
| 13         | `?:`                                                         | Ternary conditional operator                                                                           | Right to left |
| 14         | `=` `+=` `-=` `*=` `/=` `%=` `&=` `^=` `\|=` `<<=` `>>=`     | Assignment and compound assignment operators                                                           | Right to left |
| 15         | `,`                                                          | Comma operator                                                                                         | Left to right |



## Statement Blocks
A *statement block* consists of one or more statements grouped together so they are viewed by the compiler 
as though they are a single statement. For example, suppose you are an apartment manager, and if there is 
4 or more inches of snow on the ground, then you need to shovel the sidewalk. You might express this as 
(the >= operator is read as “greater than or equal to”):
``` C
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
``` C++
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


## The Five Program Steps
Every program you can think of can be reduced to five basic program elements, or steps. When you first
start to design a program, you should think of that program in terms of the following Five Program Steps.

1. Initialization step
2. Input step
3. Process step
4. Output step
5. Terminate step

An *algorithm* is nothing more than a formal statement of how a
given set of inputs are manipulated to produce a desired result. An algorithm is like a recipe or a set of
blueprints: They describe what you need to do to reach a desired goal or endpoint. And so it is with
programming: The Five Program Steps can be used to formulate a plan for solving a give programming
problem. Although algorithms are more closely tied to Steps 2 and 3 (i.e., Input and Processing), the Five
Program Steps should help you formulate an algorithm to solve whatever task is at hand.[[Beginning C for Arduino](Refrences.md#purdum-beginning-c)].


## Comments
Comments should be used any time you wish to
document what a program is doing or about to do. Reading code isn’t always easy and it might be hard for
the reader to figure out what’s going on in a particular section of code. In such cases, a comment may
make it easier for someone to decipher what the code is supposed to do. For example, if you have a black
box function that implements some really scary mathematical equation, then you might add a comment
to explain what is going on. If the function is really complex, then it is not uncommon to put a multiline
reference comment into the code that has a book and page number (or perhaps an Internet URL address)
where the reader can go for further information.
At first blush, it may seem that comments are directed to someone other than the person who actually
wrote the code. Frequently, that is true, especially if you write code in a commercial environment with
other programmers who may have to work with your code. However, even if you are the only person who
will ever see the code, you would be amazed how a piece of code that was so easy to understand this
morning may as well be written in Sanskrit six months from now. Comments should be used to help the
person reading the code—whomever that may be.
So, the question still remains: When do you add comments to a program? Too few comments often
makes the code difficult to understand. There are simply not enough comments to be helpful to your
understanding of the code. However, too many comments can have the same effect because they “get in
the way” of understanding the code. Comments are clutter if they don’t contribute any real benefit to
understanding the code.

### Single-Line Comments
Single-line comments begin with a pair of slash `(//)` characters. There can be no spaces between the two
slashes. (Otherwise the compiler might think it was looking at the division operator.) Upon seeing the two
slash characters, the compiler knows that what follows from the two slashes to the end of the current line is
a program comment and does not need to be compiled. As such, comments that begin with `//` must
appear on the same line as the two slash characters. If you fold a comment to the next line without the
leading slashes, then it will be seen as a syntax error by the compiler.
Again, an example of this type of comment is:
``` C++
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
```

### Multiline Comments
Multiline comments begin with a slash-asterisk pair `(/*) and end with an asterisk-slash pair (*/)`. There are
no spaces between the two characters pairs. Everything in between these two character pairs is treated as a
comment and is ignored by the compiler. Unlike single line comments, multiline comments can span
multiple lines. You can see an example of a multiline comment at the top of Listing 2-1.
Note that you could write the multi-line comment at the top of Listing 2-1 as:
``` C++
 /* Blink
  Turns on an LED on for 1 second, then off for 1 second, repeatedly.
 /* This example code is in the public domain.
 ```
and the program would behave exactly the same. However, multiline comments are useful for long
comments that span multiple lines because they take fewer keystrokes to implement. The compiler could
care less which you use. The important thing to remember is that comments invoke no penalty in terms of
memory space or the performance of the program, so there is no reason not to use them as needed.

There are no hard-and-fast rules for commenting the program source code. My preference is to put a
multiline comment before most function blocks or any line (or lines) of code that does something unusual
or “tricky.” For example,
``` C
x = y / 2.0;
x = y * .5; // Divide the number in half
```
Either statement produces the same result for floating point numbers. However, the second form is
slightly faster because division is the slowest math operation you can use. The comment simply jogs the
reader’s mind as to what is being done. (Normally you would not do this anyway. It would only be
noticeable if the calculation was being done thousands of times in a big program loop.)

> [!CAUTION]
> **Performance Optimization for Arduino (Multiplication vs. Division)**
>
> **Method 1: Shift Bits for Powers of 2**
> - **Slow:** `int y = x / 4;`
> - **Fast:** `int y = x / 4;`
> - **Fast Pro Max:** `int y = x >> 2;`  (3-4x faster)
> - **Note:** Only use for division/multiplication by 2, 4, 8, 16, 32... (powers of 2)
> - **Warning:** Be careful with negative numbers!
>
> **Method 2: Use Constants at Compile Time**
> - **Slow:** `float y = x / 3.0;`
> - **Fast:** `const float factor = 1.0 / 3.0;` then `float y = x * factor;`
> - **Why:** The division happens once at compile time, not repeatedly at runtime
>
> **Method 3: Avoid Floating Point Operations**
> - **Slow:** `float result = (sensorValue * 3.14) / 2.73;`
> - **Fast:** `int result = (sensorValue * 314) / 273;` (no decimals!)
> - **Why** Integer math is 5-10x faster than floating point on Arduino
> - **Remember:** Multiplication (*) is always faster than division (/) - replace `/` with `*` whenever possible



