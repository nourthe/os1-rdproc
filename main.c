#include<stdio.h>
#include<stdbool.h>
#include<getopt.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

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
		{"classic", no_argument, NULL, 'c'},
		{0, 0, 0, 0},
	};
	int c = 0; // getopt_long internal counter
	int opt_ind = 0; // option Index
	int error = 0;
	bool show_help = false;
	bool show_version = false;
	bool classic_read = false;
	rdproc('d'); // Print default output
	while ((c = getopt_long(argc, argv, "vsc:l:p:f:t:", long_opt, &opt_ind))!=-1){
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
			case 's':
				print_step_b();
				break;
			case 'l':
				for (int i = 0; i< argc; i++) {
					if (strcmp(argv[i],"-l") != 0) continue;
					if (i+2 >= argc || argv[i+2][0] == '-') {
						printf("%s", "Falta segundo argumento. \n");
						break;
					} 
					else {
						int interval = atoi(argv[i+1]);
						int duration = atoi(argv[i+2]);
						for (int i = 0; i<duration/interval; i++) {
							if (i!=0) sleep(interval);
							print_step_c1();
							print_step_c2();
							print_step_c3();
						}
					}
				}
				break;
			case 'p':
				print_step_d1(optarg);
				break;
			case 'f':
				print_step_d2(optarg);
				break;
			case 't':
				print_step_d3(optarg);
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


	return error;
}

void print_usage(){
	printf("Usage: Currently not abailable.\n");
}

void print_version(){
	printf("%s\n", VERSION);
}
