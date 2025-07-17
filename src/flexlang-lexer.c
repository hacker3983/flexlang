#include "../include/flexlang-lexer.h"

const char* flexlang_gettoken_idname(int token_type) {
	return flextoken_idnames[token_type];
}

int flexlang_gettoken_typefromchar(char character) {
	int token_type = 0;
	if(isdigit(character)) {token_type = FLEXTOKEN_INT; return token_type; }
	else if(isalpha(character)) { token_type = FLEXTOKEN_WORD; return token_type; }
	switch(character) {
		case ' ':  token_type = FLEXTOKEN_SPACE;             break;
		case '"':  token_type = FLEXTOKEN_DOUBLEQUOTE;       break;
		case '\'': token_type = FLEXTOKEN_SINGLEQUOTE;       break;
		case '{':  token_type = FLEXTOKEN_OPENCURLYBRACE;    break;
		case '}':  token_type = FLEXTOKEN_CLOSEDCURLYBRACE;  break;
		case '(':  token_type = FLEXTOKEN_OPENCURVEDBRACE;   break;
		case ')':  token_type = FLEXTOKEN_CLOSEDCURVEDBRACE; break;
		case ':':  token_type = FLEXTOKEN_COLON;             break;
		case ';':  token_type = FLEXTOKEN_SEMICOLON;         break;
		case '+':  token_type = FLEXTOKEN_ADD;               break;
		case '-':  token_type = FLEXTOKEN_SUB;               break;
		case '/':  token_type = FLEXTOKEN_DIV;               break;
		case '*':  token_type = FLEXTOKEN_MULT;              break;
		case '^':  token_type = FLEXTOKEN_XOR;               break;
		case '&':  token_type = FLEXTOKEN_AND;               break;
		case '|':  token_type = FLEXTOKEN_OR;                break;
		case '=':  token_type = FLEXTOKEN_EQUAL;             break;
		case '<':  token_type = FLEXTOKEN_LESSTHAN;          break;
		case '>':  token_type = FLEXTOKEN_GREATERTHAN;        break;
		default:   token_type = FLEXTOKEN_PUNCTUATION;
	}
	return token_type;
}

int flexlang_gettoken_type(char* tokstr, char tokchar) {
	int token_type = FLEXTOKEN_WORD;
	if(tokstr) {
		if(!strcmp(tokstr, "flex"))        token_type = FLEXTOKEN;
		else if(!strcmp(tokstr, "int"))    token_type = FLEXTOKEN_INT;
		else if(!strcmp(tokstr, "bool"))   token_type = FLEXTOKEN_BOOL;
		else if(!strcmp(tokstr, "true"))   token_type = FLEXTOKEN_BOOL;
		else if(!strcmp(tokstr, "false"))  token_type = FLEXTOKEN_BOOL;
		else if(!strcmp(tokstr, "float"))  token_type = FLEXTOKEN_FLOAT;
		else if(!strcmp(tokstr, "string")) token_type = FLEXTOKEN_STRING;
		else if(!strcmp(tokstr, "ret"))    token_type = FLEXTOKEN_RETURN;
		return token_type;
	}
	token_type = flexlang_gettoken_typefromchar(tokchar);
	return token_type;
}

char* flexlang_readint(const char* source, size_t* position, size_t source_len, size_t* token_len) {
	char* tok = NULL;
	size_t i = *position, toklen = 0;
	while(i < source_len && isdigit(source[i])) {
		flexlang_appendchartostrn(&tok, source[i], &toklen);
		i++;
	}
	*position = i, *token_len = toklen;
	return tok;
}

char* flexlang_readnumber(const char* source, size_t* position, size_t source_len, int* token_type, size_t* token_len) {
	char* tok = NULL;
	size_t i = *position, toklen = 0, toklen2 = 0;
	*token_type = FLEXTOKEN_INT;
	tok = flexlang_readint(source, &i, source_len, &toklen);
	if(source[i] == '.') {
		i++;
		flexlang_appendchartostrn(&tok, '.', &toklen);
		if(!isdigit(source[i])) {
			i--;
		}	
		char* tok2 = flexlang_readint(source, &i, source_len, &toklen2);
		if(tok || tok2) {
			*token_type = FLEXTOKEN_FLOAT;
		}
		if(tok2) {
			flexlang_appendstrtostrn(&tok, tok2, &toklen, toklen2);
			free(tok2); tok2 = NULL;
		}	
	}
	*position = i, *token_len = toklen;
	return tok;
}

char* flexlang_readword(const char* source, size_t* position, size_t source_len, size_t* token_len) {
	char* tok = NULL;
	size_t i = *position, toklen = 0;
	while(i < source_len && isalpha(source[i])) {
		flexlang_appendchartostrn(&tok, source[i], &toklen);
		i++;
	}
	*position = i, *token_len = toklen;
	return tok;
}

char* flexlang_readspecchar(const char* source, char character, size_t* position, size_t source_len, size_t* token_len) {
	char* tok = NULL;
	size_t i = *position, toklen = 0;
	while(i < source_len && source[i] == character) {
		flexlang_appendchartostrn(&tok, source[i], &toklen);
		i++;
	}
	*position = i; *token_len = toklen;
	return tok;
}

