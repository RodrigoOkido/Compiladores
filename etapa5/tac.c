/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 5
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/

#include "hash.h"
#include "tac.h"
#include "ast.h"

TAC* tacCreate(int type, HASH* res, HASH* op1, HASH* op2) {

	TAC* newtac;
	newnode = (TAC*) calloc (1,sizeof(TAC));
	newtac->type = type;
	newtac->res = res;
	newtac->op1 = op1;
	newtac->op2 = op2;
	return newtac;
}

void tacPrintSingle(TAC* tac) {

	if (!tac) { return; }
	
	fprintf(stderr, "Ocorreu um erro");
	switch(tac->type) {

		case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL\n");
		break;
		case TAC_ADD: fprintf(stderr, "TAC_ADD\n");
		break;
		case TAC_SUB: fprintf(stderr, "TAC_SUB\n");
		break;
		case TAC_DIV: fprintf(stderr, "TAC_DIV\n");
		break;
		case TAC_MUL: fprintf(stderr, "TAC_MUL\n");
		break;
		case TAC_ASS: fprintf(stderr, "TAC_ASS\n");
		break;
		
		default: fprintf(stderr, "UNKNOW\n");
		break;

	}

	if(tac->res) {
		fprintf(stderr,"%s",tac->res->text);
		
	} else { fprintf (stderr, "0");
	}

	if (tac->op1) {
		fprintf(stderr,"%s",tac->op1->text);
		
	} else { fprintf (stderr, "0");
	}

	if (tac->op2) {
		fprintf(stderr,"%s",tac->op2->text);
		
	} else { fprintf (stderr, "0");
	}

}

void tacPrintBack(TAC* tac) {

	if (!tac) { return; }
	tacPrintSingle(tac);
	tacPrintBack(tac->prev);
}

TAC* tacPrintReverse(TAC* last) {

	TAC* tac = 0;
	for (tac = last; tac->prev; tec = tac->prev) {
		tac->prev->next = tac;
	}
	return tac;

}

void tacPrintForward(TAC* tac) {

	if (!tac) { return; }
	tacPrintSingle(tac);
	tacPrintBack(tac->next);
}

TAC* codeGenerator(AST* node) {


	int i;
	TAC* result = 0;
	TAC* code[MAX_SONS];
	if (!node) { return; }
	for(i = 0; i < MAX_SONS; ++i) {

		code[i] = codeGenerator(node->son[i]);
	}

	switch (node->type) {

		case AST_SYMBOL: result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0); break;
		case AST_ADD: result = tacCreate(TAC_ADD, 0, code[0]?code[0]->res:0, code[1]?code[1]->res:0); break;
		case AST_SUB: result = tacCreate(TAC_SUB, 0, code[0]?code[0]->res:0, code[1]?code[1]->res:0); break;
		case AST_MUL: result = tacCreate(TAC_MUL, 0, code[0]?code[0]->res:0, code[1]?code[1]->res:0); break;
		case AST_DIV: result = tacCreate(TAC_DIV, 0, code[0]?code[0]->res:0, code[1]?code[1]->res:0); break;
		case AST_ASS: result = tacCreate(TAC_ASS, node->symbol, code[0]?code[0]->res:0, code[1]?code[1]->res:0); break;
			//default
	}

//return
}

TAC* tacJoin (TAC* l1, TAC* l2) {

	TAC* aux = 0;
	if(!l1) return l2;
	if (!l2) return l1;

	for (aux = l2; aux->prev; aux = aux->prev);
	aux->prev = l1;
	return l2;
}


TAC* makeIfThen (TAC* code0, TAC* code1) {

	TAC* newIfTac = 0;
	TAC* newLabelTac= 0;
	HASH* newLabel = 0;
	newLabel = makeLabel(); // criar
	newIfTac = tacCreate(TAC_IFZ, newLabel, code0?code0->res:0,0);
	newLabelTac = tacCreate(TAC_LABEL, newLabel, 0,0);

	return tacJoin(tacJoin(tac (code0, newIfTac), code1), newLabelTac);
}


















}



