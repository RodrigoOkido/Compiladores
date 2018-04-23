%{
#include "ast.h"
#include "hash.h"

#include <stdio.h>
#include <stdlib.h>


int yylex();
int yyerror(char *msg);
%}

%union {
	AST* ast;
	HASH *symbol;
}

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

%token<symbol> SYMBOL_IDENTIFIER 280
%token<symbol> SYMBOL_LIT_INT 281
%token<symbol> SYMBOL_LIT_REAL 282
%token<symbol> SYMBOL_LIT_CHAR 283
%token<symbol> SYMBOL_LIT_STRING 284

%token TOKEN_ERROR 290

%type<ast> program
%type<ast> decl
%type<ast> dec
%type<ast> vardec
%type<ast> vartype
%type<ast> more_values
%type<ast> lit_value_or_initvect
%type<ast> fundec
%type<ast> funparaml
%type<ast> paramdecl
%type<ast> paramrest
%type<ast> block
%type<ast> lcmd
%type<ast> cmd
%type<ast> return_read
%type<ast> argprint
%type<ast> restprint
%type<ast> printelement
%type<ast> exp
%type<ast> paraml
%type<ast> newparam
%type<ast> listParam


%left OPERATOR_AND OPERATOR_OR '!'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '+' '-'
%left '*' '/'





%%

program : decl		{ $$ = astCreate(AST_CMD_WHILE,0,$3,$5,0,0); }


decl : dec decl		{ $$ = astCreate(0,0,0,0,0,0); }
	|
	;


dec : vardec			{ $$ = astCreate(0,0,0,0,0,0); }
	| fundec				{ $$ = astCreate(0,0,0,0,0,0); }
	;


vardec : vartype SYMBOL_IDENTIFIER '=' lit_value_or_initvect ';'			{ $$ = astCreate(0,0,0,0,0,0); }
	| vartype '#' SYMBOL_IDENTIFIER '=' lit_value_or_initvect ';'				{ $$ = astCreate(0,0,0,0,0,0); }
	| vartype SYMBOL_IDENTIFIER'['SYMBOL_LIT_INT']'':' lit_value_or_initvect more_values ';'			{ $$ = astCreate(0,0,0,0,0,0); }
	| vartype SYMBOL_IDENTIFIER '['SYMBOL_LIT_INT']' ';'		{ $$ = astCreate(AST_CMD_WHILE,0,$3,$5,0,0); }			{ $$ = astCreate(0,0,0,0,0,0); }
	;

vartype: KW_CHAR			{ $$ = astCreate(0,0,0,0,0,0); }
	| KW_INT			{ $$ = astCreate(0,0,0,0,0,0); }
	| KW_FLOAT			{ $$ = astCreate(0,0,0,0,0,0); }
	;


more_values: lit_value_or_initvect more_values			{ $$ = astCreate(0,0,0,0,0,0); }
	|			{ $$ = astCreate(0,0,0,0,0,0); }
	;


lit_value_or_initvect: SYMBOL_LIT_INT			{ $$ = astCreate(0,0,0,0,0,0); }
	| SYMBOL_LIT_REAL			{ $$ = astCreate(0,0,0,0,0,0); }
	| SYMBOL_LIT_CHAR			{ $$ = astCreate(0,0,0,0,0,0); }
	;


fundec: vartype SYMBOL_IDENTIFIER '('funparaml')' block			{ $$ = astCreate(0,0,0,0,0,0); }
	;

funparaml: paramdecl paramrest			{ $$ = astCreate(0,0,0,0,0,0); }
	|			{ $$ = astCreate(0,0,0,0,0,0); }
	;

paramdecl: vartype SYMBOL_IDENTIFIER			{ $$ = astCreate(0,0,0,0,0,0); }
	;

paramrest: ',' paramdecl paramrest			{ $$ = astCreate(0,0,0,0,0,0); }
	|
	;


block: '{'lcmd'}'			{ $$ = astCreate(0,0,0,0,0,0); }
	;

lcmd : cmd ';' lcmd			{ $$ = astCreate(AST_LCMD,0,$1,$2,0,0); }
	| cmd			{ $$ = 0; }
	;


cmd : SYMBOL_IDENTIFIER '=' exp			{ $$ = astCreate(AST_ASS,$1,$3,0,0,0); }
		| SYMBOL_IDENTIFIER '[' exp ']' '=' exp			{ $$ = astCreate(0,0,0,0,0,0); }
		| KW_READ return_read			{ $$ = astCreate(0,0,0,0,0,0); }
		| KW_RETURN exp			{ $$ = astCreate(0,0,0,0,0,0); }
		| KW_PRINT argprint			{ $$ = astCreate(0,0,0,0,0,0); }
		| KW_WHILE '('exp')' cmd			{ $$ = astCreate(0,0,0,0,0,0); }
		| KW_IF '('exp')' KW_THEN cmd			{ $$ = astCreate(0,0,0,0,0,0); }
		| KW_IF '('exp')' KW_THEN cmd KW_ELSE cmd			{ $$ = astCreate(0,0,0,0,0,0); }
    | KW_FOR '(' SYMBOL_IDENTIFIER '=' exp KW_TO exp ')' cmd			{ $$ = astCreate(0,0,0,0,0,0); }
		| block cmd			{ $$ = astCreate(0,0,0,0,0,0); }
		|			{ $$ = astCreate(0,0,0,0,0,0); }
    ;


