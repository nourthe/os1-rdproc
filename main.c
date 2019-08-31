#include<stdio.h>
#include<stdbool.h>
#include<getopt.h>

#include"rdproc.h"

#ifndef VERSION
#define VERSION "unknown"
#endif


void print_usage();
void print_version();

int main(int argc, char* argv[]){
	const struct option long_opt [] = {
		{"help", no_argument, NULL, 1},
		{"version", no_argument, NULL, 'v'},
		{"usage", no_argument, NULL, 's'},
		{0, 0, 0, 0},
	};
	int c = 0; // getopt_long internal counter
	int opt_ind = 0; // option Index
	int error = 0;
	bool show_help = false;
	bool show_version = false;
	bool classic_read = false;
	while ((c = getopt_long(argc, argv, "vskc", long_opt, &opt_ind))!=-1){
		switch(c){
			case 1:
				show_help = true;
				break;
			case 'v':
				show_version = true;
				break;
			case 'c':
				classic_read = true;
				break;
			default:
				/* Params error */
				show_help = true;
				error = 1;
				break;
		}
	}
	if(show_version && error==0 ){
		print_version();
		return 0;
	}
	if(show_help){
		print_usage();
		return error;
	}

	if(classic_read){
		rdproc('c');
		return 0;
	}

	rdproc('d'); // Print default output

	return error;
}

void print_usage(){
	printf("Usage: Currently not abailable.\n");
}

void print_version(){
	printf("%s\n", VERSION);
}
