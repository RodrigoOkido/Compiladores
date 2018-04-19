#ifndef AST_HEADER
#define AST_HEADER

#define MAX_SONS 4

typedef struct ast_node {
	int type;
	struct ast_node *son[MAX_SONS];
}AST;


#endif
