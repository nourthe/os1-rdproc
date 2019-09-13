#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<pwd.h>
#include<unistd.h>
#include<sys/stat.h>

#include"rdfile.h"

void swholefile( char* file, char* buffer, long buf_size) {
	FILE *fp;
	fp = fopen ( file, "r");
	if (fp == NULL) {fputs ("File error. Running UNIX?",stderr); exit (1);}
	fread(buffer,sizeof(char),buf_size,fp);
	// Close
	fclose(fp);
}

void sfileline( char* file, int line_number, char* buffer, long buf_size){
	FILE *fp;
	fp = fopen ( file, "r");
	if (fp == NULL) {fputs ("File error. Running UNIX?",stderr); exit (1);}

	// Move the pointer
	for(int i=0; i<line_number; i++){
		fgets(buffer, buf_size, fp);
	}

	// Close
	fclose(fp);
}
void sdirlist( char* directory, char* buffer, long buf_size){
	DIR *dir;
	dir = opendir(directory);
	if (dir == NULL) {fputs ("Dir error. Does the directory exist? \n", stderr); exit(1);}
	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {
		// Ignore hidden files and dirs.
		if (entry->d_name[0] == '.') continue;
		struct stat fileStat;

		char file[256];
		strcpy(file, directory);
		strcat(file, "/");
		strcat(file, entry->d_name);

		lstat(file, &fileStat);

		char st[20] = "";
		char type[20] = "";
		filestat_perm_string(fileStat, st, 20);
		d_type_string(fileStat.st_mode, type, 20);
		char link[256] = "";
		if((fileStat.st_mode & S_IFMT) == S_IFLNK){
			readlink(file, link, 256);
		}

		strcat(buffer, st);
		strcat(buffer, "\t");
		strcat(buffer, type);
		strcat(buffer, "\t");
		strcat(buffer, entry->d_name);
		strcat(buffer, "\t");
		strcat(buffer, link);
		strcat(buffer, "\n");
	}
	closedir(dir);
}
void filestat_perm_string( struct stat fileStat, char* buffer, long buf_size){
	if(S_ISDIR(fileStat.st_mode)){
		strcat(buffer, "d");
	}else if (S_ISLNK(fileStat.st_mode)){
		strcat(buffer, "l");
	}else{
		strcat( buffer, "-");
	}
	strcat ( buffer, (fileStat.st_mode & S_IRUSR) ? "r" : "-");
	strcat ( buffer, (fileStat.st_mode & S_IWUSR) ? "w" : "-");
	strcat ( buffer, (fileStat.st_mode & S_IXUSR) ? "x" : "-");
	strcat ( buffer, (fileStat.st_mode & S_IRGRP) ? "r" : "-");
	strcat ( buffer, (fileStat.st_mode & S_IWGRP) ? "w" : "-");
	strcat ( buffer, (fileStat.st_mode & S_IXGRP) ? "x" : "-");
	strcat ( buffer, (fileStat.st_mode & S_IROTH) ? "r" : "-");
	strcat ( buffer, (fileStat.st_mode & S_IWOTH) ? "w" : "-");
	strcat ( buffer, (fileStat.st_mode & S_IXOTH) ? "x" : "-");
}

void d_type_string(mode_t d_type, char* buffer, long buf_size){
	switch(d_type & S_IFMT){
		case DT_UNKNOWN:
			strcpy(buffer, "UNK");
			break;
		case S_IFIFO:
			strcpy(buffer, "FIFO");
			break;
		case S_IFCHR:
			strcpy(buffer, "CHR");
			break;
		case S_IFDIR:
			strcpy(buffer, "DIR");
			break;
		case S_IFBLK:
			strcpy(buffer, "BLK");
			break;
		case S_IFREG:
			strcpy(buffer, "REG");
			break;
		case S_IFLNK:
			strcpy(buffer, "LNK");
			break;
		case S_IFSOCK:
			strcpy(buffer, "SOCK");
			break;
		case DT_WHT:
			strcpy(buffer, "WHT");
			break;
	}
}
int get_lines_number(const char* const filename) {
	FILE *fp; 
    int count = 0;  // Line counter (result)  
    char c;  // To store a character read from file 
	fp = fopen(filename, "r"); 
  	if (fp == NULL) {fputs ("File error. Running UNIX?",stderr); exit (1); return -1;}
	// Extract characters from file and store in character c 
    for (c = getc(fp); c != EOF; c = getc(fp)) 
        if (c == '\n') // Increment count if this character is newline 
            count = count + 1; 
  
    // Close the file 
    fclose(fp);  
	return count;
}
