#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include"rdproc.h"
#include"rdfile.h"
#include <unistd.h>


void rdproc(int c) {
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
			// TODO: ask if the list should be obtained by: ls /lib/modules/$(uname -r)/kernel/fs/*/*ko
			printf( "Supported filesystems: \n\t"); 
			printf("%d",get_lines_number("/proc/filesystems")); printf("\n");
			break;

		/* print_file debug */
		case 'e':
			printf("%s", rdfileline("/proc/strangefilename", 0));
			break;
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

void print_step_b() {
	char* cpu_usage_times = rdfileline("/proc/stat",1);
	char* token = strtok(cpu_usage_times," ");
	char cpu_user_time [15];
	char cpu_sys_time [15];
	char cpu_idle_time [15];

	int count = 0;
	while (token != NULL) {
		if (count == 1) strcpy(cpu_user_time,token);
		else if (count == 3) strcpy(cpu_sys_time,token);
		else if (count == 4) strcpy(cpu_idle_time,token);
		token = strtok (NULL, " ");
		count++;
	}
	printf("Cpu usage times: \n\t");
	
	long USER_HZ = sysconf(_SC_CLK_TCK);
	printf("User:\t%s [1/%li s]\n\tSystem:\t%s [1/%li s]\n\tIdle:\t%s [1/%li s] \n",
	 		cpu_user_time, USER_HZ,
	 		cpu_sys_time, USER_HZ,
	 		cpu_idle_time, USER_HZ);

	// -------- get context switches

	char* file = rdfilelines("/proc/stat",1,get_lines_number("/proc/stat"));
	char* ctxt_ocurrence = strstr(file,"ctxt");
	char* ctxt_number = strtok(ctxt_ocurrence," ");
	ctxt_number = strtok(NULL, " \n");
	printf("Context switches since boot: \n\t");
	printf("%s \n", ctxt_number);

	char* file2 = rdfilelines("/proc/stat",1,get_lines_number("/proc/stat"));
	char* processes_ocurrence = strstr(file2,"processes");

	char* processes_number = strtok(processes_ocurrence," ");
	processes_number = strtok(NULL, " \n");
	printf("Created processes since boot: \n\t");
	printf("%s \n", processes_number);
}

