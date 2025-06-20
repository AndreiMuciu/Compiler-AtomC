#pragma once
// am adaugat keywordurile, delimitatorii si operatorii care lipseau
enum{
	ID
	// keywords
	,TYPE_CHAR
	,TYPE_DOUBLE
	,TYPE_STRING
	,TYPE_INT
	,CHAR
	,DOUBLE
	,STRING
	,INT
	,ELSE
	,IF
	,RETURN
	,STRUCT
	,VOID
	,WHILE
	// delimiters
	,COMMA,SEMICOLON,LPAR,RPAR,LBRACKET,RBRACKET,LACC,RACC,END
	// operators
	,ADD,SUB,MUL,DIV,DOT,AND,OR,NOT,ASSIGN,EQUAL,NOTEQ,LESS,LESSEQ,GREATER,GREATEREQ
	};

typedef struct Token{
	int code;		// ID, TYPE_CHAR, ...
	int line;		// the line from the input file
	union{
		char *text;		// the chars for ID, STRING (dynamically allocated)
		int i;		// the value for INT
		char c;		// the value for CHAR
		double d;		// the value for DOUBLE
		};
	struct Token *next;		// next token in a simple linked list
	}Token;

Token *tokenize(const char *pch);
void showTokens(const Token *tokens);