return_read: SYMBOL_LIT_INT			{ $$ = astCreate(0,0,0,0,0,0); }
	| SYMBOL_LIT_REAL			{ $$ = astCreate(0,0,0,0,0,0); }
	| SYMBOL_LIT_CHAR			{ $$ = astCreate(0,0,0,0,0,0); }
	| SYMBOL_IDENTIFIER			{ $$ = astCreate(0,0,0,0,0,0); }
	| SYMBOL_LIT_STRING			{ $$ = astCreate(0,0,0,0,0,0); }
	;



argprint: printelement restprint			{ $$ = astCreate(0,0,0,0,0,0); }
	;


restprint: printelement restprint			{ $$ = astCreate(0,0,0,0,0,0); }
	|			{ $$ = astCreate(0,0,0,0,0,0); }
	;


printelement: exp			{ $$ = astCreate(0,0,0,0,0,0); }
	| SYMBOL_LIT_STRING			{ $$ = astCreate(0,0,0,0,0,0); }
	;


exp : SYMBOL_IDENTIFIER			{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
   	 	| SYMBOL_LIT_INT			{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
   	 	| SYMBOL_LIT_CHAR			{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
    	| exp '+' exp			{ $$ = astCreate(AST_ADD,0,$1,$3,0,0); }
    	| exp '-' exp			{ $$ = astCreate(AST_SUB,0,$1,$3,0,0); }
    	| exp '*' exp			{ $$ = astCreate(0,0,0,0,0,0); }
    	| exp '/' exp			{ $$ = astCreate(0,0,0,0,0,0); }
			| exp '<' exp			{ $$ = astCreate(0,0,0,0,0,0); }
			| exp '>' exp			{ $$ = astCreate(0,0,0,0,0,0); }
			| exp '!' exp			{ $$ = astCreate(0,0,0,0,0,0); }
			| '('exp')'			{ $$ = astCreate(0,0,0,0,0,0); }
    	| exp OPERATOR_LE exp			{ $$ = astCreate(0,0,0,0,0,0); }
    	| exp OPERATOR_GE exp			{ $$ = astCreate(0,0,0,0,0,0); }
			| exp OPERATOR_EQ exp			{ $$ = astCreate(0,0,0,0,0,0); }
			| exp OPERATOR_NE exp			{ $$ = astCreate(0,0,0,0,0,0); }
			| exp OPERATOR_AND exp			{ $$ = astCreate(0,0,0,0,0,0); }
			| exp OPERATOR_OR exp			{ $$ = astCreate(0,0,0,0,0,0); }
			| '&' SYMBOL_IDENTIFIER			{ $$ = astCreate(0,0,0,0,0,0); }
			| '#' SYMBOL_IDENTIFIER			{ $$ = astCreate(0,0,0,0,0,0); }
			| SYMBOL_IDENTIFIER '['exp']'			{ $$ = astCreate(0,0,0,0,0,0); }
			| SYMBOL_IDENTIFIER '('paraml')'			{ $$ = astCreate(0,0,0,0,0,0); }
			;


paraml: listParam newparam			{ $$ = astCreate(0,0,0,0,0,0); }
	|			{ $$ = astCreate(0,0,0,0,0,0); }
	;

newparam : ',' listParam newparam			{ $$ = astCreate(0,0,0,0,0,0); }
	|			{ $$ = astCreate(0,0,0,0,0,0); }
	;


listParam : SYMBOL_LIT_INT			{ $$ = astCreate(0,0,0,0,0,0); }
	| SYMBOL_LIT_CHAR			{ $$ = astCreate(0,0,0,0,0,0); }
	| SYMBOL_LIT_REAL			{ $$ = astCreate(0,0,0,0,0,0); }
	| SYMBOL_IDENTIFIER			{ $$ = astCreate(0,0,0,0,0,0); }
	| '#' SYMBOL_IDENTIFIER			{ $$ = astCreate(0,0,0,0,0,0); }
	| '&' SYMBOL_IDENTIFIER			{ $$ = astCreate(0,0,0,0,0,0); }
	;


%%

int yyerror(char *msg){
	fprintf(stderr,"[ERRO] Houve erro na linha %d: %s\n",getLineNumber(), msg);
	exit(3);
}
