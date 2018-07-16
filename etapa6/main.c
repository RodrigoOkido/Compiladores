/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 6
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/


#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "hash.h"
#include "semantic.h"
#include "y.tab.h"


extern FILE *yyin;
extern void hashPrint();

int main (int argc, char ** argv) {

  int tok;
  if (argc < 3) {
    fprintf(stderr, "Please insert a file. Use the following format:\n./etapa6 file_name output_filename\n");
    exit(1);
  }

  if ((yyin = fopen(argv[1],"r")) == 0) {
    fprintf(stderr, "File not found or cannot be open %s", argv[1]);
    exit(2);
  }

  if (!(outputfile = fopen(argv[2],"w")))
  {
    fprintf(stderr, "\nSomething wrong to open the outputfile %s. \n", argv[2]);
    exit(2);
  }

  yyparse();

  fclose(outputfile);

  //hashPrint();
  if(semanticError > 0){
    fprintf(stderr,"\nProgram have %d semantic errors. Need recheck... \n", getSemanticErrorsNumber());
    exit(4);
  }


  fprintf(stderr,"\nPrograma compilou corretamente. \n");
  exit(0);
} // END_MAIN
