# AtomC Compiler

A complete compiler implementation for the AtomC programming language, featuring lexical analysis, syntax parsing, semantic analysis, and code generation for a stack-based virtual machine.

## Project Overview

This project implements a full compiler pipeline for AtomC, a C-like programming language. The compiler processes AtomC source code through multiple phases:

1. **Lexical Analysis** - Tokenization of source code
2. **Syntax Analysis** - Grammar parsing and AST construction
3. **Semantic Analysis** - Type checking and symbol table management
4. **Code Generation** - Virtual machine bytecode generation
5. **Execution** - Stack-based virtual machine execution

## Architecture

### Core Components

#### 1. Lexical Analyzer (`lexer.c`, `lexer.h`)
The lexical analyzer tokenizes AtomC source code into a stream of tokens.

**Features:**
- **Keywords**: `int`, `double`, `char`, `void`, `struct`, `if`, `else`, `while`, `return`
- **Literals**: Integer, double, character, and string literals
- **Operators**: Arithmetic (`+`, `-`, `*`, `/`), relational (`<`, `<=`, `>`, `>=`), logical (`&&`, `||`, `!`), assignment (`=`), equality (`==`, `!=`)
- **Delimiters**: Parentheses, brackets, braces, semicolons, commas
- **Identifiers**: Variable and function names
- **Comments**: Single-line (`//`) and multi-line (`/* */`) comments

**Token Structure:**
```c
typedef struct Token{
    int code;           // Token type (ID, INT, DOUBLE, etc.)
    int line;           // Source line number
    union{
        char *text;     // For identifiers and strings
        int i;          // For integer literals
        char c;         // For character literals
        double d;       // For double literals
    };
    struct Token *next; // Linked list pointer
} Token;
```
#### 2. Parser (`parser.c`, `parser.h`)
Implements recursive descent parsing for AtomC grammar.

**Grammar Productions:**
- **Declarations**: Variable definitions, struct definitions, function definitions
- **Expressions**: Primary expressions, postfix operations, unary operations, binary operations (arithmetic, relational, logical), assignments
- **Statements**: Compound statements, if-else, while loops, return statements, expression statements
- **Types**: Basic types (int, double, char), arrays, structures

**Key Functions:**
- **expr()**: Expression parsing with operator precedence
- **stm()**: Statement parsing
- **varDef(), structDef(), fnDef()**: Declaration parsing
- **typeBase()**: Type parsing

#### 3. Symbol Table and Domain Analysis (ad.c, ad.h)
Manages symbols and scoping through a hierarchical domain system.

**Symbol Types:**
```c
typedef enum{
    SK_VAR,     // Variables
    SK_PARAM,   // Function parameters  
    SK_FN,      // Functions
    SK_STRUCT   // Structure definitions
} SymKind;
```

**Type System:**
```c
typedef enum{
    TB_INT, TB_DOUBLE, TB_CHAR, TB_VOID, TB_STRUCT
} TypeBase;

typedef struct{
    TypeBase tb;    // Base type
    Symbol *s;      // For struct types, points to struct symbol
    int n;          // Array dimension (-1: not array, 0: unsized array, >0: sized array)
} Type;
```

**Domain Management:**
- Stack-based scope management
- Symbol lookup across nested scopes
- Memory allocation for global and local variables
- Function parameter and local variable indexing

#### 4. Type Analysis (at.c, at.h)
Performs semantic analysis and type checking.

**Return Type Structure:**
```c
typedef struct{
    Type type;      // The expression type
    bool lval;      // True if left-value (assignable)
    bool ct;        // True if constant
} Ret;
```

**Key Functions:**
- **canBeScalar()**: Checks if type can be used as scalar
- **convTo()**: Type conversion compatibility
- **arithTypeTo()**: Arithmetic operation result type
- **findSymbolInList()**: Symbol lookup in specific lists

- #### 5. Code Generation (gc.c, gc.h)
Generates bytecode for the virtual machine.

