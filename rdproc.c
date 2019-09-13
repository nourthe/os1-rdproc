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

void printUptime(char * proc_slash_uptime) {
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

void print_step_c(int argc, char** argv) {
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
}

void print_step_c1() {
	// Disk requests
	char buffer[15000];
	sfileline("/proc/diskstats",10,buffer,15000);
	long sectors_read = -1;
	sscanf(buffer, "%*d %*d sda %ld", &sectors_read);
	printf("Peticiones a disco: %ld \n", sectors_read);
}
void print_step_c2() {
	// Hardware configurated memory
	long available = -1, total = -1;
	// Available Memory:
	char buffer[1500];
	sfileline("/proc/meminfo",3,buffer,1500);
	sscanf(buffer,"MemAvailable: %ld", &available);

	// Available Memory:
	sfileline("/proc/meminfo",1,buffer,1500);
	sscanf(buffer,"MemTotal: %ld", &total);

	printf("Memoria disponible / total: %ld / %ld \n", available, total);
}
void print_step_c3() {
	// Load Average
	char buffer[1500];
	float load = -1.0;
	sfileline("/proc/loadavg",1,buffer,1500);

	load = atof(strtok(buffer, " "));
	printf("Promedio de carga en el último minuto: %.2f \n", load);
}
void print_step_d1(char* optarg) {
	char location[200];
	sprintf(location, "/proc/%s/fd", optarg);

	//execl("/usr/bin/ls", "ls", "-GAhNg", "--time-style=+", location, (char *)0);
	char output[50000];
	sdirlist(location, output, 50000);
	printf("%s",output);
}
void print_step_d2(char* optarg) {
	char location[20000];
	sprintf(location, "/proc/%s/limits", optarg);

	char limits[20000];
	sfileline(location, 9, limits, 20000);
	printf("%s", limits);
}
void print_step_d3(char* optarg) {
	char location[20000];
	sprintf(location, "/proc/%s/stack", optarg);

	char stack[20000];
	sfileline(location, 1, stack, 20000);
	printf("%s", stack);
}
