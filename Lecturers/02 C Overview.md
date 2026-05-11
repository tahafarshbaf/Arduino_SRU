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
1. Expressions[](#expressions)
2. Statements
3. Statement Blocks
4. Function Blocks

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