char* flexlang_gettoken(const char* source, size_t* position, size_t source_len, int* token_type, size_t* token_len) {
	char* token = NULL;
	size_t i = *position, toklen = 0;
	*token_type = flexlang_gettoken_type(NULL, source[i]);
	if(ispunct(source[i])) {
		if(source[i] == '.') {
			i++;
			if(isdigit(source[i])) {
				i--;
				token = flexlang_readnumber(source, &i, source_len, token_type, token_len);
			}
			i--;
		}
		if(source[i] == '{' || source[i] == '}' || source[i] == '&' || source[i] == ':') {
			token = flexlang_readspecchar(source, source[i], &i, source_len, token_len);
			i--;
		} else if(*token_type == FLEXTOKEN_PUNCTUATION) {
			int tok_type = *token_type;
			while(i < source_len && ispunct(source[i]) && tok_type == FLEXTOKEN_PUNCTUATION) {	
				flexlang_appendchartostrn(&token, source[i], &toklen); i++;
				tok_type = flexlang_gettoken_typefromchar(source[i]);
			}
			i--;
		} else if(*token_type != FLEXTOKEN_FLOAT || *token_type != FLEXTOKEN_INT) {
			flexlang_appendchartostrn(&token, source[i], &toklen);
		}
	} else if(isalpha(source[i])) {
		token = flexlang_readword(source, &i, source_len, token_len);
		*token_type = flexlang_gettoken_type(token, 0); i--;
	} else if(source[i] == ' ') {
		token = flexlang_readspecchar(source, source[i], &i, source_len, token_len); i--;
	} else if(isdigit(source[i])) {
		token = flexlang_readnumber(source, &i, source_len, token_type, token_len); i--;
	}
	*position = i;
	return token;
}

flexlexertokens_t flexlang_createtoken(int token_type, char* token_value, size_t token_valuelen) {
	flexlexertokens_t new_token = {0};
	new_token.token_type = token_type;
      	new_token.token_value = token_value;
	new_token.token_valuelen = token_valuelen;
	return new_token;
}

flexlexertokens_t* flexlang_lexify(const char* source, size_t source_length, size_t* lexer_tokencount) {
	flexlexertokens_t* lexer_tokens = NULL;
	char* token = NULL;
	size_t token_len = 0;
	int token_type = 0;
	for(size_t i=0;i<source_length;i++) {
		token = flexlang_gettoken(source, &i, source_length, &token_type, &token_len);
		if(token) {
			flexlang_appendtoken(&lexer_tokens, token_type, token, token_len, lexer_tokencount);
		}	
	}
	return lexer_tokens;
}

flexlexertokens_t* flexlang_lexifyfile(const char* filepath, size_t* lexer_tokencount) {
	flexfile_t file = flexlang_openfile(filepath);
	flexlang_readfile(&file);
	flexlexertokens_t* lexer_tokens = flexlang_lexify(file.file_content, file.file_size, lexer_tokencount);
	flexlang_closefile(&file);
	return lexer_tokens;
}

void flexlang_appendtoken(flexlexertokens_t** lexer_tokens, int token_type, char* token_value, size_t token_valuelen,
	size_t* lexer_tokencount) {
	flexlexertokens_t new_token = flexlang_createtoken(token_type, token_value, token_valuelen);
	if(!(*lexer_tokens)) {
		*lexer_tokens = calloc(1, sizeof(flexlexertokens_t));
		(*lexer_tokens)[0] = new_token;
		(*lexer_tokencount)++;
		return;
	}

	(*lexer_tokencount)++;
	(*lexer_tokens) = realloc((*lexer_tokens), (*lexer_tokencount) * sizeof(flexlexertokens_t));
	(*lexer_tokens)[(*lexer_tokencount)-1] = new_token;
}
void flexlang_printtokens(flexlexertokens_t* lexer, size_t lexer_tokencount, const char* separator, int style_format) {
	bool show_tokentype = 0, print_newline = 0;
	int bitwise_pf1 = (style_format ^ FLEXLANG_PRINT_SHOWTOKENTYPE),
	    bitwise_pf2 = (style_format ^ FLEXLANG_PRINT_SHOWNOTOKENTYPE),
	    bitwise_pf3 = (style_format ^ FLEXLANG_PRINT_TOKENNEWLINE),
	    bitwise_pf4 = (style_format ^ FLEXLANG_PRINT_NOTOKENNEWLINE);
	if(bitwise_pf1 == FLEXLANG_PRINT_TOKENNEWLINE || bitwise_pf2 == FLEXLANG_PRINT_TOKENNEWLINE) {
		print_newline = true;
	}
	if(bitwise_pf3  == FLEXLANG_PRINT_SHOWTOKENTYPE || bitwise_pf4 == FLEXLANG_PRINT_SHOWTOKENTYPE) {
		show_tokentype = true;
	} 

	printf("[");
	(print_newline == true) ? printf("\n") : 0;
	for(size_t i=0;i<lexer_tokencount;i++) {
		if(show_tokentype) {
			printf("%s:", flexlang_gettoken_idname(lexer[i].token_type));
		}
		char* a = strstr(lexer[i].token_value, "\"");
		if(a) {
			printf("'%s'", lexer[i].token_value);
		} else {
			printf("\"%s\"", lexer[i].token_value);
		}
		(i != lexer_tokencount-1) ? printf("%s", separator) : 0;
		(i != lexer_tokencount-1 && print_newline) ? printf("\n") : 0;
	}
	(print_newline) ? printf("\n") : 0;
	printf("]\n");
}


void flexlang_delexify(flexlexertokens_t** lexer, size_t lexer_tokencount) {
	for(size_t i=0;i<lexer_tokencount;i++) {
		free((*lexer)[i].token_value); (*lexer)[i].token_value = NULL;
	}
	free(*lexer); *lexer = NULL;
}
