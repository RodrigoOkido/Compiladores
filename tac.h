/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 5
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/

#ifndef TAC_HEADER
#define TAC_HEADER

#include <stdio.h>
#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL 	1
#define TAC_ADD 	2
#define TAC_SUB 	3
#define TAC_MUL 	4
#define TAC_DIV 	5
#define TAC_ASS 	6
#define TAC_GREATER     7
#define TAC_LESS	8
#define TAC_IFZ		9
#define TAC_LABEL	10

typedef struct tac {

int type;
HASH* res;
HASH* op1;
HASH* op2;
struct tac *prev;
struct tac *next;

} TAC;

TAC* tacCreate(int type, HASH* res, HASH* op1, HASH* op2);

void tacPrintSingle(TAC* tac);

void tacPrintBack(TAC* tac);

TAC* codeGenerator(AST* node);

TAC* tacPrintReverse(TAC* last);

void tacPrintForward(TAC* tac);

TAC* makeIfThen (TAC* code0, TAC* code1);

TAC* makeBinOp(int type, TAC* code0, TAC* code1);

TAC* tacJoin (TAC* l1, TAC* l2);

#endif

