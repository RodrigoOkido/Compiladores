/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 6
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/


#include "ast.h"
#include "hash.h"



AST* astCreate(int type, HASH* symbol, AST* son0, AST* son1, AST* son2, AST* son3) {

	AST* newnode;
	newnode = (AST*) calloc (1,sizeof(AST));
	newnode->type = type;
	newnode->symbol = symbol;
	newnode->line = getLineNumber();
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

		case AST_DEC:	fprintf(stderr, "AST_DEC,\n"); break;
		case AST_VAR_DECL: fprintf(stderr, "AST_VAR_DECL,\n"); break;
		case AST_POINTER_VAR_DECL: fprintf(stderr, "AST_POINTER_VAR_DECL,\n"); break;
		case AST_VECTOR_DECL: fprintf(stderr, "AST_VECTOR_DECL,\n"); break;
		case AST_VECTOR_DECL_EMPTY: fprintf(stderr, "AST_VECTOR_DECL_EMPTY,\n"); break;
		case AST_MORE_VALUES: fprintf(stderr, "AST_MORE_VALUES,\n"); break;
		case AST_LCMD: 	fprintf(stderr, "AST_LCMD,\n"); break;
		case AST_SYMBOL: 	fprintf(stderr, "AST_SYMBOL,\n"); break;
		case AST_FUN_DECL: fprintf(stderr, "AST_FUN_DECL,\n"); break;
		case AST_FUN_PARAML: fprintf(stderr, "AST_FUN_PARAML,\n"); break;
		case AST_FUN_PARAMREST: fprintf(stderr, "AST_FUN_PARAMREST,\n"); break;
		case AST_BLOCK:		fprintf(stderr, "AST_BLOCK,\n"); break;
		case AST_VAR_ATRIB: fprintf(stderr, "AST_VAR_ATRIB,\n"); break;
		case AST_VECTOR_ATRIB: fprintf(stderr, "AST_VECTOR_ATRIB,\n"); break;
		case AST_ADD: 	fprintf(stderr, "AST_ADD,\n"); break;
		case AST_SUB: 	fprintf(stderr, "AST_SUB,\n"); break;
		case AST_MUL: 	fprintf(stderr, "AST_MUL,\n"); break;
		case AST_DIV: 	fprintf(stderr, "AST_DIV,\n,\n"); break;
		case AST_LESS:	fprintf(stderr, "AST_LESS,\n"); break;
		case AST_GREATER:	fprintf(stderr, "AST_GREATER,\n"); break;
		case AST_NEG: 	fprintf(stderr, "AST_NEG,\n"); break;
		case AST_LE: 		fprintf(stderr, "AST_LE,\n"); break;
		case AST_GE: 		fprintf(stderr, "AST_GE,\n"); break;
		case AST_EQ: 		fprintf(stderr, "AST_EQ,\n"); break;
		case AST_NE: 		fprintf(stderr, "AST_NE,\n"); break;
		case AST_AND: 	fprintf(stderr, "AST_AND,\n"); break;
		case AST_OR: 		fprintf(stderr, "AST_OR,\n"); break;
		case AST_ENDER: fprintf(stderr, "AST_ENDER,\n"); break;
		case AST_POINTER: fprintf(stderr, "AST_POINTER,\n"); break;
		case AST_ARRAY_POS: fprintf(stderr, "AST_ARRAY_POS,\n"); break;
		case AST_FUNCALL: fprintf(stderr, "AST_FUNCALL,\n"); break;
		case AST_KW_CHAR:		fprintf(stderr, "AST_KW_CHAR,\n"); break;
		case AST_KW_INT:		fprintf(stderr, "AST_KW_INT,\n"); break;
		case AST_KW_FLOAT: 	fprintf(stderr, "AST_KW_FLOAT,\n"); break;
		case AST_KW_READ:		fprintf(stderr, "AST_KW_READ,\n"); break;
		case AST_KW_RETURN:	fprintf(stderr, "AST_KW_RETURN,\n"); break;
		case AST_KW_PRINT:	fprintf(stderr, "AST_KW_PRINT,\n"); break;
		case AST_KW_WHILE: fprintf(stderr, "AST_KW_WHILE "); break;
		case AST_KW_IF:	fprintf(stderr, "AST_KW_IF,\n"); break;
		case AST_KW_FOR: fprintf(stderr, "AST_KW_FOR,\n"); break;
		case AST_NEW_BLOCK: fprintf(stderr, "AST_NEW_BLOCK,\n"); break;
		case AST_PRINT_ARG: fprintf(stderr, "AST_PRINT_ARG,\n"); break;
		case AST_PARAML: fprintf(stderr, "AST_PARAML,\n"); break;
		case AST_EXP_P: fprintf(stderr, "AST_EXP_P,\n"); break;
		case AST_POINTER_ATRIB: fprintf(stderr, "AST_POINTER_ATRIB,\n"); break;


		default: fprintf(stderr, "UNKNOW"); break;

	}

	for (int i = 0; i < MAX_SONS; ++i) {
		astPrint(node->son[i], level+1);
	}
}

