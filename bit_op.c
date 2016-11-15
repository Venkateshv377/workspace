#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fs, fd, ret, count = 0;
	char data[4];

	fs = open("src.txt", O_RDONLY | 0666);
	if (fs == -1)
		perror("Error: In opening src.txt file");	
	fd = open("dst.txt", O_CREAT | O_WRONLY | 0444);
	if (fd == -1)
		perror("Error: In opening src.txt file");	

	while((ret = read(fs, data, 3)) > 0)
	{
		data[0] = (data[0] >> 2) << 2;
		data[1] = (data[0] << 6) | ((data[1] >> 2) << 2);
		data[2] = (data[1] << 4) | ((data[2] >> 6) << 2);
		data[3] = (data[2] << 2);
		write(fd, data, 4);
		count += 4;
	}
	printf("No.of bytes written: %d\n", count);
}
