/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 4
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/


#include "semantic.h"


int semanticError = 0;



int getSemanticErrorsNumber(){
    return semanticError;
}


void checkPointerChildType (AST *node) {
  fprintf(stderr, "[ERROR] ENTREI NA CHECKPOINTER\n");
	// we can have pt = pt + inteiro, we cant have pt = pt + pt
   if(!node) return;

   if (node->type == AST_ADD || node->type == AST_SUB || node->type == AST_MUL ) {

	    int leftOperandType = node->son[0]->type;
	    int rightOperandType = node->son[1]->type;

		if (leftOperandType == AST_POINTER && rightOperandType == AST_POINTER) {

			 fprintf(stderr, "[ERROR] Semantic Error in line %d: the left/right operand %s is an pointer  \n", node->line, node->son[0]->symbol->text);
     			 semanticError++;
		}
		else if (leftOperandType == AST_POINTER && (rightOperandType != AST_SYMBOL) )  {
			 fprintf(stderr, "[ERROR] Semantic Error in line %d: the right operand %s is not an integer \n", node->line, node->son[0]->symbol->text);
     			 semanticError++;
		}
		else if (rightOperandType == AST_POINTER  && (leftOperandType != AST_SYMBOL) ) {
		    	 fprintf(stderr, "[ERROR] Semantic Error in line %d: the left operand %s is not an integer \n", node->line, node->son[0]->symbol->text);
     			 semanticError++;
		}
    }
   else {
	     fprintf(stderr, "[ERROR] Semantic Error in line %d : the left or right operand %s are not compatible. \n", node->line, node->son[0]->symbol->text);
     	 semanticError++;
	}
}


void check_pointer (AST* node) {


 if(!node) return;

 if(node->type == AST_POINTER_ATRIB) {

  	  if(node->symbol->type != SYMBOL_IDENTIFIER){

   	   fprintf(stderr, "[ERROR] Semantic Error in line %d: identifier %s already declared. \n", node->line, node->son[0]->symbol->text);
    	  semanticError++;

    	  }
	else if (node->symbol->type == SYMBOL_VAR) { // pode ponteiro float?


    	if(node->son[0]->type == AST_KW_CHAR) node->symbol->datatype = DATATYPE_CHAR;
    	if(node->son[0]->type == AST_KW_INT) node->symbol->datatype = DATATYPE_INT;
    	//if(node->son[0]->type == AST_KW_FLOAT) node->symbol->datatype = DATATYPE_FLOAT;
      /*
       else {
			 fprintf(stderr, "[ERROR] Semantic Error in line %d. \n", node->line, node->son[0]->symbol->text);
	      		 semanticError++;
			}*/


  	  checkPointerChildType (node->son[0]);
 }

}
}


int checkNodeNumType(AST *node){
  if(!node) return -1;

  //literas, variables, access to array and function can be float or integer
  if(node->type == AST_SYMBOL || node->type == AST_ARRAY_POS || node->type == AST_FUNCALL || node->type == AST_ENDER || node->type == AST_POINTER) {
      if(node->symbol->datatype == DATATYPE_FLOAT || node->symbol->type == SYMBOL_LIT_REAL) {
        return 1;
      }
      else if(node->symbol->datatype == DATATYPE_INT || node->symbol->datatype == DATATYPE_CHAR || node->symbol->type == SYMBOL_LIT_INT || node->symbol->type == SYMBOL_LIT_CHAR
         || node->symbol->type == SYMBOL_POINTER || node->symbol->type == SYMBOL_ENDER) {
        return 0;
      }
      else {
        return -1;
      }
  }
  //logical operators dont return real
  if(node->type == AST_LESS || node->type == AST_GREATER || node->type == AST_NEG || node->type == AST_LE || node->type == AST_GE
     || node->type == AST_EQ || node->type == AST_NE || node->type == AST_AND || node->type == AST_OR)
      return -1;

  //arithmetical operations require more checks
  if(node->type == AST_ADD || node->type == AST_SUB || node->type == AST_MUL || node->type == AST_DIV){
      if (checkNodeNumType(node->son[0]) || checkNodeNumType(node->son[1]) == 1)
        return checkNodeNumType(node->son[0]) || checkNodeNumType(node->son[1]);
      else
        return checkNodeNumType(node->son[0]) && checkNodeNumType(node->son[1]);
  }
  //expressions between parentesis must be checked
  if(node->type == AST_EXP_P)
      checkNodeNumType(node->son[0]);
}



