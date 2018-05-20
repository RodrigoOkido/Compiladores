/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 4
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/


#ifndef AST_HEADER
#define AST_HEADER

#define MAX_SONS 4

#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

//BEGINNING
#define AST_DEC			0

//VARIABLES AND VECTORS DECLARATIONS
#define AST_VAR_DECL 1
#define AST_POINTER_VAR_DECL 2
#define AST_VECTOR_DECL 3
#define AST_VECTOR_DECL_EMPTY 4
#define AST_MORE_VALUES 5

//COMMAND LIST AND SYMBOL
#define AST_LCMD 	6
#define AST_SYMBOL 	7

//FUNCTIONS DECLARATION
#define AST_FUN_DECL 8
#define AST_FUN_PARAML 9
#define AST_FUN_PARAMREST 10

//BLOCK
#define AST_BLOCK		11

//ATRIBUTORS
#define AST_VAR_ATRIB 12
#define AST_VECTOR_ATRIB 13

//OPERATORS
#define AST_ADD 	20
#define AST_SUB 	21
#define AST_MUL 	22
#define AST_DIV 	23
#define AST_LESS	24
#define AST_GREATER	25
#define AST_NEG 	26

//COMPARATORS
#define AST_LE 		30
#define AST_GE 		31
#define AST_EQ 		32
#define AST_NE 		33
#define AST_AND 	34
#define AST_OR 		35

//POINTERS AND MEMORY
#define AST_END 36
#define AST_POINTER 37

//CALLERS
#define AST_ARRAY_POS 38
#define AST_FUNCALL 39

//SPECIAL CHARACTERS
#define AST_KW_CHAR		40
#define AST_KW_INT		41
#define AST_KW_FLOAT 		42
#define AST_KW_DOUBLE          	43
#define AST_KW_SHORT		44
#define AST_KW_BYTE		45
#define AST_KW_LONG		46
#define AST_KW_READ		47
#define AST_KW_RETURN	48
#define AST_KW_PRINT	49
#define AST_KW_WHILE 	50
#define AST_KW_IF	51
#define AST_KW_FOR 52
#define AST_NEW_BLOCK 53

//PARAMETERS
#define AST_PRINT_ARG 54
#define AST_PARAML 55

#define AST_EXP_P 56
#define AST_ENDER 57

// new
#define AST_POINTER_ATRIB 58

FILE *outputfile;


typedef struct ast_node {
	int type;
	int line;
	HASH *symbol;
	struct ast_node *son[MAX_SONS];
}AST;

AST* astCreate(int type, HASH* symbol, AST* son0, AST* son1, AST* son2, AST* son3);

void astPrint(AST *node, int level);

void astGenerateFile(AST *node, FILE *output_file);

#endif
