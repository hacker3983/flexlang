#include "../include/flexlang.h"

char* flexlang_getcwd() {
	char* current_dir = getcwd(NULL, 0);
	return current_dir;
}


flexfile_t flexlang_openfile(const char* filename) {
	flexfile_t file = {0};
	file.file_stream = fopen(filename, "rb");
	if(file.file_stream) {
		file.filename = flexlang_copystr(filename);
	}
	return file;
}

void flexlang_readfile(flexfile_t* file) {
	if(!file->file_stream) {
		return;
	}
	fseek(file->file_stream, 0, SEEK_END);
	file->file_size = ftell(file->file_stream);
	file->file_content = calloc(file->file_size+1, sizeof(char));
	rewind(file->file_stream);
	fread(file->file_content, file->file_size, sizeof(char), file->file_stream);
}

void flexlang_closefile(flexfile_t* file) {
	if(!file->file_stream) {
		return;
	}
	free(file->filename); file->filename = NULL;
	fclose(file->file_stream); file->file_stream = NULL;
	free(file->file_content); file->file_content = NULL;
	file->file_size = 0;
}

flexdir_t flexlang_opendir(const char* directory_name) {
	flexdir_t directory = {0};
	directory.dirp = opendir(directory_name);
	directory.name = flexlang_copystr(directory_name);
	// Get the current working directory
	char* prev_dirpath = flexlang_getcwd();
	
	// change the current working directory to the directory_name or path
	// so we can determine the absolute path
	chdir(directory_name);
	char* new_dirpath = flexlang_getcwd();
	directory.path = new_dirpath;

	// change current directory back to the previous path after finding the absolute path
	// for the directory_name
	chdir(prev_dirpath);
	free(prev_dirpath);
	return directory;
}

void flexlang_readdir(flexdir_t* dir) {
	flexdir_item_t* dir_items = NULL;
	while(dir->entry = readdir(dir->dirp)) {	
		if(!dir_items) {
			dir_items = calloc(1, sizeof(flexdir_item_t));
		} else {
			dir_items = realloc(dir_items, (dir->item_count+1) * sizeof(flexdir_item_t));
		}
		// test to see if the name of the entry will be a opened as a directory
		flexdir_t temp_dir = flexlang_opendir(dir->entry->d_name);
		// if name of entry opened is not a directory then it is a file
		if(!temp_dir.dirp) {
			dir_items[dir->item_count].type = FLEXLANG_FILE;
		}
		flexlang_closedir(&temp_dir);
		dir_items[dir->item_count].name_len = strlen(dir->entry->d_name);
		dir_items[dir->item_count].name = flexlang_copystr(dir->entry->d_name);
		dir_items[dir->item_count].path = flexlang_copystr(dir->path);
		flexlang_appendchartostr(&dir_items[dir->item_count].path, '/');
		flexlang_appendstrtostr(&dir_items[dir->item_count].path, dir->entry->d_name);
		dir->item_count++;
	}
	dir->entry = NULL;
	dir->items = dir_items;
}

void flexlang_closedir(flexdir_t* directory) {
	free(directory->name); directory->name = NULL;
	free(directory->path); directory->path = NULL;
	for(size_t i=0;i<directory->item_count;i++) {
		free(directory->items[i].name); directory->items[i].name = NULL;
		free(directory->items[i].path); directory->items[i].path = NULL;
	}
	free(directory->items); directory->items = NULL;
	closedir(directory->dirp);
	*directory = (flexdir_t){0};
}