void set_Declarations(AST* node){

  if(!node) return;
  //process this node
  if(node->type == AST_VAR_DECL){

      if(node->symbol->type != SYMBOL_IDENTIFIER){
        fprintf(stderr, "[ERROR] Semantic Error in line %d [VAR_DECL]: identifier %s already declared. \n", node->line, node->symbol->text);
        semanticError++;
      }
      else{
        node->symbol->type = SYMBOL_VAR;
        if(node->son[0]->type == AST_KW_CHAR) node->symbol->datatype = DATATYPE_CHAR;
        if(node->son[0]->type == AST_KW_INT) node->symbol->datatype = DATATYPE_INT;
        if(node->son[0]->type == AST_KW_FLOAT) node->symbol->datatype = DATATYPE_FLOAT;
      }

  }

  if(node->type == AST_VECTOR_DECL || node->type == AST_VECTOR_DECL_EMPTY){
      if(node->symbol->type != SYMBOL_IDENTIFIER){
        fprintf(stderr, "[ERROR] Semantic Error in line %d [VECTOR_DECL]: identifier %s already declared. \n", node->line, node->symbol->text);
        semanticError++;
      }
      else{
        node->symbol->type = SYMBOL_VEC;
        if(node->son[0]->type == AST_KW_CHAR) node->symbol->datatype = DATATYPE_CHAR;
        if(node->son[0]->type == AST_KW_INT) node->symbol->datatype = DATATYPE_INT;
        if(node->son[0]->type == AST_KW_FLOAT) node->symbol->datatype = DATATYPE_FLOAT;
      }

  }


  if(node->type == AST_FUN_DECL){

      if(node->symbol->type != SYMBOL_IDENTIFIER && node->symbol->type != SYMBOL_VAR){
        fprintf(stderr, "[ERROR] Semantic Error in line %d [FUN_DECL]: identifier %s already declared. \n", node->line, node->symbol->text);
        semanticError++;
      }
      else{
        node->symbol->type = SYMBOL_FUNC;
  	    addFunction(node->symbol);
        if(node->son[0]->type == AST_KW_CHAR) node->symbol->datatype = DATATYPE_CHAR;
        if(node->son[0]->type == AST_KW_INT) node->symbol->datatype = DATATYPE_INT;
        if(node->son[0]->type == AST_KW_FLOAT) node->symbol->datatype = DATATYPE_FLOAT;
      }

}


  if(node->type == AST_POINTER_VAR_DECL){

      if(node->symbol->type != SYMBOL_IDENTIFIER){
        fprintf(stderr, "[ERROR] Semantic Error in line %d [POINTER_VAR_DECL]: identifier %s already declared. \n", node->line, node->symbol->text);
        semanticError++;
      }
      else{
        node->symbol->type = SYMBOL_VAR;
        if(node->son[0]->type == AST_KW_CHAR) node->symbol->datatype = DATATYPE_CHAR;
        if(node->son[0]->type == AST_KW_INT) node->symbol->datatype = DATATYPE_INT;
        if(node->son[0]->type == AST_KW_FLOAT) node->symbol->datatype = DATATYPE_FLOAT;
      }

  }

  //Para declaração dos argumentos das funções como variaveis válidas
  if(node->type == AST_FUN_PARAML || node->type == AST_FUN_PARAMREST){

      if(node->son[0]->symbol->type != SYMBOL_IDENTIFIER){
        fprintf(stderr, "[ERROR] Semantic Error in line %d [PARAM]: identifier %s already declared. \n", node->line, node->symbol->text);
        semanticError++;
      }
      else{
        node->son[0]->symbol->type = SYMBOL_VAR;
        if(node->son[0]->son[0]->type == AST_KW_CHAR) node->son[0]->symbol->datatype = DATATYPE_CHAR;
        if(node->son[0]->son[0]->type == AST_KW_INT) node->son[0]->symbol->datatype = DATATYPE_INT;
        if(node->son[0]->son[0]->type == AST_KW_FLOAT) node->son[0]->symbol->datatype = DATATYPE_FLOAT;

  	    func_list.last->numParam ++;
  	    func_list.last->paramType[func_list.last->numParam - 1] = node->son[0]->symbol->datatype;
      }

  }



  int i;
  for(i=0; i<MAX_SONS; i++){
    set_Declarations(node->son[i]);
  }
}



