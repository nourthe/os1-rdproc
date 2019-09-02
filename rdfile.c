#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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