void astGenerateFile(AST *node, FILE *output_file){
	if(node){
		switch(node->type){
			case AST_DEC: astGenerateFile(node->son[0], output_file);
						astGenerateFile(node->son[1], output_file);
						break;
			case AST_VAR_DECL: astGenerateFile(node->son[0], output_file);
						fprintf(output_file,"%s", node->symbol->text);
					  fprintf(output_file, " = ");
					  astGenerateFile(node->son[1], output_file);
					  fprintf(output_file, ";\n");
					  break;
			case AST_POINTER_VAR_DECL: astGenerateFile(node->son[0], output_file);
						fprintf(output_file, "#");
						fprintf(output_file,"%s", node->symbol->text);
					  fprintf(output_file, " = ");
					  astGenerateFile(node->son[1], output_file);
					  fprintf(output_file, ";\n");
					  break;
			case AST_VECTOR_DECL: astGenerateFile(node->son[0], output_file);
					fprintf(output_file, "%s", node->symbol->text);
					fprintf(output_file, "[");
					astGenerateFile(node->son[1], output_file);
					fprintf(output_file, "] : ");
					if(node->son[2] != 0){
						fprintf(output_file, " ");
						astGenerateFile(node->son[2], output_file);
					}
					fprintf(output_file, ";\n");
					break;
			case AST_VECTOR_DECL_EMPTY: astGenerateFile(node->son[0], output_file);
					fprintf(output_file, "%s", node->symbol->text);
					fprintf(output_file, "[");
					astGenerateFile(node->son[1], output_file);
					fprintf(output_file, "]");
					fprintf(output_file, ";\n");
					break;


			case AST_MORE_VALUES: astGenerateFile(node->son[0], output_file);
							if(node->son[1] != 0)
								astGenerateFile(node->son[1], output_file);
					break;
			case AST_LCMD: astGenerateFile(node->son[0], output_file);
							fprintf(output_file, ";\n");
							astGenerateFile(node->son[1], output_file);
					break;
			case AST_SYMBOL:fprintf(output_file, "%s", node->symbol->text);
					if(node->son[0] != 0){
						fprintf(output_file, " ");
						astGenerateFile(node->son[0], output_file);
					}
					break;
			case AST_FUN_DECL: astGenerateFile(node->son[0], output_file);
							fprintf(output_file, "%s(", node->symbol->text);
							astGenerateFile(node->son[1], output_file);
							fprintf(output_file, ")");
							astGenerateFile(node->son[2], output_file);
							fprintf(output_file, "\n");
					break;
			case AST_FUN_PARAML: astGenerateFile(node->son[0]->son[0], output_file);
					fprintf(output_file, " %s", node->son[0]->symbol->text);
					if(node->son[1] != 0)
						astGenerateFile(node->son[1], output_file);
					break;
			case AST_FUN_PARAMREST: fprintf(output_file, ", ");
					astGenerateFile(node->son[0]->son[0], output_file);
					fprintf(output_file, " %s", node->son[0]->symbol->text);
					if(node->son[1] != 0)
						astGenerateFile(node->son[1], output_file);
					break;


			case AST_BLOCK: fprintf(output_file, "{\n");
						astGenerateFile(node->son[0], output_file);
						fprintf(output_file, "\n}\n");
						break;
			case AST_VAR_ATRIB: fprintf(output_file, "%s = ", node->symbol->text);
						astGenerateFile(node->son[0], output_file);
						break;
			case AST_VECTOR_ATRIB: fprintf(output_file, "%s[", node->symbol->text);
						astGenerateFile(node->son[0], output_file);
						fprintf(output_file, "] = ");
						astGenerateFile(node->son[1], output_file);
						break;
			case AST_POINTER_ATRIB: fprintf(output_file, "%s = ", node->symbol->text);
						astGenerateFile(node->son[0], output_file);

						break;
			case AST_ADD: astGenerateFile(node->son[0], output_file);
            fprintf(output_file, " + ");
            astGenerateFile(node->son[1], output_file);
						break;
			case AST_SUB: astGenerateFile(node->son[0], output_file);
            fprintf(output_file, " - ");
            astGenerateFile(node->son[1], output_file);
						break;
			case AST_MUL: astGenerateFile(node->son[0], output_file);
            fprintf(output_file, " * ");
            astGenerateFile(node->son[1], output_file);
						break;
			case AST_DIV: astGenerateFile(node->son[0], output_file);
            fprintf(output_file, " / ");
            astGenerateFile(node->son[1], output_file);
						break;
			case AST_LESS: astGenerateFile(node->son[0], output_file);
            fprintf(output_file, " < ");
            astGenerateFile(node->son[1], output_file);
						break;
      case AST_GREATER: astGenerateFile(node->son[0], output_file);
            fprintf(output_file, " > ");
            astGenerateFile(node->son[1], output_file);
						break;
			case AST_NEG: astGenerateFile(node->son[0], output_file);
            fprintf(output_file, " ! ");
            astGenerateFile(node->son[1], output_file);
						break;
			case AST_LE: astGenerateFile(node->son[0], output_file);
            fprintf(output_file, " <= ");
            astGenerateFile(node->son[1], output_file);
						break;
			case AST_GE: astGenerateFile(node->son[0], output_file);
            fprintf(output_file, " >= ");
            astGenerateFile(node->son[1], output_file);
						break;
      case AST_EQ: astGenerateFile(node->son[0], output_file);
            fprintf(output_file, " == ");
            astGenerateFile(node->son[1], output_file);
            break;
      case AST_NE: astGenerateFile(node->son[0], output_file);
            fprintf(output_file, " != ");
            astGenerateFile(node->son[1], output_file);
            break;
      case AST_AND: astGenerateFile(node->son[0], output_file);
            fprintf(output_file, " && ");
            astGenerateFile(node->son[1], output_file);
            break;
      case AST_OR: astGenerateFile(node->son[0], output_file);
            fprintf(output_file, " || ");
            astGenerateFile(node->son[1], output_file);
            break;
      case AST_ENDER: fprintf(output_file, "&");
            fprintf(output_file, "%s", node->symbol->text);
            break;
      case AST_POINTER: fprintf(output_file, "#");
            fprintf(output_file, "%s", node->symbol->text);
            break;
      case AST_ARRAY_POS: fprintf(output_file, "%s[", node->symbol->text);
            astGenerateFile(node->son[0], output_file);
            fprintf(output_file, "]");
            break;
      case AST_FUNCALL:fprintf(output_file, "%s(", node->symbol->text);
            astGenerateFile(node->son[0], output_file);
            fprintf(output_file, ")");
            break;
      case AST_KW_CHAR: fprintf(output_file, "char "); break;
      case AST_KW_INT: fprintf(output_file, "int "); break;
      case AST_KW_FLOAT: fprintf(output_file, "float "); break;
      case AST_KW_READ: fprintf(output_file, "read ");
						astGenerateFile(node->son[0], output_file);
						break;
      case AST_KW_RETURN: fprintf(output_file, "return ");
						astGenerateFile(node->son[0], output_file);
						break;
      case AST_KW_PRINT: fprintf(output_file, "print ");
						astGenerateFile(node->son[0], output_file);
						break;
      case AST_KW_WHILE: fprintf(output_file, "while ( ");
	          astGenerateFile(node->son[0], output_file);
						fprintf(output_file, ")\n\t");
						astGenerateFile(node->son[1], output_file);
						break;
			case AST_KW_IF: fprintf(output_file, "if (");
						astGenerateFile(node->son[0], output_file);
						fprintf(output_file, ") then\n\t");
						astGenerateFile(node->son[1], output_file);
						fprintf(output_file, "\n");
						if(node->son[2] != 0){
							fprintf(output_file, "else\n\t");
							astGenerateFile(node->son[2], output_file);
						}
					break;
			case AST_KW_FOR:fprintf(output_file, "for (");
					fprintf(output_file, "%s = ", node->symbol->text);
					astGenerateFile(node->son[0], output_file);
					fprintf(output_file, " to ");
					astGenerateFile(node->son[1], output_file);
					fprintf(output_file, " ) ");
					astGenerateFile(node->son[2], output_file);
					break;
			case AST_NEW_BLOCK: astGenerateFile(node->son[0], output_file);
					astGenerateFile(node->son[1], output_file);
					break;
			case AST_PRINT_ARG: astGenerateFile(node->son[0], output_file);
						if(node->son[1] != 0){
							fprintf(output_file, " ");
							astGenerateFile(node->son[1], output_file);
						}
					break;
			case AST_PARAML: astGenerateFile(node->son[0], output_file);
						if(node->son[1] != 0){
							fprintf(output_file, ", ");
							astGenerateFile(node->son[1], output_file);
						}
					break;
			case AST_EXP_P: fprintf(output_file, "( ");
            astGenerateFile(node->son[0], output_file);
            fprintf(output_file, " )");
            break;

			default: fputs("UNKNOWN", output_file); break;
		}
	}
}



//END OF FILE
