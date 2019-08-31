#include"rdproc.h"

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void rdproc(int c){
	switch(c){

		/* Classic rdproc exercise information */
		case 'c':
			printf( "Hostname: \n\t");
			print_file_line("/proc/sys/kernel/hostname", 0);
			printf( "Date and time: \n\t");
			print_file_line("/proc/driver/rtc", 0);
			printf("\t");
			print_file_line("/proc/driver/rtc", 1);
			printf( "CPU info: \n\t");
			print_file_line("/proc/cpuinfo", 4);
			printf( "Kernel version: \n\t");
			print_file_line("/proc/version", 0);
			break;

		/* print_file debug */
		case 'e':
			print_file_line("/proc/strangefilename", 0);
	}
}

void print_file_line(char* dir, int r){
	char info[200];
	FILE *fp;
	fp = fopen ( dir, "r");
	if (fp == NULL) {fputs ("File error",stderr); exit (1);}

	// Read
	for(int i=0; i<=r; i++){
		fgets(info, 200, fp);
	}

	printf("%s", info);

	// Close
	fclose(fp);
}