void check_id_undeclared(){
    int i;
  	HASH *node;
  	for(i=0; i<HASH_SIZE; i++) {
  		for(node=table[i]; node; node=node->next) {
  			if(node->type ==  SYMBOL_IDENTIFIER){
  				fprintf (stderr,"[ERROR] Semantic Error in line %d [Undeclared]: identifier %s, not declared. \n",node->line, node->text);
  				semanticError++;
  		  }
      }
    }
}



void check_operands(AST* node) {

  //If node is NULL return
  if(!node) return;


  //Checking node type
  if(node->type == AST_ADD || node->type == AST_SUB || node->type == AST_MUL || node->type == AST_DIV ||
  node->type == AST_LESS || node->type == AST_GREATER || node->type == AST_NEG || node->type == AST_LE ||
  node->type == AST_GE || node->type == AST_EQ || node->type == AST_NE || node->type == AST_AND || node->type == AST_OR) {

      int leftOperandType = node->son[0]->type;
      int rightOperandType = node->son[1]->type;

      //in case son are an expression between parentesis
      while(leftOperandType == AST_EXP_P){
        leftOperandType = node->son[0]->type;
      }

      while(rightOperandType == AST_EXP_P){
        rightOperandType = node->son[1]->type;
      }

      //verifying left operand
      if(leftOperandType == AST_LESS || leftOperandType == AST_GREATER || leftOperandType == AST_NEG || leftOperandType == AST_LE ||
        leftOperandType == AST_GE || leftOperandType == AST_EQ || leftOperandType == AST_NE || leftOperandType == AST_AND || leftOperandType == AST_OR) {
      fprintf(stderr, "[ERROR] Semantic Error in line %d: left operand are logical. \n", node->line);
      semanticError++;
      }
      //verifying right operand
      if(rightOperandType == AST_LESS || rightOperandType == AST_GREATER || rightOperandType == AST_NEG || rightOperandType == AST_LE ||
        rightOperandType == AST_GE || rightOperandType == AST_EQ || rightOperandType == AST_NE || rightOperandType == AST_AND || rightOperandType == AST_OR) {
          fprintf(stderr, "[ERROR] Semantic Error in line %d: right operand are logical. \n", node->line);
          semanticError++;
      }

  }

  if(node->type == AST_KW_IF || node->type == AST_KW_WHILE) {
      AST *son0 = node->son[0];
      int son0type = son0->type;
      //in case son is an expression between parentesis
      while(son0type == AST_EXP_P) {
        son0 = son0->son[0];
        son0type = son0->type;
      }

      if(son0type != AST_LESS && son0type != AST_GREATER && son0type != AST_NEG && son0type != AST_LE && son0type != AST_GE && son0type != AST_EQ &&
          son0type != AST_NE && son0type != AST_AND && son0type != AST_OR) {
          fprintf(stderr, "[ERROR] Semantic Error in line %d: condition must return a boolean value.\n", node->line);
          semanticError++;
      }
  }

  /*
  int i;
  for(i=0; i<MAX_SONS; i++) {
      check_operands(node->son[i]);
  }
  */

}



