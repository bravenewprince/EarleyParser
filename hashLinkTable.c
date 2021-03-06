#include <stdlib.h>
#include "tokenKindTable.h"
#include <stdbool.h>

#define INITIAL_TK_TABLE_SIZE 1000

TokenKindTable* newTokenKindTable() {
	TokenKind* temp = (TokenKind*) calloc(INITIAL_TK_TABLE_SIZE, sizeof(TokenKind));
	TokenKindTable result = {.table = temp, .size = 1, .capasity = INITIAL_TK_TABLE_SIZE};
	return &result;
}

// given a token (which maps to a TK for that token), return it's TK.
TokenKind getTokenKind(TokenKindTable* table, Token token) {
	return table->table[token];
}

// given a token (an index), set it's tk.
void addTokenToTKTable(TokenKindTable* table, Token token, TokenKind tk) {
	if(TKTableIsFull(table)) {
		expandTKTable(table);
	}
	
	table->table[token] = tk;
}


void expandTKTable(TokenKindTable* table) {
	TokenKind* temp = (TokenKind*) calloc(2*table->capasity, sizeof(TokenKind));
	TokenKindTable result = {.table = temp, .size = 1, .capasity = INITIAL_TK_TABLE_SIZE};
	*table = result;
}

bool TKTableIsFull(TokenKindTable* table) { 
	return table->size == table->capasity;
}
