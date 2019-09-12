#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<sys/types.h>

#include"rdproc.h"
#include"rdfile.h"
#include <unistd.h>


void rdproc(int c) {
	char buffer [500];
	switch(c){
		/* Classic rdproc exercise information */
		case 'd':
			printf( "Hostname: \n\t");
			sfileline("/proc/sys/kernel/hostname", 1,buffer,500);
			printf("%s", buffer);

			sfileline("/proc/driver/rtc", 1, buffer, 500);
			printf( "Date and time: \n\t");
			printf("%s", buffer);
			printf("\t");

			sfileline("/proc/driver/rtc", 2, buffer, 500);
			printf("%s", buffer);


			printf( "CPU info: \n\t");

			sfileline("/proc/cpuinfo", 5, buffer, 500);
			printf("%s", buffer);
			printf( "Kernel version: \n\t");

			sfileline("/proc/version", 1, buffer, 500);
			printf("%s", buffer);
			printf( "Uptime: \n\t");

			sfileline("/proc/uptime", 1, buffer, 500);
			printUptime(buffer);
			// TODO: ask if the list should be obtained by: ls /lib/modules/$(uname -r)/kernel/fs/*/*ko
			printf( "Supported filesystems: \n\t"); 
			printf("%d",get_lines_number("/proc/filesystems")); printf("\n");
			break;
	}
}

void printUptime(const char *const proc_slash_uptime) {
	char * copy = proc_slash_uptime;
	char * charSecondsSinceBoot = strtok(copy, " ");
	long sencodsSinceBoot = atol(charSecondsSinceBoot);

	long uptimeHours = sencodsSinceBoot / 3600;
	long uptimeSeconds = sencodsSinceBoot % 3600;
	long uptimeMinutes = uptimeSeconds / 60;
	uptimeSeconds %= 60;

	long daysSinceBoot = uptimeHours / 24; 
	printf("%ld dias %ld:%ld:%ld \n",daysSinceBoot,uptimeHours,uptimeMinutes,uptimeSeconds);
}

void print_step_b() {
	char cpu_usage_times[500];
	sfileline("/proc/stat",1, cpu_usage_times, 500);
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

	char file [10000];
	swholefile("/proc/stat",file,10000);
	char* ctxt_ocurrence = strstr(file,"ctxt");
	char* ctxt_number = strtok(ctxt_ocurrence," ");
	ctxt_number = strtok(NULL, " \n");
	printf("Context switches since boot: \n\t");
	printf("%s \n", ctxt_number);

	char file2 [10000];
	swholefile("/proc/stat",file2,10000);
	char* processes_ocurrence = strstr(file2,"processes");

	char* processes_number = strtok(processes_ocurrence," ");
	processes_number = strtok(NULL, " \n");
	printf("Created processes since boot: \n\t");
	printf("%s \n", processes_number);
}


void print_step_c() {
	// Disk requests
	int file_line_numbers = get_lines_number("/proc/diskstats");
	long total_reads = 0;
	for (int line_number = 1; line_number<=file_line_numbers; line_number++) {
		char file1[500];
		sfileline("/proc/diskstats",line_number,file1,500);
		char* ptr = strtok(file1, " ");
		int count = 0;
		while (ptr != NULL) {
			ptr = strtok(NULL," ");
			count++;
			if (count == 3) {
				total_reads+=atol(ptr);
			}
		}
	}
	printf("Peticiones a disco: \n\t%li\n", total_reads);
}
void print_step_d1(char* optarg) {
	char location[200];
	sprintf(location, "/proc/%s/fd", optarg);

	//execl("/usr/bin/ls", "ls", "-GAhNg", "--time-style=+", location, (char *)0);
	char output[500];
	sdirlist(location, output, 500);
	printf("%s",output);
}
void print_step_d2(char* optarg) {
	char location[200];
	sprintf(location, "/proc/%s/limits", optarg);

	char limits[200];
	sfileline(location, 9, limits, 200);
	printf("%s", limits);
}
void print_step_d3(char* optarg) {
	char location[200];
	sprintf(location, "/proc/%s/stack", optarg);

	char stack[200];
	sfileline(location, 1, stack, 200);
	printf("%s", stack);
}
