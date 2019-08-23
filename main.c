#include<stdio.h>
#include<getopt.h>

#include"rdproc.h"

const volatile static char version[] = VERSION;

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
	while ((c = getopt_long(argc, argv, "vskc", long_opt, &opt_ind))!=-1){
		switch(c){
			case 1:
				print_usage();
				break;
			case 'v':
				print_version();
			default:
				rdproc(c);
		}

	}
	return 0;
}

void print_usage(){
	printf("Currently not abailable.\n");
}

void print_version(){
	printf("%s\n", VERSION);
}
