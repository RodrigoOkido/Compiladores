/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 5
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/

#include "hash.h"
#include "tac.h"
#include "ast.h"
#include <stdio.h>

TAC* tacCreate(int type, HASH* res, HASH* op1, HASH* op2) {

		TAC* newtac;
		newtac= (TAC*) calloc (1,sizeof(TAC));
		newtac->type = type;
		newtac->res = res;
		newtac->op1 = op1;
		newtac->op2 = op2;
		newtac->prev = 0;
		newtac->next = 0;
		return newtac;
}


TAC* codeGenerator(AST* node) {

		int i;
		TAC* result = 0;
		TAC* code[MAX_SONS];
		if (!node) return 0;
		for(i = 0; i < MAX_SONS; ++i) {

			code[i] = codeGenerator(node->son[i]);
		}

		switch (node->type) {

			case AST_SYMBOL: result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0); break;
			case AST_ADD: result = makeBinOp (TAC_ADD, code[0], code[1]); break;
			case AST_SUB: result = makeBinOp (TAC_SUB, code[0], code[1]); break;
			case AST_MUL: result = makeBinOp (TAC_MUL, code[0], code[1]); break;
			case AST_DIV: result = makeBinOp (TAC_DIV, code[0], code[1]); break;
			case AST_ASS: result = makeBinOp (TAC_ASS, code[0], code[1]); break;
			case AST_LESS: result = makeBinOp (TAC_LESS, code[0], code[1]); break;
			case AST_GREATER: result = makeBinOp (TAC_GREATER, code[0], code[1]); break;
			case AST_NEG: result = makeBinOp (TAC_NEG, code[0], code[1]); break;
			case AST_LE: result = makeBinOp (TAC_LE, code[0], code[1]); break;
			case AST_GE: result = makeBinOp (TAC_GE, code[0], code[1]); break;
			case AST_EQ: result = makeBinOp (TAC_EQ, code[0], code[1]); break;
			case AST_NE: result = makeBinOp (TAC_NE, code[0], code[1]); break;
			case AST_AND: result = makeBinOp (TAC_AND, code[0], code[1]); break;
			case AST_OR: result = makeBinOp (TAC_OR, code[0], code[1]); break;
			case AST_VAR_ATRIB: result = tacJoin(code[0],tacCreate(TAC_ASS, node->symbol,code[0]?code[0]->res:0,0));break;
			case AST_KW_READ: result = makeBinOp (TAC_READ, code[0], code[1]); break;
			case AST_PRINT_ARG: result = makeBinOp (TAC_PRINT, code[0], code[1]); break;
			case AST_KW_RETURN: result = makeBinOp (TAC_RET, code[0], code[1]); break;
			case AST_KW_IF: return makeIfThen(code[0], code[1]); break;
			case AST_KW_WHILE: return makeWhile(code[0], code[1]); break;

			default: result = tacJoin(tacJoin(tacJoin(code[0], code[1]), code[2]), code[3]); break;

		}

		return result;
}



TAC* makeIfThen (TAC* code0, TAC* code1) {

		TAC* newIfTac = 0;
		TAC* newLabelTac= 0;
		HASH* newLabel = 0;
		newLabel = makeLabel();

		newIfTac = tacCreate(TAC_IFZ, newLabel, code0?code0->res:0,0);
		newLabelTac = tacCreate(TAC_LABEL, newLabel, 0,0);

		return tacJoin(tacJoin(tacJoin (code0, newIfTac), code1), newLabelTac);
}


TAC* makeWhile(TAC* code0, TAC* code1){
	TAC* preConditionLabelTac = 0;
	TAC* postBlockLabelTac = 0;
	TAC* JmpTac = 0;
	TAC* JzTac = 0;


	HASH* newPreConditionLabel;
	HASH* newPostBlockLabel;

	newPreConditionLabel = makeLabel();
	newPostBlockLabel = makeLabel();

	preConditionLabelTac = tacCreate(TAC_LABEL, newPreConditionLabel, 0, 0);
	postBlockLabelTac = tacCreate(TAC_LABEL, newPostBlockLabel, 0, 0);
	JmpTac = tacCreate(TAC_JUMP, newPreConditionLabel, 0, 0);
	JzTac = tacCreate(TAC_JZ, newPostBlockLabel, code0?code0->res:0, 0);

	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(preConditionLabelTac, code0), JzTac), code1), JmpTac), postBlockLabelTac);
}


