#ifndef _FLEXLANG_LEXER_H
#define _FLEXLANG_LEXER_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "flexlang-types.h"
#include "flexlang-string.h"
#include "flexlang.h"

enum flexlang_lexer_tokenprint_format {
	FLEXLANG_PRINT_NOTOKENNEWLINE = 1,
	FLEXLANG_PRINT_TOKENNEWLINE,
	FLEXLANG_PRINT_SHOWNOTOKENTYPE,
	FLEXLANG_PRINT_SHOWTOKENTYPE
};

typedef struct flexlang_lexertokens {
	int token_type;
	char *token_value;
	size_t token_valuelen;
} flexlexertokens_t;

const char* lexer_gettokenname(int token_type);
flexlexertokens_t flexlang_createtoken(int token_type, char* token_value, size_t token_valuelen);
flexlexertokens_t* flexlang_lexifyfile(const char* filename, size_t* lexer_tokencount);
flexlexertokens_t* flexlang_lexify(const char* source, size_t source_length, size_t* lexer_tokencount);
char* flexlang_gettoken(const char* source, size_t* position, size_t source_len, int* token_type, size_t* token_len);
void flexlang_appendtoken(flexlexertokens_t** lexer_tokens, int token_type, char* token_value, size_t token_valuelen,
	size_t* lexer_tokencount);
void flexlang_printtokens(flexlexertokens_t* lexer, size_t lexer_tokencount, const char* sep, int style_format);
void flexlang_delexify(flexlexertokens_t** lexer, size_t lexer_tokencount);
#endif
