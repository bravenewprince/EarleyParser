#include <stdlib.h>
#include "stringIndexTable.h"
#include <stdbool.h>
#include <strings.h>

#include "stringTable.h"

#define INITIAL_STRING_INDEX_TABLE_CAP 1000 // subject to change

// this is the constructor for a StringIndexTable record. 
// return: a pointer to a new struct, with [0] reseverd.
StringIndexTable* newStringIndexTable() {
	
	StringIndexTable* result = (StringIndexTable*) malloc(sizeof(StringIndexTable));
	result->positionTable = (int*) calloc(INITIAL_STRING_INDEX_TABLE_CAP, sizeof(int));
	result->size = 1;
	result->capasity = INITIAL_STRING_INDEX_TABLE_CAP;

	result->positionTable[0] = 0; // just to initialize the value, and not leave it as NULL.

	return result;
}

// param: t, the stringIndexTable that you're using as a look up.
// param: str, the string who's token you want to find
// return: the token representing the string
Token positionInStrIndexTable(StringIndexTable* t, char* str) { 
	Token result = (Token) 0;
	printf("%i", t->size);
	for(int i = 1; i < t->size; i++) {
		int index = t->positionTable[i];
		char* tabledString =  stringTable->characterBuffer + index;
		int areEqual = !strcmp(tabledString, str);
		if(areEqual) {
			result = (Token) i;
			break;
		}
	}
	return result;
}

bool strIndexTableIsFull(StringIndexTable* t) {
	return t->size == t->capasity;
}

void expandStrIndexTable(StringIndexTable* t ) {
	StringIndexTable* result = (StringIndexTable*) malloc(sizeof(StringIndexTable));
	result->positionTable = (int*) calloc(2*t->capasity, sizeof(int));
	result->size = t->size;
	result->capasity = 2*t->capasity;

	result->positionTable[0] = 0; 
	t->positionTable = result->positionTable;
	t->size = result->size;
	t->capasity = result->capasity;
}


// param: t - the stringIndexTable you're using
// param: st - the string table you want to add the string to
// param: str - a string to add
// return: the token representing the string added.
Token  addStrToStrIndexTable(StringIndexTable* t, StringTable* st, char* str) {
	if(strIndexTableIsFull(t)) {
		expandStrIndexTable(t);
	}
	int position = addStrToStrTable(st, str);
	t->positionTable[t->size] = position;
	t->size++; // this line is not getting executed.
	return t->size - 1;
}
