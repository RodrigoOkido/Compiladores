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

		case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL,\n");
			break;
		case AST_ADD: fprintf(stderr, "AST_ADD,\n");
			break;
		case AST_SUB: fprintf(stderr, "AST_SUB,\n");
			break;
		case AST_LCMD: fprintf(stderr, "AST_LCMD,\n");
			break;
		case AST_ASS: fprintf(stderr, "AST_ASS,\n");
			break;
		case AST_MUL: fprintf(stderr, "AST_MUL,\n");
			break;
		case AST_DIV: fprintf(stderr, "AST_DIV,\n");
			break;
		case AST_NEG: fprintf(stderr, "AST_NEG,\n");
			break;
		case AST_LESS: fprintf(stderr, "AST_LESS,\n");
			break;
		case AST_GREAT: fprintf(stderr, "AST_GREAT,\n");
			break;		
		case AST_EQ: fprintf(stderr, "AST_EQ "); 
			break;
		case AST_LE: fprintf(stderr, "AST_LE "); 
			break;
		case AST_GE: fprintf(stderr, "AST_GE "); 
			break;
		case AST_NE: fprintf(stderr, "AST_NE "); 
			break;
		case AST_AND: fprintf(stderr, "AST_AND "); 
			break;
		case AST_OR: fprintf(stderr, "AST_OR "); 
			break;

	}

	for (int i = 0; i < MAX_SONS; ++i) {
		astPrint(node->son[i], level+1);
	}
}

//END OF FILE
