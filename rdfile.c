#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"rdfile.h"

const int BUFFER_SIZE = 1500;
char* rdfileline( char* file, int line ){
	return rdfilelines(file, line, line);
}

char* rdfilelines( char* file, int from, int to){
	char buffer[BUFFER_SIZE];
	char* total;
	FILE *fp;
	fp = fopen ( file, "r");
	if (from == 0 || to == 0) {
		fputs ("Error: you can't read a line 0", stderr); exit(1);
	}
	if (fp == NULL) {fputs ("File error. Running UNIX?",stderr); exit (1);}

	// Move the pointer
	for(int i=0; i<from; i++){
		fgets(buffer, BUFFER_SIZE, fp);
	}

	// Read
	total = malloc(BUFFER_SIZE*(to-from+1));
	for(int i=from; i<=to; i++){
		strcat( total, buffer);
		fgets(buffer, BUFFER_SIZE, fp);
	}

	// Close
	fclose(fp);

	return total;
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
