#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SIZE 1024

void childe_do(int *fd)
{
	//关闭管道写端
	close(fd[1]);
	
	int fd1 = open("2.txt",O_WRONLY | O_CREAT,0777);
	if(fd1 < 0)
	{
		perror("open");
		close(fd[0]);
		return ;	
	}
	
	char buf[SIZE] = {0};
	int ret ;
	while(ret = read(fd[0],buf,SIZE))   //读取管道
	{
		if(ret == -1)
		{
			perror("read");
			break ;
		}
		
		write(fd1,buf,ret);      //写入文件
	}
	
	close(fd[0]);
	close(fd1);
}

void parent_do(int * fd)
{
	//关闭管道读端
	close(fd[0]);
	
	int fd1 = open("1.txt",O_RDONLY);
	if(fd1 < 0)
	{
		perror("open");
		close(fd[1]);
		return ;	
	}
	
	char buf[SIZE] = {0};
	int ret;
	while(ret = read(fd1,buf,SIZE))
	{
		if(ret == -1)
		{
			perror("read");
			break ;
		}
		
		write(fd[1],buf,ret);
	}
	
	close(fd[1]);
	close(fd1);
}

int main()
{
	int fd[2] = {0};
	
	//创建无名管道,成功返回0,错误返回-1
	int piep = pipe(fd);
	if(pipe < 0)
	{
		perror("pipe");
		return -1;
	}
	
	pid_t pid = fork();
	
	switch (pid)
	{
		case -1:
			perror("fork");
			break;
		case 0 :
			childe_do(fd);
			break;
		default :
			parent_do(fd);
			break;
	}
	
	
	return 0;
}
