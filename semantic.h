/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 4
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/


#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "ast.h"
#include "y.tab.h"


//Variable which will increment at each semantic error.
extern int semanticError;

//Return the number of semantic errors.
int getSemanticErrorsNumber();

//Check if the node is an Integer.
int isNodeInt(AST *node);

//Check if the node is an Real.
int isNodeReal(AST *node);

//Check all declarations in program.
void set_Declarations(AST* node);

//Check for all, if exists, undeclared identifiers.
void check_id_undeclared();

//Check if operands types are correct.
void check_operands(AST* node);

//Check if all index of an vector are Integers.
void check_vectorIndex(AST* node);

//Check the return types.
void check_returnType(AST* node);
