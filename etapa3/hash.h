/*
  INF01147 Compiladores - Turma A - Marcelo Johann
  Trabalho : ETAPA 3
  Componentes : Lisiane Aguiar e Rodrigo Okido
*/

#define HASH_SIZE 997

#ifndef HASH_HEADER
#define HASH_HEADER


typedef struct hash_node {
	char *text;
	int type;
	struct hash_node *next;
} HASH;

HASH *table[HASH_SIZE];

void hashInit(void);
int hashAddress(char *text);
HASH *hashInsert (int type, char *text);
HASH *hashFind (char *text);
void hashPrint(void);

void initMe();
int getLineNumber();
int isRunning();

#endif
