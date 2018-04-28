/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 3
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/


#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

AST* astCreate(int type, HASH* symbol, AST* son0, AST* son1, AST* son2, AST* son3) {

	AST* newnode;
	newnode = (AST*) calloc (1,sizeof(AST));
	newnode->type = type;
	newnode->symbol = symbol;
	newnode->son[0] = son0;
	newnode->son[1] = son1;
	newnode->son[2] = son2;
	newnode->son[3] = son3;
	return newnode;

}

void astPrint(AST *node, int level) {

	if(!node) return;
	for(int i = 0; i < level; ++i){
		fprintf(stderr," ");
	}
	fprintf(stderr,"AST (");
	switch (node-> type) {

		case AST_DEC:	fprintf(stderr, "AST_DEC"); break;
		case AST_VAR_DECL: fprintf(stderr, "AST_VAR_DECL"); break;
		case AST_POINTER_VAR_DECL: fprintf(stderr, "AST_POINTER_VAR_DECL"); break;
		case AST_VECTOR_DECL: fprintf(stderr, "AST_VECTOR_DECL"); break;
		case AST_VECTOR_DECL_EMPTY: fprintf(stderr, "AST_VECTOR_DECL_EMPTY"); break;
		case AST_MORE_VALUES: fprintf(stderr, "AST_MORE_VALUES"); break;
		case AST_LCMD: 	fprintf(stderr, "AST_LCMD"); break;
		case AST_SYMBOL: 	fprintf(stderr, "AST_SYMBOL"); break;
		case AST_FUN_DECL: fprintf(stderr, "AST_FUN_DECL"); break;
		case AST_FUN_PARAML: fprintf(stderr, "AST_FUN_PARAML"); break;
		case AST_FUN_PARAM: fprintf(stderr, "AST_FUN_PARAM"); break;
		case AST_BLOCK:		fprintf(stderr, "AST_BLOCK"); break;
		case AST_VAR_ATRIB: fprintf(stderr, "AST_VAR_ATRIB"); break;
		case AST_VECTOR_ATRIB: fprintf(stderr, "AST_VECTOR_ATRIB"); break;
		case AST_ADD: 	fprintf(stderr, "AST_ADD"); break;
		case AST_SUB: 	fprintf(stderr, "AST_SUB"); break;
		case AST_MUL: 	fprintf(stderr, "AST_MUL"); break;
		case AST_DIV: 	fprintf(stderr, "AST_DIV"); break;
		case AST_LESS:	fprintf(stderr, "AST_LESS"); break;
		case AST_GREATER:	fprintf(stderr, "AST_GREATER"); break;
		case AST_NEG: 	fprintf(stderr, "AST_NEG"); break;
		case AST_LE: 		fprintf(stderr, "AST_LE"); break;
		case AST_GE: 		fprintf(stderr, "AST_GE"); break;
		case AST_EQ: 		fprintf(stderr, "AST_EQ"); break;
		case AST_NE: 		fprintf(stderr, "AST_NE"); break;
		case AST_AND: 	fprintf(stderr, "AST_AND"); break;
		case AST_OR: 		fprintf(stderr, "AST_OR"); break;
		case AST_ENDER: fprintf(stderr, "AST_ENDER"); break;
		case AST_POINTER: fprintf(stderr, "AST_POINTER"); break;
		case AST_ARRAY_POS: fprintf(stderr, "AST_ARRAY_POS"); break;
		case AST_FUNCALL: fprintf(stderr, "AST_FUNCALL"); break;
		case AST_KW_CHAR:		fprintf(stderr, "AST_KW_CHAR"); break;
		case AST_KW_INT:		fprintf(stderr, "AST_KW_INT"); break;
		case AST_KW_FLOAT: 	fprintf(stderr, "AST_KW_FLOAT"); break;
		case AST_KW_READ:		fprintf(stderr, "AST_KW_READ"); break;
		case AST_KW_RETURN:	fprintf(stderr, "AST_KW_RETURN"); break;
		case AST_KW_PRINT:	fprintf(stderr, "AST_KW_PRINT"); break;
		case AST_KW_WHILE: fprintf(stderr, "AST_KW_WHILE"); break;
		case AST_KW_IF:	fprintf(stderr, "AST_KW_IF"); break;
		case AST_KW_FOR: fprintf(stderr, "AST_KW_FOR"); break;
		case AST_NEW_BLOCK: fprintf(stderr, "AST_NEW_BLOCK"); break;
		case AST_PRINT_ARG: fprintf(stderr, "AST_PRINT_ARG"); break;
		case AST_PARAML: fprintf(stderr, "AST_PARAML"); break;

		case AST_CMD_WHILE: fprintf(stderr, "AST_CMD_WHILE"); break;
		default: fprintf(stderr, "UNKNOW"); break;

	}

	for (int i = 0; i < MAX_SONS; ++i) {
		astPrint(node->son[i], level+1);
	}
}

//END OF FILE
