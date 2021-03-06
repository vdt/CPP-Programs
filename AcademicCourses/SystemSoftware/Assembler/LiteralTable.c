//filename: LiteralTable.c
#define MAX_LIT_QUEUE 100
#define LIT_HASHSIZE 41
/*
 * Finds hash value corresponding to char* p
 */

unsigned int hashLit(char const *ptr){//form hash value from string s
	int ans = strlen(ptr);
	for(; *ptr; ptr++)
		ans = ans *29 + *ptr;
	return ans%LIT_HASHSIZE;
}

enum relocation;
struct litRecord{
	char* name;//Name of the literal
	short length;//datatype length
	int value;//LC where memory is allocated
	enum relocation reloc;
	struct litRecord *next;
};
static struct litRecord *litHashTable[LIT_HASHSIZE]; /*pointer table*/ //Static means automatically initialises as NULL ptrs

//prints LT to fp
void printLT(FILE* fp){
	int i;
	fprintf(fp, "Literal Length Value(LC) Relocation\n");
	for(i=0; i<LIT_HASHSIZE; i++){
		struct litRecord* np = litHashTable[i];
		while(np!=NULL){
			fprintf(fp, "%s\t%d\t%d\t%c\n", np->name, np->length, np->value, ((np->reloc == ABS)?'A':'R'));
			np = np->next;
		}
	}
}

struct litRecord* lookupInLit(const char * const key){
	struct litRecord* np;
	for(np = litHashTable[hashLit(key)]; np!=NULL; np = np->next)
		if(!strcmp(key, np->name))
			return np; //found
	return NULL; //not found
}

char *strCreate(const char *const s){//allocates memory for the new string and return its pointer
	char *p = (char*)malloc(strlen(s));
	if(p!=NULL)
		strcpy(p, s);
	return p;
}
struct litRecord* installInLit(const char* const literalName, short len, int val, enum relocation aReloc){//install: put litRecord in litHashTable[] if not alresdy there else update.
//return NULL for lack of memory
	struct litRecord* np;
	
	if( (np=lookupInLit(literalName)) == NULL ){//not found
		np = (struct litRecord*)malloc(sizeof(struct litRecord));
		if(np==NULL)
			return NULL;
		if( (np->name = strCreate(literalName)) == NULL){ 
			free(np);
			return NULL;
		}
		np->length = len;
		np->value = val;
		np->reloc = aReloc;
		unsigned hashval = hashLit(literalName);
		np->next = litHashTable[hashval];
		litHashTable[hashval] = np;
	}else{//found
		np->length = len;
		np->value = val;
		np->reloc = aReloc;
	}
	return np;
}


static struct litRecord *LitQueue[MAX_LIT_QUEUE];
static int litQueueFront = 0;//latest element present to be dequeued
static int litQueueBack = 0;//place for new item enqueue
static int countLitQueue = 0;//number of elements in the queue
void addLiteral(const char *const litCharPtr){
	printTimeToLog();
	if(countLitQueue < MAX_LIT_QUEUE){
		fprintf(logFile, "Literal %s added.\n", litCharPtr);
		LitQueue[litQueueBack++] = installInLit(litCharPtr, -1, -1, NIL);
		if(litQueueBack == MAX_LIT_QUEUE)
			litQueueBack=0;
		countLitQueue++;
	}else{
		fprintf(logFile, "Literal %s NOT added due to queue overflow. Please increase queue size.\n", litCharPtr);
		fprintf(stdout, "Literal %s NOT added due to queue overflow. Please increase queue size.\n", litCharPtr);
	}
}
void deleteLT(){
	int i;
	for(i=0; i<LIT_HASHSIZE; i++){
		struct litRecord* np = litHashTable[i];
		litHashTable[i] = NULL;
		while(np!=NULL){
			struct litRecord* tmp = np;
			np = np->next;
			free(tmp);
		}
	}
}
//int main(){return 0;}
