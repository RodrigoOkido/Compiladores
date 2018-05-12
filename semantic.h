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

//Check if the node is an Integer or a Real.
//@return 1 if node is type REAL, 2 if is INT, -1 otherwise.
int checkNodeNumType(AST *node);

//Check all declarations in program.
void set_Declarations(AST* node);

//Check for all, if exists, undeclared identifiers.
void check_id_undeclared();

//Check if operands types are correct.
void check_operands(AST* node);

//Checks if all declarations are in correct use.
//Guarantee if the type is the same of the expression.
void check_declaration_usage(AST* node);

//Check if all index of an vector are Integers.
void check_vectorIndex(AST* node);

//Check the return types.
void check_returnType(AST* node);
