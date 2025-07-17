#include "../include/flexlang-string.h"

void flexlang_appendchartostr(char** string, char character) {
	size_t len = strlen(*string);
	flexlang_appendchartostrn(string, character, &len);
}

void flexlang_appendchartostrn(char** string, char character, size_t* len) {
	char* new_str = calloc((*len)+2, sizeof(char));
	if(*string) {
		strcpy(new_str, *string);
	}
	new_str[(*len)++] = character;
	free(*string); *string = NULL;
	*string = new_str;
}

void flexlang_appendstrtostr(char** string1, const char* string2) {
	if(string2 == NULL) return;
	char* new_str = flexlang_concatstr(*string1, string2);
	free(*string1); *string1 = NULL;
	*string1 = new_str;
}

void flexlang_appendstrtostrn(char** string1, const char* string2, size_t* len1, size_t len2) {
	if(string2 == NULL) return;
	char* new_str = flexlang_concatnstr(*string1, string2, *len1, len2);
	free(*string1); *string1 = NULL;
	*len1 = (*len1) + len2;
	*string1 = new_str;
}

char* flexlang_concatstr(const char* string1, const char* string2) {
	if(string1 == NULL) return NULL;
	if(string2 == NULL) return NULL;
	size_t total_len = strlen(string1) + strlen(string2);
	char* new_str = calloc(total_len+1, sizeof(char));
	strcpy(new_str, string1);
	strcat(new_str, string2);
	return new_str;
}

char* flexlang_concatnstr(const char* string1, const char* string2, size_t len1, size_t len2) {
	if(string1 == NULL) return NULL;
	if(string2 == NULL) return NULL;
	size_t total_len = len1 + len2;
	char* new_str = calloc(total_len+1, sizeof(char));
	strncpy(new_str, string1, len1);
	strncat(new_str, string2, len2);
	return new_str;
}

char* flexlang_copystr(const char* string) {
	if(string == NULL) return NULL;
	char* new_str = calloc(strlen(string)+1, sizeof(char));
	strcpy(new_str, string);
	return new_str;
}

char* flexlang_copynstr(const char* string, size_t len) {
	if(string == NULL) return NULL;
	char* new_str = calloc(len+1, sizeof(char));
	strncpy(new_str, string, len);
	return new_str;
}
