#ifndef _FLEXLANG_H
#define _FLEXLANG_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include "flexlang-lexer.h"

enum item_type {
	FLEXLANG_DIR,
	FLEXLANG_FILE
};

typedef struct flexfile {
	FILE *file_stream;
	char *filename, *file_content;
	size_t file_size;
} flexfile_t;

typedef struct flexdir_item {
	int type;
	char* name, *path;
	size_t name_len;
} flexdir_item_t;

typedef struct flexdir {
	DIR* dirp;
	char* name, *path;
	struct dirent* entry;
	flexdir_item_t* items;
	size_t item_count;
} flexdir_t;

flexdir_t flexlang_opendir(const char* directory_name);
char* flexlang_getcwd();
void flexlang_readdir(flexdir_t* directory);
void flexlang_closedir(flexdir_t* directory);
flexfile_t flexlang_openfile(const char* filename);
void flexlang_readfile(flexfile_t* file);
void flexlang_closefile(flexfile_t* flexfile);
//flexlang_compile();
#endif
