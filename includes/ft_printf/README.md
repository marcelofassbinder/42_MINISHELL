<h1 align=center>
  42_FT_PRINTF 🖨️
</h1>

<div align=center>
  
A custom `printf` implementation in C. 

</div>

# About ✍
Ft_printf is part of 42 Common Core and aims to replicate the functionality of the standard C library function `printf` supporting the conversions "cspdiuxX%". The project provides a learning of new concepts that certainly will be useful for next Common Core activities. The main goal is to deepen your understanding of the inner workings of printf, enhancing your proficiency in C programming.

# Prototype 🖥️
```c
int ft_printf(const char *, ...);
```

# Challenges and Learning Objectives 🧠
- Variadic Functions: Dealing with a variable number of arguments.
- String Parsing and Formatting: Parsing format strings and handling various specifiers.

# Conversions 💡
- `%c` -> Prints a single character.
- `%s` -> Prints a string (as defined by the common C convention).
- `%p` -> The void * pointer argument has to be printed in hexadecimal format.
- `%d` -> Prints a decimal (base 10) number.
- `%i` -> Prints an integer in base 10.
- `%u` -> Prints an unsigned decimal (base 10) number.
- `%x` -> Prints a number in hexadecimal (base 16) lowercase format.
- `%X` -> Prints a number in hexadecimal (base 16) uppercase format.
- `%%` -> Prints a percent sign.

# Grade  <p><img height="30px" src="https://img.shields.io/badge/-100%20%2F%20100-success" /></p>

# Norminette 💂🏻
At 42 School, we need to follow some strict rules when writing our code. These rules are described in the Norm and checked by the formidable `norminette`. Here are some of them:
```
- No for, do...while, switch, case, goto, ternary operators and variable-length arrays are allowed
- Each function must be maximum 25 lines
- One single variable declaration per line
- You can’t declare more than 5 variables per function
- You can't write more thane 5 functions per file
...
```
[Click here](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf) to review the complete Norm document.
