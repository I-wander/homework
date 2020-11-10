#include<iostream>
#include<sys/types.h> 
#include<unistd.h>
int main()
{
	int pid;
	pid = fork();                            //创建第一个子进程
	if (pid < 0)
		printf ("failed\n") ;
	else if (pid == 0)
		printf( "This is child process B \n");
	else
		printf("This is father process A\n");

	if (pid > 0)                            //父进程才可以继续创建子进程
	{
		pid = fork();                       //创建第二个子进程，此时存在一个父进程和两个子进程
		if (pid < 0)
			printf("failed\n");
		else if (pid == 0)
			printf("This is child process C \n");
		else
			printf("This is father process A\n");
	}

	if (pid < 0)                            //验证此时存在一个父进程和两个子进程
		printf("failed\n");
	else if (pid == 0)
		printf("This is child process \n");
	else
		printf("This is father process \n");
	return 0;
}