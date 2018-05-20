%{

#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "semantic.h"
#include "hash.h"


int yylex();
int yyerror(char *msg);
%}

%union {
	AST* ast;
	HASH* symbol;
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

%type<ast> lit_value_or_initvect
%type<ast> lit_value_pointer
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

program : decl			{astPrint($1,0);  astGenerateFile($1, outputfile);
				 set_Declarations($1);
				check_id_undeclared();
				check_declaration_usage($1);
				check_operands($1);
				check_returnType($1); 
				//check_declaration_usage($1);
}

decl : dec decl			{ $$ = astCreate(AST_DEC,0,$1,$2,0,0); }
	|			{ $$ = 0; }
	;


dec : vardec			{ $$ = $1; }
	| fundec				{ $$ = $1; }
	;


vardec : vartype SYMBOL_IDENTIFIER '=' lit_value_or_initvect ';'			{ $$ = astCreate(AST_VAR_DECL,$2,$1,$4,0,0); }
	| vartype '#' SYMBOL_IDENTIFIER '=' lit_value_pointer ';'				{ $$ = astCreate(AST_POINTER_VAR_DECL,$3,$1,0,0,0); }
	| vartype SYMBOL_IDENTIFIER'['exp']'':' lit_value_or_initvect ';'			{ $$ = astCreate(AST_VECTOR_DECL,$2,$1,$4,$7,0); }
	| vartype SYMBOL_IDENTIFIER '['exp']' ';'			{ $$ = astCreate(AST_VECTOR_DECL_EMPTY,$2,$1,$4,0,0); }
	;


vartype: KW_CHAR			{ $$ = astCreate(AST_KW_CHAR,0,0,0,0,0); }
	| KW_INT			{ $$ = astCreate(AST_KW_INT,0,0,0,0,0); }
	| KW_FLOAT			{ $$ = astCreate(AST_KW_FLOAT,0,0,0,0,0); }
	;


lit_value_pointer: SYMBOL_LIT_INT { $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
		| SYMBOL_LIT_REAL { $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
		| SYMBOL_LIT_CHAR { $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
		| { $$ = 0; }
		;

lit_value_or_initvect: SYMBOL_LIT_INT lit_value_or_initvect			{ $$ = astCreate(AST_SYMBOL,$1,$2,0,0,0); }
	| SYMBOL_LIT_REAL lit_value_or_initvect			{ $$ = astCreate(AST_SYMBOL,$1,$2,0,0,0); }
	| SYMBOL_LIT_CHAR lit_value_or_initvect			{ $$ = astCreate(AST_SYMBOL,$1,$2,0,0,0); }
	|   { $$ = 0; }
	;


fundec: vartype SYMBOL_IDENTIFIER '('funparaml')' block			{ $$ = astCreate(AST_FUN_DECL,$2,$1,$4,$6,0); }
	;

funparaml: paramdecl paramrest			{ $$ = astCreate(AST_FUN_PARAML,0,$1,$2,0,0); }
	|			{ $$ = 0; }
	;

paramdecl: vartype SYMBOL_IDENTIFIER			{ $$ = astCreate(AST_SYMBOL,$2,$1,0,0,0); }
	;

paramrest: ',' paramdecl paramrest			{ $$ = astCreate(AST_FUN_PARAMREST,0,$2,$3,0,0); }
	|			{ $$ = 0; }
	;


block: '{'lcmd'}'			{ $$ = astCreate(AST_BLOCK,0,$2,0,0,0); }
	;

lcmd : cmd ';' lcmd			{ $$ = astCreate(AST_LCMD,0,$1,$3,0,0); }
	| cmd			{ $$ = $1; }
	;


cmd : SYMBOL_IDENTIFIER '=' exp			{ $$ = astCreate(AST_VAR_ATRIB,$1,$3,0,0,0); }
		| SYMBOL_IDENTIFIER '[' exp ']' '=' exp			{ $$ = astCreate(AST_VECTOR_ATRIB,$1,$3,$6,0,0); }
		| KW_READ return_read			{ $$ = astCreate(AST_KW_READ,0,$2,0,0,0); }
		| KW_RETURN exp			{ $$ = astCreate(AST_KW_RETURN,0,$2,0,0,0); }
		| KW_PRINT argprint			{ $$ = astCreate(AST_KW_PRINT,0,$2,0,0,0); }
		| KW_WHILE '('exp')' cmd			{ $$ = astCreate(AST_KW_WHILE,0,$3,$5,0,0); }
		| KW_IF '('exp')' KW_THEN cmd			{ $$ = astCreate(AST_KW_IF,0,$3,$6,0,0); }
		| KW_IF '('exp')' KW_THEN cmd KW_ELSE cmd			{ $$ = astCreate(AST_KW_IF,0,$3,$6,$8,0); }
   		 | KW_FOR '(' SYMBOL_IDENTIFIER '=' exp KW_TO exp ')' cmd			{ $$ = astCreate(AST_KW_FOR,$3,$5,$7,$9,0); }
		| block cmd			{ $$ = astCreate(AST_NEW_BLOCK,0,$1,$2,0,0); }
		|			{ $$ = 0; }
    ;


return_read: SYMBOL_LIT_INT			{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| SYMBOL_LIT_REAL			{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| SYMBOL_LIT_CHAR			{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| SYMBOL_IDENTIFIER			{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| SYMBOL_LIT_STRING			{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	;



argprint: printelement restprint			{ $$ = astCreate(AST_PRINT_ARG,0,$1,$2,0,0); }
	;


restprint: printelement restprint			{ $$ = astCreate(AST_PRINT_ARG,0,$1,$2,0,0); }
	|			{ $$ = 0; }
	;


printelement: exp			{ $$ = $1; }
	| SYMBOL_LIT_STRING			{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	;


exp : SYMBOL_IDENTIFIER			{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
   	 	| SYMBOL_LIT_INT			{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
   	 	| SYMBOL_LIT_CHAR			{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
    	| exp '+' exp			{ $$ = astCreate(AST_ADD,0,$1,$3,0,0); }
    	| exp '-' exp			{ $$ = astCreate(AST_SUB,0,$1,$3,0,0); }
    	| exp '*' exp			{ $$ = astCreate(AST_MUL,0,$1,$3,0,0); }
    	| exp '/' exp			{ $$ = astCreate(AST_DIV,0,$1,$3,0,0); }
			| exp '<' exp			{ $$ = astCreate(AST_LESS,0,$1,$3,0,0); }
			| exp '>' exp			{ $$ = astCreate(AST_GREATER,0,$1,$3,0,0); }
			| exp '!' exp			{ $$ = astCreate(AST_NEG,0,$1,$3,0,0); }
			| '('exp')'			{ $$ = astCreate(AST_EXP_P,0,$2,0,0,0); }
    	| exp OPERATOR_LE exp			{ $$ = astCreate(AST_LE,0,$1,$3,0,0); }
    	| exp OPERATOR_GE exp			{ $$ = astCreate(AST_GE,0,$1,$3,0,0); }
			| exp OPERATOR_EQ exp			{ $$ = astCreate(AST_EQ,0,$1,$3,0,0); }
			| exp OPERATOR_NE exp			{ $$ = astCreate(AST_NE,0,$1,$3,0,0); }
			| exp OPERATOR_AND exp			{ $$ = astCreate(AST_AND,0,$1,$3,0,0); }
			| exp OPERATOR_OR exp			{ $$ = astCreate(AST_OR,0,$1,$3,0,0); }
			| '&' SYMBOL_IDENTIFIER			{ $$ = astCreate(AST_ENDER,$2,0,0,0,0); }
			| '#' SYMBOL_IDENTIFIER			{ $$ = astCreate(AST_POINTER,$2,0,0,0,0); }
			| SYMBOL_IDENTIFIER '['exp']'			{ $$ = astCreate(AST_ARRAY_POS,$1,$3,0,0,0); }
			| SYMBOL_IDENTIFIER '('paraml')'			{ $$ = astCreate(AST_FUNCALL,$1,$3,0,0,0); }
			;


paraml: listParam newparam			{ $$ = astCreate(AST_PARAML,0,$1,$2,0,0); }
	|			{ $$ = 0; }
	;

newparam : ',' listParam newparam			{ $$ = astCreate(AST_PARAML,0,$2,$3,0,0); }
	|			{ $$ = 0; }
	;


listParam : SYMBOL_LIT_INT			{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| SYMBOL_LIT_CHAR			{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| SYMBOL_LIT_REAL			{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| SYMBOL_IDENTIFIER			{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| '#' SYMBOL_IDENTIFIER			{ $$ = astCreate(AST_POINTER,$2,0,0,0,0); }
	| '&' SYMBOL_IDENTIFIER			{ $$ = astCreate(AST_ENDER,$2,0,0,0,0); }
	;


%%

int yyerror(char *msg){
	fprintf(stderr,"[ERRO] Houve erro na linha %d: %s\n",getLineNumber(), msg);
	exit(3);
}
