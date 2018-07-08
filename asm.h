/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 6
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "tac.h"
#include "y.tab.h"

#define NUMBER_OF_STRINGS 30
#define STRING_LENGTH 200
#define MAX_PRINT_ARGS 5

char strings[NUMBER_OF_STRINGS][STRING_LENGTH+1];

int findString(char *stringName);

void asmGenerator(char *filename, TAC* code);
