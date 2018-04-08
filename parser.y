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
%token KW_TO				 269

%token OPERATOR_LE   270
%token OPERATOR_GE   271
%token OPERATOR_EQ   272
%token OPERATOR_NE   273
%token OPERATOR_AND  274
%token OPERATOR_OR   275

%token TK_IDENTIFIER 280
%token LIT_INT 281
%token LIT_REAL 282
%token LIT_CHAR 283
%token LIT_STRING 284

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


vardec : vartype TK_IDENTIFIER '=' lit_value_or_initvect ';'
	| vartype '#' TK_IDENTIFIER '=' lit_value_or_initvect ';'
	| vartype TK_IDENTIFIER'['LIT_INT']'':' lit_value_or_initvect more_values ';'
	| vartype TK_IDENTIFIER '['LIT_INT']' ';'
	;

vartype: KW_CHAR
	| KW_INT
	| KW_FLOAT
	;


more_values: lit_value_or_initvect more_values
	|
	;


lit_value_or_initvect: LIT_INT
	| LIT_REAL
	| LIT_CHAR
	;


fundec: vartype TK_IDENTIFIER '('funparaml')' block
	;

funparaml: paramdecl paramrest
	|
	;

paramdecl: vartype TK_IDENTIFIER
	;

paramrest: ',' paramdecl paramrest
	|
	;


block: '{'lcmd'}'
	;

lcmd : cmd ';' lcmd
	| cmd
	;


cmd : TK_IDENTIFIER '=' exp
		| TK_IDENTIFIER '[' exp ']' '=' exp
		| KW_READ return_read
		| KW_RETURN exp
		| KW_PRINT argprint
		| KW_WHILE '('exp')' cmd
		| KW_IF '('exp')' KW_THEN cmd
		| KW_IF '('exp')' KW_THEN cmd KW_ELSE cmd
    | KW_FOR '(' TK_IDENTIFIER '=' exp KW_TO exp ')' cmd
		| block
		|
    ;


return_read: LIT_INT
	| LIT_REAL
	| LIT_CHAR
	| TK_IDENTIFIER
	| LIT_STRING
	;



argprint: printelement restprint
	;


restprint: printelement restprint
	|
	;


printelement: exp
	| LIT_STRING
	;


exp : TK_IDENTIFIER
   	 	| LIT_INT
   	 	| LIT_CHAR
    	| exp '+' exp
    	| exp '-' exp
    	| exp '*' exp
    	| exp '/' exp
			| exp '<' exp
			| exp '>' exp
			| exp '!' exp
			| '('exp')'
    	| exp OPERATOR_LE exp
    	| exp OPERATOR_GE exp
			| exp OPERATOR_EQ exp
			| exp OPERATOR_NE exp
			| exp OPERATOR_AND exp
			| exp OPERATOR_OR exp
			| '&' TK_IDENTIFIER
			| '#' TK_IDENTIFIER
			| TK_IDENTIFIER '['exp']'
			| TK_IDENTIFIER '('paraml')'
			;

paraml: listParam newparam
	|
	;

newparam : ',' listParam newparam
	|
	;


listParam : LIT_INT
	| LIT_CHAR
	| LIT_REAL
	| TK_IDENTIFIER
	| '#' TK_IDENTIFIER
	| '&' TK_IDENTIFIER
	;


%%

int yyerror(char *msg){
	fprintf(stderr,"[ERRO] Houve erro na linha %d: %s\n",getLineNumber(), msg);
	exit(3);
}
