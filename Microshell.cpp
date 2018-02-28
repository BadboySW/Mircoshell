#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <strings.h>


using namespace std;

int main(void)
{
	
    const char pipes[4] = "||";
    string commandStr;
	char command[80];
	int count=0;
	int count2=0;
	bool bool_flag = false;
	pid_t pid_a;
	pid_t pid_b;
	int fd[2];
	pipe(fd);
	
	while (true){

	printf("480shell> ");

	cin.getline(command, 80);
	
	if (!strcmp(command, "quit") || !strcmp(command, "q"))
		exit(0);
	
	char *first_args[] = { (char*)0, (char*)0, (char*)0 };
	char *second_args[] = { (char*)0, (char*)0, (char*)0 };
	
	for (char *x = strtok(command, " "); x; x = strtok(NULL, " ")) {
		if(strcmp(x,pipes) && bool_flag == false){
			first_args[count++] = x;
		}
		else if(strcmp(x,pipes) && bool_flag == true){
			second_args[count2++] = x;
		}
		else 
		{
			bool_flag = true;
		}
		
	}
			
	first_args[count++] = NULL;
	second_args[count2++] = NULL;
   
	pid_a = fork();
	if (pid_a == 0) {
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);  
		execvp(first_args[0], first_args);
		return 1;
	}

	pid_b = fork();
	if (pid_b == 0) {
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		execvp(second_args[0], second_args);
		return 1;
	}
   
	close(fd[0]);
	close(fd[1]);
	wait(0);
	wait(0);			
		
	}
	
}
