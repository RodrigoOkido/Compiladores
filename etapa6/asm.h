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

#define STRING_LENGTH 300
#define STRING_NUMBER 50

#define MAX_PRINT_ARGS 5

char strings[STRING_NUMBER][STRING_LENGTH+1];

int findString(char *stringName);

void asmGenerator(char *filename, TAC* code);
