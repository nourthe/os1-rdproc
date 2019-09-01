#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include"rdproc.h"
#include"rdfile.h"


void rdproc(int c){
	switch(c){

		/* Classic rdproc exercise information */
		case 'd':
			printf( "Hostname: \n\t");
			printf("%s", rdfileline("/proc/sys/kernel/hostname", 1));
			printf( "Date and time: \n\t");
			printf("%s", rdfileline("/proc/driver/rtc", 1));
			printf("\t");
			printf("%s", rdfileline("/proc/driver/rtc", 2));
			printf( "CPU info: \n\t");
			printf("%s", rdfileline("/proc/cpuinfo", 5));
			printf( "Kernel version: \n\t");
			printf("%s", rdfileline("/proc/version", 1));
			printf( "Uptime: \n\t");
			printUptime(rdfileline("/proc/uptime", 1));
			break;

		/* print_file debug */
		case 'e':
			printf("%s", rdfileline("/proc/strangefilename", 0));
	}
}

void printUptime(char *const proc_slash_uptime) {
	char * charSecondsSinceBoot = strtok(proc_slash_uptime, " ");
	long sencodsSinceBoot = atol(charSecondsSinceBoot);

	long uptimeHours = sencodsSinceBoot / 3600;
	long uptimeSeconds = sencodsSinceBoot % 3600;
	long uptimeMinutes = uptimeSeconds / 60;
	uptimeSeconds %= 60;

	long daysSinceBoot = uptimeHours / 24; 
	printf("%ld dias %ld:%ld:%ld \n",daysSinceBoot,uptimeHours,uptimeMinutes,uptimeSeconds);	
}
