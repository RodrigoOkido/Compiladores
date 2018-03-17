
#define HASH_SIZE 997

typedef struct hash_node {
	char *text;
	int type;
	struct hash_node *next;
} HASH_NODE;

HASH_NODE *table[HASH_SIZE];

void hashInit();
int hashAddress(char *text);
HASH_NODE *hashInsert (char *text, int type);
void hashPrint();

void initMe();
int getLineNumber();
int isRunning();
