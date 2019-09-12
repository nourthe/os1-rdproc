#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<pwd.h>
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
	if (dir == NULL) {fputs ("Dir error. Does the directory exist?", stderr); exit(1);}
	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {
		struct stat fileStat;
		//struct passwd * pInfo = getpwuid(fileStat.st_uid);
		stat("/home/nahuel/prob.gv", &fileStat);
		char st[20] = "";
		filestat_perm_string(fileStat, st, 200);
		strcat(buffer, st);
		strcat(buffer, "\t");
		strcat(buffer, entry->d_name);
		strcat(buffer, "\n");
	}
	closedir(dir);
}
void filestat_perm_string( struct stat fileStat, char* buffer, long buf_size){
	strcat ( buffer, (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
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
