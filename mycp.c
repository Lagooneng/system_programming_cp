/* mycp program: copy a pile, by sys32204236 이름:  정현우 학번: 32204236, 작성일: 2021/10/10 nuna90@naver.com */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX_BUF 64

int main(int argc, char *argv[])
{
	int fd, fd1, read_size, write_size;
	char buf[MAX_BUF];
	struct stat st;

	if (argc != 3) 
	{
		printf("USAGE: %s source_file destination_file\n", argv[0]);
		exit(1);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Can not open %s. No such file\n", argv[1]);
		exit(1);
	}
	
	stat(argv[1], &st);
	
	fd1 = open(argv[2], O_RDWR | O_CREAT | O_EXCL, 0644);
	if (fd1 < 0)
	{
		printf("Can not create %s. May already exist\n", argv[2]);
		exit(1);
	}
	
	// copy
	chmod(argv[2], st.st_mode);
	while (1)
	{
		read_size = read(fd, buf, MAX_BUF);
		if (read_size == 0)
			break;
		write_size = write(fd1, buf, read_size);
	}
	// end copy
	
	close(fd);
	close(fd1);
	
	return 0;
}
