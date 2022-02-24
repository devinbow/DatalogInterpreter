To understand the project, please review the guide below. The current requisition encompasses Projects 1-5.

CS236 Projects Overview
There are five projects for CS236 that are each a piece of creating an interpreter for Dat-
alog programs (see https://www.geeksforgeeks.org/compiler-vs-interpreter-2/ for
details about interpreters). An interpreter is comprised of three components: the Lexer, the
Parser, and the Execution engine. In Project 1 you will build the Lexer. In Project 2 you
will create the Parser. In Projects 3, 4, and 5 you will develop the Execution engine.

A lexer is a program that takes as input a program file and scans the file for tokens. The
output to the lexer is a collection of tokens. These tokens can then be read by the parser.
The parser determines the meaning of the program based on the order and type of tokens.
This meaning is then given to the execution engine, which executes the program.

Why Tokens?
You might be questioning the reason we are converting programming files into tokens. Pro-
gramming languages are created to allow each programmer to use variable names, method
names, comments, strings, etc. that are specific to him or her or the application domain.
These items are very important for readability and organization to the programmer, but they
are not essential for the computer to execute the code. A lexer turns programmer-specific
“items” into programmer-independent structures called “tokens.” Each token contains the
information the computer needs, namely three items: 1) a token name, which is selected
from a set of predefined names, e.g. “STRING”; 2) the specific “item” for that token, e.g.
"Hello World"; and 3) a line number. This information allows the computer to get one step
closer to execution.
