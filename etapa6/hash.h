/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 6
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/


#define HASH_SIZE 997

#ifndef HASH_HEADER
#define HASH_HEADER


#define SYMBOL_VAR 3
#define SYMBOL_VEC 4
#define SYMBOL_FUNC 5

#define DATATYPE_CHAR 6
#define DATATYPE_INT 7
#define DATATYPE_FLOAT 8

#define SYMBOL_SCALAR 9
#define SYMBOL_FUNCTION 10
#define SYMBOL_VECTOR 11
#define SYMBOL_POINTER 12
#define SYMBOL_ENDER 13


typedef struct hash_node {
	char *text;
	int type;
  int datatype;
	int line;
	struct hash_node *next;
} HASH;

HASH *table[HASH_SIZE];

void hashInit(void);
int hashAddress(char *text);
HASH *hashInsert (int type, char *text);
HASH *hashFind (char *text);
void hashPrint(void);

HASH* makeTemp(void); //new
HASH* makeLabel(void); // new

void initMe();
int getLineNumber();
int isRunning();

#endif
