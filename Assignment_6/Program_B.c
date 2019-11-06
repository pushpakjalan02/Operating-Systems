#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/times.h>
#include<sys/time.h>
#include<unistd.h>

int main(){
	int pid;
	clock_t before_clock, after_clock;
	struct timeval before_time, after_time;

	printf("I'm Inside Parent\n");
	before_clock = times(NULL);
	gettimeofday(&before_time, NULL);

	if((pid = fork()) == 0){
		printf("Now, I'm Inside Child\n");
		sleep(3);
		exit(0);
	}

	wait(NULL);
	after_clock = times(NULL);
	gettimeofday(&after_time, NULL);

	printf("Again I'm Inside Parent\n");
	printf("Clock Ticks before Submission: %ld\n", before_clock);
	printf("Clock Ticks after Termination: %ld\n", after_clock);
	printf("Time before Submission: %ld\n", before_time.tv_sec);
	printf("Time after Termination: %ld\n", after_time.tv_sec);
	exit(0);

}