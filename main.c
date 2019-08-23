#include<stdio.h>
#include<getopt.h>

#include"rdproc.h"

void print_help();

int main(int argc, char* argv[]){
	const struct option long_options [] = {
		{"help", no_argument, NULL, 'h'},
		{"version", no_argument, NULL, 'v'},
		{"error", no_argument, NULL, 'e'},
		{0, 0, 0, 0},
	};
	int c = 0;
	int option_index = 0;
	while (c!=-1){
		c = getopt_long(argc, argv, "kce", long_options, &option_index);
		switch(c){
			case 'h':
				print_help();
				break;
			default:
				rdproc(c);
		}

	}
	return 0;
}

void print_help(){
	printf("Currently not abailable.");
}
