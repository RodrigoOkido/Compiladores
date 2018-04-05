%{
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>


int yylex();
int yyerror(char *msg);
%}


%token KW_CHAR       256
%token KW_INT        257
%token KW_FLOAT      259
%token KW_IF         261
%token KW_THEN       262
%token KW_ELSE       263
%token KW_WHILE      264
%token KW_FOR        265
%token KW_READ       266
%token KW_RETURN     267
%token KW_PRINT      268

%token OPERATOR_LE   270
%token OPERATOR_GE   271
%token OPERATOR_EQ   272
%token OPERATOR_NE   273
%token OPERATOR_AND  274
%token OPERATOR_OR   275

%token SYMBOL_IDENTIFIER
%token SYMBOL_LIT_INTEGER
%token SYMBOL_LIT_REAL
%token SYMBOL_LIT_CHAR
%token SYMBOL_LIT_STRING

%token TOKEN_ERROR 290

%left OPERATOR_AND OPERATOR_OR '!'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '+' '-'
%left '*' '/'

%%


program : decl


decl : dec decl
	|
	;

dec : vardec
	| fundec
	;


vardec : vartype SYMBOL_IDENTIFIER '=' value
	| vartype SYMBOL_IDENTIFIER '[' SYMBOL_LIT_INT ']' ':' initvect ';'


vartype : KW_CHAR
	| KW_INT
	| KW_FLOAT
	;


initvect : SYMBOL_LIT_INT
	| SYMBOL_LIT_REAL
	| SYMBOL_LIT_CHAR
	|
	;

block: '{'lcmd'}'

lcmd: cmd ';' lcmd
	|
	;

cmd : SYMBOL_IDENTIFIER '=' exp
    | KW_WHILE '('exp')' cmd
    | KW_FOR '(' SYMBOL_IDENTIFIER '=' exp to exp ')' cmd
    | KW_IF '('exp')' KW_THEN cmd
    | KW_IF '('exp')' KW_THEN cmd KW_ELSE cmd
    ;

exp : SYMBOL_IDENTIFIER
    | SYMBOL_LIT_INTEGER
    | SYMBOL_LIT_CHAR
    | exp '+' exp
    | exp '-' exp
    | exp '*' exp
    | exp '/' exp
    | exp OPERATOR_LE exp
    | exp OPERATOR_GE exp
	| exp OPERATOR_EQ exp
	| exp OPERATOR_NE exp
	| exp OPERATOR_AND exp
	| exp OPERATOR_OR exp
	;

%%

int yyerror(char *msg){
	fprintf(stderr,"[ERRO] Houve erro na linha %d: %s\n",getLineNumber(), msg);
	exit(3);
}