**Features:**
- Type conversion insertion
- Left-value to right-value conversion
- Optimization of unnecessary operations

- #### 6. Virtual Machine (vm.c, vm.h)
Stack-based virtual machine for code execution.

**Instruction Set:**
- **Stack Operations:** `PUSH_I`, `PUSH_D` (push constants)
- **Memory Operations:** `FPLOAD`, `FPSTORE` (frame pointer relative), `LOAD_I`, `LOAD_F` (dereference)
- **Arithmetic:** `ADD_I`, `ADD_D`, `SUB_I`, `SUB_F`, `MUL_I`, `MUL_F`, `DIV_I`, `DIV_F`
- **Comparison:** `LESS_I`, `LESS_D`
- **Control Flow:** `JMP`, `JF`, `JT` (jumps)
- **Function Calls:** `CALL`, `CALL_EXT`, `ENTER`, `RET`, `RET_VOID`
- **Type Conversion:** `CONV_I_F`, `CONV_F_I`
- **Utility:** `NOP`, `DROP`, `HALT`

 **VM Architecture:**
- **Stack:** 10,000-element value stack
- **Stack Pointer (SP):** Points to top of stack
- **Frame Pointer (FP):** Points to current function frame
- **Instruction Pointer (IP):** Points to current instruction

#### 7. Utilities (utils.c, utils.h)
Common utility functions for memory management and file operations.


**Functions:**
- **safeAlloc()** Safe memory allocation with error checking
- **loadFile()** File loading into memory
- **err()** Error reporting and program termination

#### AtomC Language Features
Data Types
- **Primitive Types:** `int`, `double`, `char,` `void`
- **Arrays:** Single-dimensional arrays with optional size specification
- **Frame Pointer (FP):** User-defined composite types

Control Structures
- **Conditional:** `if-else` statements
- **Loops:** `while` loops
- **Functions:** Function definitions with parameters and return values

Operations
- **Arithmetic:** `+`, `-`, `*`, `/`
- **Relational:** `<`, `<=`, `>`, `>=`, `==`, `!=`
- **Logical:** &&, `||`, `!`
- **Assignment:** `=`
- **Array Indexing:** `array[index]`
- **Structure Access:** `struct.member`

Example AtomC Program
```c
struct Point {
    int x;
    int y;
};

int factorial(int n) {
    if (n < 2) return 1;
    return n * factorial(n - 1);
}

void main() {
    int result;
    result = factorial(5);
    put_i(result);  // External function call
}
```

#### Build and Usage
**Compilation**
The project uses standard C compilation. All source files should be compiled together:

```bash
gcc -o atomc main.c lexer.c parser.c ad.c at.c gc.c vm.c utils.c
```

**Usage**

```bash
./atomc
```

The compiler reads from testgc.c by default and executes the compiled program.

**Test Files**
The project includes several test files:
- testgc.c Code generation test with recursive and iterative factorial
- testat.c Type analysis test (includes commented error cases)

**Error Handling**
The compiler provides comprehensive error reporting:
- **Lexical Errors:** Invalid characters, unterminated strings
- **Syntax Errors:** Grammar violations with line numbers
- **Semantic Errors:** Type mismatches, undefined symbols, scope violations
- **Runtime Errors:** Stack overflow, division by zero

**Memory Management**
- Dynamic allocation for tokens, symbols, and instructions
- Automatic cleanup of symbol tables when dropping scopes
- Safe memory allocation with error checking
- Proper deallocation of instruction sequences

**Virtual Machine Details**
The VM uses a unified value type for stack operations:
```c
.typedef union {
    int i;              // Integer values
    double f;           // Double values  
    void *p;            // Pointers
    void(*extFnPtr)();  // External function pointers
    Instr *instr;       // Instruction pointers
} Val;
```

Stack frames contain:
- Function parameters (negative indices from FP)
- Return address and old frame pointer
- Local variables (positive indices from FP)

This compiler demonstrates a complete implementation of language processing concepts including lexical analysis, parsing, semantic analysis, and code generation for a virtual machine target.
