#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void sys_err(const char * str){
	perror(str);
	exit(1);
}

int main(void){
	pid_t pid;
	char buf[1024];
	int fd[2];
	char *p = "test for pipe\n";
	if (pipe(fd) == -1)
		sys_err("pipe");

	pid = fork();
	if (pid < 0) {
		sys_err("fork err");
	} else if (pid != 0) {
		FILE * fp;
		fp = fopen("test.txt", "w");
		wait(NULL);
		close(fd[1]);
		int len = read(fd[0], buf, sizeof(buf));
		//write(STDOUT_FILENO, buf, len);
		fprintf(fp, "message is : %s", buf);
		close(fd[0]);
	} else {
		close(fd[0]);
		write(fd[1], p, strlen(p));
		dup2(fd[1], 1);
		printf("hahaha\n");
  		char * argv[] = {"ls", "-al", NULL};
		execv("/bin/ls", argv);
		close(fd[1]);
	}

	return 0;
}