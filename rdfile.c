#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"rdfile.h"

char* rdfileline( char* file, int line ){
	return rdfilelines(file, line, line);
}

char* rdfilelines( char* file, int from, int to){
	char buffer[200];
	char* total;
	FILE *fp;
	fp = fopen ( file, "r");
	if (from == 0 || to == 0) {
		fputs ("Error: you can't read a line 0", stderr); exit(1);
	}
	if (fp == NULL) {fputs ("File error. Running UNIX?",stderr); exit (1);}

	// Move the pointer
	for(int i=0; i<from; i++){
		fgets(buffer, 200, fp);
	}

	// Read
	total = malloc(200*(to-from+1));
	for(int i=from; i<=to; i++){
		strcat( total, buffer);
		fgets(buffer, 200, fp);
	}

	// Close
	fclose(fp);

	return total;
}