void check_declaration_usage(AST* node){

  //If node is NULL return
  if(!node) return;


  	//check if variables calls are calling variables
    if(node->type == AST_VAR_ATRIB) {
        if(node->symbol->type != SYMBOL_VAR ){
          fprintf(stderr, "[ERROR] Semantic Error in line %d [VAR_ATRIB]: identifier %s must be a variable\n", node->line, node->symbol->text);
          semanticError++;
        }
        //check if the variable and expression are the same type
        if(node->symbol->datatype == DATATYPE_CHAR || node->symbol->datatype == DATATYPE_INT ){
          if(checkNodeNumType(node->son[0]) < 0 || checkNodeNumType(node->son[0]) != 0){
            fprintf(stderr, "[ERROR] Semantic Error in line %d [VAR_ATRIB]: variable and expression type do not agree\n", node->line);
            semanticError++;
          }
        }

        if (node->symbol->datatype == DATATYPE_FLOAT) {
          if(checkNodeNumType(node->son[0]) < 0 || checkNodeNumType(node->son[0]) != 1){
            fprintf(stderr, "[ERROR] Semantic Error in line %d [VAR_ATRIB]: variable and expression type do not agree\n", node->line);
            semanticError++;
          }
        }
    }


    //check if vectors calls are calling vectors
    if(node->type == AST_VECTOR_ATRIB) {
        if(node->symbol->type != SYMBOL_VEC){
          fprintf(stderr, "[ERROR] Semantic Error in line %d [VECTOR_ATRIB]: identifier %s must be a vector\n",node->line, node->symbol->text);
          semanticError++;
        }
        //check if the vector and expression are the same type
        if(node->symbol->datatype == DATATYPE_CHAR || node->symbol->datatype == DATATYPE_INT ){
          if(checkNodeNumType(node->son[0]) < 0 || checkNodeNumType(node->son[0]) != 0){
            fprintf(stderr, "[ERROR] Semantic Error in line %d [VECTOR_ATRIB]: vector and expression type do not agree\n", node->line);
            semanticError++;
          }
        }

        else if (node->symbol->datatype == DATATYPE_FLOAT) {
          if(checkNodeNumType(node->son[0]) < 0 || checkNodeNumType(node->son[0]) != 1){
            fprintf(stderr, "[ERROR] Semantic Error in line %d [VECTOR_ATRIB]: vector and expression type do not agree\n", node->line);
            semanticError++;
          }
        }

    }


	if(node->type == AST_POINTER_ATRIB) {
  		printf("%d", node->symbol->type);
  		if(node->symbol->type != SYMBOL_VAR) {
  		   fprintf(stderr, "[ERROR] Semantic Error in line %d [POINTER_ATRIB]: identifier %s must be a variable\n",node->line, node->symbol->text);
          semanticError++;
  		}
      //check if the vector and expression are the same type
      if(node->symbol->datatype == DATATYPE_CHAR || node->symbol->datatype == DATATYPE_INT ){

        if((checkNodeNumType(node->son[0]->son[0]) < 0 || checkNodeNumType(node->son[0]->son[0]) != 0) && (checkNodeNumType(node->son[0]->son[1]) < 0 || checkNodeNumType(node->son[0]->son[1]) != 0 ) &&
        (checkNodeNumType(node->son[0]) < 0 || checkNodeNumType(node->son[0]) != 0 )){
          fprintf(stderr, "[ERROR] Semantic Error in line %d [POINTER_ATRIB]: pointer and expression type do not agree\n", node->line);
          semanticError++;
        }
      }

      else if (node->symbol->datatype == DATATYPE_FLOAT) {
        if(checkNodeNumType(node->son[0]) < 0 || checkNodeNumType(node->son[0]) != 1){
          fprintf(stderr, "[ERROR] Semantic Error in line %d [POINTER_ATRIB]: pointer and expression type do not agree\n", node->line);
          semanticError++;
        }
      }
  }




    //check if vectors calls are calling vectors and if it's index is valid
    if(node->type == AST_ARRAY_POS){
        if(node->symbol->type != SYMBOL_VEC){
          fprintf(stderr, "[ERROR] Semantic Error in line %d [ARRAY_POS]: identifier %s must be a vector\n",  node->line, node->symbol->text);
          semanticError++;
        }
        else check_vectorIndex(node);
    }

    //check if functions calls are calling functions and if it's arguments are valid
    if(node->type == AST_FUNCALL){
        if(node->symbol->type != SYMBOL_FUNC){
          fprintf(stderr, "[ERROR] Semantic Error in line %d [FUNCALL]: identifier %s must be a function\n",  node->line, node->symbol->text);
          semanticError++;
        }
        else checkFuncParam(node->son[0], node->symbol->text, node->line);
    }

    //check if variables declarations and literal are the same type
    if(node->type == AST_VAR_DECL){
        if(node->symbol->datatype == DATATYPE_CHAR || node->symbol->datatype == DATATYPE_INT ){
          if(checkNodeNumType(node->son[1]) < 0 || checkNodeNumType(node->son[1]) != 0){
            fprintf(stderr, "[ERROR] Semantic Error in line %d [VAR_DECL]: variable declaration and expression type do not agree\n", node->line);
            semanticError++;
          }
        }

        else if (node->symbol->datatype == DATATYPE_FLOAT) {
          if(checkNodeNumType(node->son[1]) < 0 || checkNodeNumType(node->son[1]) != 1){
            fprintf(stderr, "[ERROR] Semantic Error in line %d [VAR_DECL]: variable declaration and expression type do not agree\n", node->line);
            semanticError++;
          }
        }
    }

    //check if vectors declarations and literals are the same type
    if(node->type == AST_VECTOR_DECL){
        AST* current_node;
        current_node = node->son[2];
        int pos = 0;

        while(current_node != NULL){
          if(node->symbol->datatype == DATATYPE_CHAR || node->symbol->datatype == DATATYPE_INT ){
            if(checkNodeNumType(current_node) < 0 || checkNodeNumType(current_node) != 0){
              fprintf(stderr, "[ERROR] Semantic Error in line %d [VECTOR_DECL]: vector and literal_%d type do not agree\n", node->line, pos+1);
              semanticError++;
            }
          }

          else if (node->symbol->datatype == DATATYPE_FLOAT) {
            if(checkNodeNumType(current_node) < 0 || checkNodeNumType(current_node) != 1){
              fprintf(stderr, "[ERROR] Semantic Error in line %d [VECTOR_DECL]: vector and literal_%d type do not agree\n", node->line, pos+1);
              semanticError++;
            }
          }
            current_node = current_node->son[0];
            pos++;
        }
    }



    int i;
    for(i=0; i<MAX_SONS; i++){
      check_declaration_usage(node->son[i]);
    }
}



