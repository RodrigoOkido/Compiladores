#include "hash.h"
#include "tac.h"
#include "ast.h"
#include <stdio.h>

int genasm (TAC* tac) {


	for(;tac; tac=tac->next) {
		
		switch (tac->type) {
			
			case TAC_ADD:
				fprintf(asmfile, "## TAC ADD movl\t%s(%%rip), %%eax addl\t%s(%%rip)", tac->op1->text, tac->op2->text, tac->res->text);
			break;
		}
	}
}
