/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 6
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/


#include "hash.h"
#include "tac.h"
#include "ast.h"
#include <stdio.h>
#include "y.tab.h"

TAC* makePrint(TAC* code0, TAC* code1);
TAC* makeIfThenElse (TAC* code0, TAC* code1, TAC* code2);
TAC* makeFor(TAC* code0, TAC* code1, TAC* code2);
TAC* makeWhile(TAC* code0, TAC* code1);
TAC* makeFun(HASH* funSymbol, TAC* code3);
void updateFuncArgs(TAC* func, HASH* symbol);



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
				case AST_VAR_ATRIB: return tacJoin(code[0],tacCreate(TAC_ASS, node->symbol,code[0]?code[0]->res:0,0));break;
				case AST_POINTER_ATRIB: return tacJoin(code[0],tacCreate(TAC_POINTER_ASS, node->symbol,code[0]?code[0]->res:0,0));break;
				case AST_VECTOR_ATRIB: return tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_VEC_ATRIB, node->symbol, code[1]?code[1]->res:0, code[0]?code[0]->res:0)); break;
				case AST_ARRAY_POS: return tacJoin(code[0], tacCreate(TAC_VEC_INDEX, makeTemp(), node->symbol, code[0]?code[0]->res:0)); break;
				case AST_KW_READ: return tacCreate(TAC_READ, node->symbol, 0, 0); break;
				//case AST_PRINT_ARG: return tacJoin(tacCreate(TAC_PRINT, code[0]?code[0]->res:0, 0, 0), code[1]); break;
				case AST_PRINT_ARG:  return makePrint(code[0], code[1]); break;
				case AST_KW_RETURN: return tacJoin(code[0], tacCreate(TAC_RET, code[0]?code[0]->res:0, 0, 0)); break;
				case AST_KW_IF: return makeIfThenElse(code[0], code[1], code[2]); break;
				case AST_KW_FOR: return makeFor(code[0], code[1], code[2]); break;
				case AST_KW_WHILE: return makeWhile(code[0], code[1]); break;
				case AST_FUN_DECL: return makeFun(node->symbol, code[2]); break;
				case AST_FUNCALL: result = tacJoin(code[0], tacCreate(TAC_FUNCALL, node->symbol, 0, 0)); updateFuncArgs(result, node->symbol); return result; break;
				case AST_PARAML: return tacJoin(tacJoin(code[0], tacCreate(TAC_FUNARG, 0, code[0]?code[0]->res:0, 0)), code[1]); break;
				case AST_VAR_DECL: return tacJoin(code[0], tacCreate(TAC_VARDEC, node->symbol, code[1]?code[1]->res:0, 0)); break;
				case AST_POINTER_VAR_DECL: return tacJoin(code[0], tacCreate(TAC_POINTERDEC, node->symbol, code[1]?code[1]->res:0, 0)); break;
				case AST_VECTOR_DECL: return tacJoin(code[0], tacCreate(TAC_VECDEC, node->symbol, code[1]?code[1]->res:0, 0)); break;
				case AST_VECTOR_DECL_EMPTY: return tacJoin(code[0], tacCreate(TAC_VECDEC, node->symbol, code[1]?code[1]->res:0, 0)); break;
				default: result = tacJoin(tacJoin(tacJoin(code[0], code[1]), code[2]), code[3]); break;
		}

		return result;
}


TAC* makePrint(TAC* code0, TAC* code1){

	if(code0){
			return tacJoin(tacJoin(code0, tacCreate(TAC_PRINT, code0?code0->res:0, 0, 0)), code1);
	}
	return NULL;

}


TAC* makeIfThenElse (TAC* code0, TAC* code1, TAC* code2) {

		TAC* newIfTac = 0;
		TAC* newLabelTac= 0;
		TAC* ElseJmpTac = 0;
		TAC* newLabelElseTac = 0;


		HASH* newLabel = 0;
		HASH* elseLabel = 0;

		newLabel = makeLabel();
		elseLabel = makeLabel();

		newIfTac = tacCreate(TAC_JZ, newLabel, code0?code0->res:0,0);
		ElseJmpTac = tacCreate(TAC_JUMP, elseLabel, code0?code0->res:0,0);

		newLabelTac = tacCreate(TAC_LABEL, newLabel, 0,0);
		newLabelElseTac = tacCreate(TAC_LABEL, elseLabel, 0,0);

		if(code2 == NULL){
			return tacJoin(tacJoin(tacJoin (code0, newIfTac), code1), newLabelTac);
		} else {
			return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin (code0, newIfTac), code1), ElseJmpTac), newLabelTac), code2), newLabelElseTac);
		}
}

