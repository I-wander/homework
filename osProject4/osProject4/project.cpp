#include<iostream>
#include<sys/types.h> 
#include<unistd.h>
int main()
{
	int pid;
	pid = fork();                            //������һ���ӽ���
	if (pid < 0)
		printf ("failed\n") ;
	else if (pid == 0)
		printf( "This is child process B \n");
	else
		printf("This is father process A\n");

	if (pid > 0)                            //�����̲ſ��Լ��������ӽ���
	{
		pid = fork();                       //�����ڶ����ӽ��̣���ʱ����һ�������̺������ӽ���
		if (pid < 0)
			printf("failed\n");
		else if (pid == 0)
			printf("This is child process C \n");
		else
			printf("This is father process A\n");
	}

	if (pid < 0)                            //��֤��ʱ����һ�������̺������ӽ���
		printf("failed\n");
	else if (pid == 0)
		printf("This is child process \n");
	else
		printf("This is father process \n");
	return 0;
}