void check_vectorIndex(AST* node) {
    if(checkNodeNumType(node->son[0]) < 0 || checkNodeNumType(node->son[0]) == 1){
        fprintf(stderr, "[ERROR] Semantic Error in line %d: vector index is not Integer.\n", node->line);
        semanticError++;
    }
}





void check_returnType(AST* node) {
    if(!node) return;

    if(node->type == AST_FUN_DECL){
        check_returnType(node->son[3]);
        return;
    }
    if(node->type == AST_KW_RETURN) {
        //check the type of the expression that is being returned
        //in this case, the defined types are interchangeable
        if(checkNodeNumType(node->son[0]) < 0) {
            fprintf(stderr, "[ERROR] Semantic Error in line %d: return type not valid.\n", node->line);
        		semanticError++;
            return;
        }
    }

    for(int i=0; i<MAX_SONS; i++) {
        check_returnType(node->son[i]);
    }
}



void checkFuncParam(AST* node, char* function_name, int line){
	AST* current_node;
	current_node = node;
	int param_count = 0;

	FUNC_DATA_NODE* func_data;
	func_data = findFunction(function_name);
  if(func_data == NULL) return;

	int numParam = func_data->numParam;

	while(current_node!=NULL && param_count<=numParam){

      //verify if the parameter is type real
      if(func_data->paramType[param_count] == DATATYPE_FLOAT )
  			if(checkNodeNumType(current_node->son[0]) != 1){
  				fprintf(stderr, "[ERROR] Semantic Error in line %d: invalid function parameter type (parameter %i)\n",line, param_count + 1);
    			semanticError++;
  			}
      //verify if the parameter is type integer
      if(func_data->paramType[param_count] == DATATYPE_INT || func_data->paramType[param_count] == DATATYPE_CHAR || func_data->paramType[param_count] == SYMBOL_POINTER  || func_data->paramType[param_count] == SYMBOL_ENDER  )
        if(checkNodeNumType(current_node->son[0]) != 0 ){
          fprintf(stderr, "[ERROR] Semantic Error in line %d: invalid function parameter type (parameter %i)\n",line, param_count + 1);
          semanticError++;
        }


			param_count++;
			current_node = current_node->son[1];
	}

	if(param_count > numParam){
		fprintf(stderr, "[ERROR] Semantic Error in line %d: too many arguments at %s\n", line, function_name);
  		semanticError++;
	}
	if(param_count < numParam){
		fprintf(stderr, "[ERROR] Semantic Error in line %d: missing arguments at %s\n", line, function_name);
  		semanticError++;
	}
}



void addFunction(HASH* function){
	FUNC_DATA_NODE* newNode;
	newNode = (FUNC_DATA_NODE*) calloc(1, sizeof(FUNC_DATA_NODE));
	newNode->function = function;
	newNode->numParam = 0;
	newNode->next = NULL;

	if(func_list.first == NULL){
		func_list.first = newNode;
		func_list.last = newNode;
	}
	else{
		func_list.last->next = newNode;
		func_list.last = newNode;
	}
}



FUNC_DATA_NODE* findFunction(char* function_name){
	FUNC_DATA_NODE* current_func = func_list.first;
  int found = 0;

	while(current_func != NULL && found == 0){
		if(strcmp(current_func->function->text, function_name) == 0)
			found = 1;
		else
			current_func = current_func->next;
	}
  return current_func;
}