TAC* makeBinOp(int type, TAC* code0, TAC* code1) {

		TAC* newtac = tacCreate(type, makeTemp(), code0?code0->res:0, code1?code1->res:0);
		return tacJoin(code0, tacJoin(code1, newtac));
}


TAC* tacJoin (TAC* l1, TAC* l2) {

		TAC* aux = 0;
		if(!l1) return l2;
		if (!l2) return l1;

		for (aux = l2; aux->prev; aux = aux->prev) {
			aux->prev = l1;
		}
		return l2;
}


void tacPrintSingle(TAC* tac) {

		if (!tac) return;
		if (tac->type == TAC_SYMBOL) return;
		fprintf(stderr, "TAC(");
		switch(tac->type) {

			case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL\n");	break;
			case TAC_ADD: fprintf(stderr, "TAC_ADD\n");	break;
			case TAC_SUB: fprintf(stderr, "TAC_SUB\n");	break;
			case TAC_MUL: fprintf(stderr, "TAC_MUL\n");	break;
			case TAC_DIV: fprintf(stderr, "TAC_DIV\n");	break;
			case TAC_LESS: fprintf(stderr, "TAC_LESS\n");	break;
			case TAC_GREATER: fprintf(stderr, "TAC_GREATER\n");	break;
			case TAC_NEG: fprintf(stderr, "TAC_NEG\n");	break;
			case TAC_LE: fprintf(stderr, "TAC_LE\n");	break;
			case TAC_GE: fprintf(stderr, "TAC_GE\n");	break;
			case TAC_EQ: fprintf(stderr, "TAC_EQ\n");	break;
			case TAC_NE: fprintf(stderr, "TAC_NE\n");	break;
			case TAC_AND: fprintf(stderr, "TAC_AND\n");	break;
			case TAC_OR: fprintf(stderr, "TAC_OR\n");	break;
			case TAC_ASS: fprintf(stderr, "TAC_ASS\n");	break;
			case TAC_READ: fprintf(stderr, "TAC_READ\n"); break;
			case TAC_PRINT: fprintf(stderr, "TAC_PRINT\n"); break;
			case TAC_RET: fprintf(stderr, "TAC_RET\n"); break;
			case TAC_LABEL: fprintf(stderr, "TAC_LABEL\n"); break;
			case TAC_JZ: fprintf(stderr, "TAC_JZ\n"); break;
			case TAC_JUMP: fprintf(stderr, "TAC_JUMP\n"); break;
			default: fprintf(stderr, "UNKNOW\n");	break;

		}

		if(tac->res) {
			fprintf(stderr,"%s",tac->res->text);

		} else {
			fprintf (stderr, "0");
		}

		if (tac->op1) {
			fprintf(stderr,"%s",tac->op1->text);
		} else {
			fprintf (stderr, "0");
		}

		if (tac->op2) {
			fprintf(stderr,"%s",tac->op2->text);

		} else {
			fprintf (stderr, "0");
			fprintf(stderr,")\n");
		}
}

void tacPrintBack(TAC* tac) {

		if (!tac) return;
		tacPrintSingle(tac);
		tacPrintBack(tac->prev);
}

TAC* tacPrintReverse(TAC* last) {

		TAC* tac = 0;
		for (tac = last; tac->prev; tac = tac->prev) {
			tac->prev->next = tac;
		}
		return tac;
}

void tacPrintForward(TAC* tac) {

		if (!tac) return;
		tacPrintSingle(tac);
		tacPrintBack(tac->next);
}
