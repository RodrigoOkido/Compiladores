/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 5
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/

#include "hash.h"

#define TAC_SYMBOL 	1
#define TAC_ADD 	2
#define TAC_SUB 	3
#define TAC_MUL 	4
#define TAC_DIV 	5
#define TAC_ASS 	6

struct tac {

int type;
HASH *res;
HASH *op1;
HASH *op2;
struct tac *prev;
struct tac *next;

} TAC;

TAC* tacCreate(int type, HASH* res, HASH* op1, HASH* op2);

void tacPrintSingle(TAC* tac);

void tacPrintBack(TAC* tac);

TAC* codeGenerator(AST* node);

TAC* tacPrintReverse(TAC* last);

void tacPrintForward(TAC* tac);

