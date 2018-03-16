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
				fprintf(stderr, "\nBYTE");
				break;
			case KW_INT:
				fprintf(stderr, "\nSHORT");
				break;
			case KW_FLOAT:
				fprintf(stderr, "\nLONG");
				break;
			case KW_IF:
				fprintf(stderr, "\nFLOAT");
				break;
			case KW_THEN:
				fprintf(stderr, "\nDOUBLE");
				break;
			case KW_ELSE:
				fprintf(stderr, "\nWHEN");
				break;
			case KW_WHILE:
				fprintf(stderr, "\nTHEN");
				break;
			case KW_FOR:
				fprintf(stderr, "\nELSE");
				break;
			case KW_READ:
				fprintf(stderr, "\nWHILE");
				break;
			case KW_RETURN:
				fprintf(stderr, "\nFOR");
				break;
			case KW_PRINT:
				fprintf(stderr, "\nREAD");
				break;
			case OPERATOR_LE:
				fprintf(stderr, "\n(LE) <=");
				break;
			case OPERATOR_GE:
				fprintf(stderr, "\n(GE) >=");
				break;
			case OPERATOR_EQ:
				fprintf(stderr, "\n(EQ) ==");
				break;
			case OPERATOR_NE:
				fprintf(stderr, "\n(NE) !=");
				break;
			case OPERATOR_AND:
				fprintf(stderr, "\n(AND) &&");
				break;
			case OPERATOR_OR:
				fprintf(stderr, "\n(OR) ||");
				break;
      case TK_IDENTIFIER:
          printf("\nIDENTIFIER");
          break;
      case LIT_INTEGER:
          printf("\nINT");
          break;
      case LIT_REAL:
          printf("\nREAL");
          break;
      case LIT_CHAR:
          printf("\nCHAR");
          break;
      case LIT_STRING:
          printf("\nSTRING");
          break;
      case TOKEN_ERROR:
          printf("\nERRO in line %d",getLineNumber());
          break;
      case 0:
          break;
      default:
          printf("\n%c",tok);
          break;
      }

    }

  	printf("\nNumero total de linhas do arquivo: %d\n", getLineNumber());
  	hashPrint();
   	exit(0);
} // END_MAIN
