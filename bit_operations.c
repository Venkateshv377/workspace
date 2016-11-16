/* Bit wise operations */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int count = 4, total_count = 0, fs, fd, ret;
	unsigned char buff[4];

	fs = open("src.txt", O_RDONLY | 0666);
	if (fs == -1)
		perror("Error: in src file\n");

	fd = open("dst.txt", O_CREAT || O_RDWR | 0666);
	if (fd == -1)
		perror("Error: in dst file\n");
	while(ret = read(fs, buff, count))
	{
		buff[0] = ((buff[0] >> 2) << 2) | (buff[1] >> 6);
		buff[1] = ((buff[1] >> 2) << 4) | (buff[2] >> 4);
		buff[2] = ((buff[2] >> 2) << 6) | (buff[3] >> 2);
		count--;
		total_count += count;
		ret = write(fd, buff, count);
		count++;
	}
	printf("No. of bytes written into the file: %d\n", count);
	printf("\n");
}
