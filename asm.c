/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 6
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/


#include <string.h>
#include "asm.h"

int findString(char *stringName){
    int i, found = 0;

    for(i = 0; i < NUMBER_OF_STRINGS; i++){
        if(strcmp(strings[i],stringName) == 0)
            return i;
    }

    return NUMBER_OF_STRINGS + 1;
}

void fprint_print_argument(FILE *fout, TAC *arg_tac, int print_arg_count){
  switch (print_arg_count) {
    case 1: if(arg_tac->res->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%esi\n",arg_tac->res->text);
            else fprintf(fout,"movl	%s(%%rip), %%esi\n", arg_tac->res->text);
            break;
    case 2: if(arg_tac->res->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%r8d\n",arg_tac->res->text);
            else fprintf(fout,"movl	%s(%%rip), %%r8d\n", arg_tac->res->text);
            break;
    case 3: if(arg_tac->res->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%r9d\n",arg_tac->res->text);
            else fprintf(fout,"movl	%s(%%rip), %%r9d\n", arg_tac->res->text);
            break;
    case 4: if(arg_tac->res->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edi\n",arg_tac->res->text);
            else fprintf(fout,"movl	%s(%%rip), %%edi\n", arg_tac->res->text);
            break;
    case 5: if(arg_tac->res->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",arg_tac->res->text);
            else fprintf(fout,"movl	%s(%%rip), %%eax\n", arg_tac->res->text);
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
  // fprintf(fout,"\nstring_integer:\n\t.string \"%%d\"");

  //print arguments TACs
  int print_arg_count = 0;
  //print TACs
  str_count = 0;
  for (tac=code; tac ; tac=tac->next){
    switch(tac->type){
      case TAC_VARDEC: fprintf(fout,"\n.globl	%s\n"
                                    ".align 4\n"
                                    ".type	%s, @object\n"
                                    ".size	%s, 4\n"
                                    "%s:\n"
                                    "\t.long	%s\n", tac->res->text, tac->res->text, tac->res->text, tac->res->text, tac->op1->text);
                    break;
	  case TAC_VECDEC: fprintf(fout,"\n.globl	%s\n"
                                    ".align 32\n"
                                    ".type	%s, @object\n"
                                    ".size	%d, 4\n"
                                    "%s:\n"
                                    "\t.long	%s\n", tac->res->text, tac->res->text, atoi(tac->op1->text) * 4, tac->res->text, tac->op1->text);

                    break;

      case TAC_ADD: fprintf(fout,"\n### CMD ADD ###\n");
					if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edx\n",tac->op1->text);
                    else fprintf(fout,"movl %s(%%rip), %%edx\n", tac->op1->text);
                    if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                    else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
                    fprintf(fout, "addl %%edx, %%eax\n"
                                  "movl %%eax, %s(%%rip)\n", tac->res->text);
                    break;
	  case TAC_SUB: fprintf(fout,"\n### CMD SUB ###\n");
					if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edx\n",tac->op1->text);
                    else fprintf(fout,"movl %s(%%rip), %%edx\n", tac->op1->text);
                    if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                    else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
                    fprintf(fout, "subl %%eax, %%edx\n"
                                  "movl %%edx, %s(%%rip)\n", tac->res->text);
                    break;
      case TAC_MUL: fprintf(fout,"\n### CMD MUL ###\n");
					if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edx\n",tac->op1->text);
                    else fprintf(fout,"movl %s(%%rip), %%edx\n", tac->op1->text);
                    if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                    else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
                    fprintf(fout, "imull %%edx, %%eax\n"
                                  "movl %%eax, %s(%%rip)\n", tac->res->text);
                    break;
	  case TAC_DIV: fprintf(fout,"\n### CMD DIV ###\n");
					if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"\nmovl	$%s, %%eax\n",tac->op1->text);
                    else fprintf(fout,"\nmovl %s(%%rip), %%eax\n", tac->op1->text);
                    if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%ecx\n",tac->op2->text);
                    else fprintf(fout, "movl %s(%%rip), %%ecx\n", tac->op2->text);
                    fprintf(fout, "cltd\n"
								  "idivl	%%ecx\n"
                                  "movl %%eax, %s(%%rip)\n", tac->res->text);
                    break;
	  case TAC_EQ:fprintf(fout,"\n### CMD EQ ###\n");
				  if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edx\n",tac->op1->text);
                  else fprintf(fout,"movl %s(%%rip), %%edx\n", tac->op1->text);
                  if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                  else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
				  fprintf(fout, "cmpl %%eax, %%edx\n"
								"jne");
				  break;
	  case TAC_LESS:fprintf(fout,"\n### CMD LESS ###\n");
				  if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edx\n",tac->op1->text);
                  else fprintf(fout,"movl %s(%%rip), %%edx\n", tac->op1->text);
                  if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                  else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
				  fprintf(fout, "cmpl %%eax, %%edx\n"
								"jge");
				  break;
	  case TAC_GREATER:fprintf(fout,"\n### CMD GREATER ###\n");
				  if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edx\n",tac->op1->text);
                  else fprintf(fout,"movl %s(%%rip), %%edx\n", tac->op1->text);
                  if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                  else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
				  fprintf(fout, "cmpl %%eax, %%edx\n"
								"jle");
				  break;
	  case TAC_LE:fprintf(fout,"\n### CMD LE ###\n");
				  if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edx\n",tac->op1->text);
                  else fprintf(fout,"movl %s(%%rip), %%edx\n", tac->op1->text);
                  if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                  else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
				  fprintf(fout, "cmpl %%eax, %%edx\n"
								"jg");
				  break;
      case TAC_GE:fprintf(fout,"\n### CMD GE ###\n");
				  if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edx\n",tac->op1->text);
                  else fprintf(fout,"movl %s(%%rip), %%edx\n", tac->op1->text);
                  if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                  else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
				  fprintf(fout, "cmpl %%eax, %%edx\n"
								"jl");
				  break;
	  case TAC_NE:fprintf(fout,"\n### CMD NE ###\n");
				  if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edx\n",tac->op1->text);
                  else fprintf(fout,"movl %s(%%rip), %%edx\n", tac->op1->text);
                  if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                  else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
				  fprintf(fout, "cmpl %%eax, %%edx\n"
								"je");
				  break;
	  case TAC_JZ: fprintf(fout, " .%s\n", tac->res->text); //Sendo utilizado apenas para escrever o label
				  break;
	  case TAC_JUMP: fprintf(fout, "jmp .%s\n", tac->res->text);
				  break;
	  case TAC_LABEL: fprintf(fout, "\n.%s:\n", tac->res->text);
				  break;
	  case TAC_ASS: fprintf(fout,"\n### CMD ASS ###\n");
					if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %s(%%rip)\n",tac->op1->text, tac->res->text);
                    else fprintf(fout,"movl	%s(%%rip), %%eax\n"
                                      "movl %%eax, %s(%%rip)\n", tac->op1->text, tac->res->text);
                    break;
	  case TAC_VEC_ATRIB: fprintf(fout,"\n### CMD VEC ATRIB ###\n");
					if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %s+%d(%%rip)\n",tac->op1->text, tac->res->text, atoi(tac->op2->text) * 4);
                    else fprintf(fout,"movl	%s(%%rip), %%eax\n"
                                      "movl	%%eax, %s+20(%%rip)\n", tac->op1->text, tac->res->text);
                    break;
	  case TAC_VEC_INDEX: fprintf(fout,"\n### CMD VEC_INDEX ###\n");
						fprintf(fout,"movl	%s+%d(%%rip), %%eax\n"
									 "movl	%%eax, %s(%%rip)\n", tac->op1->text, atoi(tac->op2->text) * 4, tac->res->text );
                    break;
	  case TAC_FUNCALL: fprintf(fout,"\n### CMD CALL FUNCTION ### \n"
								  "movl	$0, %%eax\n"
								  "call %s\n"
								  "movl %%eax, %s(%%rip)\n", tac->op1->text, tac->res->text);
					          break;
    case TAC_PRINT_ARG: fprintf(fout,"\n### CMD PRINT ARG ###\n");
                    //fprint_print_argument(fout, tac, ++print_arg_count);
                    if(tac->res->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%esi\n",tac->res->text);
                    else fprintf(fout,"movl	%s(%%rip), %%esi\n", tac->res->text);
                    fprintf(fout,"movl	$string_integer, %%edi\n"
                              	 "\tcall	printf\n");
                    break;
    case TAC_PRINT:fprintf(fout,"\nmovl	%%r8d, %%edx\n");
                    fprintf(fout,"movl	%%r9d, %%ecx\n");
                    fprintf(fout,"movl	%%edi, %%r8d\n");
                    fprintf(fout,"movl	%%eax, %%r9d\n");
                    fprintf(fout,"## cmd PRINT\n");
                    fprintf(fout,"movl	$lit_string%d, %%edi\n"
                              	 "\tcall	printf\n", findString(tac->res->text));
                    break;
    case TAC_FUN_START: fprintf(fout,"\n.text\n"
      	                              ".globl	%s\n"
      	                              ".type	%s, @function\n"
                                      "%s:\n"
                                      "\n.cfi_startproc\n"
      	                              "pushq %%rbp\n"
      	                              "movq	%%rsp, %%rbp\n", tac->res->text, tac->res->text, tac->res->text);
                    break;
    case TAC_FUN_END:fprintf(fout,  "popq	%%rbp\n"
    	                             "ret\n"
                                    ".cfi_endproc\n");
                    break;
	  case TAC_RET:fprintf(fout,"\n### CMD RETURN ###\n");
					if(tac->res->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n", tac->res->text);
                    else fprintf(fout,"movl	%s(%%rip), %%eax\n", tac->res->text);
					break;
    }
  }

  fclose(fout);
}
