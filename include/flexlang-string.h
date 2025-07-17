#ifndef _FLEXLANG_STRING_H
#define _FLEXLANG_STRING_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void flexlang_appendchartostr(char** string, char character);
void flexlang_appendchartostrn(char** string, char character, size_t* len);
void flexlang_appendstrtostr(char** string1, const char* string2);
void flexlang_appendstrtostrn(char** string1, const char* string2, size_t* len1, size_t len2);
char* flexlang_concatstr(const char* string1, const char* string2);
char* flexlang_concatnstr(const char* string1, const char* string2, size_t len1, size_t len2);
char* flexlang_copystr(const char* string);
char* flexlang_copynstr(const char* string, size_t len);
#endif
