/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 1
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

extern FILE *yyin;

int main (int argc, char ** argv) {

  int tok;
  if (argc < 2) {
    fprintf(stderr, "Please insert a file. Use the following format:\n./etapa1 file_name\n");
    exit(1);
  }

  if ((yyin = fopen(argv[1],"r")) == 0) {
    fprintf(stderr, "File not found or cannot be open %s", argv[1]);
    exit(2);
  }

  while (isRunning()) {

    tok = yylex();
    switch(tok){
      case KW_CHAR:
				fprintf(stderr, "CHAR\n");
				break;
			case KW_INT:
				fprintf(stderr, "INT\n");
				break;
			case KW_FLOAT:
				fprintf(stderr, "FLOAT\n");
				break;
			case KW_IF:
				fprintf(stderr, "IF\n");
				break;
			case KW_THEN:
				fprintf(stderr, "THEN\n");
				break;
			case KW_ELSE:
				fprintf(stderr, "ELSE\n");
				break;
			case KW_WHILE:
				fprintf(stderr, "WHILE\n");
				break;
			case KW_FOR:
				fprintf(stderr, "FOR\n");
				break;
			case KW_READ:
				fprintf(stderr, "READ\n");
				break;
			case KW_RETURN:
				fprintf(stderr, "RETURN\n");
				break;
			case KW_PRINT:
				fprintf(stderr, "PRINT\n");
				break;
			case OPERATOR_LE:
				fprintf(stderr, "(LE) <=\n");
				break;
			case OPERATOR_GE:
				fprintf(stderr, "(GE) >=\n");
				break;
			case OPERATOR_EQ:
				fprintf(stderr, "(EQ) ==\n");
				break;
			case OPERATOR_NE:
				fprintf(stderr, "(NE) !=\n");
				break;
			case OPERATOR_AND:
				fprintf(stderr, "(AND) &&\n");
				break;
			case OPERATOR_OR:
				fprintf(stderr, "(OR) ||\n");
				break;
      case TK_IDENTIFIER:
          printf("IDENTIFIER\n");
          break;
      case LIT_INTEGER:
          printf("INT\n");
          break;
      case LIT_REAL:
          printf("REAL\n");
          break;
      case LIT_CHAR:
          printf("CHAR\n");
          break;
      case LIT_STRING:
          printf("STRING\n");
          break;
      case TOKEN_ERROR:
          printf("ERRO in line %d\n",getLineNumber());
          break;
      case 0:
          break;
      default:
          printf("%c\n",tok);
          break;
      }

    }

  	printf("\nNumero total de linhas do arquivo: %d\n", getLineNumber());
  	hashPrint();
   	exit(0);
} // END_MAIN
