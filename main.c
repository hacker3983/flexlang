#include <stdio.h>
#include <dirent.h>
#include "include/flexlang.h"

void execute_tests(const char* separator, int style_format) {
	flexdir_t directory = flexlang_opendir("tests");
	flexlang_readdir(&directory);
	size_t end_fileindex = 0;
	for(size_t i=0;i<directory.item_count;i++) {
		if(directory.items[i].type == FLEXLANG_FILE) {
			end_fileindex = i;
		}
	}
	for(size_t i=0;i<directory.item_count;i++) {
		if(directory.items[i].type == FLEXLANG_FILE) {
			const char* filepath = directory.items[i].path;
			printf("\033[31m[*]\033[0m \033[33mPerforming lexical analysis on the file %s\033[0m...\n",
				directory.items[i].name);
			size_t lexer_tokencount = 0;
			flexlexertokens_t* lexer_tokens = flexlang_lexifyfile(filepath, &lexer_tokencount);
			flexlang_printtokens(lexer_tokens, lexer_tokencount, separator, style_format);
			flexlang_delexify(&lexer_tokens, lexer_tokencount);
			if(i != end_fileindex) printf("\n");;
		}
	}
	flexlang_closedir(&directory);
}

int main(int argc, char** argv) {
	execute_tests(", ", FLEXLANG_PRINT_NOTOKENNEWLINE ^ FLEXLANG_PRINT_SHOWNOTOKENTYPE);
	return 0;
}
