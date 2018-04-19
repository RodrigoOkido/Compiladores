#include "ast.h"

AST* astCreate(int type, HASH* symbol, AST* son0, AST* son1, AST* son2, AST* son3) {

	AST* newnode;
	newnode = (AST*) calloc (1,sizeof(AST));
	newnode->type = type;
	newnode->symbol = symbol;
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
		default: fprintf(stderr, "UNKNOW,\n");
	
	}
	
	for (int i = 0; i < MAX_SONS; ++i) {
		astPrint(node->son[i], level+1);
	}
}

