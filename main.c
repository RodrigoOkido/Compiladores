/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 2
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/

#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "y.tab.h"

extern FILE *yyin;
extern void hashPrint();

int main (int argc, char ** argv) {

  int tok;
  if (argc < 2) {
    fprintf(stderr, "Please insert a file. Use the following format:\n./etapa2 file_name\n");
    exit(1);
  }

  if ((yyin = fopen(argv[1],"r")) == 0) {
    fprintf(stderr, "File not found or cannot be open %s", argv[1]);
    exit(2);
  }


  yyparse();
  //hashPrint();

  fprintf(stderr,"Programa compilou corretamente. \n");
  exit(0);
} // END_MAIN
