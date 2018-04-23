/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 3
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/


#ifndef AST_HEADER
#define AST_HEADER

#define MAX_SONS 4

#include "hash.h"

#define AST_DEC			0
#define AST_SYMBOL 	1

#define AST_ADD 	2
#define AST_SUB 	3
#define AST_MUL 	4
#define AST_DIV 	5
#define AST_LESS	6
#define AST_GREAT	7
#define AST_NEG 	10

#define AST_LE 		11
#define AST_GE 		12
#define AST_EQ 		13
#define AST_NE 		14
#define AST_AND 	15
#define AST_OR 		16

#define AST_KW_CHAR		20
#define AST_KW_INT		21
#define AST_KW_FLOAT 	22
#define AST_KW_READ		23
#define AST_KW_RETURN	24
#define AST_KW_PRINT	25
#define AST_ARG_PRINT	26

#define AST_FUNC_DEC	30
#define AST_FUNC_ARGL	31
#define AST_FUNC_ARG	32

#define AST_BLOCK		40



typedef struct ast_node {
	int type;
	HASH *symbol;
	struct ast_node *son[MAX_SONS];
}AST;

AST* astCreate(int type, HASH* symbol, AST* son0, AST* son1, AST* son2, AST* son3);

void astPrint(AST *node, int level);

#endif