TAC* makeFor (TAC* code0, TAC* code1, TAC* code2) {

	TAC* preConditionLabelTac = 0;
	TAC* postBlockLabelTac = 0;
	TAC* JmpTac = 0;
	TAC* JeTac = 0;


	HASH* beginForLabel;
	HASH* endForLabel;

	beginForLabel = makeLabel();
	endForLabel = makeLabel();

	preConditionLabelTac = tacCreate(TAC_LABEL, beginForLabel, 0, 0);
	postBlockLabelTac = tacCreate(TAC_LABEL, endForLabel, 0, 0);
	JmpTac = tacCreate(TAC_JUMP, beginForLabel, 0, 0);
	JeTac = tacCreate(TAC_JE, endForLabel, code2?code2->res:0, 0);

	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(preConditionLabelTac, code0), code1), JeTac), code2), JmpTac), postBlockLabelTac);
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



TAC* makeFun(HASH* funSymbol, TAC* code2){
		TAC* beginFunTac = 0;
		TAC* endFunTac = 0;

		beginFunTac = tacCreate(TAC_FUN_START, funSymbol, 0, 0);
		endFunTac = tacCreate(TAC_FUN_END, funSymbol, 0, 0);

		return tacJoin(tacJoin(beginFunTac, code2), endFunTac);
}



void updateFuncArgs(TAC* func, HASH* symbol){
		TAC* curr_arg;
		curr_arg = func;

		if(!curr_arg) return;

		while(curr_arg->prev != NULL){
			curr_arg = curr_arg->prev;

			if(curr_arg->type == TAC_FUNARG)
				curr_arg->res = symbol;
		}
}



TAC* makeBinOp(int type, TAC* code0, TAC* code1) {

		TAC* newtac = tacCreate(type, makeTemp(), code0?code0->res:0, code1?code1->res:0);
		return tacJoin(code0, tacJoin(code1, newtac));
}


TAC* tacJoin (TAC* l1, TAC* l2) {

		TAC* tac = l2;
		if(!l1) return l2;
		if (!l2) return l1;

		while(tac->prev)
			tac = tac->prev;

		tac->prev = l1;
		return l2;
}


void tacPrintSingle(TAC* tac) {

		if (!tac) return;
		if (tac->type == TAC_SYMBOL) return;
		fprintf(stderr, "  TAC(");
		switch(tac->type) {

				case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL ");	break;
				case TAC_ADD: fprintf(stderr, "TAC_ADD ");	break;
				case TAC_SUB: fprintf(stderr, "TAC_SUB ");	break;
				case TAC_MUL: fprintf(stderr, "TAC_MUL ");	break;
				case TAC_DIV: fprintf(stderr, "TAC_DIV ");	break;
				case TAC_LESS: fprintf(stderr, "TAC_LESS ");	break;
				case TAC_GREATER: fprintf(stderr, "TAC_GREATER ");	break;
				case TAC_NEG: fprintf(stderr, "TAC_NEG ");	break;
				case TAC_LE: fprintf(stderr, "TAC_LE ");	break;
				case TAC_GE: fprintf(stderr, "TAC_GE ");	break;
				case TAC_EQ: fprintf(stderr, "TAC_EQ ");	break;
				case TAC_NE: fprintf(stderr, "TAC_NE ");	break;
				case TAC_AND: fprintf(stderr, "TAC_AND ");	break;
				case TAC_OR: fprintf(stderr, "TAC_OR ");	break;
				case TAC_ASS: fprintf(stderr, "TAC_ASS ");	break;
				case TAC_POINTER_ASS: fprintf(stderr, "TAC_POINTER_ASS  ");	break;
				case TAC_VEC_ATRIB: fprintf(stderr, "TAC_VEC_ATRIB "); break;
				case TAC_VEC_INDEX: fprintf(stderr, "TAC_VEC_INDEX "); break;
				case TAC_READ: fprintf(stderr, "TAC_READ "); break;
				case TAC_PRINT: fprintf(stderr, "TAC_PRINT "); break;
				case TAC_PRINT_ARG: fprintf(stderr, "TAC_PRINT_ARG "); break;
				case TAC_RET: fprintf(stderr, "TAC_RET "); break;
				case TAC_LABEL: fprintf(stderr, "TAC_LABEL "); break;
				case TAC_JZ: fprintf(stderr, "TAC_JZ "); break;
				case TAC_JUMP: fprintf(stderr, "TAC_JUMP "); break;
				case TAC_JE: fprintf(stderr, "TAC_JE "); break;
				case TAC_FUN_START: fprintf(stderr, "TAC_FUN_START "); break;
				case TAC_FUN_END: fprintf(stderr, "TAC_FUN_END "); break;
				case TAC_FUNCALL: fprintf(stderr, "TAC_FUNCALL "); break;
				case TAC_FUNARG: fprintf(stderr, "TAC_FUNARG "); break;
				case TAC_POINTERDEC: fprintf(stderr, "TAC_POINTERDEC "); break;
				case TAC_VARDEC: fprintf(stderr, "TAC_VARDEC "); break;
				case TAC_VECDEC: fprintf(stderr, "TAC_VECDEC "); break;
				default: fprintf(stderr, "UNKNOW ");	break;
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



void tacPrintForward(TAC* first) {
	TAC* tac;
	for(tac = first; tac != NULL; tac = tac->next)
			tacPrintSingle(tac);

}
