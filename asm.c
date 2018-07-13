/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 6
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/


#include <string.h>
#include "asm.h"

int findString(char *stringName){
    int i, found = 0;

    for(i = 0; i < STRING_NUMBER; i++){
        if(strcmp(strings[i],stringName) == 0)
            return i;
    }

    return STRING_NUMBER + 1;
}

void fprint_print_argument(FILE *fout, TAC *arg_tac, int print_arg_count){
  switch (print_arg_count) {
    case 1: if(arg_tac->res->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%esi\n",arg_tac->res->text);
            else fprintf(fout,"\tmovl	%s(%%rip), %%esi\n", arg_tac->res->text);
            break;
    case 2: if(arg_tac->res->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%r8d\n",arg_tac->res->text);
            else fprintf(fout,"\tmovl	%s(%%rip), %%r8d\n", arg_tac->res->text);
            break;
    case 3: if(arg_tac->res->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%r9d\n",arg_tac->res->text);
            else fprintf(fout,"\tmovl	%s(%%rip), %%r9d\n", arg_tac->res->text);
            break;
    case 4: if(arg_tac->res->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edi\n",arg_tac->res->text);
            else fprintf(fout,"\tmovl	%s(%%rip), %%edi\n", arg_tac->res->text);
            break;
    case 5: if(arg_tac->res->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",arg_tac->res->text);
            else fprintf(fout,"\tmovl	%s(%%rip), %%eax\n", arg_tac->res->text);
            break;
    default: break;
  }

}

void asmGenerator(char *filename, TAC* code){
  TAC *tac =code;
  FILE *fout;

  if(!(fout = fopen(filename, "w")))
  {
    fprintf(stderr,"Cant open output file to write asm!\n");
    exit(5);
  }

  //print all values in HASH TABLE
  fprintf(fout,".data\n");
  int str_count = 0;
  int i;
  HASH *n;
  for (i=0; i< HASH_SIZE; i++)
  {
     for (n=table[i]; n; n=n->next)
     {
          if(n->type == SYMBOL_SCALAR)
            fprintf(fout,".comm %s,4,4\n",n->text);
          if(n->type == SYMBOL_LIT_STRING){
            fprintf(fout,"\nlit_string%d:\n"
                          "\t.string %s\n\n", str_count, n->text);
            strcpy(strings[str_count], n->text);
            str_count++;
          }
     }
  }

  // //to print integers directly
  fprintf(fout,"\nstring_integer:\n\t.string \"%%d\"");

  //print arguments TACs
  int print_arg_count = 0;
  //print TACs
  str_count = 0;
  for (tac=code; tac ; tac=tac->next){
    switch(tac->type){
      case TAC_ADD: fprintf(fout,"\n### CMD ADD ###\n");
					if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %s(%%rip)\n",tac->op1->text, tac->res->text);
                    else fprintf(fout,"\tmovl %s(%%rip), %%edx\n", tac->op1->text);
                    if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %%eax\n",tac->op2->text);
                    else fprintf(fout, "\tmovl %s(%%rip), %%eax\n", tac->op2->text);
                    fprintf(fout, "\taddl %%edx, %%eax\n"
                                  "\tmovl %%eax, %s(%%rip)\n", tac->res->text);
                    break;
	  case TAC_SUB: fprintf(fout,"\n### CMD SUB ###\n");
					if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %s(%%rip)\n",tac->op1->text, tac->res->text);
                    else fprintf(fout,"\tmovl %s(%%rip), %%edx\n", tac->op1->text);
                    if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %%eax\n",tac->op2->text);
                    else fprintf(fout, "\tmovl %s(%%rip), %%eax\n", tac->op2->text);
                    fprintf(fout, "\tsubl %%eax, %%edx\n"
                                  "\tmovl %%edx, %s(%%rip)\n", tac->res->text);
                    break;
      case TAC_MUL: fprintf(fout,"\n### CMD MUL ###\n");
					if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %s(%%rip)\n",tac->op1->text, tac->res->text);
                    else fprintf(fout,"\tmovl %s(%%rip), %%edx\n", tac->op1->text);
                    if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %%eax\n",tac->op2->text);
                    else fprintf(fout, "\tmovl %s(%%rip), %%eax\n", tac->op2->text);
                    fprintf(fout, "\timull %%edx, %%eax\n"
                                  "\tmovl %%eax, %s(%%rip)\n", tac->res->text);
                    break;
	  case TAC_DIV: fprintf(fout,"\n### CMD DIV ###\n");
					if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"\n\tmovl	$%s, %s(%%rip)\n",tac->op1->text, tac->res->text);
                    else fprintf(fout,"\n\tmovl %s(%%rip), %%eax\n", tac->op1->text);
                    if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %%ecx\n",tac->op2->text);
                    else fprintf(fout, "\tmovl %s(%%rip), %%ecx\n", tac->op2->text);
                    fprintf(fout, "\tcltd\n"
								  "\tidivl	%%ecx\n"
                                  "\tmovl %%eax, %s(%%rip)\n", tac->res->text);
                    break;
	  case TAC_EQ:fprintf(fout,"\n### CMD EQ ###\n");
				  if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %%edx\n",tac->op1->text);
                  else fprintf(fout,"\tmovl %s(%%rip), %%edx\n", tac->op1->text);
                  if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %%eax\n",tac->op2->text);
                  else fprintf(fout, "\tmovl %s(%%rip), %%eax\n", tac->op2->text);
				  fprintf(fout, "\tcmpl %%eax, %%edx\n"
								"\tjne");
				  break;
	  case TAC_LESS:fprintf(fout,"\n### CMD LESS ###\n");
				  if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %%edx\n",tac->op1->text);
                  else fprintf(fout,"\tmovl %s(%%rip), %%edx\n", tac->op1->text);
                  if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %%eax\n",tac->op2->text);
                  else fprintf(fout, "\tmovl %s(%%rip), %%eax\n", tac->op2->text);
				  fprintf(fout, "\tcmpl %%eax, %%edx\n"
								"\tjge");
				  break;
	  case TAC_GREATER:fprintf(fout,"\n### CMD GREATER ###\n");
				  if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %%edx\n",tac->op1->text);
                  else fprintf(fout,"\tmovl %s(%%rip), %%edx\n", tac->op1->text);
                  if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %%eax\n",tac->op2->text);
                  else fprintf(fout, "\tmovl %s(%%rip), %%eax\n", tac->op2->text);
				  fprintf(fout, "\tcmpl %%eax, %%edx\n"
								"\tjle");
				  break;
	  case TAC_LE:fprintf(fout,"\n### CMD LE ###\n");
				  if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %%edx\n",tac->op1->text);
                  else fprintf(fout,"\tmovl %s(%%rip), %%edx\n", tac->op1->text);
                  if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %%eax\n",tac->op2->text);
                  else fprintf(fout, "\tmovl %s(%%rip), %%eax\n", tac->op2->text);
				  fprintf(fout, "\tcmpl %%eax, %%edx\n"
								"\tjg");
				  break;
      case TAC_GE:fprintf(fout,"\n### CMD GE ###\n");
				  if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %%edx\n",tac->op1->text);
                  else fprintf(fout,"\tmovl %s(%%rip), %%edx\n", tac->op1->text);
                  if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %%eax\n",tac->op2->text);
                  else fprintf(fout, "\tmovl %s(%%rip), %%eax\n", tac->op2->text);
				  fprintf(fout, "\tcmpl %%eax, %%edx\n"
								"\tjl");
				  break;
	  case TAC_NE:fprintf(fout,"\n### CMD NE ###\n");
				  if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %%edx\n",tac->op1->text);
                  else fprintf(fout,"\tmovl %s(%%rip), %%edx\n", tac->op1->text);
                  if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %%eax\n",tac->op2->text);
                  else fprintf(fout, "\tmovl %s(%%rip), %%eax\n", tac->op2->text);
				  fprintf(fout, "\tcmpl %%eax, %%edx\n"
								"\tje");
				  break;

    case TAC_ASS: fprintf(fout,"\n### CMD ASS ###\n");
      					if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %s(%%rip)\n",tac->op1->text, tac->res->text);
                          else fprintf(fout,"\tmovl	%s(%%rip), %%eax\n"
                                            "\tmovl %%eax, %s(%%rip)\n", tac->op1->text, tac->res->text);
                          break;
    case TAC_VEC_ATRIB: fprintf(fout,"\n### CMD VEC ATRIB ###\n");
      					if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %s+%d(%%rip)\n",tac->op1->text, tac->res->text, atoi(tac->op2->text) * 4);
                          else fprintf(fout,"\tmovl	%s(%%rip), %%eax\n"
                                            "\tmovl	%%eax, %s+20(%%rip)\n", tac->op1->text, tac->res->text);
                          break;
    case TAC_VEC_INDEX: fprintf(fout,"\n### CMD VEC_INDEX ###\n");
      						fprintf(fout,"\tmovl	%s+%d(%%rip), %%eax\n"
      									 "\tmovl	%%eax, %s(%%rip)\n", tac->op1->text, atoi(tac->op2->text) * 4, tac->res->text );
                          break;

    case TAC_RET:fprintf(fout,"\n### CMD RETURN ###\n");
					if(tac->res->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %%eax\n", tac->res->text);
                    else fprintf(fout,"\tmovl	%s(%%rip), %%eax\n", tac->res->text);
					break;
    case TAC_JZ: fprintf(fout, "\t .%s\n", tac->res->text); //Sendo utilizado apenas para escrever o label
				  break;
	  case TAC_JUMP: fprintf(fout, "\tjmp .%s\n", tac->res->text);
				  break;
	  case TAC_LABEL: fprintf(fout, "\t\n.%s:\n", tac->res->text);
				  break;
    case TAC_FUN_START: fprintf(fout,"\n.text\n"
      	                              ".globl	%s\n"
      	                              ".type	%s, @function\n"
                                      "%s:\n"
                                      "\n.cfi_startproc\n"
      	                              "\tpushq %%rbp\n"
                                      // "\t.cfi_def_cfa_offset 16\n"
                                      // "\t.cfi_offset 6, -16\n"
      	                              "\tmovq	%%rsp, %%rbp\n", tac->res->text, tac->res->text, tac->res->text);
                                      //"\t.cfi_def_cfa_register 6\n"
                    break;
    case TAC_FUN_END:fprintf(fout,  "\tpopq	%%rbp\n"
                                    // "\t.cfi_def_cfa 7, 8\n"
    	                             "\tret\n"
                                    "\t.cfi_endproc\n");
                    break;
	  case TAC_FUNCALL: fprintf(fout,"\n### CMD CALL FUNCTION ### \n"
								  "\tmovl	$0, %%eax\n"
								  "\tcall %s\n"
								  "\tmovl %%eax, %s(%%rip)\n", tac->op1->text, tac->res->text);
					          break;
    case TAC_PRINT_ARG: fprintf(fout,"\n### CMD PRINT ARG ###\n");
                    //fprint_print_argument(fout, tac, ++print_arg_count);
                    if(tac->res->type == SYMBOL_LIT_INT) fprintf(fout,"\tmovl	$%s, %%esi\n",tac->res->text);
                    else fprintf(fout,"\tmovl	%s(%%rip), %%esi\n", tac->res->text);
                    fprintf(fout,"\tmovl	$string_integer, %%edi\n"
                                  "\tmovl	$0, %%eax\n"
                              	 "\tcall	printf\n");
                    break;
    case TAC_PRINT:
                    fprintf(fout,"## cmd PRINT\n");
                    fprintf(fout,"\tmovl	$lit_string%d, %%edi\n"
                                 "\tmovl $0, %%eax\n"
                              	 "\tcall	printf\n", findString(tac->res->text));
                    break;
    case TAC_VARDEC: fprintf(fout,"\n.globl	%s\n"
                                  "\t.align 4\n"
                                  "\t.type	%s, @object\n"
                                  "\t.size	%s, 4\n"
                                  "%s:\n"
                                  "\t.long	%s\n", tac->res->text, tac->res->text, tac->res->text, tac->res->text, tac->op1->text);
                  break;
    case TAC_VECDEC: fprintf(fout,"\n.globl	%s\n"
                                  ".align 32\n"
                                  ".type	%s, @object\n"
                                  ".size	%s, %d\n"
                                  "%s:\n"
                                  "\t.long	%s\n", tac->res->text, tac->res->text, tac->res->text, atoi(tac->op1->text) * 4, tac->res->text, tac->op1->text);

                  break;

    }
  }

  fclose(fout);
}
