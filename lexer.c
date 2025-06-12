#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "lexer.h"
#include "utils.h"

Token *tokens;	// single linked list of tokens
Token *lastTk;		// the last token in list

int line=1;		// the current line in the input file

// adds a token to the end of the tokens list and returns it
// sets its code and line
Token *addTk(int code){
	Token *tk=safeAlloc(sizeof(Token));
	tk->code=code;
	tk->line=line;
	tk->next=NULL;
	if(lastTk){
		lastTk->next=tk;
		}else{
		tokens=tk;
		}
	lastTk=tk;
	return tk;
	}

char *extract(const char *begin,const char *end){
	size_t length = end - begin;
	char *result = safeAlloc(length + 1);
	strncpy(result, begin, length);
	result[length] = '\0';	
	return result;
}

Token *tokenize(const char *pch){
	const char *start;
	Token *tk;
	for(;;){
		switch(*pch){
			case ' ':case '\t':pch++;break;
			case '\r':		// handles different kinds of newlines (Windows: \r\n, Linux: \n, MacOS, OS X: \r or \n)
				if(pch[1]=='\n')pch++;
				// fallthrough to \n
			case '\n':
				line++;
				pch++;
				break;
			case '\0':addTk(END);return tokens;
			case ',':addTk(COMMA);pch++;break;
			case ';':addTk(SEMICOLON);pch++;break;
			case '(':addTk(LPAR);pch++;break;
			case ')':addTk(RPAR);pch++;break;
			case '[':addTk(LBRACKET);pch++;break;
			case ']':addTk(RBRACKET);pch++;break;
			case '{':addTk(LACC);pch++;break;
			case '}':addTk(RACC);pch++;break;
			case '+':addTk(ADD);pch++;break;
			case '-':addTk(SUB);pch++;break;
			case '*':addTk(MUL);pch++;break;
			case '.':addTk(DOT);pch++;break;
			case '/':	
				if(pch[1] == '/'){
					pch += 2;
					while(*pch != '\n' && *pch != '\0'){
						pch++;
					}
					break;
				} else if(pch[1] == '*'){
					pch += 2;
					while(*pch != '\0'){
						if(*pch == '*' && pch[1] == '/'){
							pch += 2;
							break;
						}
						if(*pch == '\n'){
							line++;
						}
						pch++;
					}
					break;
				}
				addTk(DIV);pch++;break;
			case '&':	
				if(pch[1]=='&'){
					addTk(AND);
					pch+=2;
				}else{
					err("invalid char: %c (%d)",*pch,*pch);
				}
				break;
			case '|':
				if(pch[1]=='|'){
					addTk(OR);
					pch+=2;
				}else{
					err("invalid char: %c (%d)",*pch,*pch);
				}
				break;
			case '!':
				if(pch[1]=='='){
					addTk(NOTEQ);
					pch+=2;
				}else{
					addTk(NOT);
					pch++;
				}
				break;
			case '<':
				if(pch[1]=='='){
					addTk(LESSEQ);
					pch+=2;
				}else{
					addTk(LESS);
					pch++;
				}
				break;
			case '>':
				if(pch[1]=='='){
					addTk(GREATEREQ);
					pch+=2;
				}else{
					addTk(GREATER);
					pch++;
				}
				break;
			case '=':
				if(pch[1]=='='){
					addTk(EQUAL);
					pch+=2;
				}else{
					addTk(ASSIGN);
					pch++;
				}
				break;
			default:
				if(isalpha(*pch)||*pch=='_'){
					for(start=pch++;isalnum(*pch)||*pch=='_';pch++){}
					char *text=extract(start,pch);
					if(strcmp(text,"else")==0)addTk(ELSE);
					else if(strcmp(text,"if")==0)addTk(IF);
					else if(strcmp(text,"return")==0)addTk(RETURN);
					else if(strcmp(text,"struct")==0)addTk(STRUCT);
					else if(strcmp(text,"void")==0)addTk(VOID);
					else if(strcmp(text,"while")==0)addTk(WHILE);
					else if(strcmp(text,"char")==0)addTk(TYPE_CHAR);
					else if(strcmp(text, "int")==0)addTk(TYPE_INT);
					else if(strcmp(text, "double")==0)addTk(TYPE_DOUBLE);
					else if(strcmp(text, "string")==0)addTk(TYPE_STRING);
					else{
						tk=addTk(ID);
						tk->text=text;
					}
				} else if (*pch == '\'') {
					if (pch[1] == '\'') {
						err("empty char");
					} else if (pch[2] != '\'') {
						err("invalid char: %c (%d)", pch[1], pch[1]);
					} else {
						tk = addTk(CHAR);
						tk->c = pch[1];
						pch += 3;
					}
				} else if(*pch == '"'){
					for(start = ++pch; *pch != '"'; pch++){
						if(*pch == '\0'){
							err("missing second \"");
						}
					}
					char *text = extract(start, pch);
					tk = addTk(STRING);
					tk->text = text;
					pch++;
				} else if (isdigit(*pch)) {
					start = pch;
					while (isdigit(*pch)) pch++;
					
					int has_decimal = 0;
					if (*pch == '.') {
						pch++;
						if (!isdigit(*pch)) {
							err("Invalid decimal part");
						}
						while (isdigit(*pch)) pch++;
						has_decimal = 1;
					}
					
					int has_exponent = 0;
					if (*pch == 'e' || *pch == 'E') {
						pch++;
						if (*pch == '+' || *pch == '-') {
							pch++;
						}
						if (!isdigit(*pch)) {
							err("Invalid exponent part");
						}
						while (isdigit(*pch)) pch++;
						has_exponent = 1;
					}
					
					if (has_decimal || has_exponent) {
						tk = addTk(DOUBLE);
						tk->d = atof(extract(start, pch));
					} else {
						tk = addTk(INT);
						tk->i = atoi(extract(start, pch));
					}
				}
				else err("invalid char: %c (%d)",*pch,*pch);
			}
		}
	}

void showTokens(const Token *tokens){
	char *codeNames[]={"ID","TYPE_CHAR","TYPE_DOUBLE","TYPE_STRING","TYPE_INT","CHAR","DOUBLE","STRING","INT","ELSE","IF","RETURN","STRUCT","VOID","WHILE","COMMA","SEMICOLON","LPAR","RPAR","LBRACKET","RBRACKET","LACC","RACC","END","ADD","SUB","MUL","DIV","DOT","AND","OR","NOT","ASSIGN","EQUAL","NOTEQ","LESS","LESSEQ","GREATER","GREATEREQ"};
	for(const Token *tk=tokens;tk;tk=tk->next){
		if(tk->code==ID||tk->code==STRING){
			printf("%d  %s:%s\n",tk->line, codeNames[tk->code],tk->text);
		}else if(tk->code==INT){
			printf("%d  %s:%d\n",tk->line, codeNames[tk->code],tk->i);
		}else if(tk->code==CHAR){
			printf("%d  %s:%c\n",tk->line, codeNames[tk->code],tk->c);
		}else if(tk->code==DOUBLE){
			printf("%d  %s:%g\n",tk->line, codeNames[tk->code],tk->d);
		} else{
			printf("%d  %s\n",tk->line, codeNames[tk->code]);
		}
	}
}
