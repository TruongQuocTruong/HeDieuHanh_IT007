#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>

void on_sigint(){
	printf("\nYou are pressed CRTL+C! Goodbye!\n");
	exit(0);
}
int main(){
	printf("Welcome to IT007, I am 19522446\n");
	
	pid_t pid;
	pid = fork();
	if(pid==0){
		
		system("gedit abcd.txt");
		
	}
	else{
	signal(SIGINT,on_sigint);
	wait(NULL);
	}
	return 0;
}
