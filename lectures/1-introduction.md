
# Programming in C

## Curriculum

* [History](#history)
* [Where is C Used and by Whom?](#where-is-c-used-and-by-whom)
* [Platforms and Portability](#platforms-and-portability)
* [Syntax](#syntax)
* [Hello World](#hello-world)
* [Operators](#operators)
* [Fundamental Data Types](#fundamental-data-types)
* [Identifiers](#identifiers)
* [Variables](#variables)
* [Functions](#functions)
* [Formatted Output](#formatted-output)
* [Scope and Modularity](#scope-and-modularity)
* [The Preprocessor](#the-preprocessor)
* [Documentation](#documentation)
* [Standard Libraries](#standard-libraries)
* [A Double Precision Postfix Calculator](#a-double-precision-postfix-calculator)
* [Appendix: Specific Width Integers](#appendix-specific-width-integers)
  
## History

C was developed by Dennis Ritchie between 1969 and 1973 at AT&T Bell Labs.  The origin of C is closely tied to the development of the Unix operating system, originally implemented in assembly language on a PDP-7 by Ritchie and Thompson, incorporating several ideas from colleagues. Eventually they decided to port the operating system to a PDP-11. B (the predecessor language of C) was unable to take advantage of some of the PDP-11's features, notably byte addressability, led to the development of an early version of C.  As its popularity began to increase significantly during the late 1970s and 1980s, versions of C were implemented for a wide variety of mainframe computers, minicomputers, and microcomputers, including the IBM PC.

In 1983, the American National Standards Institute (ANSI) formed a committee, to establish a standard specification of C. They based the C standard on the Unix implementation; however, the non-portable portion of the Unix C library was handed off to an IEEE working group to become the basis for the 1988 POSIX standard. In 1989, the C standard was ratified and this version of the language is often referred to as ANSI C, Standard C, or sometimes C89.  In 1990, the ANSI C standard (with formatting changes) was adopted by the International Organization for Standardization (ISO), which is sometimes called C90. Therefore, the terms "C89" and "C90" refer to the same programming language.

The C standard was further revised in 1999, which is commonly referred to as "C99". C99 introduced several new features, including inline functions, several new data types (including long long int and a complex type to represent complex numbers), variable-length arrays, improved support for floating point numbers, support for variadic macros (macros of variable arity), and support for one-line comments beginning with //, as in C++. Many of these had already been implemented as extensions in several C compilers.

In 2007, work began on another revision of the C standard, informally called "C1X" until its official publication on 2011-12-08. The C standards committee adopted guidelines to limit the adoption of new features that had not been tested by existing implementations.  The C11 standard adds numerous new features to C and the library, including type generic macros, anonymous structures, improved Unicode support, atomic operations, multi-threading, and bounds-checked functions. It also makes some portions of the existing C99 library optional, and improves compatibility with C++.

C has been around for a long, long time and it continues to be used daily for many different kinds of systems.  Given that most major operating systems are still written exclusively or primarily in C mean that it will continue to be with with us for generations.  It is far from a perfect language, but it provides everything needed to write any kind of program. C compilers are some of the most important programs in existence and hosting one on a platform is still considered to be the minimum necessary for a viable computing system. 

## Where is C Used and by Whom?

Programs:

* The compilers, interpreters and/or runtimes for: C, Python, Ruby, Java, D, PHP, Perl, etc.
* git
* The Linux kernel
* Most operating systems (BSD, Windows, Mac OS)
* Most Unix programs
* The firmware that runs in every bit of electronics around you

Famous Programmers:

* K&R, obviously
* Richard Stallman
* Linus Torvalds
* Guido van Rossum
* Yukihiro Matsumoto

## Platforms and Portability

Unlike some other modern languages that try to provide a consistent of the platform to the programmer, C directly exposes the capabilities (or lack thereof) of the host and operating system.  Therefore, there are are some important considerations that are not applicable to other languages.  Some of these are:

* Compiler Standard Compliance - What version of the C standard does the compiler implement?  How complete, strict and tested is the conformance?
* CPU Native Word Size - what is the bit width of a word? 16bit? 32bit? 64bit?
* CPU Endianess - Is it big-endian? little-endian? (or very rarely, bi-endian?)
* OS Library Support - Is POSIX supported? Which version? What extensions? Is the UNIX API supported? Which version? Are there bugs?

For simple programs that target Unix-like systems (Mac OS or Linux), most of these will not be problematic.  However, medium to large programs that must run on various flavors of Unix (Mac OS, Linux, FreeBSD, OpenBSD, Solaris, etc.) or even Windows, target multiple CPUs (Intel x86, AMD64, ARM, SPARC, PowerPC, etc.) or support various compilers (GCC, GCC-LLVM, Clang, SunC, etc) portability is a major concern.  Given this is a common issue, programmers can make use of "feature macros" and C's (in)famous preprocessor to tailor their source code to individual OS/CPU/compiler combinations at build time.  This is actually quite a large topic, and beyond the scope of this document.  Suffice it to say that if you write a C program of any reasonable size and wish to share it with people, you *will* be considering portability in your build.

## Syntax

It's pretty much what you're used to if you've written some code in any other modern language:

* Comments are delimited by `/* */` or from `//` to the end of the line
* Expressions are delimited by a semicolon:

```c
frobnicate();
int a = 1;
```
* A semicolon by itself is meaningless, but legal
* Blocks are enclosed by curly braces `{ }` and contain zero or more statements (any syntax)

```c
{
    int answer = 42;
}
```
* Declaration of variables is required before use and can occur anywhere, but:
* Variables are lexically (block) scoped
* Almost no whitespace is required anywhere, but please use a lot of it!
* Standard crop of flow control: `if`/`else if`/`else`/`for`/`while`/`do while`/`switch`/`break`/`continue`/`goto`
* The `for` loop is *not* a foreach construct, but takes the form: `for(<initialize expression>; <conditional expression>; <increment expression>)`
* Functions must be uniquely named - there is no overloading or redefinition

## Hello world

The original "hello, world" program comes from the the first book on C: "The C Programming Language" by Brian Kernighan and Dennis Ritchie.  In that grand tradition, here is your first program:

```c
#include <stdio.h>
 
int main()
{
    printf("hello, world\n");
    
    return 0;
}
```

Type this into a text file named `hello.c` and the compile it using:

    cc -o hello hello.c

If you typed it in correctly the compiler will produce no output and there will be a new executable file `hello` in the current directory.  Run it:

    ./hello
    
... and feel the magic.  You're now a C programmer, congratulations!  You can now take a personal position on the One True Way To Place Braces.

## Operators

* Assignment: =, +=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=
* Equality: ==, !=
* Relational: <, <=, >, >=
* Arithmetic: +, -, *, /, %
* Boolean logic: &&, ||, !
* Conditional: ?:
* Incremental: ++, --
* Referential: &, *, [ ], ., ->
* Bitwise: ~, &, |, ^, >>, <<
* Size: sizeof
* Expression grouping: ()
* Sequencing: ,
* Type coercion: (*type*)

If you prefer more friendly names than some of the above symbols, you can use the header file `iso646.h` to make these definitions available:

| Symbol  | Operator |
| ------  | :------: |
| and     |    &&    |
| or      |    &#124;&#124;  |
| not     |    !     |
| bitand  |    &     |
| bitor   |    &#124;    |
| xor     |    ^     |
| compl   |    ~     |
| and\_eq |    &=    |
| or\_eq  |    &#124;=   |
| xor\_eq |    ^=    |
| not\_eq |    !=    |

However, don't do this.  Why not?  Because nobody else is, and it will be confusing for everyone who is using the standard symbols.  You'll be much better off if you just learn and use the standard syntax.

### Operator Magic

Although C doesn't allow you to create your own operators or change the meaning of existing ones, it has a rich set of them built-in.  Most of them should be familiar from other languages that have borrowed them over the years, but there are a few worth noting in particular.

**Compound Assignment**

In addition to the `=` character meaning assignment, you can also combine an assignment with another operation.

Consider this example:

```c
int foo = 5;
foo += 6;
```

The second line is equivalent to `foo = foo + 6;` in a much more compact form.  You will notice in the above list, that you can use compound assignment with any of the arithmetic or bitwise operators (except bitwise not - it is a unary operator).

**Conditional Operator**

There is a special operator that acts as a compact form of an if/else statement that has a value, the conditional operator: `?:`.  In C statements (like `if`, `for`) don't have a value and can't appear on the right-hand side of an assignment, they are only control flow. So, this operator provides a shortcut to conditionalize values.  It is also unusual in that it is the only ternary operator (taking three arguments) in the language.

Consider this example (`%` is the modulo operator):

```c
int foo = 4;
int bar = foo % 2 ? function1(foo) : function2(foo);
```

Which is equivalent to:

```c
int foo = 4;
int bar;

if(foo % 2)
{
    bar = function1(foo);
}
else
{
    bar = function2(foo);
}
```

**Increment and Decrement Operators**

Incrementing and decrementing integers and other related types is such a common operation that there are special operators just for that: `++` and `--` respectively.  They may seem very ordinary, but they have a neat trick they can do: they can appear before or after the value the modify.

Consider this example:

```c
int foo = 5;
frobnicate(foo++);
```

compared with this small change:

```c
int foo = 5;
frobnicate(++foo);
```

In the first example, the value that is seen by the body of the `frobnicate` function would be 5.  The `++` operator appears *after* the value it it is modifying, so it takes effect **after** the value is used.  In this case, the "use" of the value is to be passed to the function `frobnicate`.  On the next line after the function call, the value of `foo` will be 6.  The second example has the opposite behavior to the first.  The function will see a value of 6, since the operator appearing *before* the value means that it is incremented **before** it is used.  The decrement operator has the same semantics regarding its positioning, just the opposite effect to the increment operator.  The distinction in meaning based on the position of the operator is subtle, but also very powerful.  Be sure to carefully consider how you're using these operators in practice.

**sizeof Operator**

The usage of the `sizeof` operator actually looks just like it is a function, but don't let that fool you!  Its purpose is to provide a portable way to query the size in bytes of any type or variable at runtime.

To find out the size in bytes of an integer type, you could write:

```c
printf("size of an int: %zd\n", sizeof(int));
```

The normal use case for this operator is when dealing with memory allocation.  We'll cover that in detail in a future lesson.

### Operator Precedence

The syntax of C is infix, like most other languages, and this means a precedence of the operators or "order of operations" is required.  This allows the compiler to know in what order to apply all of the operators so the syntax is unambiguous.  The following table lists this precedence:

| Operator     | Grouping |
| ------------ | -------- |
| () [] -> .   | left to right |
| ! ~ ++ -- + - (type) * & sizeof |  right to left |
| * / %        | left to right |
| + -          | left to right |
| << >>        | left to right |
| < <= > >=    | left to right |
| == !=        | left to right |
| &            | left to right |
| ^            | left to right |
| &#124;       | left to right |
| &&           | left to right |
| &#124;&#124; | left to right |
| ?:           | right to left |
| = += -= *= /= %= &= ^= &#124;= <<= >>= | right to left |
| ,            |  left to right |

The precedence of the arithmetic operators uses the common mathematical model as you can see.  Operators that have the same precedence are applied according to their grouping, which is usually left to right, but not always.  You can wrap parenthesis around any expression to ensure that it evaluated how you intend.

One important caveat to watch out for is that there is no guarantee of the order that the operands themselves will be evaluated!

Consider this example:

```c
foo() + bar();
```

The programmer has no way of knowing which of these two function calls will happen first.  Keep this in mind, and make sure that functions with side-effects do not get used where the order of invocation is unknown.  Better yet, avoid side effects in your functions.

## Fundamental Data Types

### Integers

**Available Types**

| type            | width |
| --------------- | :---: |
| bool            | 1     |
| char            | 8     |
| short (int)     | 16    |
| int             | 16    |
| long (int)      | 32    |
| long long (int) | 64    |

All of the above types except `bool` are available by default, but since `bool` was added in C99 you must include the header `stdbool.h` to use it.  The `bool` type supports the literals `true` and `false`.  The other types support literals specified in decimal (`128`), octal (`0200`) or hexidecimal (`0x80`).

Any of the above (except `bool`) can be prefixed with `signed` or `unsigned` to declare the signedness, with `signed` being the default.  A signed integer reserves the least significant bit for the value of the sign, thus halving the maximum possible value.

The widths above are the *common* values, and the actual may differ between platforms (no guarantees are made).  See the Appendix for more available integer types.

**Literal Values**

An optional suffix can be added to any integer literal to indicate its type.  No suffix indicates an `int`.  The following integer literal suffixes are supported:

| suffix                | type               |
| --------------------- | ------------------ |
| u / U                 | unsigned int       |
| l / L                 | long               |
| ul / uL / Ul / UL     | unsigned long      |
| ll /Ll / lL / LL      | long long          |
| ull / uLl / ulL / ULL | unsigned long long |

The `char` type also accepts literals bracketed by single quotes: `'z'`.  The glyph inside the single quotes can be any printable (i.e. something on your keyboard) ASCII character, or any one of these escape sequences:

| sequence | meaning             |
| -------- | ------------------- |
| `\a`     | alert               |
| `\b`     | bell                |
| `\f`     | form feed           |
| `\n`     | newline             |
| `\r`     | return              |
| `\t`     | tab                 |
| `\v`     | vertical tab        |
| `\'`     | single quote        |
| `\"`     | double quote        |
| `\?`     | question mark       |
| `\\`     | solidus             |
| `\ooo`   | an octal value      |
| `\xhh`   | a hexidecimal value |

The integer value of all character literals and escape sequences (except the hexidecimal and octal ones) will be the ASCII decimal value for that character.

**Type Promotion**

Integer types can be assigned and passed to functions from smaller width values to larger width values, this is called "type promotion".  The type promotion hierarchy is generally this:

    char -> unsigned char -> int -> unsigned int -> long -> unsigned long -> long long -> unsigned long long -> float -> double -> long double

Anywhere a larger width type is expected, a smaller type can be given and that value will be automatically promoted to the appropriate type.  This behavior is seen in most other programming languages, so it should not come as a surprise.

**Type Conversion**

Automatic conversion between signedness of types is also supported, but be careful!  An unsigned value that is too large to be represented by a signed value of the same bit-width will cause some unexpected results from the sign flipping.

Consider this program:

```c
#include <stdio.h>
#include <stdint.h>

int main()
{
    uint8_t value1 = 129;
    printf("unsigned value: %u\n", value1);
    int8_t value2 = value1;
    printf("signed value: %i\n", value2);
    return 0;
}
```

When run, it will output this:

    unsigned value: 129
    signed value: -127

Most compilers offer optional warnings to let you know when you're making a conversion from unsigned to signed, since you probably don't really want this.  

**Overflow**

Since integers in C are simply fixed bit width values, the behavior of overflowing a value is not elegant.  A word-size integer will not be transformed into a bignum to preserve your value, nor will any error be signaled, the value will simply wrap around to 0.

Consider this program:

```c
#include <stdio.h>
#include <stdint.h>

int main()
{
    uint32_t value = UINT32_MAX;
    printf("value: %u\n", value);
    value += 1;
    printf("value: %u\n", value);
    return 0;
}
```

When run, it will output this (on most 32-bit platforms):

    value: 4294967295
    value: 0

This hopefully demonstrates the importance of carefully considering the limits of the values that will be represented by integer variables in your program.

### Real Numbers

| type        | width    |
| ----------- | :------: |
| float       | 24 + 8   |
| double      | 53 + 11  |
| long double | 113 + 15 |

The above widths are the precision + exponent.

Real number literals are expressed in the format:

    [sign]<integer part>[.<fractional part>][(e|E)[sign]<exponent part>][suffix]
    
This is the same format for literals accepted by most other modern programming languages, except for the suffix.  The suffix can be `f` or `F` to indicate a float type literal and `l` or `L` to indicated a long double type literal.  No suffix indicates a double literal.

There are feature macros defined in the header file `float.h` to portably query the limits and precision of real numbers:

X can be `FLT`, `DBL` or `LDBL`

| macro        | purpose                          |
| ------------ | -------------------------------- |
| X\_RADIX     | Base of the exponential notation |
| X\_MANT\_DIG | Number of digits of the mantissa |
| X\_MAX\_EXP  | Maximum value of the exponent    |
| X\_MIN\_EXP  | Minimum value of the exponent    |

To use one of these, simply include the macro word (e.g. `DBL_RADIX` for the numeric base of the radix of the `double` type) anywhere you could use literal number.

### Complex Numbers

Complex numbers are represented by the types `float complex`, `double complex` and `long double complex` and are provided by the header `complex.h`.  The real and imaginary parts of a complex number both have the given type `float`, `double` or `long double`.  A discussion of using complex numbers is beyond the scope of this document, but some Internet searching can turn up some useful articles.

You can make a complex number from a literal like this:

```c
double complex x = 5.0 + 6.0 * I;
```

The real part is `5.0` and the imaginary part is `6.0`.

Complex numbers also support arithmetic using the built-in operators, and there are complex number specific versions of the standard exponential, trigonometric and hyperbolic functions available in the header file `complex.h`.

### Arrays

C does not provide any built-in containers, but there are complex types: structures, enumerations and arrays.  An array is not in any way a dynamic type, it is merely a contiguous block of memory divided into cells of the same size.  While the cells of any array can be accessed and changed at any time, the length of an array cannot be changed once it has been declared. Arrays can be made from any type, so are they very flexible.

For example, here is an array of 10 integers:

```c
int array[10];
```

This array has been declared statically, and will live (and be visible) in whatever scope the above declaration appeared in.  The initial value of each cell of the array is not guaranteed and could be anything, so be careful!  C uses the common square bracket syntax to access array elements, and the index value is 0-oriented:

```c
int fifth = array[4];
```

C99 introduced variable-length arrays, so a literal is not always required when declaring an array.  Consider this function:

```c
int process(int n)
{
    int values[n];
    
    for(int i = 0; i < n; i++)
    {
        values[i] = get_value();
    }

    return process(values, n);
}
```

An array of integers of length `n` is declared for each invocation of the function, and that array is given to another function after being filled with values.  Arrays can be initialized from literals using this syntax:

```c
int values[3] = {1, 2, 3};
```

The length of the array is optional for arrays initialized in this way, and if not given then then the length of the array is specified by the number of literals given.  If the length of the array is longer than the number of literals provided, the rest of the array's cells will not be initialized.  It is an error to provide too many literals in the initialization block.  The usual rules for type promotion and conversion also apply here.  

### Strings

C doesn't actually have a built-in type for string, but by convention they are represented by arrays of `char` with a terminating null byte (`'\0'`).  There are a number string handling functions provided in the standard library, and they all expect their string parameters to follow this convention.  String literals are wrapped in double quotes and support the same escape sequences as given above for the `char` type:

    char name[] = "Alice";

The variable name now points to an array of `char` that is 6 cells long: 5 for the given literal characters and 1 for the terminating null byte.  You can create your own non-literal arrays of `char` like we created arrays of `int` above, but be careful about placing the null byte correctly if you will pass that array to any other function.  

Consider this program:

```c
#include <stdio.h>

int main(void)
{
    char value[5];
    value[] = {'f', 'o', 'o'};
    value[4] = '\\0';
}
```

There is one uninitialized cell in the 3rd position, so if you pass this to a function like `printf` the result could be anything.

C also supports "wide" characters, which can be used to represent multi-byte character encodings such as Unicode's UTF-16, or Shift-JIS.  The type of one of these characters is `wchar_t` provided by the header `stdlib.h`.  A wide string is an array of `wchar_t` terminated by the wide null byte: `L'\0'`.  These sorts of encoding concerns are a very complicated issue, and supporting them correctly requires the use of a mature third-party library.

Given that C predates both Unicode and most all multi-byte encodings, UTF-8 is a very attractive encoding to use since it is backwards compatible with ASCII and Latin-1.  A UTF-8 encoded string could be represented as an array of `uint8_t` with or without a terminating null byte.  In addition, any common ASCII encoded `char` array is also UTF-8 encoded.  The C11 standard added support for UTF-8 encoded literals using the syntax: `u8"ようこそ"` but this doesn't seem to be support yet by either GCC or Clang.

### Void

The `void` keyword has two meanings in C: it is used for functions that either return no value or take no parameters (or both), and to represent the universal type for pointers.  The keyword by itself cannot be used for variable declarations or for type coercion.  We will discuss the second meaning in a future lesson, and its meaning for functions will be discussed shortly.

## Identifiers

Identifiers (names of variables, functions, macros, etc) are case sensitive and are have certain rules:

* The first character *cannot* be a number
* The legal characters are: underscore, digits, and the upper and lower case alphabet

## Variables

You've already seen various examples of declaring variables above.  In C, all variables **must** be declared before they can be used and the declarations take this form:

    [<storage class>] [<qualifier>] <type> <identifier> [= <initializer>] [, <identifier>  [= <initializer>] ]*;

This "meta-syntax" notation works like this: square brackets surround optional things, angle brackets indicate required values, the asterisk means "zero or more" in the regular expression sense, and the common and equal signs are literal C syntax that must appear.

So, you can read this as: optional storage class, optional qualifier, required type, required identifier with an optional initializer, followed by more comma separated optional identifiers each with its own optional initializer with a required semicolon at the end.

Every variable has a "storage class", which can be specified or implied.

| Specifier | Lifetime | Scope     | Default initializer |
| --------- | -------- | --------- | ------------------- |
| auto      | Block    | Block     | None                |
| register  | Block    | Block     | None                |
| static    | Program  | Enclosing | Zero                |
| extern    | Program  | Enclosing | Zero                |

If a specifier is not given, which is the case for most variables, auto is assumed.  Thus, it is never necessary to specify auto, it exists for backwards compatibility with ancient codebases. The `register` specifier is a hint asking to compiler to store the value of the variable in a CPU register if possible, but no guarantees are made.  

Specifying `static` inside a function or any block (block scope) means the value is preserved between invocations (dangerous and not thread-safe!).  Outside a function (compilation unit scope, i.e. "within a source file") it means that the variable will be automatically initialized (to zero unless otherwise specified) at program start time and be visible for the lifetime of the program.

The `extern` specifier indicates that the declaration of the variable occurs somewhere else, either outside that block or in another compilation unit (i.e. source file).  The `auto` and `register` specifiers cannot be used with declarations at the compilation unit scope (i.e. in the source file but outside any function).

To summarize storage class: `auto` and `register` are almost never used, `static` is useful for file-level declarations and `extern` will be seen from time-to-time but is probably a code smell indicating something that should be in a header file.

Finally, there are two type qualifiers: `const` and `volatile`.  Not specifying a qualifier means that the variable is a normal mutable one.  The first qualifier indicates that the value will not change after it is initialized for the lifetime of the enclosing scope.  The second indicates that the value of the variable may change at any time, even though no assignment was made by the program.  This may happen if a program has multiple threads sharing variables.  The type qualifiers are mutually exclusive.

Here is an example of using both `static` and `const` together to declare a constant:

```c
static const char COPYRIGHT[] = "Copyright (c) 1984 Yoyodyne Propulsion Systems";
```

Something like this would typically be put at the top of a file.

C allows you to declare multiple variables of the same type simultaneously.  This can be handy to save space, but can make it hard to find where a variable is declared so use sparingly.  Any declaration can also include an optional initializer, and you've also already seen examples of initializers above.  Obviously, the type of the initializer must be compatible with the type of the variable.

## Functions

Just like variables, all functions **must** be declared before they are used (except the entry point function `main`).

A function declaration looks like this:

    [<qualifier>] <return-type> <identifier>( [ <type> <identifier> ] [ , <type> <identifier> ]* );

A function definition looks like this:

    [<qualifier>] <return-type> <identifier>([ <type> <identifier> ] [ , <type> <identifier> ]* )
    {
        <statements>
        return [<expression of type return-type>];
    }

You can read the function signature as:  optional qualifier, required type, required identifier, followed by parenthesis surrounding and optional comma-separated list of type identifier pairs. There is a semicolon at the end of the declaration, but the definition is followed by a block.

Why is there a difference between declaration and definition?  Because that's just how it is.  The real answer is that it makes things easier for the compiler: it doesn't have to make multiple passes over the source it's compiling to ensure that everything has the proper signatures.

The <qualifier> can be any one of: `extern`, `static` or `inline`.  The `extern` qualifier indicates that the definition lives in another compilation unit.  Like `auto`, it is applied by default so usually redundant when dealing with function declarations and header files.  However, it can serve as a signal that a function declaration that doesn't live in a header file needs to be used, but is defined elsewhere.  This is probably a code smell for something that should be in a header file though.  Functions can also take the `static` specifier, which means that the function will not be available outside its compilation unit.  Finally, the `inline` specifier is a hint to the compiler to try to replace calls to that function with the literal body of the function.  No guarantees are made that this will happen though.

The <return-type> can be any primitive type, a user defined type or `void` (meaning nothing is returned).  Multiple returns values are not supported (directly).

The parameter list can be empty, but if any are specified they must be typed and the compiler will enforce the type of all of the arguments.  There is no support for default parameter values or keyword parameters.  You are allowed to leave some parameters unspecified so a function can take a variable number of arguments, but there is a special syntax for this which we will cover in a future lesson.

The body of the function can contain any kind of statements.  If a return value was specified (i.e. not `void`) the the function **must** specify enough `return` statements (with a value of the correct type) to cover all of the exit points.  There is no default return value.  Functions with `void` return type do not need to use the `return` statement, but can use one to force an explicit (e.g. early) return.  However, the proper use is: `return;`, **not** `return void;`.

### Main

The hello world example above shows a real function definition for the standard entry point `main`.  All programs must define this function somewhere, and it can one of several forms:

```c
int main(void)
int main()

int main(int argc, char **argv)
int main(int argc, char *argv[])
```

The first two indicate that the program doesn't care about processing arguments from the command line, and the second two indicate the program does want these arguments.  The first two and the second two are equivalent, which you choose depends on if you need to use command line arguments or not, and which style of syntax for arrays of strings you prefer.  It is possible to have a void return type but your compiler will complain about that.  Since `main` is special, you cannot have a declaration for it anywhere and you also cannot specify any qualifiers.

The minimum acceptable C program looks like this:

```c
int main(void)
{
}
```

Most compilers will issue a warning about not having a `return` statement, but will insert one for you and compile the program anyway.

### Call by Value

Functions are invoked with copies of values that are specified at the call site, this is known as "call-by-value".  Because of this, changes to the value of a parameter inside a function does not effect the original value given to the function.

Consider this program:

```c
void foo(int value);

void foo(int value)
{
    value = 5;
}

int main()
{
    int x = 0;
    foo(x);
}
```

After the function `foo` is called, the value of the variable `x` is *still* zero.  C works this way because (again) it's easier for the compiler, but it has the added benefit that some careless mistakes cannot hurt your program.  If you want to give a mutable value to a function, there is a special way to do this.

Consider this change to the above program:

```c
void foo(int *value);

void foo(int *value)
{
    *value = 5;
}

int main()
{
    int x = 0;
    foo(&x);
}
```

Now, after the function `foo` is called the value of `x` will be 5.  The asterisk in the function parameter `value` indicates that it will be a reference (pointer) to a value instead of the value itself.  The use of the asterisk in the expression `*value = 5;` means: "set the value referred to by this parameter".  If you had written that expression without the asterisk, it would have changed the place referred to by your function parameter and _maybe_ crashed your program.  Finally, to make sure we pass a mutable value to our function, we use the ampersand in the `main` function like this: `foo(&x);`.  This means: "pass a reference to this variable, instead of its value".

## Formatted Output

You've already seen the library function `printf` used above to write output.  This and other very useful functions are provided by the header `stdio.h`.  Almost every program will make use of these functions somewhere.  When a program is started, three files are automatically opened: standard in, standard out, and standard error.  The `stdio.h` header also defines constants you can use to refer to these: `stdin`, `stdout` and `stderr`, respectively.  There are a huge number of I/O functions available in the standard library and elsewhere, so let's talk about two very useful ones to start with.

### printf

The `printf` function is the workhorse of standard formatted output in C, and its format string convention has been copied by almost every other language in existence.  It writes only to the standard output console.  It has this signature:

```c
int printf(char * format, ...);
```

The ellipsis is legal syntax that means this function can take a variable number of arguments.  In the case of `printf` it is at least one with no upper bound.  The characters in the format string are interpreted to determine how many arguments have been given, and how what types they are.

### fprintf

The `fprintf` function work exactly like `printf` but it allows you to specify the file to write to as the first argument.  It has this signature:

```c
int printf(FILE *file, char * format, ...);
```

Unless you are writing to a file you have opened yourself, the most common value for the first argument of `fprintf` is `stderr`: for error messages to the user.

### Format String

The format string can contain any characters legal in a string, and placeholders beginning with a `%` will be replaced with the value of a given argument according to special syntax in the form:

    %[parameter][flags][width][.precision][length]type

Any other character not part of a placeholder will be copied directly to the output.  The syntax of the format string is very rich, so this will only be a summary of the type conversions available.  [Wikipedia](https://en.wikipedia.org/wiki/Printf) has a good description of the complete syntax.  The following characters are supported for the `type` component:

| character | meaning |
| --------- | ------- |
| d, i      | int as a signed decimal number. '%d' and '%i' are synonymous for output, but are different when used with scanf() for input (using %i will interpret a number as hexadecimal if it's preceded by 0x, and octal if it's preceded by 0.) |
| u         | Print decimal unsigned int. |
| f, F      | double in normal (fixed-point) notation. 'f' and 'F' only differs in how the strings for an infinite number or NaN are printed ('inf', 'infinity' and 'nan' for 'f', 'INF', 'INFINITY' and 'NAN' for 'F'). |
| e, E      | double value in standard form ([-]d.ddd e[+/-]ddd). An E conversion uses the letter E (rather than e) to introduce the exponent. The exponent always contains at least two digits; if the value is zero, the exponent is 00. |
| g, G      | double in either normal or exponential notation, whichever is more appropriate for its magnitude. 'g' uses lower-case letters, 'G' uses upper-case letters. This type differs slightly from fixed-point notation in that insignificant zeroes to the right of the decimal point are not included. Also, the decimal point is not included on whole numbers. |
| x, X      | unsigned int as a hexadecimal number. 'x' uses lower-case letters and 'X' uses upper-case. |
| o	        | unsigned int in octal. |
| s	        | null-terminated string. |
| c	        | char (character). |
| p	        | void * (pointer to void) in an implementation-defined format. |
| n	        | Print nothing, but write number of characters successfully written so far into an integer pointer parameter. |
| %	        | a literal '%' character (this type doesn't accept any flags, width, precision or length). |

It is a best practice to always use a string literal for your format strings.  Because of the `%n` conversion, arbitrary data can be written to memory through a call to the `printf` family.  See [this article](https://en.wikipedia.org/wiki/Format_string_attack) for a more in-depth discussion.

## Scope and Modularity

C is an imperative language without any high-level organization features such as modules, packages or classes.  Because of this, it is easy to write monolithic code that is poorly organized and difficult to maintain.  However, a program can be made of any number of source files, and they can act as de facto modules to organize your code.  Header files allow you to create interfaces for your modules and hide implementation details from other parts of the program or system.

### Header Files

Header files are a convention that allows declarations and definitions to be separated to encourage modular design.  Many header files have already been mentioned, and you've seen their usage above with the `#include` directive.  Whenever this directive is encountered, the entire contents of the referenced file are inserted verbatim into the current source file at that location.  There are two ways of referring to files in this directive: using angle brackets or double quotes.

For example:

```c
#include <stdio.h>
```

means to search for the file named `stdio.h` in the system paths: typically `/usr/include` and `/usr/local/include` on Unix.

Alternately:

```c
#include "foo.h"
```

means to look in the current directory followed by any other paths specified to the compiler (such as `<project dir>/src/include`).

All `#include` directives from the just inserted file will be recursively expanded until no more are found.  As you might expect, dumping an entire file into the current one is a very simplistic approach.  Since there is no dependency tracking among these header files, there is a real danger of including the same file multiple times.  To solve this an "include guard" is used, of which there are two flavors: placing `#pragma once` at the top of all of your header files, or wrapping the entire contents of the header file in a preprocessor conditional (these conditionals will be covered later).  The first option is far more simple and easier to read.

An example header file:

```c
/*
 * Copyright (c) 1984 Yoyodyne Propulsion Systems
 */

#pragma once

int frobnicate();

```

## The Preprocessor

The C preprocessor is a macro system that is part of all compilers and is responsible for handling directives staring with a hash mark (such as `#include`).  It does not support a full language on its own but only a few simple commands.

The preprocessor directives available are:

* `#include` - insert referenced file here
* `#define` - define a new macro name or function-like macro
* `#undef` - discard the definition of a macro name or function-like macro
* `#if`, `#elif`, `#else`, `#endif` - conditional compilation based on expressions
* `#ifdef`, `#ifndef` - conditional compilation based on definition of other macros
* `#error` - signal an error to the compiler process

The usage of `#include` was discussed in the previous section and a complete treatment of macros and conditionals will be given in a future lesson.  The next section has a brief overview of macros.

### Macro Overview

To create a macro that will replace every instance of the macro identifier with some value, you can write:

```c
#define PI 3.1415926
```

The macro name can be any legal identifier, and the replacement value can be anything at all.  It is conventional to write the names of macros in upper-case to distinguish them from variables.  Now all occurrences of `PI` (when used like an identifier) which be replaced by `3.1415926`:

```c
double pi = PI;
```

For most cases it is probably better to use a constant expression instead.

A function-like macro looks a bit like a function in that it has parameters, but they are not typed.  In fact, since the are handled by the preprocessor the compiler doesn't ever see the definitions of macros, only their expansions.  Just like functions the macro parameters are optional, but their names must be declared in the macro if the are to be used.

Here is an example function-like macro and its usage:

```c
#define ENSURE_NONZERO(v) if((v) == 0)              \
    {                                               \
        fprintf(stderr, "error: value is zero!\n"); \
        return -1;                                  \
    }

int do_that_thing(int value)
{
    ENSURE_NONZERO(value);

    // do some work
    
    return 0;
}
```

This would expand to:

```c
int do_that_thing(int value)
{
    if((value) == 0){fprintf(stderr, "error: value is zero!\n");return -1;};

    // do some work
    
    return 0;
}
```

These type of macros are useful for abstracting some bit of code that needs to be used repeatedly but aren't suitable for extracting into a function.

This macro takes one parameter: `v`.  The names of macro parameters must be legal identifiers, just as the name of the macro.  Macros must appear all on one line, so the newlines in the above example are escaped.  When using a macro parameter in the macro body, it is good practice to wrap it in parenthesis.  This is because the argument passed to a macro could be an expression, instead of a literal or a variable name.  Unlike a real function call where the expression would be evaluated and its value passed, the literal text of the expression is passed to the macro.  If the macro parameter is then used without the parenthesis, illegal syntax could be created.

For example:

```c
int do_all_the_things(int value[])
{
    int a;
    ENSURE_NONZERO(a = value[0]);

    // do some work
    
    return 0;
}
```

This would expand to:

```c
int do_all_the_things(int value[])
{
    if((a = value[0]) == 0){fprintf(stderr, "error: value is zero!\n");return -1;};

    // do some work
    
    return 0;
}
```

Without the parenthesis around the `v` macro parameter, the expansion above would have a syntax error.

## Documentation

The long history of C has done wonders for its documentation: it's almost universally available.  Anywhere you have man pages, you have the documentation for all the functions in the C standard library in section 3.  Try running `man 3 printf` in your terminal!  

## Standard Libraries

Compilers for C and operating systems provide implementations of the C standard library functions, as specified in the ISO and ANSI standard documents.  All of these functions are available from various header files, divided according to functionality.  Some of the commonly used headers are:

### ISO/ANSI Standard

| header       | functionality |
| -------------| ------------- |
| ctype.h      | classify characters by their types or convert characters |
| errno.h      | testing error codes reported by library functions |
| inttypes.h   | exact width integer types |
| math.h       | mathematical functions |
| stdbool.h    | boolean data type |
| stdint.h     | exact width integer types |
| stdio.h      | core input and output |
| stdlib.h     | numeric conversion, pseudo-random numbers generation, memory allocation, process control |
| string.h     | string handling |
| time.h       | date and time handling |
| stdarg.h     | varying number of arguments to functions |

[Wikipedia](https://en.wikipedia.org/wiki/C_standard_library) has an exhaustive list of all available header files and the functions in each one.

### POSIX Standard

The POSIX standard defines a super-set of the C Standard Library, adding additional functionality such as threads, IPC, message queues, etc.  Again [Wikipedia](https://en.wikipedia.org/wiki/C_POSIX_library) has the goods on this.

## A Double Precision Postfix Calculator

Now let's write some code!  We're going to make a command-line double precision postfix calculator using what we've learned so far.  This will be an interactive program to evaluate postfix arithmetic expressions.  So instead of writing:

    >> (2 + 3) * (10 / 2)

you would write:

    >> 2 3 + 10 2 / *

for the same result.

The program will be interactive, providing a prompt for you to type postfix expressions into.  Each number entered will be accumulated in an internal stack, and the operators (`+`, `-`, `/`, `*`) will pop two values off of that stack, apply the operation and push the result back on the stack.  There are two stack commands supported: `p` will "peek" at the top of the stack and print that value, and `P` will "pop" (i.e. remove) the top value of the stack and print it.  Variables will be supported in "registers" named by lower-case alphabetic characters.  The store command `s` will pop a value off of the stack and put it into a register.  The load command `l` will copy the value from a register and push it onto the stack.  Both of these commands must be followed by the letter of the register to use, like this: `sa` will store into the "a" register, and `lb` will load from the "b" register.

To quit the program, you type control-d.

### Getting Started

Follow the directions in this [chapter's exercise README](../exercises/introduction/README.md).

On your own machine run these commands to start a batteries-included shell:

    $ cd `/path/to/c-programming/exercises/introduction`
    $ docker run -it -v `pwd`:/projects/introduction -w /projects/introduction gcc:latest bash
    # make

There should now be a executable program file in the current directory called `calc`.  You can try it out by running:

    ./calc

It doesn't do much right now, but we'll fix that.  We're going to implement these functions in [`calc.c`](../exercises/introduction/calc.c):

* `push`
* `pop`
* `drop`

## Appendix: Specific Width Integers

To demand an integer type of a specific width, there are special cross-platform types that you can use these types the header file `stdint.h`:

N can be `8`, `16`, `32` or `64`

| signed           | unsigned        |
| ---------------- | --------------- |
| intN\_t          | uintN\_t        |
| int\_leastN\_t   | uint\_leastN\_t |
| int\_fastN\_t    | uint\_fastN\_t  |

To portably determine the maximum and minimum possible values for integers of a specific width, you can use these feature macros also from `stdint.h`:

N can be `8`, `16`, `32` or `64`

| type                | maximum value        | minimum value    |
| ------------------- | -------------------- | ---------------- |
| intN\_t             | INTN\_MAX            | INTN\_MIN        |
| int\_leastN\_t      | INT\_LEASTN\_MAX     | INT\_LEASTN\_MIN |
| int\_fastN\_t       | INT\_FASTN\_MAX      | INT\_FASTN\_MIN  |
| uintN\_t            | UINTN\_MAX           | 0 |
| uint\_leastN\_t     | UINT\_LEASTN\_MAX    | 0 |
| uint\_fastN\_t      | UINT\_FASTN\_MAX     | 0 |
