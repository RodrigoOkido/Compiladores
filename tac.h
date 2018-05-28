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
#define TAC_LESS 7
#define TAC_GREATER 8
#define TAC_NEG 9
#define TAC_LE 10
#define TAC_GE 11
#define TAC_EQ 12
#define TAC_NE 13
#define TAC_AND 14
#define TAC_OR 15
#define TAC_IFZ		16
#define TAC_LABEL	17

typedef struct tac {

int type;
HASH* res;
HASH* op1;
HASH* op2;
struct tac *prev;
struct tac *next;

} TAC;


//Function tacCreate.
TAC* tacCreate(int type, HASH* res, HASH* op1, HASH* op2);

//Function codeGenerator.
TAC* codeGenerator(AST* node);

//Function makeIfThen.
TAC* makeIfThen (TAC* code0, TAC* code1);

//Function makeBinOp.
TAC* makeBinOp(int type, TAC* code0, TAC* code1);

//Function tacJoin.
TAC* tacJoin (TAC* l1, TAC* l2);

//Function tacPrintSingle.
void tacPrintSingle(TAC* tac);

//Function tacPrintBack.
void tacPrintBack(TAC* tac);

//Function tacPrintReverse.
TAC* tacPrintReverse(TAC* last);

//Function tacPrintForward.
void tacPrintForward(TAC* tac);

#endif
