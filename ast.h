#ifndef AST_HEADER
#define AST_HEADER

#define MAX_SONS 4

#include "hash.h"

typedef struct ast_node {
	int type;
	struct ast_node *son[MAX_SONS];
}AST;

AST* astCreate(int type, HASH* symbol, AST* son0, AST* son1, AST* son2, AST* son3);

void astPrint(AST *node, int level);

#endif
